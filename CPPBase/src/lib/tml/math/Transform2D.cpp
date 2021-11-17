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
 * @brief コンストラクタ
 * @param pos (position)
 */
tml::Transform2D::Transform2D(const tml::XMFLOAT2EX &pos) :
	position(pos),
	angle(0.0f),
	scale(1.0f)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param angle (angle)
 */
tml::Transform2D::Transform2D(const tml::XMFLOAT2EX &pos, const FLOAT angle) :
	position(pos),
	angle(angle),
	scale(1.0f)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param angle (angle)
 * @param scale (scale)
 */
tml::Transform2D::Transform2D(const tml::XMFLOAT2EX &pos, const FLOAT angle, const tml::XMFLOAT2EX &scale) :
	position(pos),
	angle(angle),
	scale(scale)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Transform2D::Transform2D(const tml::Transform2D &src)
{
	this->position = src.position;
	this->angle = src.angle;
	this->scale = src.scale;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Transform2D &tml::Transform2D::operator =(const tml::Transform2D &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->position = src.position;
	this->angle = src.angle;
	this->scale = src.scale;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Transform2D::Transform2D(tml::Transform2D &&src) noexcept
{
	this->position = src.position;
	this->angle = src.angle;
	this->scale = src.scale;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Transform2D &tml::Transform2D::operator =(tml::Transform2D &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->position = src.position;
	this->angle = src.angle;
	this->scale = src.scale;

	src.Init();

	return ((*this));
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
 * @brief operator +関数
 * @param trans (transform)
 * @return trans (transform)
 */
tml::Transform2D tml::Transform2D::operator +(const tml::Transform2D &trans) const
{
	tml::XMFLOAT2EX tmp_pos = this->position;
	FLOAT tmp_angle = this->angle;
	tml::XMFLOAT2EX tmp_scale = this->scale;

	tmp_pos += trans.position;
	tmp_angle += trans.angle;
	tmp_scale += trans.scale;

	return (tml::Transform2D(tmp_pos, tmp_angle, tmp_scale));
}


/**
 * @brief operator +=関数
 * @param trans (transform)
 * @return trans (transform)
 */
tml::Transform2D &tml::Transform2D::operator +=(const tml::Transform2D &trans)
{
	this->position += trans.position;
	this->angle += trans.angle;
	this->scale += trans.scale;

	return ((*this));
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


/**
 * @brief Init関数
 * @param pos (position)
 */
void tml::Transform2D::Init(const tml::XMFLOAT2EX &pos)
{
	this->Release();

	this->position = pos;
	this->angle = 0.0f;
	this->scale = 1.0f;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param angle (angle)
 */
void tml::Transform2D::Init(const tml::XMFLOAT2EX &pos, const FLOAT angle)
{
	this->Release();

	this->position = pos;
	this->angle = angle;
	this->scale = 1.0f;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param angle (angle)
 * @param scale (scale)
 */
void tml::Transform2D::Init(const tml::XMFLOAT2EX &pos, const FLOAT angle, const tml::XMFLOAT2EX &scale)
{
	this->Release();

	this->position = pos;
	this->angle = angle;
	this->scale = scale;

	return;
}


/**
 * @brief Look関数
 * @param pos (position)
 */
void tml::Transform2D::Look(const tml::XMFLOAT2EX &pos)
{
	this->angle = DirectX::XMVectorGetX(DirectX::XMVector2AngleBetweenVectors(DirectX::XMLoadFloat2(&this->position), DirectX::XMLoadFloat2(&pos)));

	return;
}
