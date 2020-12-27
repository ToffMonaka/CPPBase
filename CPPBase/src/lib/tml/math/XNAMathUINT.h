/**
 * @file
 * @brief XNAMathUINTヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_XNAMATH.h"
#pragma warning(push)
#pragma warning(disable: 4838)
#include <xnamath.h>
#pragma warning(pop)


/**
 * @brief XMUINT2構造体
 */
typedef struct XMUINT2_
{
	UINT x;
	UINT y;

	XMUINT2_()
	{
		return;
	}

	XMUINT2_(const UINT x, const UINT y) :
		x(x),
		y(y)
	{
		return;
	}
} XMUINT2;


/**
 * @brief XMUINT3構造体
 */
typedef struct XMUINT3_
{
	UINT x;
	UINT y;
	UINT z;

	XMUINT3_()
	{
		return;
	}

	XMUINT3_(const UINT x, const UINT y, const UINT z) :
		x(x),
		y(y),
		z(z)
	{
		return;
	}
} XMUINT3;


/**
 * @brief XMUINT4構造体
 */
typedef struct XMUINT4_
{
	UINT x;
	UINT y;
	UINT z;
	UINT w;

	XMUINT4_()
	{
		return;
	}

	XMUINT4_(const UINT x, const UINT y, const UINT z, const UINT w) :
		x(x),
		y(y),
		z(z),
		w(w)
	{
		return;
	}
} XMUINT4;


namespace tml {
/**
 * @brief XMUINT2EX構造体
 */
typedef struct XMUINT2EX_ : public XMUINT2
{
	XMUINT2EX_() :
		XMUINT2(0U, 0U)
	{
		return;
	}

	explicit XMUINT2EX_(const UINT x, const UINT y) :
		XMUINT2(x, y)
	{
		return;
	}

	explicit XMUINT2EX_(const UINT val) :
		XMUINT2(val, val)
	{
		return;
	}

	explicit XMUINT2EX_(const XMUINT2 &val) :
		XMUINT2(val.x, val.y)
	{
		return;
	}

	explicit XMUINT2EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		XMUINT2(1U, 0U)
	{
		return;
	}

	explicit XMUINT2EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		XMUINT2(0U, 1U)
	{
		return;
	}

	tml::XMUINT2EX_ &operator =(const UINT val)
	{
		this->x = val;
		this->y = val;

		return ((*this));
	}

	tml::XMUINT2EX_ &operator =(const XMUINT2 &val)
	{
		this->x = val.x;
		this->y = val.y;

		return ((*this));
	}

	tml::XMUINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1U;
		this->y = 0U;

		return ((*this));
	}

	tml::XMUINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0U;
		this->y = 1U;

		return ((*this));
	}

	bool operator ==(const UINT val) const
	{
		return ((this->x == val) && (this->y == val));
	}

	bool operator ==(const XMUINT2 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y));
	}

	bool operator !=(const UINT val) const
	{
		return ((this->x != val) || (this->y != val));
	}

	bool operator !=(const XMUINT2 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y));
	}

	tml::XMUINT2EX_ operator +(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x + val, this->y + val));
	}

	tml::XMUINT2EX_ operator +(const XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x + val.x, this->y + val.y));
	}

	tml::XMUINT2EX_ &operator +=(const UINT val)
	{
		this->x += val;
		this->y += val;

		return ((*this));
	}

	tml::XMUINT2EX_ &operator +=(const XMUINT2 &val)
	{
		this->x += val.x;
		this->y += val.y;

		return ((*this));
	}

	tml::XMUINT2EX_ operator -(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x - val, this->y - val));
	}

	tml::XMUINT2EX_ operator -(const XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x - val.x, this->y - val.y));
	}

	tml::XMUINT2EX_ &operator -=(const UINT val)
	{
		this->x -= val;
		this->y -= val;

		return ((*this));
	}

	tml::XMUINT2EX_ &operator -=(const XMUINT2 &val)
	{
		this->x -= val.x;
		this->y -= val.y;

		return ((*this));
	}

	tml::XMUINT2EX_ operator *(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x * val, this->y * val));
	}

	tml::XMUINT2EX_ operator *(const XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x * val.x, this->y * val.y));
	}

	tml::XMUINT2EX_ &operator *=(const UINT val)
	{
		this->x *= val;
		this->y *= val;

		return ((*this));
	}

	tml::XMUINT2EX_ &operator *=(const XMUINT2 &val)
	{
		this->x *= val.x;
		this->y *= val.y;

		return ((*this));
	}

	tml::XMUINT2EX_ operator /(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x / val, this->y / val));
	}

	tml::XMUINT2EX_ operator /(const XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x / val.x, this->y / val.y));
	}

	tml::XMUINT2EX_ &operator /=(const UINT val)
	{
		this->x /= val;
		this->y /= val;

		return ((*this));
	}

	tml::XMUINT2EX_ &operator /=(const XMUINT2 &val)
	{
		this->x /= val.x;
		this->y /= val.y;

		return ((*this));
	}
} XMUINT2EX;


/**
 * @brief XMUINT3EX構造体
 */
typedef struct XMUINT3EX_ : public XMUINT3
{
	XMUINT3EX_() :
		XMUINT3(0U, 0U, 0U)
	{
		return;
	}

	explicit XMUINT3EX_(const UINT x, const UINT y, const UINT z) :
		XMUINT3(x, y, z)
	{
		return;
	}

	explicit XMUINT3EX_(const UINT val) :
		XMUINT3(val, val, val)
	{
		return;
	}

	explicit XMUINT3EX_(const XMUINT3 &val) :
		XMUINT3(val.x, val.y, val.z)
	{
		return;
	}

	explicit XMUINT3EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		XMUINT3(1U, 0U, 0U)
	{
		return;
	}

	explicit XMUINT3EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		XMUINT3(0U, 1U, 0U)
	{
		return;
	}

	explicit XMUINT3EX_(const tml::ConstantUtil::XNAMATH::Z_VECTOR type) :
		XMUINT3(0U, 0U, 1U)
	{
		return;
	}

	tml::XMUINT3EX_ &operator =(const UINT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator =(const XMUINT3 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1U;
		this->y = 0U;
		this->z = 0U;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0U;
		this->y = 1U;
		this->z = 0U;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Z_VECTOR type)
	{
		this->x = 0U;
		this->y = 0U;
		this->z = 1U;

		return ((*this));
	}

	bool operator ==(const UINT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val));
	}

	bool operator ==(const XMUINT3 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z));
	}

	bool operator !=(const UINT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val));
	}

	bool operator !=(const XMUINT3 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z));
	}

	tml::XMUINT3EX_ operator +(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x + val, this->y + val, this->z + val));
	}

	tml::XMUINT3EX_ operator +(const XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x + val.x, this->y + val.y, this->z + val.z));
	}

	tml::XMUINT3EX_ &operator +=(const UINT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator +=(const XMUINT3 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;

		return ((*this));
	}

	tml::XMUINT3EX_ operator -(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x - val, this->y - val, this->z - val));
	}

	tml::XMUINT3EX_ operator -(const XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x - val.x, this->y - val.y, this->z - val.z));
	}

	tml::XMUINT3EX_ &operator -=(const UINT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator -=(const XMUINT3 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;

		return ((*this));
	}

	tml::XMUINT3EX_ operator *(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x * val, this->y * val, this->z * val));
	}

	tml::XMUINT3EX_ operator *(const XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x * val.x, this->y * val.y, this->z * val.z));
	}

	tml::XMUINT3EX_ &operator *=(const UINT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator *=(const XMUINT3 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;

		return ((*this));
	}

	tml::XMUINT3EX_ operator /(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x / val, this->y / val, this->z / val));
	}

	tml::XMUINT3EX_ operator /(const XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x / val.x, this->y / val.y, this->z / val.z));
	}

	tml::XMUINT3EX_ &operator /=(const UINT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;

		return ((*this));
	}

	tml::XMUINT3EX_ &operator /=(const XMUINT3 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;

		return ((*this));
	}
} XMUINT3EX;


/**
 * @brief XMUINT4EX構造体
 */
typedef struct XMUINT4EX_ : public XMUINT4
{
	XMUINT4EX_() :
		XMUINT4(0U, 0U, 0U, 0U)
	{
		return;
	}

	explicit XMUINT4EX_(const UINT x, const UINT y, const UINT z, const UINT w) :
		XMUINT4(x, y, z, w)
	{
		return;
	}

	explicit XMUINT4EX_(const UINT val) :
		XMUINT4(val, val, val, val)
	{
		return;
	}

	explicit XMUINT4EX_(const XMUINT4 &val) :
		XMUINT4(val.x, val.y, val.z, val.w)
	{
		return;
	}

	explicit XMUINT4EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type) :
		XMUINT4(0U, 0U, 0U, 1U)
	{
		return;
	}

	tml::XMUINT4EX_ &operator =(const UINT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;
		this->w = val;

		return ((*this));
	}

	tml::XMUINT4EX_ &operator =(const XMUINT4 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;
		this->w = val.w;

		return ((*this));
	}

	tml::XMUINT4EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type)
	{
		this->x = 0U;
		this->y = 0U;
		this->z = 0U;
		this->w = 1U;

		return ((*this));
	}

	bool operator ==(const UINT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val) && (this->w == val));
	}

	bool operator ==(const XMUINT4 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z) && (this->w == val.w));
	}

	bool operator !=(const UINT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val) || (this->w != val));
	}

	bool operator !=(const XMUINT4 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z) || (this->w != val.w));
	}

	tml::XMUINT4EX_ operator +(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x + val, this->y + val, this->z + val, this->w + val));
	}

	tml::XMUINT4EX_ operator +(const XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x + val.x, this->y + val.y, this->z + val.z, this->w + val.w));
	}

	tml::XMUINT4EX_ &operator +=(const UINT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	}

	tml::XMUINT4EX_ &operator +=(const XMUINT4 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;
		this->w += val.w;

		return ((*this));
	}

	tml::XMUINT4EX_ operator -(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x - val, this->y - val, this->z - val, this->w - val));
	}

	tml::XMUINT4EX_ operator -(const XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x - val.x, this->y - val.y, this->z - val.z, this->w - val.w));
	}

	tml::XMUINT4EX_ &operator -=(const UINT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;
		this->w -= val;

		return ((*this));
	}

	tml::XMUINT4EX_ &operator -=(const XMUINT4 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;
		this->w -= val.w;

		return ((*this));
	}

	tml::XMUINT4EX_ operator *(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x * val, this->y * val, this->z * val, this->w * val));
	}

	tml::XMUINT4EX_ operator *(const XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x * val.x, this->y * val.y, this->z * val.z, this->w * val.w));
	}

	tml::XMUINT4EX_ &operator *=(const UINT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;
		this->w *= val;

		return ((*this));
	}

	tml::XMUINT4EX_ &operator *=(const XMUINT4 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;
		this->w *= val.w;

		return ((*this));
	}

	tml::XMUINT4EX_ operator /(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x / val, this->y / val, this->z / val, this->w / val));
	}

	tml::XMUINT4EX_ operator /(const XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x / val.x, this->y / val.y, this->z / val.z, this->w / val.w));
	}

	tml::XMUINT4EX_ &operator /=(const UINT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;
		this->w /= val;

		return ((*this));
	}

	tml::XMUINT4EX_ &operator /=(const XMUINT4 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;
		this->w /= val.w;

		return ((*this));
	}
} XMUINT4EX;
}
