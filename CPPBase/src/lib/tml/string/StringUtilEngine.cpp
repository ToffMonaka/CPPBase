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
 * @brief Init�֐�
 */
void tml::StringUtilEngine::Init(void)
{
	this->locale_name_.clear();

	return;
}


/**
 * @brief Create�֐�
 * @param locale_name (locale_name)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::StringUtilEngine::Create(const CHAR *locale_name)
{
	this->locale_name_ = locale_name;

	return (0);
}
