/**
 * @file
 * @brief Fogヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief FogDescクラス
 */
class FogDesc : public tml::graphic::ManagerResourceDesc
{
public:
	tml::XMPosition3D position;
	tml::ConstantUtil::GRAPHIC::FOG_EFFECT_TYPE effect_type;
	tml::XMFLOAT3EX color;
	/*
	FLOAT mul_value;
	FLOAT near_range;
	FLOAT far_range;
	*/

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	FogDesc();
	virtual ~FogDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::FogDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fogクラス
 */
class Fog : public tml::graphic::ManagerResource
{
public: Fog(const tml::graphic::Fog &) = delete;
public: tml::graphic::Fog &operator =(const tml::graphic::Fog &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::FOG);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::FOG_TYPE::BASE);

private:
	tml::ConstantUtil::GRAPHIC::FOG_EFFECT_TYPE effect_type_;
	tml::XMFLOAT3EX col_;
	/*
	FLOAT mul_val_;
	FLOAT near_rng_;
	FLOAT far_rng_;
	FLOAT rng_val1_;
	FLOAT rng_val2_;
	*/

public:
	tml::XMPosition3D position;

private:
	void Release(void);

public:
	Fog();
	virtual ~Fog();

	virtual void Init(void);
	INT Create(const tml::graphic::FogDesc &);

	tml::ConstantUtil::GRAPHIC::FOG_EFFECT_TYPE GetEffectType(void) const;
	const tml::XMFLOAT3EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT3EX &);
	/*
	FLOAT GetMulValue(void) const;
	void SetMulValue(const FLOAT);
	FLOAT GetNearRange(void) const;
	void SetNearRange(const FLOAT);
	FLOAT GetFarRange(void) const;
	void SetFarRange(const FLOAT);
	FLOAT GetRangeValue1(void) const;
	FLOAT GetRangeValue2(void) const;
	*/
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog::Release(void)
{
	return;
}


/**
 * @brief GetEffectType関数
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_EFFECT_TYPE tml::graphic::Fog::GetEffectType(void) const
{
	return (this->effect_type_);
}


/**
 * @brief GetColor関数
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Fog::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor関数
 * @param col (color)
 */
inline void tml::graphic::Fog::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}


#if 0
/**
 * @brief GetMulValue関数
 * @return mul_val (mul_value)
 */
inline FLOAT tml::graphic::Fog::GetMulValue(void) const
{
	return (this->mul_val_);
}


/**
 * @brief SetMulValue関数
 * @param mul_val (mul_value)
 */
inline void tml::graphic::Fog::SetMulValue(const FLOAT mul_val)
{
	this->mul_val_ = mul_val;

	return;
}


/**
 * @brief GetNearRange関数
 * @return near_rng (near_range)
 */
inline FLOAT tml::graphic::Fog::GetNearRange(void) const
{
	return (this->near_rng_);
}


/**
 * @brief GetFarRange関数
 * @return far_rng (far_range)
 */
inline FLOAT tml::graphic::Fog::GetFarRange(void) const
{
	return (this->far_rng_);
}


/**
 * @brief GetRangeValue1関数
 * @return rng_val1 (range_value1)
 */
inline FLOAT tml::graphic::Fog::GetRangeValue1(void) const
{
	return (this->rng_val1_);
}


/**
 * @brief GetRangeValue2関数
 * @return rng_val2 (range_value2)
 */
inline FLOAT tml::graphic::Fog::GetRangeValue2(void) const
{
	return (this->rng_val2_);
}
#endif
