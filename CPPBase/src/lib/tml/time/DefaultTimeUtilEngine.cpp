/**
 * @file
 * @brief DefaultTimeUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultTimeUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultTimeUtilEngine::DefaultTimeUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultTimeUtilEngine::~DefaultTimeUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultTimeUtilEngine::Init(void)
{
	this->Release();

	tml::TimeUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultTimeUtilEngine::Create(void)
{
	this->Init();

	if (tml::TimeUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
