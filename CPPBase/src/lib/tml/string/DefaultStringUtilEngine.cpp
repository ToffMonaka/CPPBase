/**
 * @file
 * @brief DefaultStringUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultStringUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultStringUtilEngineDesc::DefaultStringUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultStringUtilEngineDesc::~DefaultStringUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultStringUtilEngineDesc::Init(void)
{
	this->Release();

	tml::StringUtilEngineDesc::Init();

	return;
}


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
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::DefaultStringUtilEngine::Create(const tml::DefaultStringUtilEngineDesc &desc)
{
	this->Init();

	if (tml::StringUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
