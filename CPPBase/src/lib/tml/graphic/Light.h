/**
 * @file
 * @brief Light�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief LightDesc�N���X
 */
class LightDesc : public tml::graphic::ManagerResourceDesc
{
public:
	tml::XMPosition3D position;
	tml::ConstantUtil::GRAPHIC::LIGHT_EFFECT_TYPE effect_type;
	tml::XMFLOAT3EX color;
	/*
	FLOAT mul_value;
	FLOAT add_value;
	FLOAT exp_value;
	tml::XMFLOAT3EX attenuation;
	FLOAT range;
	FLOAT range_exp_value;
	FLOAT cut_angle;
	FLOAT soft_angle;
	bool shadow_flag;
	*/

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	LightDesc();
	virtual ~LightDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::LightDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Light�N���X
 */
class Light : public tml::graphic::ManagerResource
{
public: Light(const tml::graphic::Light &) = delete;
public: tml::graphic::Light &operator =(const tml::graphic::Light &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::LIGHT);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::BASE);

private:
	tml::ConstantUtil::GRAPHIC::LIGHT_EFFECT_TYPE effect_type_;
	tml::XMFLOAT3EX col_;
	bool draw_set_flg_;
	/*
	FLOAT mul_val_;
	FLOAT add_val_;
	FLOAT exp_val_;
	tml::XMFLOAT3EX atten_;
	FLOAT rng_;
	FLOAT rng_exp_val_;
	FLOAT cut_angle_;
	FLOAT soft_angle_;
	FLOAT cut_val_;
	FLOAT soft_val_;
	bool shadow_flg_;
	*/

public:
	tml::XMPosition3D position;

private:
	void Release(void);

public:
	Light();
	virtual ~Light();

	virtual void Init(void);
	INT Create(const tml::graphic::LightDesc &);

	tml::ConstantUtil::GRAPHIC::LIGHT_EFFECT_TYPE GetEffectType(void) const;
	const tml::XMFLOAT3EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT3EX &);
	bool GetDrawSetFlag(void) const;
	void SetDrawSetFlag(const bool);
	/*
	FLOAT GetMulValue(void) const;
	void SetMulValue(const FLOAT);
	FLOAT GetAddValue(void) const;
	void SetAddValue(const FLOAT);
	FLOAT GetExpValue(void) const;
	void SetExpValue(const FLOAT);
	const tml::XMFLOAT3EX &GetAttenuation(void) const;
	void SetAttenuation(const tml::XMFLOAT3EX &);
	FLOAT GetRange(void) const;
	void SetRange(const FLOAT);
	FLOAT GetRangeExpValue(void) const;
	void SetRangeExpValue(const FLOAT);
	FLOAT GetCutAngle(void) const;
	void SetCutAngle(const FLOAT);
	FLOAT GetSoftAngle(void) const;
	void SetSoftAngle(const FLOAT);
	FLOAT GetCutValue(void) const;
	FLOAT GetSoftValue(void) const;
	*/
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Light::Release(void)
{
	return;
}


/**
 * @brief GetEffectType�֐�
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::LIGHT_EFFECT_TYPE tml::graphic::Light::GetEffectType(void) const
{
	return (this->effect_type_);
}


/**
 * @brief GetColor�֐�
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Light::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor�֐�
 * @param col (color)
 */
inline void tml::graphic::Light::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}


/**
 * @brief GetDrawSetFlag�֐�
 * @return draw_set_flg (draw_set_flag)
 */
inline bool tml::graphic::Light::GetDrawSetFlag(void) const
{
	return (this->draw_set_flg_);
}


/**
 * @brief SetDrawSetFlag�֐�
 * @param draw_set_flg (draw_set_flag)
 */
inline void tml::graphic::Light::SetDrawSetFlag(const bool draw_set_flg)
{
	this->draw_set_flg_ = draw_set_flg;

	return;
}


#if 0
/**
 * @brief GetMulValue���֐�
 * @return mul_val (mul_value)
 */
inline FLOAT tml::graphic::Light::GetMulValue(void) const
{
	return (this->mul_val_);
}


/**
 * @brief SetMulValue�֐�
 * @param mul_val (mul_value)
 */
inline void tml::graphic::Light::SetMulValue(const FLOAT mul_val)
{
	this->mul_val_ = mul_val;

	return;
}


/**
 * @brief GetAddValue�֐�
 * @return add_val (add_value)
 */
inline FLOAT tml::graphic::Light::GetAddValue(void) const
{
	return (this->add_val_);
}


/**
 * @brief SetAddValue�֐�
 * @param add_val (add_value)
 */
inline void tml::graphic::Light::SetAddValue(const FLOAT add_val)
{
	this->add_val_ = add_val;

	return;
}


/**
 * @brief GetExpValue�֐�
 * @return exp_val (exp_value)
 */
inline FLOAT tml::graphic::Light::GetExpValue(void) const
{
	return (this->exp_val_);
}


/**
 * @brief SetExpValue�֐�
 * @param exp_val (exp_value)
 */
inline void tml::graphic::Light::SetExpValue(const FLOAT exp_val)
{
	this->exp_val_ = exp_val;

	return;
}


/**
 * @brief GetAttenuation�֐�
 * @return atten (attenuation)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Light::GetAttenuation(void) const
{
	return (this->atten_);
}


/**
 * @brief SetAttenuation�֐�
 * @param atten (attenuation)
 */
inline void tml::graphic::Light::SetAttenuation(const tml::XMFLOAT3EX &atten)
{
	this->atten_ = atten;

	return;
}


/**
 * @brief GetRange�֐�
 * @return rng (range)
 */
inline FLOAT tml::graphic::Light::GetRange(void) const
{
	return (this->rng_);
}


/**
 * @brief SetRange�֐�
 * @param rng (range)
 */
inline void tml::graphic::Light::SetRange(const FLOAT rng)
{
	this->rng_ = rng;

	return;
}


/**
 * @brief GetRangeExpValue�֐�
 * @return rng_exp_val (range_exp_value)
 */
inline FLOAT tml::graphic::Light::GetRangeExpValue(void) const
{
	return (this->rng_exp_val_);
}


/**
 * @brief SetRangeExpValue�֐�
 * @param rng_exp_val (range_exp_value)
 */
inline void tml::graphic::Light::SetRangeExpValue(const FLOAT rng_exp_val)
{
	this->rng_exp_val_ = rng_exp_val;

	return;
}


/**
 * @brief GetCutAngle�֐�
 * @return cut_angle (cut_angle)
 */
inline FLOAT tml::graphic::Light::GetCutAngle(void) const
{
	return (this->cut_angle_);
}


/**
 * @brief GetSoftAngle�֐�
 * @return soft_angle (soft_angle)
 */
inline FLOAT tml::graphic::Light::GetSoftAngle(void) const
{
	return (this->soft_angle_);
}


/**
 * @brief GetCutValue�֐�
 * @return cut_val (cut_value)
 */
inline FLOAT tml::graphic::Light::GetCutValue(void) const
{
	return (this->cut_val_);
}


/**
 * @brief GetSoftValue�֐�
 * @return soft_val (soft_value)
 */
inline FLOAT tml::graphic::Light::GetSoftValue(void) const
{
	return (this->soft_val_);
}
#endif
