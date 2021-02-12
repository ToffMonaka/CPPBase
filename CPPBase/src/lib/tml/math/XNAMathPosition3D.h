/**
 * @file
 * @brief XNAMathPosition3D�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathFLOAT.h"


namespace tml {
/**
 * @brief XMPosition3D�N���X
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
	FLOAT GetLength(const tml::XMFLOAT3EX &) const;
	void SetLength(const tml::XMFLOAT3EX &, const FLOAT);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::XMPosition3D::Release(void)
{
	return;
}


/**
 * @brief Get�֐�
 * @return pos (position)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::Get(void) const
{
	return (this->pos_);
}


/**
 * @brief Set�֐�
 * @param pos (position)
 */
inline void tml::XMPosition3D::Set(const tml::XMFLOAT3EX &pos)
{
	this->pos_ = pos;

	return;
}


/**
 * @brief GetX�֐�
 * @return x (x)
 */
inline FLOAT tml::XMPosition3D::GetX(void) const
{
	return (this->pos_.x);
}


/**
 * @brief SetX�֐�
 * @param x (x)
 */
inline void tml::XMPosition3D::SetX(const FLOAT x)
{
	this->pos_.x = x;

	return;
}


/**
 * @brief GetY�֐�
 * @return y (y)
 */
inline FLOAT tml::XMPosition3D::GetY(void) const
{
	return (this->pos_.y);
}


/**
 * @brief SetY�֐�
 * @param y (y)
 */
inline void tml::XMPosition3D::SetY(const FLOAT y)
{
	this->pos_.y = y;

	return;
}


/**
 * @brief GetZ�֐�
 * @return z (z)
 */
inline FLOAT tml::XMPosition3D::GetZ(void) const
{
	return (this->pos_.z);
}


/**
 * @brief SetZ�֐�
 * @param z (z)
 */
inline void tml::XMPosition3D::SetZ(const FLOAT z)
{
	this->pos_.z = z;

	return;
}


/**
 * @brief Move�֐�
 * @param pos (position)
 */
inline void tml::XMPosition3D::Move(const tml::XMFLOAT3EX &pos)
{
	this->pos_ += pos;

	return;
}


/**
 * @brief Move�֐�
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::XMPosition3D::Move(const tml::XMFLOAT3EX &axis_vec, const FLOAT len)
{
	this->pos_ += axis_vec * len;

	return;
}


/**
 * @brief Rotation�֐�
 * @param quat (quaternion)
 */
inline void tml::XMPosition3D::Rotation(const tml::XMFLOAT4EX &quat)
{
	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&this->quat_), XMLoadFloat4(&quat))));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Rotation�֐�
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
 * @brief Rotation�֐�
 * @param axis_vec (axis_vector)
 * @param angle (angle)
 */
inline void tml::XMPosition3D::Rotation(const tml::XMFLOAT3EX &axis_vec, const FLOAT angle)
{
	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&this->quat_), XMQuaternionRotationNormal(XMLoadFloat3(&axis_vec), angle))));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Look�֐�
 * @param pos (position)
 */
inline void tml::XMPosition3D::Look(const tml::XMFLOAT3EX &pos)
{
	XMVECTOR determinant;

	XMVECTOR tmp_pos = XMLoadFloat3(&this->pos_);
	XMVECTOR tmp_vec = XMVectorSubtract(XMLoadFloat3(&pos), tmp_pos);

	if (XMVectorGetX(XMVector3LengthSq(tmp_vec)) <= 0.0f) {
		tmp_vec = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	}

	XMMATRIX rot_mat = XMMatrixInverse(&determinant, XMMatrixLookToLH(tmp_pos, tmp_vec, XMLoadFloat3(&this->y_axis_vec_)));

	if (XMMatrixIsNaN(rot_mat)) {
		tmp_vec = XMVectorAdd(tmp_vec, XMVectorSet(0.0f, 0.0f, 0.0001f, 0.0f));
		rot_mat = XMMatrixInverse(&determinant, XMMatrixLookToLH(tmp_pos, tmp_vec, XMLoadFloat3(&this->y_axis_vec_)));
	}

	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionRotationMatrix(rot_mat)));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief GetQuaternion�֐�
 * @return quat (quaternion)
 */
inline const tml::XMFLOAT4EX &tml::XMPosition3D::GetQuaternion(void) const
{
	return (this->quat_);
}


/**
 * @brief SetQuaternion�֐�
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
 * @brief GetAngle�֐�
 * @return angle (angle)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetAngle(void) const
{
	return (this->angle_);
}


/**
 * @brief SetAngle�֐�
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
 * @brief GetXAxisVector�֐�
 * @return x_axis_vec (x_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetXAxisVector(void) const
{
	return (this->x_axis_vec_);
}


/**
 * @brief GetYAxisVector�֐�
 * @return y_axis_vec (y_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetYAxisVector(void) const
{
	return (this->y_axis_vec_);
}


/**
 * @brief GetZAxisVector�֐�
 * @return z_axis_vec (z_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition3D::GetZAxisVector(void) const
{
	return (this->z_axis_vec_);
}


/**
 * @brief GetLength�֐�
 * @param pos (position)
 * @return len (length)
 */
inline FLOAT tml::XMPosition3D::GetLength(const tml::XMFLOAT3EX &pos) const
{
	XMVECTOR tmp_pos = XMLoadFloat3(&pos);

	return (XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&this->pos_), tmp_pos))));
}


/**
 * @brief SetLength�֐�
 * @param pos (position)
 * @param len (length)
 */
inline void tml::XMPosition3D::SetLength(const tml::XMFLOAT3EX &pos, const FLOAT len)
{
	XMVECTOR tmp_pos = XMLoadFloat3(&pos);

	XMStoreFloat3(&this->pos_, XMVectorMultiplyAdd(XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&this->pos_), tmp_pos)), XMVectorSet(len, len, len, 0.0f), tmp_pos));

	return;
}
