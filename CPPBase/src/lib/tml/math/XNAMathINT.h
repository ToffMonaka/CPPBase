/**
 * @file
 * @brief XNAMathINTヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_XNAMATH.h"
#pragma warning(push)
#pragma warning(disable: 4838)
#include <xnamath.h>
#pragma warning(pop)


/**
 * @brief XMINT2構造体
 */
typedef struct XMINT2_
{
	INT x;
	INT y;

	XMINT2_()
	{
		return;
	}

	XMINT2_(const INT x, const INT y) :
		x(x),
		y(y)
	{
		return;
	}
} XMINT2;


/**
 * @brief XMINT3構造体
 */
typedef struct XMINT3_
{
	INT x;
	INT y;
	INT z;

	XMINT3_()
	{
		return;
	}

	XMINT3_(const INT x, const INT y, const INT z) :
		x(x),
		y(y),
		z(z)
	{
		return;
	}
} XMINT3;


/**
 * @brief XMINT4構造体
 */
typedef struct XMINT4_
{
	INT x;
	INT y;
	INT z;
	INT w;

	XMINT4_()
	{
		return;
	}

	XMINT4_(const INT x, const INT y, const INT z, const INT w) :
		x(x),
		y(y),
		z(z),
		w(w)
	{
		return;
	}
} XMINT4;


namespace tml {
/**
 * @brief XMINT2EX構造体
 */
typedef struct XMINT2EX_ : public XMINT2
{
	XMINT2EX_() :
		XMINT2(0, 0)
	{
		return;
	}

	explicit XMINT2EX_(const INT x, const INT y) :
		XMINT2(x, y)
	{
		return;
	}

	explicit XMINT2EX_(const INT val) :
		XMINT2(val, val)
	{
		return;
	}

	explicit XMINT2EX_(const XMINT2 &val) :
		XMINT2(val.x, val.y)
	{
		return;
	}

	explicit XMINT2EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		XMINT2(1, 0)
	{
		return;
	}

	explicit XMINT2EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		XMINT2(0, 1)
	{
		return;
	}

	tml::XMINT2EX_ &operator =(const INT val)
	{
		this->x = val;
		this->y = val;

		return ((*this));
	}

	tml::XMINT2EX_ &operator =(const XMINT2 &val)
	{
		this->x = val.x;
		this->y = val.y;

		return ((*this));
	}

	tml::XMINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1;
		this->y = 0;

		return ((*this));
	}

	tml::XMINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0;
		this->y = 1;

		return ((*this));
	}

	bool operator ==(const INT val) const
	{
		return ((this->x == val) && (this->y == val));
	}

	bool operator ==(const XMINT2 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y));
	}

	bool operator !=(const INT val) const
	{
		return ((this->x != val) || (this->y != val));
	}

	bool operator !=(const XMINT2 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y));
	}

	tml::XMINT2EX_ operator +(const INT val) const
	{
		return (tml::XMINT2EX_(this->x + val, this->y + val));
	}

	tml::XMINT2EX_ operator +(const XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x + val.x, this->y + val.y));
	}

	tml::XMINT2EX_ &operator +=(const INT val)
	{
		this->x += val;
		this->y += val;

		return ((*this));
	}

	tml::XMINT2EX_ &operator +=(const XMINT2 &val)
	{
		this->x += val.x;
		this->y += val.y;

		return ((*this));
	}

	tml::XMINT2EX_ operator -(const INT val) const
	{
		return (tml::XMINT2EX_(this->x - val, this->y - val));
	}

	tml::XMINT2EX_ operator -(const XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x - val.x, this->y - val.y));
	}

	tml::XMINT2EX_ &operator -=(const INT val)
	{
		this->x -= val;
		this->y -= val;

		return ((*this));
	}

	tml::XMINT2EX_ &operator -=(const XMINT2 &val)
	{
		this->x -= val.x;
		this->y -= val.y;

		return ((*this));
	}

	tml::XMINT2EX_ operator *(const INT val) const
	{
		return (tml::XMINT2EX_(this->x * val, this->y * val));
	}

	tml::XMINT2EX_ operator *(const XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x * val.x, this->y * val.y));
	}

	tml::XMINT2EX_ &operator *=(const INT val)
	{
		this->x *= val;
		this->y *= val;

		return ((*this));
	}

	tml::XMINT2EX_ &operator *=(const XMINT2 &val)
	{
		this->x *= val.x;
		this->y *= val.y;

		return ((*this));
	}

	tml::XMINT2EX_ operator /(const INT val) const
	{
		return (tml::XMINT2EX_(this->x / val, this->y / val));
	}

	tml::XMINT2EX_ operator /(const XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x / val.x, this->y / val.y));
	}

	tml::XMINT2EX_ &operator /=(const INT val)
	{
		this->x /= val;
		this->y /= val;

		return ((*this));
	}

	tml::XMINT2EX_ &operator /=(const XMINT2 &val)
	{
		this->x /= val.x;
		this->y /= val.y;

		return ((*this));
	}

	tml::XMINT2EX_ operator -(void)
	{
		return (tml::XMINT2EX_(-this->x, -this->y));
	}
} XMINT2EX;


/**
 * @brief XMINT3EX構造体
 */
typedef struct XMINT3EX_ : public XMINT3
{
	XMINT3EX_() :
		XMINT3(0, 0, 0)
	{
		return;
	}

	explicit XMINT3EX_(const INT x, const INT y, const INT z) :
		XMINT3(x, y, z)
	{
		return;
	}

	explicit XMINT3EX_(const INT val) :
		XMINT3(val, val, val)
	{
		return;
	}

	explicit XMINT3EX_(const XMINT3 &val) :
		XMINT3(val.x, val.y, val.z)
	{
		return;
	}

	explicit XMINT3EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		XMINT3(1, 0, 0)
	{
		return;
	}

	explicit XMINT3EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		XMINT3(0, 1, 0)
	{
		return;
	}

	explicit XMINT3EX_(const tml::ConstantUtil::XNAMATH::Z_VECTOR type) :
		XMINT3(0, 0, 1)
	{
		return;
	}

	tml::XMINT3EX_ &operator =(const INT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;

		return ((*this));
	}

	tml::XMINT3EX_ &operator =(const XMINT3 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;

		return ((*this));
	}

	tml::XMINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1;
		this->y = 0;
		this->z = 0;

		return ((*this));
	}

	tml::XMINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0;
		this->y = 1;
		this->z = 0;

		return ((*this));
	}

	tml::XMINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Z_VECTOR type)
	{
		this->x = 0;
		this->y = 0;
		this->z = 1;

		return ((*this));
	}

	bool operator ==(const INT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val));
	}

	bool operator ==(const XMINT3 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z));
	}

	bool operator !=(const INT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val));
	}

	bool operator !=(const XMINT3 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z));
	}

	tml::XMINT3EX_ operator +(const INT val) const
	{
		return (tml::XMINT3EX_(this->x + val, this->y + val, this->z + val));
	}

	tml::XMINT3EX_ operator +(const XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x + val.x, this->y + val.y, this->z + val.z));
	}

	tml::XMINT3EX_ &operator +=(const INT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	}

	tml::XMINT3EX_ &operator +=(const XMINT3 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;

		return ((*this));
	}

	tml::XMINT3EX_ operator -(const INT val) const
	{
		return (tml::XMINT3EX_(this->x - val, this->y - val, this->z - val));
	}

	tml::XMINT3EX_ operator -(const XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x - val.x, this->y - val.y, this->z - val.z));
	}

	tml::XMINT3EX_ &operator -=(const INT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;

		return ((*this));
	}

	tml::XMINT3EX_ &operator -=(const XMINT3 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;

		return ((*this));
	}

	tml::XMINT3EX_ operator *(const INT val) const
	{
		return (tml::XMINT3EX_(this->x * val, this->y * val, this->z * val));
	}

	tml::XMINT3EX_ operator *(const XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x * val.x, this->y * val.y, this->z * val.z));
	}

	tml::XMINT3EX_ &operator *=(const INT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;

		return ((*this));
	}

	tml::XMINT3EX_ &operator *=(const XMINT3 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;

		return ((*this));
	}

	tml::XMINT3EX_ operator /(const INT val) const
	{
		return (tml::XMINT3EX_(this->x / val, this->y / val, this->z / val));
	}

	tml::XMINT3EX_ operator /(const XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x / val.x, this->y / val.y, this->z / val.z));
	}

	tml::XMINT3EX_ &operator /=(const INT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;

		return ((*this));
	}

	tml::XMINT3EX_ &operator /=(const XMINT3 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;

		return ((*this));
	}

	tml::XMINT3EX_ operator -(void)
	{
		return (tml::XMINT3EX_(-this->x, -this->y, -this->z));
	}
} XMINT3EX;


/**
 * @brief XMINT4EX構造体
 */
typedef struct XMINT4EX_ : public XMINT4
{
	XMINT4EX_() :
		XMINT4(0, 0, 0, 0)
	{
		return;
	}

	explicit XMINT4EX_(const INT x, const INT y, const INT z, const INT w) :
		XMINT4(x, y, z, w)
	{
		return;
	}

	explicit XMINT4EX_(const INT val) :
		XMINT4(val, val, val, val)
	{
		return;
	}

	explicit XMINT4EX_(const XMINT4 &val) :
		XMINT4(val.x, val.y, val.z, val.w)
	{
		return;
	}

	explicit XMINT4EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type) :
		XMINT4(0, 0, 0, 1)
	{
		return;
	}

	tml::XMINT4EX_ &operator =(const INT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;
		this->w = val;

		return ((*this));
	}

	tml::XMINT4EX_ &operator =(const XMINT4 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;
		this->w = val.w;

		return ((*this));
	}

	tml::XMINT4EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type)
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;

		return ((*this));
	}

	bool operator ==(const INT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val) && (this->w == val));
	}

	bool operator ==(const XMINT4 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z) && (this->w == val.w));
	}

	bool operator !=(const INT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val) || (this->w != val));
	}

	bool operator !=(const XMINT4 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z) || (this->w != val.w));
	}

	tml::XMINT4EX_ operator +(const INT val) const
	{
		return (tml::XMINT4EX_(this->x + val, this->y + val, this->z + val, this->w + val));
	}

	tml::XMINT4EX_ operator +(const XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x + val.x, this->y + val.y, this->z + val.z, this->w + val.w));
	}

	tml::XMINT4EX_ &operator +=(const INT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	}

	tml::XMINT4EX_ &operator +=(const XMINT4 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;
		this->w += val.w;

		return ((*this));
	}

	tml::XMINT4EX_ operator -(const INT val) const
	{
		return (tml::XMINT4EX_(this->x - val, this->y - val, this->z - val, this->w - val));
	}

	tml::XMINT4EX_ operator -(const XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x - val.x, this->y - val.y, this->z - val.z, this->w - val.w));
	}

	tml::XMINT4EX_ &operator -=(const INT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;
		this->w -= val;

		return ((*this));
	}

	tml::XMINT4EX_ &operator -=(const XMINT4 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;
		this->w -= val.w;

		return ((*this));
	}

	tml::XMINT4EX_ operator *(const INT val) const
	{
		return (tml::XMINT4EX_(this->x * val, this->y * val, this->z * val, this->w * val));
	}

	tml::XMINT4EX_ operator *(const XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x * val.x, this->y * val.y, this->z * val.z, this->w * val.w));
	}

	tml::XMINT4EX_ &operator *=(const INT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;
		this->w *= val;

		return ((*this));
	}

	tml::XMINT4EX_ &operator *=(const XMINT4 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;
		this->w *= val.w;

		return ((*this));
	}

	tml::XMINT4EX_ operator /(const INT val) const
	{
		return (tml::XMINT4EX_(this->x / val, this->y / val, this->z / val, this->w / val));
	}

	tml::XMINT4EX_ operator /(const XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x / val.x, this->y / val.y, this->z / val.z, this->w / val.w));
	}

	tml::XMINT4EX_ &operator /=(const INT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;
		this->w /= val;

		return ((*this));
	}

	tml::XMINT4EX_ &operator /=(const XMINT4 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;
		this->w /= val.w;

		return ((*this));
	}

	tml::XMINT4EX_ operator -(void)
	{
		return (tml::XMINT4EX_(-this->x, -this->y, -this->z, -this->w));
	}
} XMINT4EX;
}
