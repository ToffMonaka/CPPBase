/**
 * @file
 * @brief Transform3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathVectorFLOAT.h"
#include "XNAMathMatrixFLOAT.h"


namespace tml {
/**
 * @brief Transform3Dクラス
 */
class Transform3D
{
public:
	tml::XMFLOAT3EX position;
	tml::XMFLOAT4EX quaternion;
	tml::XMFLOAT3EX scale;

private:
	void Release(void);

public:
	Transform3D();
	Transform3D(const tml::XMFLOAT3EX &);
	Transform3D(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
	Transform3D(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &, const tml::XMFLOAT3EX &);
	Transform3D(const tml::Transform3D &);
	tml::Transform3D &operator =(const tml::Transform3D &);
	Transform3D(tml::Transform3D &&) noexcept;
	tml::Transform3D &operator =(tml::Transform3D &&) noexcept;
	virtual ~Transform3D();
	tml::Transform3D operator +(const tml::Transform3D &) const;
	tml::Transform3D &operator +=(const tml::Transform3D &);

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT3EX &);
	virtual void Init(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
	virtual void Init(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &, const tml::XMFLOAT3EX &);

	void Move(const tml::XMFLOAT3EX &);
	void Move(const tml::XMFLOAT3EX &, const FLOAT);
	void Rotation(const tml::XMFLOAT4EX &);
	void Rotation(const tml::XMFLOAT3EX &, const FLOAT);
	void Zoom(const tml::XMFLOAT3EX &);
	void Look(const tml::XMFLOAT3EX &);
	tml::XMFLOAT3EX GetXAxisVector(void) const;
	tml::XMFLOAT3EX GetYAxisVector(void) const;
	tml::XMFLOAT3EX GetZAxisVector(void) const;
	FLOAT GetDistance(const tml::XMFLOAT3EX &) const;
	void SetDistance(const tml::XMFLOAT3EX &, const FLOAT);
	tml::XMFLOAT3EX GetAngle(void) const;
	void SetAngle(const tml::XMFLOAT3EX &);
};
}


/**
 * @brief Release関数
 */
inline void tml::Transform3D::Release(void)
{
	return;
}


/**
 * @brief Move関数
 * @param pos (position)
 */
inline void tml::Transform3D::Move(const tml::XMFLOAT3EX &pos)
{
	this->position += pos;

	return;
}


/**
 * @brief Move関数
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::Transform3D::Move(const tml::XMFLOAT3EX &axis_vec, const FLOAT len)
{
	this->position += axis_vec * len;

	return;
}


/**
 * @brief Rotation関数
 * @param quat (quaternion)
 */
inline void tml::Transform3D::Rotation(const tml::XMFLOAT4EX &quat)
{
	DirectX::XMStoreFloat4(&this->quaternion, DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&this->quaternion), DirectX::XMLoadFloat4(&quat)));

	return;
}


/**
 * @brief Rotation関数
 * @param axis_vec (axis_vector)
 * @param angle (angle)
 */
inline void tml::Transform3D::Rotation(const tml::XMFLOAT3EX &axis_vec, const FLOAT angle)
{
	DirectX::XMStoreFloat4(&this->quaternion, DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&this->quaternion), DirectX::XMQuaternionRotationNormal(DirectX::XMLoadFloat3(&axis_vec), angle)));

	return;
}


/**
 * @brief Zoom関数
 * @param scale (scale)
 */
inline void tml::Transform3D::Zoom(const tml::XMFLOAT3EX &scale)
{
	this->scale += scale;

	return;
}


/**
 * @brief GetXAxisVector関数
 * @return x_axis_vec (x_axis_vector)
 */
inline tml::XMFLOAT3EX tml::Transform3D::GetXAxisVector(void) const
{
	tml::XMFLOAT3EX x_axis_vec;

	DirectX::XMStoreFloat3(&x_axis_vec, DirectX::XMVector3Rotate(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), DirectX::XMLoadFloat4(&this->quaternion)));

	return (x_axis_vec);
}


/**
 * @brief GetYAxisVector関数
 * @return y_axis_vec (y_axis_vector)
 */
inline tml::XMFLOAT3EX tml::Transform3D::GetYAxisVector(void) const
{
	tml::XMFLOAT3EX y_axis_vec;

	DirectX::XMStoreFloat3(&y_axis_vec, DirectX::XMVector3Rotate(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMLoadFloat4(&this->quaternion)));

	return (y_axis_vec);
}


/**
 * @brief GetZAxisVector関数
 * @return z_axis_vec (z_axis_vector)
 */
inline tml::XMFLOAT3EX tml::Transform3D::GetZAxisVector(void) const
{
	tml::XMFLOAT3EX z_axis_vec;

	DirectX::XMStoreFloat3(&z_axis_vec, DirectX::XMVector3Rotate(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), DirectX::XMLoadFloat4(&this->quaternion)));

	return (z_axis_vec);
}


/**
 * @brief GetDistance関数
 * @param pos (position)
 * @return dist (distance)
 */
inline FLOAT tml::Transform3D::GetDistance(const tml::XMFLOAT3EX &pos) const
{
	return (DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&this->position), DirectX::XMLoadFloat3(&pos)))));
}


/**
 * @brief SetDistance関数
 * @param pos (position)
 * @param dist (distance)
 */
inline void tml::Transform3D::SetDistance(const tml::XMFLOAT3EX &pos, const FLOAT dist)
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat3(&pos);

	DirectX::XMStoreFloat3(&this->position, DirectX::XMVectorMultiplyAdd(DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&this->position), tmp_pos)), DirectX::XMVectorSet(dist, dist, dist, 0.0f), tmp_pos));

	return;
}


/**
 * @brief GetAngle関数
 *
 * three.jsを参考
 *
 * @return angle (angle)
 */
inline tml::XMFLOAT3EX tml::Transform3D::GetAngle(void) const
{
	tml::XMFLOAT3EX angle;

	tml::XMFLOAT3X3EX rot_mat;
		
	DirectX::XMStoreFloat3x3(&rot_mat, DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&this->quaternion))));

	angle.x = std::asin(-tml::Clamp(rot_mat._23, -1.0f, 1.0f));

	if (std::abs(rot_mat._23) < 0.99999f) {
		angle.y = std::atan2(rot_mat._13, rot_mat._33);
		angle.z = std::atan2(rot_mat._21, rot_mat._22);
	} else {
		angle.y = std::atan2(-rot_mat._31, rot_mat._11);
		angle.z = 0.0f;
	}

	return (angle);
}


/**
 * @brief SetAngle関数
 *
 * three.jsを参考
 *
 * @param angle (angle)
 */
inline void tml::Transform3D::SetAngle(const tml::XMFLOAT3EX &angle)
{
	DirectX::XMStoreFloat4(&this->quaternion, DirectX::XMQuaternionRotationRollPitchYawFromVector(DirectX::XMVectorSet(angle.x, angle.y, angle.z, 0.0f)));

	return;
}
