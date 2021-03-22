/**
 * @file
 * @brief XNAMathPosition2Dコードファイル
 */


#include "XNAMathPosition2D.h"


/**
 * @brief コンストラクタ
 */
tml::XMPosition2D::XMPosition2D() :
	pos_(0.0f),
	angle_(0.0f),
	x_axis_vec_(tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE),
	y_axis_vec_(tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 */
tml::XMPosition2D::XMPosition2D(const tml::XMFLOAT2EX &pos) :
	pos_(pos),
	angle_(0.0f),
	x_axis_vec_(tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE),
	y_axis_vec_(tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param angle (angle)
 */
tml::XMPosition2D::XMPosition2D(const tml::XMFLOAT2EX &pos, const FLOAT angle) :
	pos_(pos),
	angle_(angle)
{
	this->UpdateAxisVectorFromAngle();

	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::XMPosition2D::XMPosition2D(const tml::XMPosition2D &src)
{
	this->pos_ = src.pos_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::XMPosition2D &tml::XMPosition2D::operator =(const tml::XMPosition2D &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->pos_ = src.pos_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::XMPosition2D::XMPosition2D(tml::XMPosition2D &&src) noexcept
{
	this->pos_ = src.pos_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::XMPosition2D &tml::XMPosition2D::operator =(tml::XMPosition2D &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->pos_ = src.pos_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
tml::XMPosition2D::~XMPosition2D()
{
	this->Release();

	return;
}


/**
 * @brief operator +関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition2D tml::XMPosition2D::operator +(const tml::XMPosition2D &pos) const
{
	tml::XMFLOAT2EX tmp_pos(this->pos_);
	FLOAT tmp_angle = this->angle_;

	tmp_pos += pos.pos_;
	tmp_angle += pos.angle_;

	return (tml::XMPosition2D(tmp_pos, tmp_angle));
}


/**
 * @brief operator +=関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition2D &tml::XMPosition2D::operator +=(const tml::XMPosition2D &pos)
{
	this->pos_ += pos.pos_;
	this->angle_ += pos.angle_;

	this->UpdateAxisVectorFromAngle();

	return ((*this));
}


/**
 * @brief operator -関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition2D tml::XMPosition2D::operator -(const tml::XMPosition2D &pos) const
{
	tml::XMFLOAT2EX tmp_pos(this->pos_);
	FLOAT tmp_angle = this->angle_;

	tmp_pos -= pos.pos_;
	tmp_angle -= pos.angle_;

	return (tml::XMPosition2D(tmp_pos, tmp_angle));
}


/**
 * @brief operator -=関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition2D &tml::XMPosition2D::operator -=(const tml::XMPosition2D &pos)
{
	this->pos_ -= pos.pos_;
	this->angle_ -= pos.angle_;

	this->UpdateAxisVectorFromAngle();

	return ((*this));
}


/**
 * @brief Init関数
 */
void tml::XMPosition2D::Init(void)
{
	this->Release();

	this->pos_ = 0.0f;
	this->angle_ = 0.0f;
	this->x_axis_vec_ = tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE;
	this->y_axis_vec_ = tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 */
void tml::XMPosition2D::Init(const tml::XMFLOAT2EX &pos)
{
	this->Release();

	this->pos_ = pos;
	this->angle_ = 0.0f;
	this->x_axis_vec_ = tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE;
	this->y_axis_vec_ = tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param angle (angle)
 */
void tml::XMPosition2D::Init(const tml::XMFLOAT2EX &pos, const FLOAT angle)
{
	this->Release();

	this->pos_ = pos;
	this->angle_ = angle;

	this->UpdateAxisVectorFromAngle();

	return;
}


/**
 * @brief UpdateAxisVectorFromAngle関数
 */
void tml::XMPosition2D::UpdateAxisVectorFromAngle(void)
{
	XMMATRIX rot_mat = XMMatrixRotationZ(this->angle_);

	XMStoreFloat2(&this->x_axis_vec_, XMVector2Transform(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rot_mat));
	XMStoreFloat2(&this->y_axis_vec_, XMVector2Transform(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rot_mat));

	return;
}
