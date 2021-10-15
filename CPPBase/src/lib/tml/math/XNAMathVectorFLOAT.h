/**
 * @file
 * @brief XNAMathFLOATヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_XNAMATH.h"


namespace tml {
/**
 * @brief XMFLOAT2EX構造体
 */
typedef struct XMFLOAT2EX_ : public DirectX::XMFLOAT2
{
	XMFLOAT2EX_() :
		DirectX::XMFLOAT2(0.0f, 0.0f)
	{
		return;
	};

	explicit XMFLOAT2EX_(const FLOAT x, const FLOAT y) :
		DirectX::XMFLOAT2(x, y)
	{
		return;
	};

	explicit XMFLOAT2EX_(const FLOAT val) :
		DirectX::XMFLOAT2(val, val)
	{
		return;
	};

	tml::XMFLOAT2EX_ &operator =(const FLOAT val)
	{
		this->x = val;
		this->y = val;

		return ((*this));
	};

	explicit XMFLOAT2EX_(const DirectX::XMFLOAT2 &val) :
		DirectX::XMFLOAT2(val.x, val.y)
	{
		return;
	};

	tml::XMFLOAT2EX_ &operator =(const DirectX::XMFLOAT2 &val)
	{
		this->x = val.x;
		this->y = val.y;

		return ((*this));
	};

	explicit XMFLOAT2EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		DirectX::XMFLOAT2(1.0f, 0.0f)
	{
		return;
	};

	tml::XMFLOAT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1.0f;
		this->y = 0.0f;

		return ((*this));
	};

	explicit XMFLOAT2EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		DirectX::XMFLOAT2(0.0f, 1.0f)
	{
		return;
	};

	tml::XMFLOAT2EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0.0f;
		this->y = 1.0f;

		return ((*this));
	};

	bool operator ==(const FLOAT val) const
	{
		return ((this->x == val) && (this->y == val));
	};

	bool operator ==(const DirectX::XMFLOAT2 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y));
	};

	bool operator !=(const FLOAT val) const
	{
		return ((this->x != val) || (this->y != val));
	};

	bool operator !=(const DirectX::XMFLOAT2 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y));
	};

	tml::XMFLOAT2EX_ operator +(const FLOAT val) const
	{
		return (tml::XMFLOAT2EX_(this->x + val, this->y + val));
	};

	tml::XMFLOAT2EX_ operator +(const DirectX::XMFLOAT2 &val) const
	{
		return (tml::XMFLOAT2EX_(this->x + val.x, this->y + val.y));
	};

	tml::XMFLOAT2EX_ &operator +=(const FLOAT val)
	{
		this->x += val;
		this->y += val;

		return ((*this));
	};

	tml::XMFLOAT2EX_ &operator +=(const DirectX::XMFLOAT2 &val)
	{
		this->x += val.x;
		this->y += val.y;

		return ((*this));
	};

	tml::XMFLOAT2EX_ operator -(const FLOAT val) const
	{
		return (tml::XMFLOAT2EX_(this->x - val, this->y - val));
	};

	tml::XMFLOAT2EX_ operator -(const DirectX::XMFLOAT2 &val) const
	{
		return (tml::XMFLOAT2EX_(this->x - val.x, this->y - val.y));
	};

	tml::XMFLOAT2EX_ &operator -=(const FLOAT val)
	{
		this->x -= val;
		this->y -= val;

		return ((*this));
	};

	tml::XMFLOAT2EX_ &operator -=(const DirectX::XMFLOAT2 &val)
	{
		this->x -= val.x;
		this->y -= val.y;

		return ((*this));
	};

	tml::XMFLOAT2EX_ operator *(const FLOAT val) const
	{
		return (tml::XMFLOAT2EX_(this->x * val, this->y * val));
	};

	tml::XMFLOAT2EX_ operator *(const DirectX::XMFLOAT2 &val) const
	{
		return (tml::XMFLOAT2EX_(this->x * val.x, this->y * val.y));
	};

	tml::XMFLOAT2EX_ &operator *=(const FLOAT val)
	{
		this->x *= val;
		this->y *= val;

		return ((*this));
	};

	tml::XMFLOAT2EX_ &operator *=(const DirectX::XMFLOAT2 &val)
	{
		this->x *= val.x;
		this->y *= val.y;

		return ((*this));
	};

	tml::XMFLOAT2EX_ operator /(const FLOAT val) const
	{
		auto tmp_val = 1.0f / val;

		return (tml::XMFLOAT2EX_(this->x * tmp_val, this->y * tmp_val));
	};

	tml::XMFLOAT2EX_ operator /(const DirectX::XMFLOAT2 &val) const
	{
		return (tml::XMFLOAT2EX_(this->x / val.x, this->y / val.y));
	};

	tml::XMFLOAT2EX_ &operator /=(const FLOAT val)
	{
		auto tmp_val = 1.0f / val;

		this->x *= tmp_val;
		this->y *= tmp_val;

		return ((*this));
	};

	tml::XMFLOAT2EX_ &operator /=(const DirectX::XMFLOAT2 &val)
	{
		this->x /= val.x;
		this->y /= val.y;

		return ((*this));
	};

	tml::XMFLOAT2EX_ operator -(void)
	{
		return (tml::XMFLOAT2EX_(-this->x, -this->y));
	};

	float GetHalfX(void) const
	{
		return (this->x * 0.5f);
	};

	float GetHalfY(void) const
	{
		return (this->y * 0.5f);
	};
} XMFLOAT2EX;


/**
 * @brief XMFLOAT3EX構造体
 */
typedef struct XMFLOAT3EX_ : public DirectX::XMFLOAT3
{
	XMFLOAT3EX_() :
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)
	{
		return;
	};

	explicit XMFLOAT3EX_(const FLOAT x, const FLOAT y, const FLOAT z) :
		DirectX::XMFLOAT3(x, y, z)
	{
		return;
	};

	explicit XMFLOAT3EX_(const FLOAT val) :
		DirectX::XMFLOAT3(val, val, val)
	{
		return;
	};

	tml::XMFLOAT3EX_ &operator =(const FLOAT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;

		return ((*this));
	};

	explicit XMFLOAT3EX_(const DirectX::XMFLOAT3 &val) :
		DirectX::XMFLOAT3(val.x, val.y, val.z)
	{
		return;
	};

	tml::XMFLOAT3EX_ &operator =(const DirectX::XMFLOAT3 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;

		return ((*this));
	};

	explicit XMFLOAT3EX_(const tml::ConstantUtil::XNAMATH::X_VECTOR type) :
		DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)
	{
		return;
	};

	tml::XMFLOAT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::X_VECTOR type)
	{
		this->x = 1.0f;
		this->y = 0.0f;
		this->z = 0.0f;

		return ((*this));
	};

	explicit XMFLOAT3EX_(const tml::ConstantUtil::XNAMATH::Y_VECTOR type) :
		DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)
	{
		return;
	};

	tml::XMFLOAT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Y_VECTOR type)
	{
		this->x = 0.0f;
		this->y = 1.0f;
		this->z = 0.0f;

		return ((*this));
	};

	explicit XMFLOAT3EX_(const tml::ConstantUtil::XNAMATH::Z_VECTOR type) :
		DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)
	{
		return;
	};

	tml::XMFLOAT3EX_ &operator =(const tml::ConstantUtil::XNAMATH::Z_VECTOR type)
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 1.0f;

		return ((*this));
	};

	bool operator ==(const FLOAT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val));
	};

	bool operator ==(const DirectX::XMFLOAT3 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z));
	};

	bool operator !=(const FLOAT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val));
	};

	bool operator !=(const DirectX::XMFLOAT3 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z));
	};

	tml::XMFLOAT3EX_ operator +(const FLOAT val) const
	{
		return (tml::XMFLOAT3EX_(this->x + val, this->y + val, this->z + val));
	};

	tml::XMFLOAT3EX_ operator +(const DirectX::XMFLOAT3 &val) const
	{
		return (tml::XMFLOAT3EX_(this->x + val.x, this->y + val.y, this->z + val.z));
	};

	tml::XMFLOAT3EX_ &operator +=(const FLOAT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	};

	tml::XMFLOAT3EX_ &operator +=(const DirectX::XMFLOAT3 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;

		return ((*this));
	};

	tml::XMFLOAT3EX_ operator -(const FLOAT val) const
	{
		return (tml::XMFLOAT3EX_(this->x - val, this->y - val, this->z - val));
	};

	tml::XMFLOAT3EX_ operator -(const DirectX::XMFLOAT3 &val) const
	{
		return (tml::XMFLOAT3EX_(this->x - val.x, this->y - val.y, this->z - val.z));
	};

	tml::XMFLOAT3EX_ &operator -=(const FLOAT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;

		return ((*this));
	};

	tml::XMFLOAT3EX_ &operator -=(const DirectX::XMFLOAT3 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;

		return ((*this));
	};

	tml::XMFLOAT3EX_ operator *(const FLOAT val) const
	{
		return (tml::XMFLOAT3EX_(this->x * val, this->y * val, this->z * val));
	};

	tml::XMFLOAT3EX_ operator *(const DirectX::XMFLOAT3 &val) const
	{
		return (tml::XMFLOAT3EX_(this->x * val.x, this->y * val.y, this->z * val.z));
	};

	tml::XMFLOAT3EX_ &operator *=(const FLOAT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;

		return ((*this));
	};

	tml::XMFLOAT3EX_ &operator *=(const DirectX::XMFLOAT3 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;

		return ((*this));
	};

	tml::XMFLOAT3EX_ operator /(const FLOAT val) const
	{
		auto tmp_val = 1.0f / val;

		return (tml::XMFLOAT3EX_(this->x * tmp_val, this->y * tmp_val, this->z * tmp_val));
	};

	tml::XMFLOAT3EX_ operator /(const DirectX::XMFLOAT3 &val) const
	{
		return (tml::XMFLOAT3EX_(this->x / val.x, this->y / val.y, this->z / val.z));
	};

	tml::XMFLOAT3EX_ &operator /=(const FLOAT val)
	{
		auto tmp_val = 1.0f / val;

		this->x *= tmp_val;
		this->y *= tmp_val;
		this->z *= tmp_val;

		return ((*this));
	};

	tml::XMFLOAT3EX_ &operator /=(const DirectX::XMFLOAT3 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;

		return ((*this));
	};

	tml::XMFLOAT3EX_ operator -(void)
	{
		return (tml::XMFLOAT3EX_(-this->x, -this->y, -this->z));
	};

	float GetHalfX(void) const
	{
		return (this->x * 0.5f);
	};

	float GetHalfY(void) const
	{
		return (this->y * 0.5f);
	};

	float GetHalfZ(void) const
	{
		return (this->z * 0.5f);
	};
} XMFLOAT3EX;


/**
 * @brief XMFLOAT4EX構造体
 */
typedef struct XMFLOAT4EX_ : public DirectX::XMFLOAT4
{
	XMFLOAT4EX_() :
		DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
	{
		return;
	};

	explicit XMFLOAT4EX_(const FLOAT x, const FLOAT y, const FLOAT z, const FLOAT w) :
		DirectX::XMFLOAT4(x, y, z, w)
	{
		return;
	};

	explicit XMFLOAT4EX_(const FLOAT val) :
		DirectX::XMFLOAT4(val, val, val, val)
	{
		return;
	};

	tml::XMFLOAT4EX_ &operator =(const FLOAT val)
	{
		this->x = val;
		this->y = val;
		this->z = val;
		this->w = val;

		return ((*this));
	};

	explicit XMFLOAT4EX_(const DirectX::XMFLOAT4 &val) :
		DirectX::XMFLOAT4(val.x, val.y, val.z, val.w)
	{
		return;
	};

	tml::XMFLOAT4EX_ &operator =(const DirectX::XMFLOAT4 &val)
	{
		this->x = val.x;
		this->y = val.y;
		this->z = val.z;
		this->w = val.w;

		return ((*this));
	};

	explicit XMFLOAT4EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type) :
		DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
	{
		return;
	};

	tml::XMFLOAT4EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR type)
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 1.0f;

		return ((*this));
	};

	bool operator ==(const FLOAT val) const
	{
		return ((this->x == val) && (this->y == val) && (this->z == val) && (this->w == val));
	};

	bool operator ==(const DirectX::XMFLOAT4 &val) const
	{
		return ((this->x == val.x) && (this->y == val.y) && (this->z == val.z) && (this->w == val.w));
	};

	bool operator !=(const FLOAT val) const
	{
		return ((this->x != val) || (this->y != val) || (this->z != val) || (this->w != val));
	};

	bool operator !=(const DirectX::XMFLOAT4 &val) const
	{
		return ((this->x != val.x) || (this->y != val.y) || (this->z != val.z) || (this->w != val.w));
	};

	tml::XMFLOAT4EX_ operator +(const FLOAT val) const
	{
		return (tml::XMFLOAT4EX_(this->x + val, this->y + val, this->z + val, this->w + val));
	};

	tml::XMFLOAT4EX_ operator +(const DirectX::XMFLOAT4 &val) const
	{
		return (tml::XMFLOAT4EX_(this->x + val.x, this->y + val.y, this->z + val.z, this->w + val.w));
	};

	tml::XMFLOAT4EX_ &operator +=(const FLOAT val)
	{
		this->x += val;
		this->y += val;
		this->z += val;

		return ((*this));
	};

	tml::XMFLOAT4EX_ &operator +=(const DirectX::XMFLOAT4 &val)
	{
		this->x += val.x;
		this->y += val.y;
		this->z += val.z;
		this->w += val.w;

		return ((*this));
	};

	tml::XMFLOAT4EX_ operator -(const FLOAT val) const
	{
		return (tml::XMFLOAT4EX_(this->x - val, this->y - val, this->z - val, this->w - val));
	};

	tml::XMFLOAT4EX_ operator -(const DirectX::XMFLOAT4 &val) const
	{
		return (tml::XMFLOAT4EX_(this->x - val.x, this->y - val.y, this->z - val.z, this->w - val.w));
	};

	tml::XMFLOAT4EX_ &operator -=(const FLOAT val)
	{
		this->x -= val;
		this->y -= val;
		this->z -= val;
		this->w -= val;

		return ((*this));
	};

	tml::XMFLOAT4EX_ &operator -=(const DirectX::XMFLOAT4 &val)
	{
		this->x -= val.x;
		this->y -= val.y;
		this->z -= val.z;
		this->w -= val.w;

		return ((*this));
	};

	tml::XMFLOAT4EX_ operator *(const FLOAT val) const
	{
		return (tml::XMFLOAT4EX_(this->x * val, this->y * val, this->z * val, this->w * val));
	};

	tml::XMFLOAT4EX_ operator *(const DirectX::XMFLOAT4 &val) const
	{
		return (tml::XMFLOAT4EX_(this->x * val.x, this->y * val.y, this->z * val.z, this->w * val.w));
	};

	tml::XMFLOAT4EX_ &operator *=(const FLOAT val)
	{
		this->x *= val;
		this->y *= val;
		this->z *= val;
		this->w *= val;

		return ((*this));
	};

	tml::XMFLOAT4EX_ &operator *=(const DirectX::XMFLOAT4 &val)
	{
		this->x *= val.x;
		this->y *= val.y;
		this->z *= val.z;
		this->w *= val.w;

		return ((*this));
	};

	tml::XMFLOAT4EX_ operator /(const FLOAT val) const
	{
		auto tmp_val = 1.0f / val;

		return (tml::XMFLOAT4EX_(this->x * tmp_val, this->y * tmp_val, this->z * tmp_val, this->w * tmp_val));
	};

	tml::XMFLOAT4EX_ operator /(const DirectX::XMFLOAT4 &val) const
	{
		return (tml::XMFLOAT4EX_(this->x / val.x, this->y / val.y, this->z / val.z, this->w / val.w));
	};

	tml::XMFLOAT4EX_ &operator /=(const FLOAT val)
	{
		auto tmp_val = 1.0f / val;

		this->x *= tmp_val;
		this->y *= tmp_val;
		this->z *= tmp_val;
		this->w *= tmp_val;

		return ((*this));
	};

	tml::XMFLOAT4EX_ &operator /=(const DirectX::XMFLOAT4 &val)
	{
		this->x /= val.x;
		this->y /= val.y;
		this->z /= val.z;
		this->w /= val.w;

		return ((*this));
	};

	tml::XMFLOAT4EX_ operator -(void)
	{
		return (tml::XMFLOAT4EX_(-this->x, -this->y, -this->z, -this->w));
	};

	float GetHalfX(void) const
	{
		return (this->x * 0.5f);
	};

	float GetHalfY(void) const
	{
		return (this->y * 0.5f);
	};

	float GetHalfZ(void) const
	{
		return (this->z * 0.5f);
	};

	float GetHalfW(void) const
	{
		return (this->w * 0.5f);
	};
} XMFLOAT4EX;
}
