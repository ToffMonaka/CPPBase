/**
 * @file
 * @brief DefaultRandomUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultRandomUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultRandomUtilEngine::DefaultRandomUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultRandomUtilEngine::~DefaultRandomUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultRandomUtilEngine::Init(void)
{
	this->Release();

	tml::RandomUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultRandomUtilEngine::Create(void)
{
	this->Init();

	if (tml::RandomUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
