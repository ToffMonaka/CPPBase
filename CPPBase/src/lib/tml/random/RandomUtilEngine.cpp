/**
 * @file
 * @brief RandomUtilEngine�R�[�h�t�@�C��
 */


#include "RandomUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::RandomUtilEngineDesc::RandomUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::RandomUtilEngineDesc::~RandomUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::RandomUtilEngineDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::RandomUtilEngine::RandomUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::RandomUtilEngine::~RandomUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::RandomUtilEngine::Init(void)
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
INT tml::RandomUtilEngine::Create(const tml::RandomUtilEngineDesc &desc)
{
	return (0);
}
