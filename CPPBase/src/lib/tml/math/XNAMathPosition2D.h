/**
 * @file
 * @brief XNAMathPosition2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathFLOAT.h"


namespace tml {
/**
 * @brief XMPosition2Dクラス
 */
class XMPosition2D
{
private:
	tml::XMFLOAT2EX pos_;
	FLOAT angle_;
	tml::XMFLOAT2EX x_axis_vec_;
	tml::XMFLOAT2EX y_axis_vec_;

private:
	void UpdateAxisVectorFromAngle(void);

protected:
	void Release(void);

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
	void Rotation(const FLOAT );
	FLOAT GetAngle(void) const;
	void SetAngle(const FLOAT);
	const tml::XMFLOAT2EX &GetXAxisVector(void) const;
	const tml::XMFLOAT2EX &GetYAxisVector(void) const;
	FLOAT GetLength(const tml::XMFLOAT2EX &) const;
	void SetLength(const tml::XMFLOAT2EX &, const FLOAT);
};
}


/**
 * @brief Release関数
 */
inline void tml::XMPosition2D::Release(void)
{
	return;
}


/**
 * @brief Get関数
 * @return pos (position)
 */
inline const tml::XMFLOAT2EX &tml::XMPosition2D::Get(void) const
{
	return (this->pos_);
}


/**
 * @brief Set関数
 * @param pos (position)
 */
inline void tml::XMPosition2D::Set(const tml::XMFLOAT2EX &pos)
{
	this->pos_ = pos;

	return;
}


/**
 * @brief GetX関数
 * @return x (x)
 */
inline FLOAT tml::XMPosition2D::GetX(void) const
{
	return (this->pos_.x);
}


/**
 * @brief SetX関数
 * @param x (x)
 */
inline void tml::XMPosition2D::SetX(const FLOAT x)
{
	this->pos_.x = x;

	return;
}


/**
 * @brief GetY関数
 * @return y (y)
 */
inline FLOAT tml::XMPosition2D::GetY(void) const
{
	return (this->pos_.y);
}


/**
 * @brief SetY関数
 * @param y (y)
 */
inline void tml::XMPosition2D::SetY(const FLOAT y)
{
	this->pos_.y = y;

	return;
}


/**
 * @brief Move関数
 * @param pos (position)
 */
inline void tml::XMPosition2D::Move(const tml::XMFLOAT2EX &pos)
{
	this->pos_ += pos;

	return;
}


/**
 * @brief Move関数
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::XMPosition2D::Move(const tml::XMFLOAT2EX &axis_vec, const FLOAT len)
{
	this->pos_ += axis_vec * len;

	return;
}


/**
 * @brief Rotation関数
 * @param angle (angle)
 */
inline void tml::XMPosition2D::Rotation(const FLOAT angle)
{
	this->angle_ += angle;

	this->UpdateAxisVectorFromAngle();

	return;
}


/**
 * @brief GetAngle関数
 * @return angle (angle)
 */
inline FLOAT tml::XMPosition2D::GetAngle(void) const
{
	return (this->angle_);
}


/**
 * @brief SetAngle関数
 * @param angle (angle)
 */
inline void tml::XMPosition2D::SetAngle(const FLOAT angle)
{
	this->angle_ = angle;

	this->UpdateAxisVectorFromAngle();

	return;
}


/**
 * @brief GetXAxisVector関数
 * @return x_axis_vec (x_axis_vector)
 */
inline const tml::XMFLOAT2EX &tml::XMPosition2D::GetXAxisVector(void) const
{
	return (this->x_axis_vec_);
}


/**
 * @brief GetYAxisVector関数
 * @return y_axis_vec (y_axis_vector)
 */
inline const tml::XMFLOAT2EX &tml::XMPosition2D::GetYAxisVector(void) const
{
	return (this->y_axis_vec_);
}


/**
 * @brief GetLength関数
 * @param pos (position)
 * @return len (length)
 */
inline FLOAT tml::XMPosition2D::GetLength(const tml::XMFLOAT2EX &pos) const
{
	XMVECTOR tmp_pos = XMLoadFloat2(&pos);

	return (XMVectorGetX(XMVector2Length(XMVectorSubtract(XMLoadFloat2(&this->pos_), tmp_pos))));
}


/**
 * @brief SetLength関数
 * @param pos (position)
 * @param len (length)
 */
inline void tml::XMPosition2D::SetLength(const tml::XMFLOAT2EX &pos, const FLOAT len)
{
	XMVECTOR tmp_pos = XMLoadFloat2(&pos);

	XMStoreFloat2(&this->pos_, XMVectorMultiplyAdd(XMVector2Normalize(XMVectorSubtract(XMLoadFloat2(&this->pos_), tmp_pos)), XMVectorSet(len, len, 0.0f, 0.0f), tmp_pos));

	return;
}
