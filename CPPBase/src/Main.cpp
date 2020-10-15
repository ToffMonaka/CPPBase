/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"
#include "lib/tml/memory/NewAllocator.h"
#include "lib/tml/memory/MallocAllocator.h"
#include "lib/tml/memory/DlmallocAllocator.h"


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
	{
		tml::DlmallocAllocator allocator;

		allocator.Create(1024U);

		auto p = allocator.Get<tml::Allocator::INFO>(1U);

		allocator.Release<tml::Allocator::INFO>(&p);

		int a = 0;
	}

	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
