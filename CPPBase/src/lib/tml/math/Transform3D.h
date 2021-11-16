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
	Transform3D(const tml::Transform3D &);
	tml::Transform3D &operator =(const tml::Transform3D &);
	Transform3D(tml::Transform3D &&) noexcept;
	tml::Transform3D &operator =(tml::Transform3D &&) noexcept;
	virtual ~Transform3D();

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT3EX &);
	virtual void Init(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);

	void Move(const tml::XMFLOAT3EX &);
	void Move(const tml::XMFLOAT3EX &, const FLOAT);
	void Rotation(const tml::XMFLOAT4EX &);
	void Zoom(const tml::XMFLOAT3EX &);
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
 * @brief Zoom関数
 * @param scale (scale)
 */
inline void tml::Transform3D::Zoom(const tml::XMFLOAT3EX &scale)
{
	this->scale += scale;

	return;
}
