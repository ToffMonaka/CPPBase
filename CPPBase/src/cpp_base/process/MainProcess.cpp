/**
 * @file
 * @brief MainProcessコードファイル
 */


#include "MainProcess.h"
#include "../../lib/tml/memory/MemoryUtil.h"
#include "../../lib/tml/string/StringUtil.h"
#include "../../lib/tml/time/TimeUtil.h"
#include "../../lib/tml/time/Clock.h"
#include "../../lib/tml/time/Date.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/random/RandomUtil.h"
#include "../../lib/tml/file/FileUtil.h"
#include "../../lib/tml/file/BinaryFile.h"
#include "../../lib/tml/file/TextFile.h"
#include "../../lib/tml/process/ProcessUtil.h"
#include "../../lib/tml/thread/ThreadUtil.h"
#include "../constant/ConstantUtil_WINDOW.h"
#include "../thread/MainThread.h"
#include "../resource/resource.h"


/**
 * @brief コンストラクタ
 */
cpp_base::MainProcess::MainProcess()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::MainProcess::~MainProcess()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::MainProcess::Release(void)
{
	tml::Process::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::MainProcess::Init(void)
{
	this->Release();

	this->frame_rate_.Init();

	tml::Process::Init();

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
INT cpp_base::MainProcess::Create(const HINSTANCE instance_handle, const WCHAR *wnd_name, const INT wnd_show_type)
{
	this->Release();

	if (tml::Process::Create(instance_handle, wnd_name, wnd_show_type) < 0) {
		this->Init();

		return (-1);
	}

	this->frame_rate_.Init();

	return (0);
}

/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainProcess::Start(void)
{
	{// MainThread Start
		std::unique_ptr<tml::Thread> th = std::make_unique<cpp_base::MainThread>();

		if (dynamic_cast<cpp_base::MainThread *>(th.get())->Create() < 0) {
			return (-1);
		}

		if (tml::ThreadUtil::Start(th, true) < 0) {
			return (-1);
		}
	}

	{// Window Create
		WNDCLASSEX wnd_class = {};

		wnd_class.cbSize = sizeof(wnd_class);
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.lpfnWndProc = cpp_base::MainProcess::WindowProcedure;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		wnd_class.hInstance = this->GetInstanceHandle();
		wnd_class.hIcon = LoadIcon(this->GetInstanceHandle(), MAKEINTRESOURCE(IDI_APPLICATION_ICON1));
		wnd_class.hCursor = LoadCursor(this->GetInstanceHandle(), IDC_ARROW);
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wnd_class.lpszMenuName = nullptr;
		wnd_class.lpszClassName = cpp_base::ConstantUtil::WINDOW::CLASS_NAME;
		wnd_class.hIconSm = nullptr;

		if (this->CreateWindow_(wnd_class) < 0) {
			return (-1);
		}
	}

	{// Test
		tml::TextFile txt_file;

		txt_file.read_plan.file_path = L"test1.txt";

		txt_file.Read();

		auto &str_cont = txt_file.data.string_container;

		/*
		txt_file.write_plan.file_path = L"test2.txt";

		txt_file.Write();
		*/

		int a = 0;
	}

	this->frame_rate_.Start(60U);

	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::MainProcess::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::MainProcess::Update(void)
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
LRESULT CALLBACK cpp_base::MainProcess::WindowProcedure(HWND wnd_handle, UINT msg_type, WPARAM msg_param1, LPARAM msg_param2)
{
	switch (msg_type) {
	case WM_DESTROY: {
		PostQuitMessage(0);

		return (0);
	}
	}

	return (DefWindowProc(wnd_handle, msg_type, msg_param1, msg_param2));
}
