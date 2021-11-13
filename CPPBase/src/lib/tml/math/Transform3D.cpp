/**
 * @file
 * @brief Transform3Dコードファイル
 */


#include "Transform3D.h"


/**
 * @brief コンストラクタ
 */
tml::Transform3D::Transform3D() :
	position(0.0f),
	quaternion(tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE),
	scale(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Transform3D::~Transform3D()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Transform3D::Init(void)
{
	this->Release();

	this->position = 0.0f;
	this->quaternion = tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE;
	this->scale = 1.0f;

	return;
}
