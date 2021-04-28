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
#include "../../lib/tml/input/Manager.h"
#include "../../lib/tml/input/MouseEvent.h"
#include "../../lib/tml/input/KeyboardEvent.h"
#include "../constant/ConstantUtil_FILE.h"
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
	this->scene_mgr_.Init();
	this->sound_mgr_.Init();
	this->graphic_mgr_.Init();
	this->input_mgr_.Init();

	this->DeleteWindow_();
	this->DeleteCOM();

	tml::MainThread::Release();

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
 * @return res (result)<br>
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
		this->sys_conf_file_.read_desc.data.file_path = cpp_base::ConstantUtil::FILE::SYSTEM_CONFIG_FILE_PATH;

		if (this->sys_conf_file_.Read() < 0) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainThread::Start(void)
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
		wnd_class.hIcon = LoadIcon(this->GetInstanceHandle(), MAKEINTRESOURCE(IDI_APPLICATION_ICON1));
		wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wnd_class.lpszMenuName = nullptr;
		wnd_class.lpszClassName = cpp_base::ConstantUtil::WINDOW::CLASS_NAME;
		wnd_class.hIconSm = nullptr;

		if (this->CreateWindow_(wnd_class, this->sys_conf_file_.data.window_position, this->sys_conf_file_.data.window_size) < 0) {
			return (-1);
		}
	}

	{// InputManager Create
		tml::input::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();

		if (this->input_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// GraphicManager Create
		tml::graphic::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.size = this->sys_conf_file_.data.window_size;
		desc.vsync_flag = this->sys_conf_file_.data.graphic_vsync_flag;
		desc.frame_rate_limit = this->sys_conf_file_.data.graphic_frame_rate_limit;

		if (this->graphic_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// SoundManager Create
		tml::sound::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.SetVolume(tml::ConstantUtil::SOUND::SOUND_TYPE::BGM, this->sys_conf_file_.data.sound_bgm_volume);
		desc.SetMuteFlag(tml::ConstantUtil::SOUND::SOUND_TYPE::BGM, this->sys_conf_file_.data.sound_bgm_mute_flag);
		desc.SetVolume(tml::ConstantUtil::SOUND::SOUND_TYPE::SE, this->sys_conf_file_.data.sound_se_volume);
		desc.SetMuteFlag(tml::ConstantUtil::SOUND::SOUND_TYPE::SE, this->sys_conf_file_.data.sound_se_mute_flag);

		if (this->sound_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// SceneManager Create
		tml::scene::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.resource_count_container[static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::SCENE)] = cpp_base::ConstantUtil::SCENE::SCENE_TYPE_COUNT;
		desc.input_manager = &this->input_mgr_;
		desc.graphic_manager = &this->graphic_mgr_;
		desc.sound_manager = &this->sound_mgr_;

		if (this->scene_mgr_.Create(desc) < 0) {
			return (-1);
		}
	}

	{// InitScene Start
		tml::shared_ptr<tml::scene::Scene> scene;

		cpp_base::scene::InitSceneDesc desc;

		desc.manager = &this->scene_mgr_;

		this->scene_mgr_.GetResource<cpp_base::scene::InitScene>(scene, desc);

		if (scene == nullptr) {
			return (-1);
		}

		if (this->scene_mgr_.Start(scene) < 0) {
			return (-1);
		}

		this->scene_mgr_.ReleaseResource(scene);
	}

	{// TestThread Start
		std::unique_ptr<tml::SubThread> th = std::make_unique<cpp_base::TestThread>();

		if (dynamic_cast<cpp_base::TestThread *>(th.get())->Create() < 0) {
			return (-1);
		}

		if (tml::ThreadUtil::Start(th) < 0) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::MainThread::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::MainThread::Update(void)
{
	this->scene_mgr_.Update();

	if (this->scene_mgr_.Get() == nullptr) {
		this->SetLoopFlag(false);
	}

	return;
}


/**
 * @brief WindowProcedure関数
 * @param wnd_handle (window_handle)
 * @param msg_type (message_type)
 * @param msg_wp (message_wparameter)
 * @param msg_lp (message_lparameter)
 * @return res (result)<br>
 * 0未満=失敗
 */
LRESULT CALLBACK cpp_base::MainThread::WindowProcedure(HWND wnd_handle, UINT msg_type, WPARAM msg_wp, LPARAM msg_lp)
{
	static cpp_base::MainThread *th = nullptr;

	if (th == nullptr) {
		th = reinterpret_cast<cpp_base::MainThread *>(tml::ThreadUtil::Get());
	}

	switch (msg_type) {
	case WM_CREATE: {
		std::array<RAWINPUTDEVICE, 2U> rid_ary;

		// Mouse Set
		rid_ary[0].usUsagePage = 0x01;
		rid_ary[0].usUsage = 0x02;
		rid_ary[0].dwFlags = 0UL;
		rid_ary[0].hwndTarget = wnd_handle;
 
		// Keyboard Set
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
		th->GetInputManager().SetMouseCodeState(false);
		th->GetInputManager().SetKeyboardCodeState(false);

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
			tml::input::MouseEventDesc event_desc;

			event_desc.manager = &th->GetInputManager();
			event_desc.data.SetRawInput(ri.data.mouse, th->GetInputManager().GetMousePosition());

			th->GetInputManager().AddEvent<tml::input::MouseEvent>(event_desc);

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::LEFT, true);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::LEFT_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::LEFT, false);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::RIGHT_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::RIGHT, true);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::RIGHT_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::RIGHT, false);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::MIDDLE_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::MIDDLE, true);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::MIDDLE_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::MIDDLE, false);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE1_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE1, true);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE1_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE1, false);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE2_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE2, true);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE2_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE2, false);
			}

			break;
		}
		case RIM_TYPEKEYBOARD: {
			tml::input::KeyboardEventDesc event_desc;

			event_desc.manager = &th->GetInputManager();
			event_desc.data.SetRawInput(ri.data.keyboard);

			th->GetInputManager().AddEvent<tml::input::KeyboardEvent>(event_desc);

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::BUTTON_DOWN)) {
				th->GetInputManager().SetKeyboardCodeState(event_desc.data.code, true);
			}

			if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::BUTTON_UP)) {
				th->GetInputManager().SetKeyboardCodeState(event_desc.data.code, false);
			}

			break;
		}
		}

		return (0);
	}
	case WM_MOUSEMOVE: {
		th->GetInputManager().SetMousePosition(tml::XMINT2EX(GET_X_LPARAM(msg_lp), GET_Y_LPARAM(msg_lp)));

		return (0);
	}
	}

	return (DefWindowProc(wnd_handle, msg_type, msg_wp, msg_lp));
}
