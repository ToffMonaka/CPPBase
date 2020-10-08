/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"


/**
 * @brief wWinMain関数
 *
 * 最初に呼ばれる関数
 *
 * @param instance_handle …
 * @param prev_instance_handle …
 * @param cmd_line_str …
 * @param wnd_show_type …
 * @return exit_code …
 */
int APIENTRY wWinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE prev_instance_handle, _In_ LPWSTR cmd_line_str, _In_ int wnd_show_type)
{
	MSG msg = {};

	return ((int)msg.wParam);
}
