/**
 * @file
 * @brief DefaultRandomUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultRandomUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultRandomUtilEngineDesc::DefaultRandomUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultRandomUtilEngineDesc::~DefaultRandomUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultRandomUtilEngineDesc::Init(void)
{
	this->Release();

	tml::RandomUtilEngineDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultRandomUtilEngine::DefaultRandomUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultRandomUtilEngine::~DefaultRandomUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultRandomUtilEngine::Init(void)
{
	this->Release();

	tml::RandomUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::DefaultRandomUtilEngine::Create(const tml::DefaultRandomUtilEngineDesc &desc)
{
	this->Init();

	if (tml::RandomUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
