/**
 * @file
 * @brief Main�R�[�h�t�@�C��
 */


#include "Main.h"


/**
 * @brief wWinMain�֐�
 *
 * �ŏ��ɌĂ΂��֐�
 *
 * @param instance_handle : instance_handle
 * @param prev_instance_handle : prev_instance_handle
 * @param cmd_line_str : command_line_string
 * @param wnd_show_type : window_show_type
 * @return exit_code : exit_code<br>0�ȊO=���s
 */
INT APIENTRY wWinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE prev_instance_handle, _In_ WCHAR *cmd_line_str, _In_ INT wnd_show_type)
{
	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
