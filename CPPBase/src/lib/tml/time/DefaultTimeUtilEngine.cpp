/**
 * @file
 * @brief DefaultTimeUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultTimeUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultTimeUtilEngineDesc::DefaultTimeUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultTimeUtilEngineDesc::~DefaultTimeUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultTimeUtilEngineDesc::Init(void)
{
	this->Release();

	tml::TimeUtilEngineDesc::Init();

	return;
}


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
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::DefaultTimeUtilEngine::Create(const tml::DefaultTimeUtilEngineDesc &desc)
{
	this->Init();

	if (tml::TimeUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
