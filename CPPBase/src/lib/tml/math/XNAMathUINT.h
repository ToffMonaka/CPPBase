/**
 * @file
 * @brief XNAMathUINTヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_XNAMATH.h"


namespace tml {
/**
 * @brief XMUINT2EX構造体
 */
typedef struct XMUINT2EX_ : public DirectX::XMUINT2
{
	XMUINT2EX_() :
		DirectX::XMUINT2(0U, 0U)
	{
		return;
	};

	explicit XMUINT2EX_(const UINT x, const UINT y) :
		DirectX::XMUINT2(x, y)
	{
		return;
	};

	explicit XMUINT2EX_(const UINT val) :
		DirectX::XMUINT2(val, val)
	{
		return;
	};

	tml::XMUINT2EX_ &operator =(const UINT val)
	{
		this->x = val;
		this->y = val;

		return ((*this));
	};

	explicit XMUINT2EX_(const DirectX::XMUINT2 &val) :
		DirectX::XMUINT2(val.x, val.y)
	{
		return;
	};

	tml::XMUINT2EX_ &operator =(const DirectX::XMUINT2 &val)
	{
		this->x = val.x;
		this->y = val.y;

		return ((*this));
	};

	explicit XMUINT2EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		DirectX::XMUINT2(1U, 0U)
	{
		return;
	};

	tml::XMUINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1U;
		this->y = 0U;

		return ((*this));
	};

	explicit XMUINT2EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		DirectX::XMUINT2(0U, 1U)
	{
		return;
	};

	tml::XMUINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0U;
		this->y = 1U;

		return ((*this));
	};

	bool operator ==(const UINT val) const
	{
		return ((this->x == val) && (this->y == val));
	};

	bool operator ==(const DirectX::XMUINT2 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y));
	};

	bool operator !=(const UINT val) const
	{
		return ((this->x != val) || (this->y != val));
	};

	bool operator !=(const DirectX::XMUINT2 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y));
	};

	tml::XMUINT2EX_ operator +(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x + val, this->y + val));
	};

	tml::XMUINT2EX_ operator +(const DirectX::XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x + val.x, this->y + val.y));
	};

	tml::XMUINT2EX_ &operator +=(const UINT val)
	{
		this->x += val;
		this->y += val;

		return ((*this));
	};

	tml::XMUINT2EX_ &operator +=(const DirectX::XMUINT2 &val)
	{
		this->x += val.x;
		this->y += val.y;

		return ((*this));
	};

	tml::XMUINT2EX_ operator -(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x - val, this->y - val));
	};

	tml::XMUINT2EX_ operator -(const DirectX::XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x - val.x, this->y - val.y));
	};

	tml::XMUINT2EX_ &operator -=(const UINT val)
	{
		this->x -= val;
		this->y -= val;

		return ((*this));
	};

	tml::XMUINT2EX_ &operator -=(const DirectX::XMUINT2 &val)
	{
		this->x -= val.x;
		this->y -= val.y;

		return ((*this));
	};

	tml::XMUINT2EX_ operator *(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x * val, this->y * val));
	};

	tml::XMUINT2EX_ operator *(const DirectX::XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x * val.x, this->y * val.y));
	};

	tml::XMUINT2EX_ &operator *=(const UINT val)
	{
		this->x *= val;
		this->y *= val;

		return ((*this));
	};

	tml::XMUINT2EX_ &operator *=(const DirectX::XMUINT2 &val)
	{
		this->x *= val.x;
		this->y *= val.y;

		return ((*this));
	};

	tml::XMUINT2EX_ operator /(const UINT val) const
	{
		return (tml::XMUINT2EX_(this->x / val, this->y / val));
	};

	tml::XMUINT2EX_ operator /(const DirectX::XMUINT2 &val) const
	{
		return (tml::XMUINT2EX_(this->x / val.x, this->y / val.y));
	};

	tml::XMUINT2EX_ &operator /=(const UINT val)
	{
		this->x /= val;
		this->y /= val;

		return ((*this));
	};

	tml::XMUINT2EX_ &operator /=(const DirectX::XMUINT2 &val)
	{
		this->x /= val.x;
		this->y /= val.y;

		return ((*this));
	};

	UINT GetHalfX(void) const
	{
		return (this->x >> 1);
	};

	UINT GetHalfY(void) const
	{
		return (this->y >> 1);
	};
} XMUINT2EX;


/**
 * @brief XMUINT3EX構造体
 */
typedef struct XMUINT3EX_ : public DirectX::XMUINT3
{
	XMUINT3EX_() :
		DirectX::XMUINT3(0U, 0U, 0U)
	{
		return;
	};

	explicit XMUINT3EX_(const UINT x, const UINT y, const UINT z) :
		DirectX::XMUINT3(x, y, z)
	{
		return;
	};

	explicit XMUINT3EX_(const UINT val) :
		DirectX::XMUINT3(val, val, val)
	{
		return;
	};

	tml::XMUINT3EX_ &operator =(const UINT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;

		return ((*this));
	};

	explicit XMUINT3EX_(const DirectX::XMUINT3 &val) :
		DirectX::XMUINT3(val.x, val.y, val.z)
	{
		return;
	};

	tml::XMUINT3EX_ &operator =(const DirectX::XMUINT3 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;

		return ((*this));
	};

	explicit XMUINT3EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		DirectX::XMUINT3(1U, 0U, 0U)
	{
		return;
	};

	tml::XMUINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1U;
		this->y = 0U;
		this->z = 0U;

		return ((*this));
	};

	explicit XMUINT3EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		DirectX::XMUINT3(0U, 1U, 0U)
	{
		return;
	};

	tml::XMUINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0U;
		this->y = 1U;
		this->z = 0U;

		return ((*this));
	};

	explicit XMUINT3EX_(const tml::ConstantUtil::XNAMATH::Z_VECTOR type) :
		DirectX::XMUINT3(0U, 0U, 1U)
	{
		return;
	};

	tml::XMUINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Z_VECTOR type)
	{
		this->x = 0U;
		this->y = 0U;
		this->z = 1U;

		return ((*this));
	};

	bool operator ==(const UINT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val));
	};

	bool operator ==(const DirectX::XMUINT3 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z));
	};

	bool operator !=(const UINT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val));
	};

	bool operator !=(const DirectX::XMUINT3 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z));
	};

	tml::XMUINT3EX_ operator +(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x + val, this->y + val, this->z + val));
	};

	tml::XMUINT3EX_ operator +(const DirectX::XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x + val.x, this->y + val.y, this->z + val.z));
	};

	tml::XMUINT3EX_ &operator +=(const UINT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	};

	tml::XMUINT3EX_ &operator +=(const DirectX::XMUINT3 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;

		return ((*this));
	};

	tml::XMUINT3EX_ operator -(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x - val, this->y - val, this->z - val));
	};

	tml::XMUINT3EX_ operator -(const DirectX::XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x - val.x, this->y - val.y, this->z - val.z));
	};

	tml::XMUINT3EX_ &operator -=(const UINT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;

		return ((*this));
	};

	tml::XMUINT3EX_ &operator -=(const DirectX::XMUINT3 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;

		return ((*this));
	};

	tml::XMUINT3EX_ operator *(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x * val, this->y * val, this->z * val));
	};

	tml::XMUINT3EX_ operator *(const DirectX::XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x * val.x, this->y * val.y, this->z * val.z));
	};

	tml::XMUINT3EX_ &operator *=(const UINT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;

		return ((*this));
	};

	tml::XMUINT3EX_ &operator *=(const DirectX::XMUINT3 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;

		return ((*this));
	};

	tml::XMUINT3EX_ operator /(const UINT val) const
	{
		return (tml::XMUINT3EX_(this->x / val, this->y / val, this->z / val));
	};

	tml::XMUINT3EX_ operator /(const DirectX::XMUINT3 &val) const
	{
		return (tml::XMUINT3EX_(this->x / val.x, this->y / val.y, this->z / val.z));
	};

	tml::XMUINT3EX_ &operator /=(const UINT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;

		return ((*this));
	};

	tml::XMUINT3EX_ &operator /=(const DirectX::XMUINT3 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;

		return ((*this));
	};

	UINT GetHalfX(void) const
	{
		return (this->x >> 1);
	};

	UINT GetHalfY(void) const
	{
		return (this->y >> 1);
	};

	UINT GetHalfZ(void) const
	{
		return (this->z >> 1);
	};
} XMUINT3EX;


/**
 * @brief XMUINT4EX構造体
 */
typedef struct XMUINT4EX_ : public DirectX::XMUINT4
{
	XMUINT4EX_() :
		DirectX::XMUINT4(0U, 0U, 0U, 0U)
	{
		return;
	};

	explicit XMUINT4EX_(const UINT x, const UINT y, const UINT z, const UINT w) :
		DirectX::XMUINT4(x, y, z, w)
	{
		return;
	};

	explicit XMUINT4EX_(const UINT val) :
		DirectX::XMUINT4(val, val, val, val)
	{
		return;
	};

	tml::XMUINT4EX_ &operator =(const UINT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;
		this->w = val;

		return ((*this));
	};

	explicit XMUINT4EX_(const DirectX::XMUINT4 &val) :
		DirectX::XMUINT4(val.x, val.y, val.z, val.w)
	{
		return;
	};

	tml::XMUINT4EX_ &operator =(const DirectX::XMUINT4 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;
		this->w = val.w;

		return ((*this));
	};

	explicit XMUINT4EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type) :
		DirectX::XMUINT4(0U, 0U, 0U, 1U)
	{
		return;
	};

	tml::XMUINT4EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type)
	{
		this->x = 0U;
		this->y = 0U;
		this->z = 0U;
		this->w = 1U;

		return ((*this));
	};

	bool operator ==(const UINT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val) && (this->w == val));
	};

	bool operator ==(const DirectX::XMUINT4 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z) && (this->w == val.w));
	};

	bool operator !=(const UINT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val) || (this->w != val));
	};

	bool operator !=(const DirectX::XMUINT4 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z) || (this->w != val.w));
	};

	tml::XMUINT4EX_ operator +(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x + val, this->y + val, this->z + val, this->w + val));
	};

	tml::XMUINT4EX_ operator +(const DirectX::XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x + val.x, this->y + val.y, this->z + val.z, this->w + val.w));
	};

	tml::XMUINT4EX_ &operator +=(const UINT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	};

	tml::XMUINT4EX_ &operator +=(const DirectX::XMUINT4 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;
		this->w += val.w;

		return ((*this));
	};

	tml::XMUINT4EX_ operator -(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x - val, this->y - val, this->z - val, this->w - val));
	};

	tml::XMUINT4EX_ operator -(const DirectX::XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x - val.x, this->y - val.y, this->z - val.z, this->w - val.w));
	};

	tml::XMUINT4EX_ &operator -=(const UINT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;
		this->w -= val;

		return ((*this));
	};

	tml::XMUINT4EX_ &operator -=(const DirectX::XMUINT4 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;
		this->w -= val.w;

		return ((*this));
	};

	tml::XMUINT4EX_ operator *(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x * val, this->y * val, this->z * val, this->w * val));
	};

	tml::XMUINT4EX_ operator *(const DirectX::XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x * val.x, this->y * val.y, this->z * val.z, this->w * val.w));
	};

	tml::XMUINT4EX_ &operator *=(const UINT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;
		this->w *= val;

		return ((*this));
	};

	tml::XMUINT4EX_ &operator *=(const DirectX::XMUINT4 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;
		this->w *= val.w;

		return ((*this));
	};

	tml::XMUINT4EX_ operator /(const UINT val) const
	{
		return (tml::XMUINT4EX_(this->x / val, this->y / val, this->z / val, this->w / val));
	};

	tml::XMUINT4EX_ operator /(const DirectX::XMUINT4 &val) const
	{
		return (tml::XMUINT4EX_(this->x / val.x, this->y / val.y, this->z / val.z, this->w / val.w));
	};

	tml::XMUINT4EX_ &operator /=(const UINT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;
		this->w /= val;

		return ((*this));
	};

	tml::XMUINT4EX_ &operator /=(const DirectX::XMUINT4 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;
		this->w /= val.w;

		return ((*this));
	};

	UINT GetHalfX(void) const
	{
		return (this->x >> 1);
	};

	UINT GetHalfY(void) const
	{
		return (this->y >> 1);
	};

	UINT GetHalfZ(void) const
	{
		return (this->z >> 1);
	};

	UINT GetHalfW(void) const
	{
		return (this->w >> 1);
	};
} XMUINT4EX;
}
