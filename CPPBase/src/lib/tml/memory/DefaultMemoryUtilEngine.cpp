/**
 * @file
 * @brief DefaultMemoryUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultMemoryUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultMemoryUtilEngine::DefaultMemoryUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultMemoryUtilEngine::~DefaultMemoryUtilEngine()
{
	this->Init();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultMemoryUtilEngine::Init(void)
{
	tml::MemoryUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultMemoryUtilEngine::Create(void)
{
	if (tml::MemoryUtilEngine::Create() < 0) {
		return (-1);
	}

	return (0);
}
