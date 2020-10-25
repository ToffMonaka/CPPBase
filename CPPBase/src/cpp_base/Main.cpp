/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"
#include "../lib/tml/memory/MemoryUtil.h"
#include "../lib/tml/memory/DefaultMemoryUtilEngine.h"


/**
 * @brief wWinMain関数
 *
 * 最初に呼ばれる関数
 *
 * @param instance_handle (instance_handle)
 * @param prev_instance_handle (prev_instance_handle)
 * @param cmd_line_str (command_line_string)
 * @param wnd_show_type (window_show_type)
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
INT APIENTRY wWinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE prev_instance_handle, _In_ WCHAR *cmd_line_str, _In_ INT wnd_show_type)
{
	return (cpp_base::CreateMain(instance_handle, prev_instance_handle, cmd_line_str, wnd_show_type));
}


/**
 * @brief InitMain関数
 */
void cpp_base::InitMain(void)
{
	tml::MemoryUtil::Init();

	return;
}


/**
 * @brief CreateMain関数
 * @param instance_handle (instance_handle)
 * @param prev_instance_handle (prev_instance_handle)
 * @param cmd_line_str (command_line_string)
 * @param wnd_show_type (window_show_type)
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
INT cpp_base::CreateMain(HINSTANCE instance_handle, HINSTANCE prev_instance_handle, WCHAR *cmd_line_str, INT wnd_show_type)
{
	{// MemoryUtil Create
		std::unique_ptr<tml::MemoryUtilEngine> engine(new tml::DefaultMemoryUtilEngine());

		if (dynamic_cast<tml::DefaultMemoryUtilEngine *>(engine.get())->Create(tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC, 1048576U) < 0) {
			cpp_base::InitMain();

			return (0);
		}

		if (tml::MemoryUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (0);
		}
	}

	{// Test
		auto allocator_info = tml::MemoryUtil::GetAllocatorInfo();

		int a = 0;
	}

	MSG msg = {};

	cpp_base::InitMain();

	return (static_cast<INT>(msg.wParam));
}
