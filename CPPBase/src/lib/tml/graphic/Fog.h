/**
 * @file
 * @brief Fogヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief FogDescクラス
 */
class FogDesc : public tml::GraphicResourceDesc
{
public:
	tml::ConstantUtil::GRAPHIC::FOG_TYPE type;
	tml::XMPosition position;
	tml::XMFLOAT3EX color;
	FLOAT mul_value;
	FLOAT near_range;
	FLOAT far_range;

public:
	FogDesc();
	virtual ~FogDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Fogクラス
 */
class Fog : public tml::GraphicResource
{
public: Fog(const tml::Fog &) = delete;
public: tml::Fog &operator =(const tml::Fog &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::ConstantUtil::GRAPHIC::FOG_TYPE type_;
	tml::XMFLOAT3EX col_;
	FLOAT mul_val_;
	FLOAT near_rng_;
	FLOAT far_rng_;
	FLOAT rng_val1_;
	FLOAT rng_val2_;

public:
	tml::XMPosition position;

private:
	void Release(void);

public:
	Fog();
	virtual ~Fog();

	virtual void Init(void);
	INT Create(const tml::FogDesc &);


	tml::ConstantUtil::GRAPHIC::FOG_TYPE GetType(void) const;
	const tml::XMFLOAT3EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT3EX &);
	FLOAT GetMulValue(void) const;
	void SetMulValue(const FLOAT);
	FLOAT GetNearRange(void) const;
	void SetNearRange(const FLOAT);
	FLOAT GetFarRange(void) const;
	void SetFarRange(const FLOAT);
	FLOAT GetRangeValue1(void) const;
	FLOAT GetRangeValue2(void) const;
};
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_TYPE tml::Fog::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetColor関数
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::Fog::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor関数
 * @param col (color)
 */
inline void tml::Fog::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}


/**
 * @brief GetMulValue関数
 * @return mul_val (mul_value)
 */
inline FLOAT tml::Fog::GetMulValue(void) const
{
	return (this->mul_val_);
}


/**
 * @brief SetMulValue関数
 * @param mul_val (mul_value)
 */
inline void tml::Fog::SetMulValue(const FLOAT mul_val)
{
	this->mul_val_ = mul_val;

	return;
}


/**
 * @brief GetNearRange関数
 * @return near_rng (near_range)
 */
inline FLOAT tml::Fog::GetNearRange(void) const
{
	return (this->near_rng_);
}


/**
 * @brief GetFarRange関数
 * @return far_rng (far_range)
 */
inline FLOAT tml::Fog::GetFarRange(void) const
{
	return (this->far_rng_);
}


/**
 * @brief GetRangeValue1関数
 * @return rng_val1 (range_value1)
 */
inline FLOAT tml::Fog::GetRangeValue1(void) const
{
	return (this->rng_val1_);
}


/**
 * @brief GetRangeValue2関数
 * @return rng_val2 (range_value2)
 */
inline FLOAT tml::Fog::GetRangeValue2(void) const
{
	return (this->rng_val2_);
}
