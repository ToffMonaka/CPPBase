/**
 * @file
 * @brief FileUtilEngine�R�[�h�t�@�C��
 */


#include "FileUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::FileUtilEngineDesc::FileUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileUtilEngineDesc::~FileUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileUtilEngineDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::FileUtilEngine::FileUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileUtilEngine::~FileUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileUtilEngine::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::FileUtilEngine::Create(const tml::FileUtilEngineDesc &desc)
{
	return (0);
}
