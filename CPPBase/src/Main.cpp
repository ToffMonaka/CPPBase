/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"
#include "lib/tml/MemoryUtil.h"


/**
 * @brief wWinMain関数
 *
 * 最初に呼ばれる関数
 *
 * @param instance_handle : 
 * @param prev_instance_handle : 
 * @param cmd_line_str : 
 * @param wnd_show_type : 
 * @return exit_code : 
 */
INT APIENTRY wWinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE prev_instance_handle, _In_ WCHAR *cmd_line_str, _In_ INT wnd_show_type)
{
	MSG msg = {};

	return ((INT)msg.wParam);
}
