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
 * @param instance_handle �c�C���X�^���X�n���h��
 * @param prev_instance_handle �c�O�̃C���X�^���X�n���h��
 * @param cmd_line_str �c�R�}���h���C��������
 * @param wnd_show_type �c�E�B���h�E�\���^�C�v
 * @return exit_code �c�I���R�[�h
 */
int APIENTRY wWinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE prev_instance_handle, _In_ LPWSTR cmd_line_str, _In_ int wnd_show_type)
{
	MSG msg = {};

	return ((int)msg.wParam);
}
