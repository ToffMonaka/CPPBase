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
