/**
 * @file
 * @brief DefaultFileUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultFileUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultFileUtilEngine::DefaultFileUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultFileUtilEngine::~DefaultFileUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultFileUtilEngine::Init(void)
{
	this->Release();

	tml::FileUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultFileUtilEngine::Create(void)
{
	this->Init();

	if (tml::FileUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
