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
 * @param instance_handle …インスタンスハンドル
 * @param prev_instance_handle …前のインスタンスハンドル
 * @param cmd_line_str …コマンドライン文字列
 * @param wnd_show_type …ウィンドウ表示タイプ
 * @return exit_code …終了コード
 */
int APIENTRY wWinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE prev_instance_handle, _In_ LPWSTR cmd_line_str, _In_ int wnd_show_type)
{
	MSG msg = {};

	return ((int)msg.wParam);
}
