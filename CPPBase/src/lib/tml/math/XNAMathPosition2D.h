/**
 * @file
 * @brief XNAMathPosition2D�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathFLOAT.h"


namespace tml {
/**
 * @brief XMPosition2D�N���X
 */
class XMPosition2D
{
private:
	tml::XMFLOAT2EX pos_;
	FLOAT angle_;
	tml::XMFLOAT2EX x_axis_vec_;
	tml::XMFLOAT2EX y_axis_vec_;

private:
	void Release(void);

	void UpdateAxisVectorFromAngle(void);

public:
	XMPosition2D();
	XMPosition2D(const tml::XMFLOAT2EX &);
	XMPosition2D(const tml::XMFLOAT2EX &, const FLOAT);
	XMPosition2D(const tml::XMPosition2D &);
	tml::XMPosition2D &operator =(const tml::XMPosition2D &);
	XMPosition2D(tml::XMPosition2D &&) noexcept;
	tml::XMPosition2D &operator =(tml::XMPosition2D &&) noexcept;
	virtual ~XMPosition2D();
	tml::XMPosition2D operator +(const tml::XMPosition2D &) const;
	tml::XMPosition2D &operator +=(const tml::XMPosition2D &);
	tml::XMPosition2D operator -(const tml::XMPosition2D &) const;
	tml::XMPosition2D &operator -=(const tml::XMPosition2D &);

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT2EX &);
	virtual void Init(const tml::XMFLOAT2EX &, const FLOAT);

	const tml::XMFLOAT2EX &Get(void) const;
	void Set(const tml::XMFLOAT2EX &);
	FLOAT GetX(void) const;
	void SetX(const FLOAT);
	FLOAT GetY(void) const;
	void SetY(const FLOAT);
	void Move(const tml::XMFLOAT2EX &);
	void Move(const tml::XMFLOAT2EX &, const FLOAT);
	void Rotation(const FLOAT);
	void Look(const tml::XMFLOAT2EX &);
	FLOAT GetAngle(void) const;
	void SetAngle(const FLOAT);
	const tml::XMFLOAT2EX &GetXAxisVector(void) const;
	const tml::XMFLOAT2EX &GetYAxisVector(void) const;
	FLOAT GetDistance(const tml::XMFLOAT2EX &) const;
	void SetDistance(const tml::XMFLOAT2EX &, const FLOAT);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::XMPosition2D::Release(void)
{
	return;
}


/**
 * @brief Get�֐�
 * @return pos (position)
 */
inline const tml::XMFLOAT2EX &tml::XMPosition2D::Get(void) const
{
	return (this->pos_);
}


/**
 * @brief Set�֐�
 * @param pos (position)
 */
inline void tml::XMPosition2D::Set(const tml::XMFLOAT2EX &pos)
{
	this->pos_ = pos;

	return;
}


/**
 * @brief GetX�֐�
 * @return x (x)
 */
inline FLOAT tml::XMPosition2D::GetX(void) const
{
	return (this->pos_.x);
}


/**
 * @brief SetX�֐�
 * @param x (x)
 */
inline void tml::XMPosition2D::SetX(const FLOAT x)
{
	this->pos_.x = x;

	return;
}


/**
 * @brief GetY�֐�
 * @return y (y)
 */
inline FLOAT tml::XMPosition2D::GetY(void) const
{
	return (this->pos_.y);
}


/**
 * @brief SetY�֐�
 * @param y (y)
 */
inline void tml::XMPosition2D::SetY(const FLOAT y)
{
	this->pos_.y = y;

	return;
}


/**
 * @brief Move�֐�
 * @param pos (position)
 */
inline void tml::XMPosition2D::Move(const tml::XMFLOAT2EX &pos)
{
	this->pos_ += pos;

	return;
}


/**
 * @brief Move�֐�
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::XMPosition2D::Move(const tml::XMFLOAT2EX &axis_vec, const FLOAT len)
{
	this->pos_ += axis_vec * len;

	return;
}


/**
 * @brief Rotation�֐�
 * @param angle (angle)
 */
inline void tml::XMPosition2D::Rotation(const FLOAT angle)
{
	this->angle_ += angle;

	this->UpdateAxisVectorFromAngle();

	return;
}


/**
 * @brief GetAngle�֐�
 * @return angle (angle)
 */
inline FLOAT tml::XMPosition2D::GetAngle(void) const
{
	return (this->angle_);
}


/**
 * @brief SetAngle�֐�
 * @param angle (angle)
 */
inline void tml::XMPosition2D::SetAngle(const FLOAT angle)
{
	this->angle_ = angle;

	this->UpdateAxisVectorFromAngle();

	return;
}


/**
 * @brief GetXAxisVector�֐�
 * @return x_axis_vec (x_axis_vector)
 */
inline const tml::XMFLOAT2EX &tml::XMPosition2D::GetXAxisVector(void) const
{
	return (this->x_axis_vec_);
}


/**
 * @brief GetYAxisVector�֐�
 * @return y_axis_vec (y_axis_vector)
 */
inline const tml::XMFLOAT2EX &tml::XMPosition2D::GetYAxisVector(void) const
{
	return (this->y_axis_vec_);
}


/**
 * @brief GetDistance�֐�
 * @param pos (position)
 * @return dist (distance)
 */
inline FLOAT tml::XMPosition2D::GetDistance(const tml::XMFLOAT2EX &pos) const
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat2(&pos);

	return (DirectX::XMVectorGetX(DirectX::XMVector2Length(DirectX::XMVectorSubtract(DirectX::XMLoadFloat2(&this->pos_), tmp_pos))));
}


/**
 * @brief SetDistance�֐�
 * @param pos (position)
 * @param dist (distance)
 */
inline void tml::XMPosition2D::SetDistance(const tml::XMFLOAT2EX &pos, const FLOAT dist)
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat2(&pos);

	DirectX::XMStoreFloat2(&this->pos_, DirectX::XMVectorMultiplyAdd(DirectX::XMVector2Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat2(&this->pos_), tmp_pos)), DirectX::XMVectorSet(dist, dist, 0.0f, 0.0f), tmp_pos));

	return;
}
