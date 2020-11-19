/**
 * @file
 * @brief DefaultStringUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultStringUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultStringUtilEngine::DefaultStringUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultStringUtilEngine::~DefaultStringUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::DefaultStringUtilEngine::Release(void)
{
	tml::StringUtilEngine::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultStringUtilEngine::Init(void)
{
	this->Release();

	tml::StringUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param local_name (local_name)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultStringUtilEngine::Create(const CHAR *local_name)
{
	this->Release();

	if (tml::StringUtilEngine::Create(local_name) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
