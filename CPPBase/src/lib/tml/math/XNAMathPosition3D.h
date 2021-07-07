/**
 * @file
 * @brief XNAMathPosition3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathFLOAT.h"


namespace tml {
/**
 * @brief XMPosition3Dクラス
 */
class XMPosition3D
{
private:
	tml::XMFLOAT3EX pos_;
	tml::XMFLOAT4EX quat_;
	tml::XMFLOAT3EX angle_;
	tml::XMFLOAT3EX x_axis_vec_;
	tml::XMFLOAT3EX y_axis_vec_;
	tml::XMFLOAT3EX z_axis_vec_;

private:
	void UpdateQuaternionFromAngle(void);
	void UpdateAngleFromQuaternion(void);
	void UpdateAxisVectorFromQuaternion(void);

protected:
	void Release(void);

public:
	XMPosition3D();
	XMPosition3D(const tml::XMFLOAT3EX &);
	XMPosition3D(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
	XMPosition3D(const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &);
	XMPosition3D(const tml::XMPosition3D &);
	tml::XMPosition3D &operator =(const tml::XMPosition3D &);
	XMPosition3D(tml::XMPosition3D &&) noexcept;
	tml::XMPosition3D &operator =(tml::XMPosition3D &&) noexcept;
	virtual ~XMPosition3D();
	tml::XMPosition3D operator +(const tml::XMPosition3D &) const;
	tml::XMPosition3D &operator +=(const tml::XMPosition3D &);
	tml::XMPosition3D operator -(const tml::XMPosition3D &) const;
	tml::XMPosition3D &operator -=(const tml::XMPosition3D &);

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT3EX &);
	virtual void Init(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
	virtual void Init(const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &);

	const tml::XMFLOAT3EX &Get(void) const;
	void Set(const tml::XMFLOAT3EX &);
	FLOAT GetX(void) const;
	void SetX(const FLOAT);
	FLOAT GetY(void) const;
	void SetY(const FLOAT);
	FLOAT GetZ(void) const;
	void SetZ(const FLOAT);
	void Move(const tml::XMFLOAT3EX &);
	void Move(const tml::XMFLOAT3EX &, const FLOAT);
	void Rotation(const tml::XMFLOAT4EX &);
	void Rotation(const tml::XMFLOAT3EX &);
	void Rotation(const tml::XMFLOAT3EX &, const FLOAT);
	void Look(const tml::XMFLOAT3EX &);
	const tml::XMFLOAT4EX &GetQuaternion(void) const;
	void SetQuaternion(const tml::XMFLOAT4EX &);
	const tml::XMFLOAT3EX &GetAngle(void) const;
	void SetAngle(const tml::XMFLOAT3EX &);
	const tml::XMFLOAT3EX &GetXAxisVector(void) const;
	const tml::XMFLOAT3EX &GetYAxisVector(void) const;
	const tml::XMFLOAT3EX &GetZAxisVector(void) const;
	FLOAT GetDistance(const tml::XMFLOAT3EX &) const;
	void SetDistance(const tml::XMFLOAT3EX &, const FLOAT);
};
}


/**
 * @brief Release関数
 */
inline void tml::XMPosition3D::Release(void)
{
	return;
}


/**
 * @brief Get関数
 * @return pos (position)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::Get(void) const
{
	return (this->pos_);
}


/**
 * @brief Set関数
 * @param pos (position)
 */
inline void tml::XMPosition3D::Set(const tml::XMFLOAT3EX &pos)
{
	this->pos_ = pos;

	return;
}


/**
 * @brief GetX関数
 * @return x (x)
 */
inline FLOAT tml::XMPosition3D::GetX(void) const
{
	return (this->pos_.x);
}


/**
 * @brief SetX関数
 * @param x (x)
 */
inline void tml::XMPosition3D::SetX(const FLOAT x)
{
	this->pos_.x = x;

	return;
}


/**
 * @brief GetY関数
 * @return y (y)
 */
inline FLOAT tml::XMPosition3D::GetY(void) const
{
	return (this->pos_.y);
}


/**
 * @brief SetY関数
 * @param y (y)
 */
inline void tml::XMPosition3D::SetY(const FLOAT y)
{
	this->pos_.y = y;

	return;
}


/**
 * @brief GetZ関数
 * @return z (z)
 */
inline FLOAT tml::XMPosition3D::GetZ(void) const
{
	return (this->pos_.z);
}


/**
 * @brief SetZ関数
 * @param z (z)
 */
inline void tml::XMPosition3D::SetZ(const FLOAT z)
{
	this->pos_.z = z;

	return;
}


/**
 * @brief Move関数
 * @param pos (position)
 */
inline void tml::XMPosition3D::Move(const tml::XMFLOAT3EX &pos)
{
	this->pos_ += pos;

	return;
}


/**
 * @brief Move関数
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::XMPosition3D::Move(const tml::XMFLOAT3EX &axis_vec, const FLOAT len)
{
	this->pos_ += axis_vec * len;

	return;
}


/**
 * @brief Rotation関数
 * @param quat (quaternion)
 */
inline void tml::XMPosition3D::Rotation(const tml::XMFLOAT4EX &quat)
{
	DirectX::XMStoreFloat4(&this->quat_, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&this->quat_), DirectX::XMLoadFloat4(&quat))));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Rotation関数
 * @param angle (angle)
 */
inline void tml::XMPosition3D::Rotation(const tml::XMFLOAT3EX &angle)
{
	this->angle_ += angle;

	this->UpdateQuaternionFromAngle();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Rotation関数
 * @param axis_vec (axis_vector)
 * @param angle (angle)
 */
inline void tml::XMPosition3D::Rotation(const tml::XMFLOAT3EX &axis_vec, const FLOAT angle)
{
	DirectX::XMStoreFloat4(&this->quat_, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&this->quat_), DirectX::XMQuaternionRotationNormal(DirectX::XMLoadFloat3(&axis_vec), angle))));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief GetQuaternion関数
 * @return quat (quaternion)
 */
inline const tml::XMFLOAT4EX &tml::XMPosition3D::GetQuaternion(void) const
{
	return (this->quat_);
}


/**
 * @brief SetQuaternion関数
 * @param quat (quaternion)
 */
inline void tml::XMPosition3D::SetQuaternion(const tml::XMFLOAT4EX &quat)
{
	this->quat_ = quat;

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief GetAngle関数
 * @return angle (angle)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetAngle(void) const
{
	return (this->angle_);
}


/**
 * @brief SetAngle関数
 * @param angle (angle)
 */
inline void tml::XMPosition3D::SetAngle(const tml::XMFLOAT3EX &angle)
{
	this->angle_ = angle;

	this->UpdateQuaternionFromAngle();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief GetXAxisVector関数
 * @return x_axis_vec (x_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetXAxisVector(void) const
{
	return (this->x_axis_vec_);
}


/**
 * @brief GetYAxisVector関数
 * @return y_axis_vec (y_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetYAxisVector(void) const
{
	return (this->y_axis_vec_);
}


/**
 * @brief GetZAxisVector関数
 * @return z_axis_vec (z_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetZAxisVector(void) const
{
	return (this->z_axis_vec_);
}


/**
 * @brief GetDistance関数
 * @param pos (position)
 * @return dist (distance)
 */
inline FLOAT tml::XMPosition3D::GetDistance(const tml::XMFLOAT3EX &pos) const
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat3(&pos);

	return (DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&this->pos_), tmp_pos))));
}


/**
 * @brief SetDistance関数
 * @param pos (position)
 * @param dist (distance)
 */
inline void tml::XMPosition3D::SetDistance(const tml::XMFLOAT3EX &pos, const FLOAT dist)
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat3(&pos);

	DirectX::XMStoreFloat3(&this->pos_, DirectX::XMVectorMultiplyAdd(DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&this->pos_), tmp_pos)), DirectX::XMVectorSet(dist, dist, dist, 0.0f), tmp_pos));

	return;
}
