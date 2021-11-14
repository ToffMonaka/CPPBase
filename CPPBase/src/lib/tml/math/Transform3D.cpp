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
 * @brief コンストラクタ
 * @param pos (position)
 */
tml::Transform3D::Transform3D(const tml::XMFLOAT3EX &pos) :
	position(pos),
	quaternion(tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE),
	scale(1.0f)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param quat (quaternion)
 */
tml::Transform3D::Transform3D(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat) :
	position(pos),
	quaternion(quat),
	scale(1.0f)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Transform3D::Transform3D(const tml::Transform3D &src)
{
	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Transform3D &tml::Transform3D::operator =(const tml::Transform3D &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Transform3D::Transform3D(tml::Transform3D &&src) noexcept
{
	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Transform3D &tml::Transform3D::operator =(tml::Transform3D &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	src.Init();

	return ((*this));
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


/**
 * @brief Init関数
 * @param pos (position)
 */
void tml::Transform3D::Init(const tml::XMFLOAT3EX &pos)
{
	this->Release();

	this->position = pos;
	this->quaternion = tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE;
	this->scale = 1.0f;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param quat (quaternion)
 */
void tml::Transform3D::Init(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat)
{
	this->Release();

	this->position = pos;
	this->quaternion = quat;
	this->scale = 1.0f;

	return;
}
