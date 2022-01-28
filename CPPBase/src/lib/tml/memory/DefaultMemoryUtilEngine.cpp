/**
 * @file
 * @brief DefaultMemoryUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultMemoryUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultMemoryUtilEngineDesc::DefaultMemoryUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultMemoryUtilEngineDesc::~DefaultMemoryUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultMemoryUtilEngineDesc::Init(void)
{
	this->Release();

	tml::MemoryUtilEngineDesc::Init();

	return;
}


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
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultMemoryUtilEngine::Init(void)
{
	this->Release();

	tml::MemoryUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::DefaultMemoryUtilEngine::Create(const tml::DefaultMemoryUtilEngineDesc &desc)
{
	this->Init();

	if (tml::MemoryUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
