/**
 * @file
 * @brief Transform2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathVectorFLOAT.h"
#include "XNAMathMatrixFLOAT.h"


namespace tml {
/**
 * @brief Transform2Dクラス
 */
class Transform2D
{
public:
	tml::XMFLOAT2EX position;
	FLOAT angle;
	tml::XMFLOAT2EX scale;

private:
	void Release(void);

public:
	Transform2D();
	Transform2D(const tml::XMFLOAT2EX &);
	Transform2D(const tml::XMFLOAT2EX &, const FLOAT);
	Transform2D(const tml::XMFLOAT2EX &, const FLOAT, const tml::XMFLOAT2EX &);
	Transform2D(const tml::Transform2D &);
	tml::Transform2D &operator =(const tml::Transform2D &);
	Transform2D(tml::Transform2D &&) noexcept;
	tml::Transform2D &operator =(tml::Transform2D &&) noexcept;
	virtual ~Transform2D();
	tml::Transform2D operator +(const tml::Transform2D &) const;
	tml::Transform2D &operator +=(const tml::Transform2D &);

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT2EX &);
	virtual void Init(const tml::XMFLOAT2EX &, const FLOAT);
	virtual void Init(const tml::XMFLOAT2EX &, const FLOAT, const tml::XMFLOAT2EX &);

	void Move(const tml::XMFLOAT2EX &);
	void Move(const tml::XMFLOAT2EX &, const FLOAT);
	void Rotation(const FLOAT);
	void Zoom(const tml::XMFLOAT2EX &);
	void Look(const tml::XMFLOAT2EX &);
	tml::XMFLOAT2EX GetXAxisVector(void) const;
	tml::XMFLOAT2EX GetYAxisVector(void) const;
	FLOAT GetDistance(const tml::XMFLOAT2EX &) const;
	void SetDistance(const tml::XMFLOAT2EX &, const FLOAT);
};
}


/**
 * @brief Release関数
 */
inline void tml::Transform2D::Release(void)
{
	return;
}


/**
 * @brief Move関数
 * @param pos (position)
 */
inline void tml::Transform2D::Move(const tml::XMFLOAT2EX &pos)
{
	this->position += pos;

	return;
}


/**
 * @brief Move関数
 * @param axis_vec (axis_vector)
 * @param len (length)
 */
inline void tml::Transform2D::Move(const tml::XMFLOAT2EX &axis_vec, const FLOAT len)
{
	this->position += axis_vec * len;

	return;
}


/**
 * @brief Rotation関数
 * @param angle (angle)
 */
inline void tml::Transform2D::Rotation(const FLOAT angle)
{
	this->angle += angle;

	return;
}


/**
 * @brief Zoom関数
 * @param scale (scale)
 */
inline void tml::Transform2D::Zoom(const tml::XMFLOAT2EX &scale)
{
	this->scale += scale;

	return;
}


/**
 * @brief GetXAxisVector関数
 * @return x_axis_vec (x_axis_vector)
 */
inline tml::XMFLOAT2EX tml::Transform2D::GetXAxisVector(void) const
{
	tml::XMFLOAT2EX x_axis_vec;

	DirectX::XMStoreFloat2(&x_axis_vec, DirectX::XMVector2Transform(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), DirectX::XMMatrixRotationZ(this->angle)));

	return (x_axis_vec);
}


/**
 * @brief GetYAxisVector関数
 * @return y_axis_vec (y_axis_vector)
 */
inline tml::XMFLOAT2EX tml::Transform2D::GetYAxisVector(void) const
{
	tml::XMFLOAT2EX y_axis_vec;

	DirectX::XMStoreFloat2(&y_axis_vec, DirectX::XMVector2Transform(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), DirectX::XMMatrixRotationZ(this->angle)));

	return (y_axis_vec);
}


/**
 * @brief GetDistance関数
 * @param pos (position)
 * @return dist (distance)
 */
inline FLOAT tml::Transform2D::GetDistance(const tml::XMFLOAT2EX &pos) const
{
	return (DirectX::XMVectorGetX(DirectX::XMVector2Length(DirectX::XMVectorSubtract(DirectX::XMLoadFloat2(&this->position), DirectX::XMLoadFloat2(&pos)))));
}


/**
 * @brief SetDistance関数
 * @param pos (position)
 * @param dist (distance)
 */
inline void tml::Transform2D::SetDistance(const tml::XMFLOAT2EX &pos, const FLOAT dist)
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat2(&pos);

	DirectX::XMStoreFloat2(&this->position, DirectX::XMVectorMultiplyAdd(DirectX::XMVector2Normalize(DirectX::XMVectorSubtract(DirectX::XMLoadFloat2(&this->position), tmp_pos)), DirectX::XMVectorSet(dist, dist, 0.0f, 0.0f), tmp_pos));

	return;
}
