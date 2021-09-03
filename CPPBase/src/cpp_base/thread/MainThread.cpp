/**
 * @file
 * @brief MainThreadコードファイル
 */


#include "MainThread.h"
#include <windowsx.h>
#include "../../lib/tml/memory/MemoryUtil.h"
#include "../../lib/tml/string/StringUtil.h"
#include "../../lib/tml/time/TimeUtil.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/random/RandomUtil.h"
#include "../../lib/tml/file/FileUtil.h"
#include "../../lib/tml/thread/ThreadUtil.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../constant/ConstantUtil_WINDOW.h"
#include "../resource/resource.h"
#include "../thread/TestThread.h"
#include "../scene/InitScene.h"


/**
 * @brief コンストラクタ
 */
cpp_base::MainThread::MainThread()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::MainThread::~MainThread()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::MainThread::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::MainThread::Init(void)
{
	this->Release();

	this->sys_conf_file_.Init();

	tml::MainThread::Init();

	return;
}


/**
 * @brief Create関数
 * @param instance_handle (instance_handle)
 * @param wnd_name (window_name)
 * @param wnd_show_type (window_show_type)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainThread::Create(const HINSTANCE instance_handle, const WCHAR *wnd_name, const INT wnd_show_type)
{
	this->Init();

	if (tml::MainThread::Create(instance_handle, wnd_name, wnd_show_type) < 0) {
		this->Init();

		return (-1);
	}

	{// SystemConfigFile Read
		this->sys_conf_file_.read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::SYSTEM_CONFIG;

		if (this->sys_conf_file_.Read() < 0) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainThread::OnStart(void)
{
	{// COM Create
		if (this->CreateCOM() < 0) {
			return (-1);
		}
	}

	{// Window Create
		WNDCLASSEX wnd_class = {};

		wnd_class.cbSize = sizeof(wnd_class);
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.lpfnWndProc = cpp_base::MainThread::WindowProcedure;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		wnd_class.hInstance = this->GetInstanceHandle();
		wnd_class.hIcon = LoadIcon(this->GetInstanceHandle(), MAKEINTRESOURCE(IDI_APPLICATION_ICON));
		wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wnd_class.lpszMenuName = nullptr;
		wnd_class.lpszClassName = cpp_base::ConstantUtil::WINDOW::CLASS_NAME;
		wnd_class.hIconSm = nullptr;

		if (this->CreateWindow_(wnd_class, this->sys_conf_file_.data.window_position, this->sys_conf_file_.data.window_size) < 0) {
			return (-1);
		}
	}

	{// ManagerFactory Create
		cpp_base::ManagerFactoryDesc desc;

		if (this->mgr_factory_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// InputManager Create
		cpp_base::input::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.factory = &this->mgr_factory_;

		if (this->input_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// GraphicManager Create
		cpp_base::graphic::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.factory = &this->mgr_factory_;
		desc.size = this->sys_conf_file_.data.window_size;
		desc.vsync_flag = this->sys_conf_file_.data.graphic_vsync_flag;
		desc.frame_rate_limit = this->sys_conf_file_.data.graphic_frame_rate_limit;

		if (this->graphic_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// SoundManager Create
		cpp_base::sound::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.factory = &this->mgr_factory_;
		desc.SetVolume(tml::ConstantUtil::SOUND::SOUND_TYPE::BGM, this->sys_conf_file_.data.sound_bgm_volume);
		desc.SetMuteFlag(tml::ConstantUtil::SOUND::SOUND_TYPE::BGM, this->sys_conf_file_.data.sound_bgm_mute_flag);
		desc.SetVolume(tml::ConstantUtil::SOUND::SOUND_TYPE::SE, this->sys_conf_file_.data.sound_se_volume);
		desc.SetMuteFlag(tml::ConstantUtil::SOUND::SOUND_TYPE::SE, this->sys_conf_file_.data.sound_se_mute_flag);

		if (this->sound_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// SceneManager Create
		cpp_base::scene::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.factory = &this->mgr_factory_;
		desc.SetInputManager(&this->input_mgr_);
		desc.SetGraphicManager(&this->graphic_mgr_);
		desc.SetSoundManager(&this->sound_mgr_);

		if (this->scene_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// InitScene Start
		tml::shared_ptr<tml::scene::Scene> scene;

		if (this->scene_mgr_.GetScene(scene, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::INIT_SCENE_PREFAB)) == nullptr) {
			if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
				OutputDebugString(L"Error: InitScene Create\n");
			}

			return (-1);
		}

		if (this->scene_mgr_.StartScene(scene) < 0) {
			if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
				OutputDebugString(L"Error: InitScene Start\n");
			}

			return (-1);
		}
	}

	{// TestThread Start
		std::unique_ptr<tml::SubThread> th = std::make_unique<cpp_base::TestThread>();

		if (reinterpret_cast<cpp_base::TestThread *>(th.get())->Create() < 0) {
			if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
				OutputDebugString(L"Error: TestThread Create\n");
			}

			return (-1);
		}

		if (tml::ThreadUtil::Start(th) < 0) {
			if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
				OutputDebugString(L"Error: TestThread Start\n");
			}

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::MainThread::OnEnd(void)
{
	this->scene_mgr_.Init();
	this->sound_mgr_.Init();
	this->graphic_mgr_.Init();
	this->input_mgr_.Init();
	this->mgr_factory_.Init();

	this->DeleteWindow_();

	this->DeleteCOM();

	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::MainThread::OnUpdate(void)
{
	this->scene_mgr_.Update();

	if (this->scene_mgr_.GetScene() == nullptr) {
		this->SetStartFlag(false);
	}

	return;
}


/**
 * @brief WindowProcedure関数
 * @param wnd_handle (window_handle)
 * @param msg_type (message_type)
 * @param msg_wp (message_wparameter)
 * @param msg_lp (message_lparameter)
 * @return result (result)<br>
 * 0未満=失敗
 */
LRESULT CALLBACK cpp_base::MainThread::WindowProcedure(HWND wnd_handle, UINT msg_type, WPARAM msg_wp, LPARAM msg_lp)
{
	static cpp_base::MainThread *th = nullptr;

	if (th == nullptr) {
		th = dynamic_cast<cpp_base::MainThread *>(tml::ThreadUtil::Get());
	}

	switch (msg_type) {
	case WM_CREATE: {
		std::array<RAWINPUTDEVICE, 2U> rid_ary;

		// MouseDevice Set
		rid_ary[0].usUsagePage = 0x01;
		rid_ary[0].usUsage = 0x02;
		rid_ary[0].dwFlags = 0UL;
		rid_ary[0].hwndTarget = wnd_handle;
 
		// KeyboardDevice Set
		rid_ary[1].usUsagePage = 0x01;
		rid_ary[1].usUsage = 0x06;
		rid_ary[1].dwFlags = 0UL;
		rid_ary[1].hwndTarget = wnd_handle;
 
		RegisterRawInputDevices(rid_ary.data(), rid_ary.size(), sizeof(RAWINPUTDEVICE));

		return (0);
	}
	case WM_DESTROY: {
		PostQuitMessage(0);

		return (0);
	}
	case WM_SETFOCUS: {
		return (0);
	}
	case WM_KILLFOCUS: {
		th->GetInputManager().ClearMouseDeviceCodeState();
		th->GetInputManager().ClearKeyboardDeviceCodeState();

		return (0);
	}
	case WM_INPUT: {
		RAWINPUT ri;
		UINT ri_size = 0U;

		GetRawInputData(reinterpret_cast<HRAWINPUT>(msg_lp), RID_INPUT, nullptr, &ri_size, sizeof(RAWINPUTHEADER));

		if ((ri_size <= 0U) || (ri_size > sizeof(RAWINPUT))) {
			return (0);
		}

		if (GetRawInputData(reinterpret_cast<HRAWINPUT>(msg_lp), RID_INPUT, &ri, &ri_size, sizeof(RAWINPUTHEADER)) != ri_size) {
			return (0);
		}

		switch (ri.header.dwType) {
		case RIM_TYPEMOUSE: {
			th->GetInputManager().AddMouseDeviceRawInput(ri.data.mouse, th->GetInputManager().GetMouseDevicePosition());

			break;
		}
		case RIM_TYPEKEYBOARD: {
			th->GetInputManager().AddKeyboardDeviceRawInput(ri.data.keyboard);

			break;
		}
		}

		return (0);
	}
	case WM_MOUSEMOVE: {
		th->GetInputManager().SetMouseDevicePosition(tml::XMINT2EX(GET_X_LPARAM(msg_lp), GET_Y_LPARAM(msg_lp)));

		return (0);
	}
	}

	return (DefWindowProc(wnd_handle, msg_type, msg_wp, msg_lp));
}


#if 0
#endif
