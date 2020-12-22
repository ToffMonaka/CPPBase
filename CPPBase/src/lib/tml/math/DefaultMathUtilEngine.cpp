/**
 * @file
 * @brief DefaultMathUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultMathUtilEngine.h"


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
 * @brief Release�֐�
 */
void tml::DefaultMathUtilEngine::Release(void)
{
	tml::MathUtilEngine::Release();

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
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultMathUtilEngine::Create(void)
{
	this->Init();

	if (tml::MathUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
