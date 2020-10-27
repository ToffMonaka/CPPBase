/**
 * @file
 * @brief DefaultProcessUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultProcessUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultProcessUtilEngine::DefaultProcessUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultProcessUtilEngine::~DefaultProcessUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::DefaultProcessUtilEngine::Release(void)
{
	tml::ProcessUtilEngine::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultProcessUtilEngine::Init(void)
{
	this->Release();

	tml::ProcessUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultProcessUtilEngine::Create(void)
{
	this->Release();

	if (tml::ProcessUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
