/**
 * @file
 * @brief StringUtilEngine�R�[�h�t�@�C��
 */


#include "StringUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::StringUtilEngineDesc::StringUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::StringUtilEngineDesc::~StringUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::StringUtilEngineDesc::Init(void)
{
	this->Release();

	this->locale_name.clear();

	return;
}


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
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::StringUtilEngine::Init(void)
{
	this->Release();

	this->locale_name_.clear();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::StringUtilEngine::Create(const tml::StringUtilEngineDesc &desc)
{
	this->locale_name_ = desc.locale_name;

	return (0);
}
