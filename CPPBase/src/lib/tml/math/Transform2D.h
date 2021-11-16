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
	Transform2D(const tml::Transform2D &);
	tml::Transform2D &operator =(const tml::Transform2D &);
	Transform2D(tml::Transform2D &&) noexcept;
	tml::Transform2D &operator =(tml::Transform2D &&) noexcept;
	virtual ~Transform2D();

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT2EX &);
	virtual void Init(const tml::XMFLOAT2EX &, const FLOAT);

	void Move(const tml::XMFLOAT2EX &);
	void Move(const tml::XMFLOAT2EX &, const FLOAT);
	void Rotation(const FLOAT);
	void Zoom(const tml::XMFLOAT2EX &);
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
