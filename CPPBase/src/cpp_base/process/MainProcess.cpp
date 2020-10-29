/**
 * @file
 * @brief MainProcess�R�[�h�t�@�C��
 */


#include "MainProcess.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::MainProcess::MainProcess()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::MainProcess::~MainProcess()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::MainProcess::Release(void)
{
	tml::Process::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::MainProcess::Init(void)
{
	this->Release();

	tml::Process::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::MainProcess::Create(void)
{
	this->Release();

	if (tml::Process::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
