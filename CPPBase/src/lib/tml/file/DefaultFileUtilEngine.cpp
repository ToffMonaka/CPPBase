/**
 * @file
 * @brief DefaultFileUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultFileUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultFileUtilEngineDesc::DefaultFileUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultFileUtilEngineDesc::~DefaultFileUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultFileUtilEngineDesc::Init(void)
{
	this->Release();

	tml::FileUtilEngineDesc::Init();

	return;
}


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
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::DefaultFileUtilEngine::Create(const tml::DefaultFileUtilEngineDesc &desc)
{
	this->Init();

	if (tml::FileUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
