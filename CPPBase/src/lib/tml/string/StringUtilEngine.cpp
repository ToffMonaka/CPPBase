/**
 * @file
 * @brief StringUtilEngine�R�[�h�t�@�C��
 */


#include "StringUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::StringUtilEngine::StringUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::StringUtilEngine::~StringUtilEngine()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::StringUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::StringUtilEngine::Init(void)
{
	this->local_name_.clear();

	return;
}


/**
 * @brief Create�֐�
 * @param local_name (local_name)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::StringUtilEngine::Create(const CHAR *local_name)
{
	this->local_name_ = local_name;

	return (0);
}
