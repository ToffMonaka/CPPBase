/**
 * @file
 * @brief DefaultThreadUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultThreadUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultThreadUtilEngineDesc::DefaultThreadUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultThreadUtilEngineDesc::~DefaultThreadUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultThreadUtilEngineDesc::Init(void)
{
	this->Release();

	tml::ThreadUtilEngineDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultThreadUtilEngine::DefaultThreadUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultThreadUtilEngine::~DefaultThreadUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultThreadUtilEngine::Init(void)
{
	this->Release();

	tml::ThreadUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::DefaultThreadUtilEngine::Create(const tml::DefaultThreadUtilEngineDesc &desc)
{
	this->Init();

	if (tml::ThreadUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
