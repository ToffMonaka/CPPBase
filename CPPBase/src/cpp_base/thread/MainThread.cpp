/**
 * @file
 * @brief MainThreadコードファイル
 */


#include "MainThread.h"
#include "../../lib/tml/memory/MemoryUtil.h"
#include "../../lib/tml/string/StringUtil.h"
#include "../../lib/tml/time/TimeUtil.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/random/RandomUtil.h"
#include "../../lib/tml/file/FileUtil.h"
#include "../../lib/tml/thread/ThreadUtil.h"
#include "../constant/ConstantUtil_WINDOW.h"
#include "../constant/ConstantUtil_FILE.h"
#include "../resource/resource.h"
#include "../thread/TestThread.h"


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
	tml::MainThread::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::MainThread::Init(void)
{
	this->Release();

	this->frame_rate_.Init();
	this->sys_conf_file_.Init();
	this->input_mgr_.Init();
	this->graphic_mgr_.Init();
	this->sound_mgr_.Init();

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
		this->sys_conf_file_.read_plan.file_path = cpp_base::ConstantUtil::FILE::SYSTEM_CONFIG_FILE_PATH;

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
	{// Window Create
		WNDCLASSEX wnd_class = {};

		wnd_class.cbSize = sizeof(wnd_class);
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.lpfnWndProc = cpp_base::MainThread::WindowProcedure;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		wnd_class.hInstance = this->GetInstanceHandle();
		wnd_class.hIcon = LoadIcon(this->GetInstanceHandle(), MAKEINTRESOURCE(IDI_APPLICATION_ICON1));
		wnd_class.hCursor = LoadCursor(this->GetInstanceHandle(), IDC_ARROW);
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wnd_class.lpszMenuName = nullptr;
		wnd_class.lpszClassName = cpp_base::ConstantUtil::WINDOW::CLASS_NAME;
		wnd_class.hIconSm = nullptr;

		if (this->CreateWindow_(
			wnd_class,
			this->sys_conf_file_.data.window_x, this->sys_conf_file_.data.window_y, this->sys_conf_file_.data.window_width, this->sys_conf_file_.data.window_height
		) < 0) {
			return (-1);
		}
	}

	// InputManager Create
	if (this->input_mgr_.Create() < 0) {
		this->Init();

		return (-1);
	}

	// GraphicManager Create
	if (this->graphic_mgr_.Create(this->GetWindowHandle(), this->sys_conf_file_.data.window_width, this->sys_conf_file_.data.window_height) < 0) {
		this->Init();

		return (-1);
	}

	// SoundManager Create
	if (this->sound_mgr_.Create() < 0) {
		this->Init();

		return (-1);
	}

	{// Test
		{// TestThread Start
			std::unique_ptr<tml::SubThread> th = std::make_unique<cpp_base::TestThread>();

			if (dynamic_cast<cpp_base::TestThread *>(th.get())->Create() < 0) {
				return (-1);
			}

			if (tml::ThreadUtil::Start(th) < 0) {
				return (-1);
			}
		}

		int a = 0;
	}

	this->frame_rate_.Start(60U);

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
	this->frame_rate_.Update();

	return;
}


/**
 * @brief WindowProcedure関数
 * @param wnd_handle (window_handle)
 * @param msg_type (message_type)
 * @param msg_param1 (message_parameter1)
 * @param msg_param2 (message_parameter2)
 * @return res (result)<br>
 * 0未満=失敗
 */
LRESULT CALLBACK cpp_base::MainThread::WindowProcedure(HWND wnd_handle, UINT msg_type, WPARAM msg_param1, LPARAM msg_param2)
{
	switch (msg_type) {
	case WM_DESTROY: {
		PostQuitMessage(0);

		return (0);
	}
	}

	return (DefWindowProc(wnd_handle, msg_type, msg_param1, msg_param2));
}
