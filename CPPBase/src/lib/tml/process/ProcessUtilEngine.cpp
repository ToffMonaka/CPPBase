/**
 * @file
 * @brief ProcessUtilEngine�R�[�h�t�@�C��
 */


#include "ProcessUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ProcessUtilEngine::ProcessUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ProcessUtilEngine::~ProcessUtilEngine()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::ProcessUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ProcessUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ProcessUtilEngine::Create(void)
{
	return (0);
}


/**
 * @brief Start�֐�
 * @param proc (process)
 * @return res (result)<br>
 * 0����=���s,-2=���d�N��
 */
INT tml::ProcessUtilEngine::Start(std::unique_ptr<tml::Process> &proc)
{
	return (0);
}


/**
 * @brief End�֐�
 */
void tml::ProcessUtilEngine::End(void)
{
	return;
}


/**
 * @brief GetExitCode�֐�
 * @return exit_code (exit_code)<br>
 * 0�ȊO=���s
 */
INT tml::ProcessUtilEngine::GetExitCode(void)
{
	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
