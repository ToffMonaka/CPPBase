/**
 * @file
 * @brief DefaultMathUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultMathUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultMathUtilEngineDesc::DefaultMathUtilEngineDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultMathUtilEngineDesc::~DefaultMathUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultMathUtilEngineDesc::Init(void)
{
	this->Release();

	tml::MathUtilEngineDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultMathUtilEngine::DefaultMathUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultMathUtilEngine::~DefaultMathUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultMathUtilEngine::Init(void)
{
	this->Release();

	tml::MathUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::DefaultMathUtilEngine::Create(const tml::DefaultMathUtilEngineDesc &desc)
{
	this->Init();

	if (tml::MathUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
