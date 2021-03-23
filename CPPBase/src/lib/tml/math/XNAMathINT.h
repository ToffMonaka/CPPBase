/**
 * @file
 * @brief XNAMathINTヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_XNAMATH.h"


namespace tml {
/**
 * @brief XMINT2EX構造体
 */
typedef struct XMINT2EX_ : public DirectX::XMINT2
{
	XMINT2EX_() :
		DirectX::XMINT2(0, 0)
	{
		return;
	};

	explicit XMINT2EX_(const INT x, const INT y) :
		DirectX::XMINT2(x, y)
	{
		return;
	};

	explicit XMINT2EX_(const INT val) :
		DirectX::XMINT2(val, val)
	{
		return;
	};

	tml::XMINT2EX_ &operator =(const INT val)
	{
		this->x = val;
		this->y = val;

		return ((*this));
	};

	explicit XMINT2EX_(const DirectX::XMINT2 &val) :
		DirectX::XMINT2(val.x, val.y)
	{
		return;
	};

	tml::XMINT2EX_ &operator =(const DirectX::XMINT2 &val)
	{
		this->x = val.x;
		this->y = val.y;

		return ((*this));
	};

	explicit XMINT2EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		DirectX::XMINT2(1, 0)
	{
		return;
	};

	tml::XMINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1;
		this->y = 0;

		return ((*this));
	};

	explicit XMINT2EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		DirectX::XMINT2(0, 1)
	{
		return;
	};

	tml::XMINT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0;
		this->y = 1;

		return ((*this));
	};

	bool operator ==(const INT val) const
	{
		return ((this->x == val) && (this->y == val));
	};

	bool operator ==(const DirectX::XMINT2 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y));
	};

	bool operator !=(const INT val) const
	{
		return ((this->x != val) || (this->y != val));
	};

	bool operator !=(const DirectX::XMINT2 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y));
	};

	tml::XMINT2EX_ operator +(const INT val) const
	{
		return (tml::XMINT2EX_(this->x + val, this->y + val));
	};

	tml::XMINT2EX_ operator +(const DirectX::XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x + val.x, this->y + val.y));
	};

	tml::XMINT2EX_ &operator +=(const INT val)
	{
		this->x += val;
		this->y += val;

		return ((*this));
	};

	tml::XMINT2EX_ &operator +=(const DirectX::XMINT2 &val)
	{
		this->x += val.x;
		this->y += val.y;

		return ((*this));
	};

	tml::XMINT2EX_ operator -(const INT val) const
	{
		return (tml::XMINT2EX_(this->x - val, this->y - val));
	};

	tml::XMINT2EX_ operator -(const DirectX::XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x - val.x, this->y - val.y));
	};

	tml::XMINT2EX_ &operator -=(const INT val)
	{
		this->x -= val;
		this->y -= val;

		return ((*this));
	};

	tml::XMINT2EX_ &operator -=(const DirectX::XMINT2 &val)
	{
		this->x -= val.x;
		this->y -= val.y;

		return ((*this));
	};

	tml::XMINT2EX_ operator *(const INT val) const
	{
		return (tml::XMINT2EX_(this->x * val, this->y * val));
	};

	tml::XMINT2EX_ operator *(const DirectX::XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x * val.x, this->y * val.y));
	};

	tml::XMINT2EX_ &operator *=(const INT val)
	{
		this->x *= val;
		this->y *= val;

		return ((*this));
	};

	tml::XMINT2EX_ &operator *=(const DirectX::XMINT2 &val)
	{
		this->x *= val.x;
		this->y *= val.y;

		return ((*this));
	};

	tml::XMINT2EX_ operator /(const INT val) const
	{
		return (tml::XMINT2EX_(this->x / val, this->y / val));
	};

	tml::XMINT2EX_ operator /(const DirectX::XMINT2 &val) const
	{
		return (tml::XMINT2EX_(this->x / val.x, this->y / val.y));
	};

	tml::XMINT2EX_ &operator /=(const INT val)
	{
		this->x /= val;
		this->y /= val;

		return ((*this));
	};

	tml::XMINT2EX_ &operator /=(const DirectX::XMINT2 &val)
	{
		this->x /= val.x;
		this->y /= val.y;

		return ((*this));
	};

	tml::XMINT2EX_ operator -(void)
	{
		return (tml::XMINT2EX_(-this->x, -this->y));
	};
} XMINT2EX;


/**
 * @brief XMINT3EX構造体
 */
typedef struct XMINT3EX_ : public DirectX::XMINT3
{
	XMINT3EX_() :
		DirectX::XMINT3(0, 0, 0)
	{
		return;
	};

	explicit XMINT3EX_(const INT x, const INT y, const INT z) :
		DirectX::XMINT3(x, y, z)
	{
		return;
	};

	explicit XMINT3EX_(const INT val) :
		DirectX::XMINT3(val, val, val)
	{
		return;
	};

	tml::XMINT3EX_ &operator =(const INT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;

		return ((*this));
	};

	explicit XMINT3EX_(const DirectX::XMINT3 &val) :
		DirectX::XMINT3(val.x, val.y, val.z)
	{
		return;
	};

	tml::XMINT3EX_ &operator =(const DirectX::XMINT3 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;

		return ((*this));
	};

	explicit XMINT3EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		DirectX::XMINT3(1, 0, 0)
	{
		return;
	};

	tml::XMINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1;
		this->y = 0;
		this->z = 0;

		return ((*this));
	};

	explicit XMINT3EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		DirectX::XMINT3(0, 1, 0)
	{
		return;
	};

	tml::XMINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0;
		this->y = 1;
		this->z = 0;

		return ((*this));
	};

	explicit XMINT3EX_(const tml::ConstantUtil::XNAMATH::Z_VECTOR type) :
		DirectX::XMINT3(0, 0, 1)
	{
		return;
	};

	tml::XMINT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Z_VECTOR type)
	{
		this->x = 0;
		this->y = 0;
		this->z = 1;

		return ((*this));
	};

	bool operator ==(const INT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val));
	};

	bool operator ==(const DirectX::XMINT3 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z));
	};

	bool operator !=(const INT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val));
	};

	bool operator !=(const DirectX::XMINT3 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z));
	};

	tml::XMINT3EX_ operator +(const INT val) const
	{
		return (tml::XMINT3EX_(this->x + val, this->y + val, this->z + val));
	};

	tml::XMINT3EX_ operator +(const DirectX::XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x + val.x, this->y + val.y, this->z + val.z));
	};

	tml::XMINT3EX_ &operator +=(const INT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	};

	tml::XMINT3EX_ &operator +=(const DirectX::XMINT3 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;

		return ((*this));
	};

	tml::XMINT3EX_ operator -(const INT val) const
	{
		return (tml::XMINT3EX_(this->x - val, this->y - val, this->z - val));
	};

	tml::XMINT3EX_ operator -(const DirectX::XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x - val.x, this->y - val.y, this->z - val.z));
	};

	tml::XMINT3EX_ &operator -=(const INT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;

		return ((*this));
	};

	tml::XMINT3EX_ &operator -=(const DirectX::XMINT3 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;

		return ((*this));
	};

	tml::XMINT3EX_ operator *(const INT val) const
	{
		return (tml::XMINT3EX_(this->x * val, this->y * val, this->z * val));
	};

	tml::XMINT3EX_ operator *(const DirectX::XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x * val.x, this->y * val.y, this->z * val.z));
	};

	tml::XMINT3EX_ &operator *=(const INT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;

		return ((*this));
	};

	tml::XMINT3EX_ &operator *=(const DirectX::XMINT3 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;

		return ((*this));
	};

	tml::XMINT3EX_ operator /(const INT val) const
	{
		return (tml::XMINT3EX_(this->x / val, this->y / val, this->z / val));
	};

	tml::XMINT3EX_ operator /(const DirectX::XMINT3 &val) const
	{
		return (tml::XMINT3EX_(this->x / val.x, this->y / val.y, this->z / val.z));
	};

	tml::XMINT3EX_ &operator /=(const INT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;

		return ((*this));
	};

	tml::XMINT3EX_ &operator /=(const DirectX::XMINT3 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;

		return ((*this));
	};

	tml::XMINT3EX_ operator -(void)
	{
		return (tml::XMINT3EX_(-this->x, -this->y, -this->z));
	};
} XMINT3EX;


/**
 * @brief XMINT4EX構造体
 */
typedef struct XMINT4EX_ : public DirectX::XMINT4
{
	XMINT4EX_() :
		DirectX::XMINT4(0, 0, 0, 0)
	{
		return;
	};

	explicit XMINT4EX_(const INT x, const INT y, const INT z, const INT w) :
		DirectX::XMINT4(x, y, z, w)
	{
		return;
	};

	explicit XMINT4EX_(const INT val) :
		DirectX::XMINT4(val, val, val, val)
	{
		return;
	};

	tml::XMINT4EX_ &operator =(const INT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;
		this->w = val;

		return ((*this));
	};

	explicit XMINT4EX_(const DirectX::XMINT4 &val) :
		DirectX::XMINT4(val.x, val.y, val.z, val.w)
	{
		return;
	};

	tml::XMINT4EX_ &operator =(const DirectX::XMINT4 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;
		this->w = val.w;

		return ((*this));
	};

	explicit XMINT4EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type) :
		DirectX::XMINT4(0, 0, 0, 1)
	{
		return;
	};

	tml::XMINT4EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type)
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;

		return ((*this));
	};

	bool operator ==(const INT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val) && (this->w == val));
	};

	bool operator ==(const DirectX::XMINT4 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z) && (this->w == val.w));
	};

	bool operator !=(const INT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val) || (this->w != val));
	};

	bool operator !=(const DirectX::XMINT4 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z) || (this->w != val.w));
	};

	tml::XMINT4EX_ operator +(const INT val) const
	{
		return (tml::XMINT4EX_(this->x + val, this->y + val, this->z + val, this->w + val));
	};

	tml::XMINT4EX_ operator +(const DirectX::XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x + val.x, this->y + val.y, this->z + val.z, this->w + val.w));
	};

	tml::XMINT4EX_ &operator +=(const INT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	};

	tml::XMINT4EX_ &operator +=(const DirectX::XMINT4 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;
		this->w += val.w;

		return ((*this));
	};

	tml::XMINT4EX_ operator -(const INT val) const
	{
		return (tml::XMINT4EX_(this->x - val, this->y - val, this->z - val, this->w - val));
	};

	tml::XMINT4EX_ operator -(const DirectX::XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x - val.x, this->y - val.y, this->z - val.z, this->w - val.w));
	};

	tml::XMINT4EX_ &operator -=(const INT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;
		this->w -= val;

		return ((*this));
	};

	tml::XMINT4EX_ &operator -=(const DirectX::XMINT4 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;
		this->w -= val.w;

		return ((*this));
	};

	tml::XMINT4EX_ operator *(const INT val) const
	{
		return (tml::XMINT4EX_(this->x * val, this->y * val, this->z * val, this->w * val));
	};

	tml::XMINT4EX_ operator *(const DirectX::XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x * val.x, this->y * val.y, this->z * val.z, this->w * val.w));
	};

	tml::XMINT4EX_ &operator *=(const INT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;
		this->w *= val;

		return ((*this));
	};

	tml::XMINT4EX_ &operator *=(const DirectX::XMINT4 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;
		this->w *= val.w;

		return ((*this));
	};

	tml::XMINT4EX_ operator /(const INT val) const
	{
		return (tml::XMINT4EX_(this->x / val, this->y / val, this->z / val, this->w / val));
	};

	tml::XMINT4EX_ operator /(const DirectX::XMINT4 &val) const
	{
		return (tml::XMINT4EX_(this->x / val.x, this->y / val.y, this->z / val.z, this->w / val.w));
	};

	tml::XMINT4EX_ &operator /=(const INT val)
	{
		this->x /= val;
		this->y /= val;
		this->z /= val;
		this->w /= val;

		return ((*this));
	};

	tml::XMINT4EX_ &operator /=(const DirectX::XMINT4 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;
		this->w /= val.w;

		return ((*this));
	};

	tml::XMINT4EX_ operator -(void)
	{
		return (tml::XMINT4EX_(-this->x, -this->y, -this->z, -this->w));
	};
} XMINT4EX;
}
