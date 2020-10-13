/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"
#include "lib/tml/memory/MemoryUtil.h"
#include "lib/tml/memory/DefaultMemoryUtilEngine.h"
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
		tml::NewAllocator allocator;

		allocator.Create();

		auto p = allocator.Get<tml::Allocator::INFO>(1U);

		allocator.Release<tml::Allocator::INFO>(&p);

		tml::DefaultMemoryUtilEngine engine;

		if (engine.Create() < 0) {
			int a = 0;
		}

		if (tml::MemoryUtil::Create() < 0) {
			int a = 0;
		}

		tml::MemoryUtil::Init();
	}

	int a = 0;

	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
