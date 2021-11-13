/**
 * @file
 * @brief Transform2D�R�[�h�t�@�C��
 */


#include "Transform2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::Transform2D::Transform2D() :
	position(0.0f),
	angle(0.0f),
	scale(1.0f)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Transform2D::~Transform2D()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Transform2D::Init(void)
{
	this->Release();

	this->position = 0.0f;
	this->angle = 0.0f;
	this->scale = 1.0f;

	return;
}
