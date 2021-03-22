/**
 * @file
 * @brief Fog�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief FogDesc�N���X
 */
class FogDesc : public tml::graphic::ResourceDesc
{
public:
	tml::ConstantUtil::GRAPHIC::FOG_TYPE type;
	tml::XMPosition3D position;
	tml::XMFLOAT3EX color;
	FLOAT mul_value;
	FLOAT near_range;
	FLOAT far_range;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	FogDesc();
	virtual ~FogDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FogDesc::Release(void)
{
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fog�N���X
 */
class Fog : public tml::graphic::Resource
{
public: Fog(const tml::graphic::Fog &) = delete;
public: tml::graphic::Fog &operator =(const tml::graphic::Fog &) = delete;
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
	tml::XMPosition3D position;

protected:
	void Release(void);

public:
	Fog();
	virtual ~Fog();

	virtual void Init(void);
	INT Create(const tml::graphic::FogDesc &);

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
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Fog::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_TYPE tml::graphic::Fog::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetColor�֐�
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Fog::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor�֐�
 * @param col (color)
 */
inline void tml::graphic::Fog::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}


/**
 * @brief GetMulValue�֐�
 * @return mul_val (mul_value)
 */
inline FLOAT tml::graphic::Fog::GetMulValue(void) const
{
	return (this->mul_val_);
}


/**
 * @brief SetMulValue�֐�
 * @param mul_val (mul_value)
 */
inline void tml::graphic::Fog::SetMulValue(const FLOAT mul_val)
{
	this->mul_val_ = mul_val;

	return;
}


/**
 * @brief GetNearRange�֐�
 * @return near_rng (near_range)
 */
inline FLOAT tml::graphic::Fog::GetNearRange(void) const
{
	return (this->near_rng_);
}


/**
 * @brief GetFarRange�֐�
 * @return far_rng (far_range)
 */
inline FLOAT tml::graphic::Fog::GetFarRange(void) const
{
	return (this->far_rng_);
}


/**
 * @brief GetRangeValue1�֐�
 * @return rng_val1 (range_value1)
 */
inline FLOAT tml::graphic::Fog::GetRangeValue1(void) const
{
	return (this->rng_val1_);
}


/**
 * @brief GetRangeValue2�֐�
 * @return rng_val2 (range_value2)
 */
inline FLOAT tml::graphic::Fog::GetRangeValue2(void) const
{
	return (this->rng_val2_);
}
