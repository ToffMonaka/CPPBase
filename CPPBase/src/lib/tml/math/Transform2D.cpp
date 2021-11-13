/**
 * @file
 * @brief Transform2Dコードファイル
 */


#include "Transform2D.h"


/**
 * @brief コンストラクタ
 */
tml::Transform2D::Transform2D() :
	position(0.0f),
	angle(0.0f),
	scale(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Transform2D::~Transform2D()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Transform2D::Init(void)
{
	this->Release();

	this->position = 0.0f;
	this->angle = 0.0f;
	this->scale = 1.0f;

	return;
}
