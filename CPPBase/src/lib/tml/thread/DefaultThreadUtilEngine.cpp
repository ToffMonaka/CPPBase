/**
 * @file
 * @brief DefaultThreadUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultThreadUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultThreadUtilEngine::DefaultThreadUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultThreadUtilEngine::~DefaultThreadUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::DefaultThreadUtilEngine::Release(void)
{
	tml::ThreadUtilEngine::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultThreadUtilEngine::Init(void)
{
	this->Release();

	tml::ThreadUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultThreadUtilEngine::Create(void)
{
	this->Release();

	if (tml::ThreadUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
