/**
 * @file
 * @brief TimeUtilEngine�R�[�h�t�@�C��
 */


#include "TimeUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::TimeUtilEngineDesc::TimeUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TimeUtilEngineDesc::~TimeUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::TimeUtilEngineDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TimeUtilEngine::TimeUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TimeUtilEngine::~TimeUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::TimeUtilEngine::Init(void)
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
INT tml::TimeUtilEngine::Create(const tml::TimeUtilEngineDesc &desc)
{
	return (0);
}
