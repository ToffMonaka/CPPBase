/**
 * @file
 * @brief XNAMathFLOATヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_XNAMATH.h"


namespace tml {
/**
 * @brief XMFLOAT3X3E構造体
 */
typedef struct XMFLOAT3X3EX_ : public DirectX::XMFLOAT3X3
{
	XMFLOAT3X3EX_() :
		DirectX::XMFLOAT3X3(
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		)
	{
		return;
	};

	explicit XMFLOAT3X3EX_(
		const FLOAT _11, const FLOAT _12, const FLOAT _13,
		const FLOAT _21, const FLOAT _22, const FLOAT _23,
		const FLOAT _31, const FLOAT _32, const FLOAT _33
	) :
		DirectX::XMFLOAT3X3(
			_11, _12, _13,
			_21, _22, _23,
			_31, _32, _33
		)
	{
		return;
	};

	explicit XMFLOAT3X3EX_(const FLOAT val) :
		DirectX::XMFLOAT3X3(
			val, val, val,
			val, val, val,
			val, val, val
		)
	{
		return;
	};

	tml::XMFLOAT3X3EX_ &operator =(const FLOAT val)
	{
		this->_11 = val; this->_12 = val; this->_13 = val;
		this->_21 = val; this->_22 = val; this->_23 = val;
		this->_31 = val; this->_32 = val; this->_33 = val;

		return ((*this));
	};

	explicit XMFLOAT3X3EX_(const DirectX::XMFLOAT3X3 &val) :
		DirectX::XMFLOAT3X3(
			val._11, val._12, val._13,
			val._21, val._22, val._23,
			val._31, val._32, val._33
		)
	{
		return;
	};

	tml::XMFLOAT3X3EX_ &operator =(const DirectX::XMFLOAT3X3 &val)
	{
		this->_11 = val._11; this->_12 = val._12; this->_13 = val._13;
		this->_21 = val._21; this->_22 = val._22; this->_23 = val._23;
		this->_31 = val._31; this->_32 = val._32; this->_33 = val._33;

		return ((*this));
	};

	explicit XMFLOAT3X3EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX type) :
		DirectX::XMFLOAT3X3(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		)
	{
		return;
	};

	tml::XMFLOAT3X3EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX type)
	{
		this->_11 = 1.0f; this->_12 = 0.0f; this->_13 = 0.0f;
		this->_21 = 0.0f; this->_22 = 1.0f; this->_23 = 0.0f;
		this->_31 = 0.0f; this->_32 = 0.0f; this->_33 = 1.0f;

		return ((*this));
	};

	bool operator ==(const FLOAT val) const
	{
		return (
			(this->_11 == val) && (this->_12 == val) && (this->_13 == val) &&
			(this->_21 == val) && (this->_22 == val) && (this->_23 == val) &&
			(this->_31 == val) && (this->_32 == val) && (this->_33 == val)
		);
	};

	bool operator ==(const DirectX::XMFLOAT3X3 &val) const
	{
		return (
			(this->_11 == val._11) && (this->_12 == val._12) && (this->_13 == val._13) &&
			(this->_21 == val._21) && (this->_22 == val._22) && (this->_23 == val._23) &&
			(this->_31 == val._31) && (this->_32 == val._32) && (this->_33 == val._33)
		);
	};

	bool operator !=(const FLOAT val) const
	{
		return (
			(this->_11 != val) || (this->_12 != val) || (this->_13 != val) ||
			(this->_21 != val) || (this->_22 != val) || (this->_23 != val) ||
			(this->_31 != val) || (this->_32 != val) || (this->_33 != val) 
		);
	};

	bool operator !=(const DirectX::XMFLOAT3X3 &val) const
	{
		return (
			(this->_11 != val._11) || (this->_12 != val._12) || (this->_13 != val._13) ||
			(this->_21 != val._21) || (this->_22 != val._22) || (this->_23 != val._23) ||
			(this->_31 != val._31) || (this->_32 != val._32) || (this->_33 != val._33)
		);
	};

	tml::XMFLOAT3X3EX_ operator +(const FLOAT val) const
	{
		return (tml::XMFLOAT3X3EX_(
			this->_11 + val, this->_12 + val, this->_13 + val,
			this->_21 + val, this->_22 + val, this->_23 + val,
			this->_31 + val, this->_32 + val, this->_33 + val
		));
	};

	tml::XMFLOAT3X3EX_ operator +(const DirectX::XMFLOAT3X3 &val) const
	{
		return (tml::XMFLOAT3X3EX_(
			this->_11 + val._11, this->_12 + val._12, this->_13 + val._13,
			this->_21 + val._21, this->_22 + val._22, this->_23 + val._23,
			this->_31 + val._31, this->_32 + val._32, this->_33 + val._33
		));
	};

	tml::XMFLOAT3X3EX_ &operator +=(const FLOAT val)
	{
		this->_11 += val; this->_12 += val; this->_13 += val;
		this->_21 += val; this->_22 += val; this->_23 += val;
		this->_31 += val; this->_32 += val; this->_33 += val;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ &operator +=(const DirectX::XMFLOAT3X3 &val)
	{
		this->_11 += val._11; this->_12 += val._12; this->_13 += val._13;
		this->_21 += val._21; this->_22 += val._22; this->_23 += val._23;
		this->_31 += val._31; this->_32 += val._32; this->_33 += val._33;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ operator -(const FLOAT val) const
	{
		return (tml::XMFLOAT3X3EX_(
			this->_11 - val, this->_12 - val, this->_13 - val,
			this->_21 - val, this->_22 - val, this->_23 - val,
			this->_31 - val, this->_32 - val, this->_33 - val
		));
	};

	tml::XMFLOAT3X3EX_ operator -(const DirectX::XMFLOAT3X3 &val) const
	{
		return (tml::XMFLOAT3X3EX_(
			this->_11 - val._11, this->_12 - val._12, this->_13 - val._13,
			this->_21 - val._21, this->_22 - val._22, this->_23 - val._23,
			this->_31 - val._31, this->_32 - val._32, this->_33 - val._33
		));
	};

	tml::XMFLOAT3X3EX_ &operator -=(const FLOAT val)
	{
		this->_11 -= val; this->_12 -= val; this->_13 -= val;
		this->_21 -= val; this->_22 -= val; this->_23 -= val;
		this->_31 -= val; this->_32 -= val; this->_33 -= val;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ &operator -=(const DirectX::XMFLOAT3X3 &val)
	{
		this->_11 -= val._11; this->_12 -= val._12; this->_13 -= val._13;
		this->_21 -= val._21; this->_22 -= val._22; this->_23 -= val._23;
		this->_31 -= val._31; this->_32 -= val._32; this->_33 -= val._33;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ operator *(const FLOAT val) const
	{
		return (tml::XMFLOAT3X3EX_(
			this->_11 * val, this->_12 * val, this->_13 * val,
			this->_21 * val, this->_22 * val, this->_23 * val,
			this->_31 * val, this->_32 * val, this->_33 * val
		));
	};

	tml::XMFLOAT3X3EX_ operator *(const DirectX::XMFLOAT3X3 &val) const
	{
		return (tml::XMFLOAT3X3EX_(
			this->_11 * val._11, this->_12 * val._12, this->_13 * val._13,
			this->_21 * val._21, this->_22 * val._22, this->_23 * val._23,
			this->_31 * val._31, this->_32 * val._32, this->_33 * val._33
		));
	};

	tml::XMFLOAT3X3EX_ &operator *=(const FLOAT val)
	{
		this->_11 *= val; this->_12 *= val; this->_13 *= val;
		this->_21 *= val; this->_22 *= val; this->_23 *= val;
		this->_31 *= val; this->_32 *= val; this->_33 *= val;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ &operator *=(const DirectX::XMFLOAT3X3 &val)
	{
		this->_11 *= val._11; this->_12 *= val._12; this->_13 *= val._13;
		this->_21 *= val._21; this->_22 *= val._22; this->_23 *= val._23;
		this->_31 *= val._31; this->_32 *= val._32; this->_33 *= val._33;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ operator /(const FLOAT val) const
	{
		auto tmp_val = 1.0f / val;

		return (tml::XMFLOAT3X3EX_(
			this->_11 * tmp_val, this->_12 * tmp_val, this->_13 * tmp_val,
			this->_21 * tmp_val, this->_22 * tmp_val, this->_23 * tmp_val,
			this->_31 * tmp_val, this->_32 * tmp_val, this->_33 * tmp_val
		));
	};

	tml::XMFLOAT3X3EX_ operator /(const DirectX::XMFLOAT3X3 &val) const
	{
		return (tml::XMFLOAT3X3EX_(
			this->_11 / val._11, this->_12 / val._12, this->_13 / val._13,
			this->_21 / val._21, this->_22 / val._22, this->_23 / val._23,
			this->_31 / val._31, this->_32 / val._32, this->_33 / val._33
		));
	};

	tml::XMFLOAT3X3EX_ &operator /=(const FLOAT val)
	{
		auto tmp_val = 1.0f / val;

		this->_11 *= tmp_val; this->_12 *= tmp_val; this->_13 *= tmp_val;
		this->_21 *= tmp_val; this->_22 *= tmp_val; this->_23 *= tmp_val;
		this->_31 *= tmp_val; this->_32 *= tmp_val; this->_33 *= tmp_val;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ &operator /=(const DirectX::XMFLOAT3X3 &val)
	{
		this->_11 /= val._11; this->_12 /= val._12; this->_13 /= val._13;
		this->_21 /= val._21; this->_22 /= val._22; this->_23 /= val._23;
		this->_31 /= val._31; this->_32 /= val._32; this->_33 /= val._33;

		return ((*this));
	};

	tml::XMFLOAT3X3EX_ operator -(void)
	{
		return (tml::XMFLOAT3X3EX_(
			-this->_11, -this->_12, -this->_13,
			-this->_21, -this->_22, -this->_23,
			-this->_31, -this->_32, -this->_33
		));
	};
} XMFLOAT3X3EX;


/**
 * @brief XMFLOAT4X3EX構造体
 */
typedef struct XMFLOAT4X3EX_ : public DirectX::XMFLOAT4X3
{
	XMFLOAT4X3EX_() :
		DirectX::XMFLOAT4X3(
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		)
	{
		return;
	};

	explicit XMFLOAT4X3EX_(
		const FLOAT _11, const FLOAT _12, const FLOAT _13,
		const FLOAT _21, const FLOAT _22, const FLOAT _23,
		const FLOAT _31, const FLOAT _32, const FLOAT _33,
		const FLOAT _41, const FLOAT _42, const FLOAT _43
	) :
		DirectX::XMFLOAT4X3(
			_11, _12, _13,
			_21, _22, _23,
			_31, _32, _33,
			_41, _42, _43
		)
	{
		return;
	};

	explicit XMFLOAT4X3EX_(const FLOAT val) :
		DirectX::XMFLOAT4X3(
			val, val, val,
			val, val, val,
			val, val, val,
			val, val, val
		)
	{
		return;
	};

	tml::XMFLOAT4X3EX_ &operator =(const FLOAT val)
	{
		this->_11 = val; this->_12 = val; this->_13 = val;
		this->_21 = val; this->_22 = val; this->_23 = val;
		this->_31 = val; this->_32 = val; this->_33 = val;
		this->_41 = val; this->_42 = val; this->_43 = val;

		return ((*this));
	};

	explicit XMFLOAT4X3EX_(const DirectX::XMFLOAT4X3 &val) :
		DirectX::XMFLOAT4X3(
			val._11, val._12, val._13,
			val._21, val._22, val._23,
			val._31, val._32, val._33,
			val._41, val._42, val._43
		)
	{
		return;
	};

	tml::XMFLOAT4X3EX_ &operator =(const DirectX::XMFLOAT4X3 &val)
	{
		this->_11 = val._11; this->_12 = val._12; this->_13 = val._13;
		this->_21 = val._21; this->_22 = val._22; this->_23 = val._23;
		this->_31 = val._31; this->_32 = val._32; this->_33 = val._33;
		this->_41 = val._41; this->_42 = val._42; this->_43 = val._43;

		return ((*this));
	};

	explicit XMFLOAT4X3EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX type) :
		DirectX::XMFLOAT4X3(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f
		)
	{
		return;
	};

	tml::XMFLOAT4X3EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX type)
	{
		this->_11 = 1.0f; this->_12 = 0.0f; this->_13 = 0.0f;
		this->_21 = 0.0f; this->_22 = 1.0f; this->_23 = 0.0f;
		this->_31 = 0.0f; this->_32 = 0.0f; this->_33 = 1.0f;
		this->_41 = 0.0f; this->_42 = 0.0f; this->_43 = 0.0f;

		return ((*this));
	};

	bool operator ==(const FLOAT val) const
	{
		return (
			(this->_11 == val) && (this->_12 == val) && (this->_13 == val) &&
			(this->_21 == val) && (this->_22 == val) && (this->_23 == val) &&
			(this->_31 == val) && (this->_32 == val) && (this->_33 == val) &&
			(this->_41 == val) && (this->_42 == val) && (this->_43 == val)
		);
	};

	bool operator ==(const DirectX::XMFLOAT4X3 &val) const
	{
		return (
			(this->_11 == val._11) && (this->_12 == val._12) && (this->_13 == val._13) &&
			(this->_21 == val._21) && (this->_22 == val._22) && (this->_23 == val._23) &&
			(this->_31 == val._31) && (this->_32 == val._32) && (this->_33 == val._33) &&
			(this->_41 == val._41) && (this->_42 == val._42) && (this->_43 == val._43)
		);
	};

	bool operator !=(const FLOAT val) const
	{
		return (
			(this->_11 != val) || (this->_12 != val) || (this->_13 != val) ||
			(this->_21 != val) || (this->_22 != val) || (this->_23 != val) ||
			(this->_31 != val) || (this->_32 != val) || (this->_33 != val) ||
			(this->_41 != val) || (this->_42 != val) || (this->_43 != val) 
		);
	};

	bool operator !=(const DirectX::XMFLOAT4X3 &val) const
	{
		return (
			(this->_11 != val._11) || (this->_12 != val._12) || (this->_13 != val._13) ||
			(this->_21 != val._21) || (this->_22 != val._22) || (this->_23 != val._23) ||
			(this->_31 != val._31) || (this->_32 != val._32) || (this->_33 != val._33) ||
			(this->_41 != val._41) || (this->_42 != val._42) || (this->_43 != val._43)
		);
	};

	tml::XMFLOAT4X3EX_ operator +(const FLOAT val) const
	{
		return (tml::XMFLOAT4X3EX_(
			this->_11 + val, this->_12 + val, this->_13 + val,
			this->_21 + val, this->_22 + val, this->_23 + val,
			this->_31 + val, this->_32 + val, this->_33 + val,
			this->_41 + val, this->_42 + val, this->_43 + val
		));
	};

	tml::XMFLOAT4X3EX_ operator +(const DirectX::XMFLOAT4X3 &val) const
	{
		return (tml::XMFLOAT4X3EX_(
			this->_11 + val._11, this->_12 + val._12, this->_13 + val._13,
			this->_21 + val._21, this->_22 + val._22, this->_23 + val._23,
			this->_31 + val._31, this->_32 + val._32, this->_33 + val._33,
			this->_41 + val._41, this->_42 + val._42, this->_43 + val._43
		));
	};

	tml::XMFLOAT4X3EX_ &operator +=(const FLOAT val)
	{
		this->_11 += val; this->_12 += val; this->_13 += val;
		this->_21 += val; this->_22 += val; this->_23 += val;
		this->_31 += val; this->_32 += val; this->_33 += val;
		this->_41 += val; this->_42 += val; this->_43 += val;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ &operator +=(const DirectX::XMFLOAT4X3 &val)
	{
		this->_11 += val._11; this->_12 += val._12; this->_13 += val._13;
		this->_21 += val._21; this->_22 += val._22; this->_23 += val._23;
		this->_31 += val._31; this->_32 += val._32; this->_33 += val._33;
		this->_41 += val._41; this->_42 += val._42; this->_43 += val._43;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ operator -(const FLOAT val) const
	{
		return (tml::XMFLOAT4X3EX_(
			this->_11 - val, this->_12 - val, this->_13 - val,
			this->_21 - val, this->_22 - val, this->_23 - val,
			this->_31 - val, this->_32 - val, this->_33 - val,
			this->_41 - val, this->_42 - val, this->_43 - val
		));
	};

	tml::XMFLOAT4X3EX_ operator -(const DirectX::XMFLOAT4X3 &val) const
	{
		return (tml::XMFLOAT4X3EX_(
			this->_11 - val._11, this->_12 - val._12, this->_13 - val._13,
			this->_21 - val._21, this->_22 - val._22, this->_23 - val._23,
			this->_31 - val._31, this->_32 - val._32, this->_33 - val._33,
			this->_41 - val._41, this->_42 - val._42, this->_43 - val._43
		));
	};

	tml::XMFLOAT4X3EX_ &operator -=(const FLOAT val)
	{
		this->_11 -= val; this->_12 -= val; this->_13 -= val;
		this->_21 -= val; this->_22 -= val; this->_23 -= val;
		this->_31 -= val; this->_32 -= val; this->_33 -= val;
		this->_41 -= val; this->_42 -= val; this->_43 -= val;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ &operator -=(const DirectX::XMFLOAT4X3 &val)
	{
		this->_11 -= val._11; this->_12 -= val._12; this->_13 -= val._13;
		this->_21 -= val._21; this->_22 -= val._22; this->_23 -= val._23;
		this->_31 -= val._31; this->_32 -= val._32; this->_33 -= val._33;
		this->_41 -= val._41; this->_42 -= val._42; this->_43 -= val._43;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ operator *(const FLOAT val) const
	{
		return (tml::XMFLOAT4X3EX_(
			this->_11 * val, this->_12 * val, this->_13 * val,
			this->_21 * val, this->_22 * val, this->_23 * val,
			this->_31 * val, this->_32 * val, this->_33 * val,
			this->_41 * val, this->_42 * val, this->_43 * val
		));
	};

	tml::XMFLOAT4X3EX_ operator *(const DirectX::XMFLOAT4X3 &val) const
	{
		return (tml::XMFLOAT4X3EX_(
			this->_11 * val._11, this->_12 * val._12, this->_13 * val._13,
			this->_21 * val._21, this->_22 * val._22, this->_23 * val._23,
			this->_31 * val._31, this->_32 * val._32, this->_33 * val._33,
			this->_41 * val._41, this->_42 * val._42, this->_43 * val._43
		));
	};

	tml::XMFLOAT4X3EX_ &operator *=(const FLOAT val)
	{
		this->_11 *= val; this->_12 *= val; this->_13 *= val;
		this->_21 *= val; this->_22 *= val; this->_23 *= val;
		this->_31 *= val; this->_32 *= val; this->_33 *= val;
		this->_41 *= val; this->_42 *= val; this->_43 *= val;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ &operator *=(const DirectX::XMFLOAT4X3 &val)
	{
		this->_11 *= val._11; this->_12 *= val._12; this->_13 *= val._13;
		this->_21 *= val._21; this->_22 *= val._22; this->_23 *= val._23;
		this->_31 *= val._31; this->_32 *= val._32; this->_33 *= val._33;
		this->_41 *= val._41; this->_42 *= val._42; this->_43 *= val._43;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ operator /(const FLOAT val) const
	{
		auto tmp_val = 1.0f / val;

		return (tml::XMFLOAT4X3EX_(
			this->_11 * tmp_val, this->_12 * tmp_val, this->_13 * tmp_val,
			this->_21 * tmp_val, this->_22 * tmp_val, this->_23 * tmp_val,
			this->_31 * tmp_val, this->_32 * tmp_val, this->_33 * tmp_val,
			this->_41 * tmp_val, this->_42 * tmp_val, this->_43 * tmp_val
		));
	};

	tml::XMFLOAT4X3EX_ operator /(const DirectX::XMFLOAT4X3 &val) const
	{
		return (tml::XMFLOAT4X3EX_(
			this->_11 / val._11, this->_12 / val._12, this->_13 / val._13,
			this->_21 / val._21, this->_22 / val._22, this->_23 / val._23,
			this->_31 / val._31, this->_32 / val._32, this->_33 / val._33,
			this->_41 / val._41, this->_42 / val._42, this->_43 / val._43
		));
	};

	tml::XMFLOAT4X3EX_ &operator /=(const FLOAT val)
	{
		auto tmp_val = 1.0f / val;

		this->_11 *= tmp_val; this->_12 *= tmp_val; this->_13 *= tmp_val;
		this->_21 *= tmp_val; this->_22 *= tmp_val; this->_23 *= tmp_val;
		this->_31 *= tmp_val; this->_32 *= tmp_val; this->_33 *= tmp_val;
		this->_41 *= tmp_val; this->_42 *= tmp_val; this->_43 *= tmp_val;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ &operator /=(const DirectX::XMFLOAT4X3 &val)
	{
		this->_11 /= val._11; this->_12 /= val._12; this->_13 /= val._13;
		this->_21 /= val._21; this->_22 /= val._22; this->_23 /= val._23;
		this->_31 /= val._31; this->_32 /= val._32; this->_33 /= val._33;
		this->_41 /= val._41; this->_42 /= val._42; this->_43 /= val._43;

		return ((*this));
	};

	tml::XMFLOAT4X3EX_ operator -(void)
	{
		return (tml::XMFLOAT4X3EX_(
			-this->_11, -this->_12, -this->_13,
			-this->_21, -this->_22, -this->_23,
			-this->_31, -this->_32, -this->_33,
			-this->_41, -this->_42, -this->_43
		));
	};
} XMFLOAT4X3EX;


/**
 * @brief XMFLOAT4X4E構造体
 */
typedef struct XMFLOAT4X4EX_ : public DirectX::XMFLOAT4X4
{
	XMFLOAT4X4EX_() :
		DirectX::XMFLOAT4X4(
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f
		)
	{
		return;
	};

	explicit XMFLOAT4X4EX_(
		const FLOAT _11, const FLOAT _12, const FLOAT _13, const FLOAT _14,
		const FLOAT _21, const FLOAT _22, const FLOAT _23, const FLOAT _24,
		const FLOAT _31, const FLOAT _32, const FLOAT _33, const FLOAT _34,
		const FLOAT _41, const FLOAT _42, const FLOAT _43, const FLOAT _44
	) :
		DirectX::XMFLOAT4X4(
			_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44
		)
	{
		return;
	};

	explicit XMFLOAT4X4EX_(const FLOAT val) :
		DirectX::XMFLOAT4X4(
			val, val, val, val,
			val, val, val, val,
			val, val, val, val,
			val, val, val, val
		)
	{
		return;
	};

	tml::XMFLOAT4X4EX_ &operator =(const FLOAT val)
	{
		this->_11 = val; this->_12 = val; this->_13 = val; this->_14 = val;
		this->_21 = val; this->_22 = val; this->_23 = val; this->_24 = val;
		this->_31 = val; this->_32 = val; this->_33 = val; this->_34 = val;
		this->_41 = val; this->_42 = val; this->_43 = val; this->_44 = val;

		return ((*this));
	};

	explicit XMFLOAT4X4EX_(const DirectX::XMFLOAT4X4 &val) :
		DirectX::XMFLOAT4X4(
			val._11, val._12, val._13, val._14,
			val._21, val._22, val._23, val._24,
			val._31, val._32, val._33, val._34,
			val._41, val._42, val._43, val._44
		)
	{
		return;
	};

	tml::XMFLOAT4X4EX_ &operator =(const DirectX::XMFLOAT4X4 &val)
	{
		this->_11 = val._11; this->_12 = val._12; this->_13 = val._13; this->_14 = val._14;
		this->_21 = val._21; this->_22 = val._22; this->_23 = val._23; this->_24 = val._24;
		this->_31 = val._31; this->_32 = val._32; this->_33 = val._33; this->_34 = val._34;
		this->_41 = val._41; this->_42 = val._42; this->_43 = val._43; this->_44 = val._44;

		return ((*this));
	};

	explicit XMFLOAT4X4EX_(const tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX type) :
		DirectX::XMFLOAT4X4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		)
	{
		return;
	};

	tml::XMFLOAT4X4EX_ &operator =(const tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX type)
	{
		this->_11 = 1.0f; this->_12 = 0.0f; this->_13 = 0.0f; this->_14 = 0.0f;
		this->_21 = 0.0f; this->_22 = 1.0f; this->_23 = 0.0f; this->_24 = 0.0f;
		this->_31 = 0.0f; this->_32 = 0.0f; this->_33 = 1.0f; this->_34 = 0.0f;
		this->_41 = 0.0f; this->_42 = 0.0f; this->_43 = 0.0f; this->_44 = 1.0f;

		return ((*this));
	};

	bool operator ==(const FLOAT val) const
	{
		return (
			(this->_11 == val) && (this->_12 == val) && (this->_13 == val) && (this->_14 == val) &&
			(this->_21 == val) && (this->_22 == val) && (this->_23 == val) && (this->_24 == val) &&
			(this->_31 == val) && (this->_32 == val) && (this->_33 == val) && (this->_34 == val) &&
			(this->_41 == val) && (this->_42 == val) && (this->_43 == val) && (this->_44 == val)
		);
	};

	bool operator ==(const DirectX::XMFLOAT4X4 &val) const
	{
		return (
			(this->_11 == val._11) && (this->_12 == val._12) && (this->_13 == val._13) && (this->_14 == val._14) &&
			(this->_21 == val._21) && (this->_22 == val._22) && (this->_23 == val._23) && (this->_24 == val._24) &&
			(this->_31 == val._31) && (this->_32 == val._32) && (this->_33 == val._33) && (this->_34 == val._34) &&
			(this->_41 == val._41) && (this->_42 == val._42) && (this->_43 == val._43) && (this->_44 == val._44)
		);
	};

	bool operator !=(const FLOAT val) const
	{
		return (
			(this->_11 != val) || (this->_12 != val) || (this->_13 != val) || (this->_14 != val) ||
			(this->_21 != val) || (this->_22 != val) || (this->_23 != val) || (this->_24 != val) ||
			(this->_31 != val) || (this->_32 != val) || (this->_33 != val) || (this->_34 != val) ||
			(this->_41 != val) || (this->_42 != val) || (this->_43 != val) || (this->_44 != val)
		);
	};

	bool operator !=(const DirectX::XMFLOAT4X4 &val) const
	{
		return (
			(this->_11 != val._11) || (this->_12 != val._12) || (this->_13 != val._13) || (this->_14 != val._14) ||
			(this->_21 != val._21) || (this->_22 != val._22) || (this->_23 != val._23) || (this->_24 != val._24) ||
			(this->_31 != val._31) || (this->_32 != val._32) || (this->_33 != val._33) || (this->_34 != val._34) ||
			(this->_41 != val._41) || (this->_42 != val._42) || (this->_43 != val._43) || (this->_44 != val._44)
		);
	};

	tml::XMFLOAT4X4EX_ operator +(const FLOAT val) const
	{
		return (tml::XMFLOAT4X4EX_(
			this->_11 + val, this->_12 + val, this->_13 + val, this->_14 + val,
			this->_21 + val, this->_22 + val, this->_23 + val, this->_24 + val,
			this->_31 + val, this->_32 + val, this->_33 + val, this->_34 + val,
			this->_41 + val, this->_42 + val, this->_43 + val, this->_44 + val
		));
	};

	tml::XMFLOAT4X4EX_ operator +(const DirectX::XMFLOAT4X4 &val) const
	{
		return (tml::XMFLOAT4X4EX_(
			this->_11 + val._11, this->_12 + val._12, this->_13 + val._13, this->_14 + val._14,
			this->_21 + val._21, this->_22 + val._22, this->_23 + val._23, this->_24 + val._24,
			this->_31 + val._31, this->_32 + val._32, this->_33 + val._33, this->_34 + val._34,
			this->_41 + val._41, this->_42 + val._42, this->_43 + val._43, this->_44 + val._44
		));
	};

	tml::XMFLOAT4X4EX_ &operator +=(const FLOAT val)
	{
		this->_11 += val; this->_12 += val; this->_13 += val; this->_14 += val;
		this->_21 += val; this->_22 += val; this->_23 += val; this->_24 += val;
		this->_31 += val; this->_32 += val; this->_33 += val; this->_34 += val;
		this->_41 += val; this->_42 += val; this->_43 += val; this->_44 += val;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ &operator +=(const DirectX::XMFLOAT4X4 &val)
	{
		this->_11 += val._11; this->_12 += val._12; this->_13 += val._13; this->_14 += val._14;
		this->_21 += val._21; this->_22 += val._22; this->_23 += val._23; this->_24 += val._24;
		this->_31 += val._31; this->_32 += val._32; this->_33 += val._33; this->_34 += val._34;
		this->_41 += val._41; this->_42 += val._42; this->_43 += val._43; this->_44 += val._44;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ operator -(const FLOAT val) const
	{
		return (tml::XMFLOAT4X4EX_(
			this->_11 - val, this->_12 - val, this->_13 - val, this->_14 - val,
			this->_21 - val, this->_22 - val, this->_23 - val, this->_24 - val,
			this->_31 - val, this->_32 - val, this->_33 - val, this->_34 - val,
			this->_41 - val, this->_42 - val, this->_43 - val, this->_44 - val
		));
	};

	tml::XMFLOAT4X4EX_ operator -(const DirectX::XMFLOAT4X4 &val) const
	{
		return (tml::XMFLOAT4X4EX_(
			this->_11 - val._11, this->_12 - val._12, this->_13 - val._13, this->_14 - val._14,
			this->_21 - val._21, this->_22 - val._22, this->_23 - val._23, this->_24 - val._24,
			this->_31 - val._31, this->_32 - val._32, this->_33 - val._33, this->_34 - val._34,
			this->_41 - val._41, this->_42 - val._42, this->_43 - val._43, this->_44 - val._44
		));
	};

	tml::XMFLOAT4X4EX_ &operator -=(const FLOAT val)
	{
		this->_11 -= val; this->_12 -= val; this->_13 -= val; this->_14 -= val;
		this->_21 -= val; this->_22 -= val; this->_23 -= val; this->_24 -= val;
		this->_31 -= val; this->_32 -= val; this->_33 -= val; this->_34 -= val;
		this->_41 -= val; this->_42 -= val; this->_43 -= val; this->_44 -= val;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ &operator -=(const DirectX::XMFLOAT4X4 &val)
	{
		this->_11 -= val._11; this->_12 -= val._12; this->_13 -= val._13; this->_14 -= val._14;
		this->_21 -= val._21; this->_22 -= val._22; this->_23 -= val._23; this->_24 -= val._24;
		this->_31 -= val._31; this->_32 -= val._32; this->_33 -= val._33; this->_34 -= val._34;
		this->_41 -= val._41; this->_42 -= val._42; this->_43 -= val._43; this->_44 -= val._44;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ operator *(const FLOAT val) const
	{
		return (tml::XMFLOAT4X4EX_(
			this->_11 * val, this->_12 * val, this->_13 * val, this->_14 * val,
			this->_21 * val, this->_22 * val, this->_23 * val, this->_24 * val,
			this->_31 * val, this->_32 * val, this->_33 * val, this->_34 * val,
			this->_41 * val, this->_42 * val, this->_43 * val, this->_44 * val
		));
	};

	tml::XMFLOAT4X4EX_ operator *(const DirectX::XMFLOAT4X4 &val) const
	{
		return (tml::XMFLOAT4X4EX_(
			this->_11 * val._11, this->_12 * val._12, this->_13 * val._13, this->_14 * val._14,
			this->_21 * val._21, this->_22 * val._22, this->_23 * val._23, this->_24 * val._24,
			this->_31 * val._31, this->_32 * val._32, this->_33 * val._33, this->_34 * val._34,
			this->_41 * val._41, this->_42 * val._42, this->_43 * val._43, this->_44 * val._44
		));
	};

	tml::XMFLOAT4X4EX_ &operator *=(const FLOAT val)
	{
		this->_11 *= val; this->_12 *= val; this->_13 *= val; this->_14 *= val;
		this->_21 *= val; this->_22 *= val; this->_23 *= val; this->_24 *= val;
		this->_31 *= val; this->_32 *= val; this->_33 *= val; this->_34 *= val;
		this->_41 *= val; this->_42 *= val; this->_43 *= val; this->_44 *= val;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ &operator *=(const DirectX::XMFLOAT4X4 &val)
	{
		this->_11 *= val._11; this->_12 *= val._12; this->_13 *= val._13; this->_14 *= val._14;
		this->_21 *= val._21; this->_22 *= val._22; this->_23 *= val._23; this->_24 *= val._24;
		this->_31 *= val._31; this->_32 *= val._32; this->_33 *= val._33; this->_34 *= val._34;
		this->_41 *= val._41; this->_42 *= val._42; this->_43 *= val._43; this->_44 *= val._44;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ operator /(const FLOAT val) const
	{
		auto tmp_val = 1.0f / val;

		return (tml::XMFLOAT4X4EX_(
			this->_11 * tmp_val, this->_12 * tmp_val, this->_13 * tmp_val, this->_14 * tmp_val,
			this->_21 * tmp_val, this->_22 * tmp_val, this->_23 * tmp_val, this->_24 * tmp_val,
			this->_31 * tmp_val, this->_32 * tmp_val, this->_33 * tmp_val, this->_34 * tmp_val,
			this->_41 * tmp_val, this->_42 * tmp_val, this->_43 * tmp_val, this->_44 * tmp_val
		));
	};

	tml::XMFLOAT4X4EX_ operator /(const DirectX::XMFLOAT4X4 &val) const
	{
		return (tml::XMFLOAT4X4EX_(
			this->_11 / val._11, this->_12 / val._12, this->_13 / val._13, this->_14 / val._14,
			this->_21 / val._21, this->_22 / val._22, this->_23 / val._23, this->_24 / val._24,
			this->_31 / val._31, this->_32 / val._32, this->_33 / val._33, this->_34 / val._34,
			this->_41 / val._41, this->_42 / val._42, this->_43 / val._43, this->_44 / val._44
		));
	};

	tml::XMFLOAT4X4EX_ &operator /=(const FLOAT val)
	{
		auto tmp_val = 1.0f / val;

		this->_11 *= tmp_val; this->_12 *= tmp_val; this->_13 *= tmp_val; this->_14 *= tmp_val;
		this->_21 *= tmp_val; this->_22 *= tmp_val; this->_23 *= tmp_val; this->_24 *= tmp_val;
		this->_31 *= tmp_val; this->_32 *= tmp_val; this->_33 *= tmp_val; this->_34 *= tmp_val;
		this->_41 *= tmp_val; this->_42 *= tmp_val; this->_43 *= tmp_val; this->_44 *= tmp_val;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ &operator /=(const DirectX::XMFLOAT4X4 &val)
	{
		this->_11 /= val._11; this->_12 /= val._12; this->_13 /= val._13; this->_14 /= val._14;
		this->_21 /= val._21; this->_22 /= val._22; this->_23 /= val._23; this->_24 /= val._24;
		this->_31 /= val._31; this->_32 /= val._32; this->_33 /= val._33; this->_34 /= val._34;
		this->_41 /= val._41; this->_42 /= val._42; this->_43 /= val._43; this->_44 /= val._44;

		return ((*this));
	};

	tml::XMFLOAT4X4EX_ operator -(void)
	{
		return (tml::XMFLOAT4X4EX_(
			-this->_11, -this->_12, -this->_13, -this->_14,
			-this->_21, -this->_22, -this->_23, -this->_24,
			-this->_31, -this->_32, -this->_33, -this->_34,
			-this->_41, -this->_42, -this->_43, -this->_44
		));
	};
} XMFLOAT4X4EX;
}
