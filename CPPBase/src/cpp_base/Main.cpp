/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"
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
	{
		tml::DefaultMemoryUtilEngine engine;

		if (engine.Create(tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC, 1024U) < 0) {
			int a = 0;
		} else {
			tml::MemoryUtilEngine *p1 = engine.Get<tml::DefaultMemoryUtilEngine>(5U);
			tml::MemoryUtilEngine *p2 = engine.Get<tml::DefaultMemoryUtilEngine>(10U);

			auto allocator_type = engine.GetAllocatorType();
			auto allocator_info = engine.GetAllocatorInfo();

			engine.Release(&p1);
			engine.Release(&p2);
		}

		int a = 0;
	}

	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
