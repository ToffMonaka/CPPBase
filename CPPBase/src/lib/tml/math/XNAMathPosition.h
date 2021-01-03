/**
 * @file
 * @brief XNAMathPositionヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathFLOAT.h"


namespace tml {
/**
 * @brief XMPositionクラス
 */
class XMPosition
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
	void UpdateXYZAxisVectorFromQuaternion(void);

public:
	XMPosition();
	XMPosition(const tml::XMFLOAT3EX &);
	XMPosition(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
	XMPosition(const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &);
	XMPosition(const tml::XMPosition &);
	tml::XMPosition &operator =(const tml::XMPosition &);
	XMPosition(tml::XMPosition &&) noexcept;
	tml::XMPosition &operator =(tml::XMPosition &&) noexcept;
	virtual ~XMPosition();
	tml::XMPosition operator +(const tml::XMPosition &) const;
	tml::XMPosition &operator +=(const tml::XMPosition &);
	tml::XMPosition operator -(const tml::XMPosition &) const;
	tml::XMPosition &operator -=(const tml::XMPosition &);

	virtual void Init(void);

	const tml::XMFLOAT3EX &Get(void) const;
	void Set(const tml::XMFLOAT3EX &);
	void Set(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
	void Set(const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &);
	void Move(const tml::XMFLOAT3EX &);
	void Move(const tml::XMFLOAT3EX &, const FLOAT);
	void Rotation(const tml::XMFLOAT3EX &);
	void Rotation(const tml::XMFLOAT3EX &, const FLOAT);
	void Rotation(const tml::XMFLOAT4EX &);
	void Look(const tml::XMFLOAT3EX &);
	void Look(const tml::XMFLOAT3EX &, const FLOAT);
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
 * @brief Get関数
 * @return pos (position)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition::Get(void) const
{
	return (this->pos_);
}


/**
 * @brief Set関数
 * @param pos (position)
 */
inline void tml::XMPosition::Set(const tml::XMFLOAT3EX &pos)
{
	this->pos_ = pos;

	return;
}


/**
 * @brief Set関数
 * @param pos (position)
 * @param quat (quaternion)
 */
inline void tml::XMPosition::Set(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat)
{
	this->pos_ = pos;
	this->quat_ = quat;

	this->UpdateAngleFromQuaternion();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Set関数
 * @param pos (position)
 * @param angle (angle)
 */
inline void tml::XMPosition::Set(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT3EX &angle)
{
	this->pos_ = pos;
	this->angle_ = angle;

	this->UpdateQuaternionFromAngle();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Move関数
 * @param pos (position)
 */
inline void tml::XMPosition::Move(const tml::XMFLOAT3EX &pos)
{
	this->pos_ += pos;

	return;
}


/**
 * @brief Move関数
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::XMPosition::Move(const tml::XMFLOAT3EX &axis_vec, const FLOAT len)
{
	this->pos_ += axis_vec * len;

	return;
}


/**
 * @brief Rotation関数
 * @param angle (angle)
 */
inline void tml::XMPosition::Rotation(const tml::XMFLOAT3EX &angle)
{
	this->angle_ += angle;

	this->UpdateQuaternionFromAngle();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Rotation関数
 * @param axis_vec (axis_vector)
 * @param angle (angle)
 */
inline void tml::XMPosition::Rotation(const tml::XMFLOAT3EX &axis_vec, const FLOAT angle)
{
	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&this->quat_), XMQuaternionRotationNormal(XMLoadFloat3(&axis_vec), angle))));

	this->UpdateAngleFromQuaternion();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Rotation関数
 * @param quat (quaternion)
 */
inline void tml::XMPosition::Rotation(const tml::XMFLOAT4EX &quat)
{
	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&this->quat_), XMLoadFloat4(&quat))));

	this->UpdateAngleFromQuaternion();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Look関数
 * @param pos (position)
 */
inline void tml::XMPosition::Look(const tml::XMFLOAT3EX &pos)
{
	XMVECTOR determinant;

	XMVECTOR tmp_pos = XMLoadFloat3(&this->pos_);
	XMVECTOR tmp_vec = XMVectorSubtract(XMLoadFloat3(&pos), tmp_pos);

	if (XMVectorGetX(XMVector3LengthSq(tmp_vec)) <= 0.0f) {
		tmp_vec = g_XMIdentityR2;
	}

	XMMATRIX rot_mat = XMMatrixInverse(&determinant, XMMatrixLookToLH(tmp_pos, tmp_vec, XMLoadFloat3(&this->y_axis_vec_)));

	if (XMMatrixIsNaN(rot_mat)) {
		tmp_vec = XMVectorAdd(tmp_vec, XMVectorSet(0.0f, 0.0f, 0.0001f, 0.0f));
		rot_mat = XMMatrixInverse(&determinant, XMMatrixLookToLH(tmp_pos, tmp_vec, XMLoadFloat3(&this->y_axis_vec_)));
	}

	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionRotationMatrix(rot_mat)));

	this->UpdateAngleFromQuaternion();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Look関数
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::XMPosition::Look(const tml::XMFLOAT3EX &axis_vec, const FLOAT len)
{
	XMVECTOR determinant;

	XMVECTOR tmp_pos = XMLoadFloat3(&this->pos_);
	XMVECTOR tmp_vec = XMVectorSubtract(XMVectorMultiply(XMLoadFloat3(&axis_vec), XMVectorSet(len, len, len, 0.0f)), tmp_pos);

	if (XMVectorGetX(XMVector3LengthSq(tmp_vec)) <= 0.0f) {
		tmp_vec = g_XMIdentityR2;
	}

	XMMATRIX rot_mat = XMMatrixInverse(&determinant, XMMatrixLookToLH(tmp_pos, tmp_vec, XMLoadFloat3(&this->y_axis_vec_)));

	if (XMMatrixIsNaN(rot_mat)) {
		tmp_vec = XMVectorAdd(tmp_vec, XMVectorSet(0.0f, 0.0f, 0.0001f, 0.0f));
		rot_mat = XMMatrixInverse(&determinant, XMMatrixLookToLH(tmp_pos, tmp_vec, XMLoadFloat3(&this->y_axis_vec_)));
	}

	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionRotationMatrix(rot_mat)));

	this->UpdateAngleFromQuaternion();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief GetQuaternion関数
 * @return quat (quaternion)
 */
inline const tml::XMFLOAT4EX &tml::XMPosition::GetQuaternion(void) const
{
	return (this->quat_);
}


/**
 * @brief SetQuaternion関数
 * @param quat (quaternion)
 */
inline void tml::XMPosition::SetQuaternion(const tml::XMFLOAT4EX &quat)
{
	this->quat_ = quat;

	this->UpdateAngleFromQuaternion();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief GetAngle関数
 * @return angle (angle)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition::GetAngle(void) const
{
	return (this->angle_);
}


/**
 * @brief SetAngle関数
 * @param angle (angle)
 */
inline void tml::XMPosition::SetAngle(const tml::XMFLOAT3EX &angle)
{
	this->angle_ = angle;

	this->UpdateQuaternionFromAngle();
	this->UpdateXYZAxisVectorFromQuaternion();

	return;
}


/**
 * @brief GetXAxisVector関数
 * @return x_axis_vec (x_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition::GetXAxisVector(void) const
{
	return (this->x_axis_vec_);
}


/**
 * @brief GetYAxisVector関数
 * @return y_axis_vec (y_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition::GetYAxisVector(void) const
{
	return (this->y_axis_vec_);
}


/**
 * @brief GetZAxisVector関数
 * @return z_axis_vec (z_axis_vector)
 */
inline const tml::XMFLOAT3EX &tml::XMPosition::GetZAxisVector(void) const
{
	return (this->z_axis_vec_);
}


/**
 * @brief GetLength関数
 * @param pos (position)
 * @return len (length)
 */
inline FLOAT tml::XMPosition::GetLength(const tml::XMFLOAT3EX &pos) const
{
	XMVECTOR tmp_pos = XMLoadFloat3(&pos);

	return (XMVectorGetX(XMVector3Length(XMVectorSubtract(XMLoadFloat3(&this->pos_), tmp_pos))));
}


/**
 * @brief SetLength関数
 * @param pos (position)
 * @param len (length)
 */
inline void tml::XMPosition::SetLength(const tml::XMFLOAT3EX &pos, const FLOAT len)
{
	XMVECTOR tmp_pos = XMLoadFloat3(&pos);

	XMStoreFloat3(&this->pos_, XMVectorMultiplyAdd(XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&this->pos_), tmp_pos)), XMVectorSet(len, len, len, 0.0f), tmp_pos));

	return;
}
