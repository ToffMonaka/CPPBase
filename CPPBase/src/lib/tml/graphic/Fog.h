/**
 * @file
 * @brief Fog�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathPosition.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief FogDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::graphic::FogDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fog�N���X
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
	UINT draw_set_canvas_cnt_;
	std::vector<const tml::graphic::Canvas *> draw_set_canvas_cont_;
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
	bool IsDrawSet(const tml::graphic::Canvas *) const;
	void SetDrawSet(const tml::graphic::Canvas *);
	void ClearDrawSet(void);
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
 * @brief Release�֐�
 */
inline void tml::graphic::Fog::Release(void)
{
	return;
}


/**
 * @brief GetEffectType�֐�
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_EFFECT_TYPE tml::graphic::Fog::GetEffectType(void) const
{
	return (this->effect_type_);
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
 * @brief IsDrawSet�֐�
 * @param draw_set_canvas (draw_set_canvas)
 * @return result_flg (result_flag)<br>
 * false=�Z�b�g����,true=�Z�b�g�L��
 */
inline bool tml::graphic::Fog::IsDrawSet(const tml::graphic::Canvas *draw_set_canvas) const
{
	for (UINT draw_set_canvas_i = 0U; draw_set_canvas_i < this->draw_set_canvas_cnt_; ++draw_set_canvas_i) {
		if (this->draw_set_canvas_cont_[draw_set_canvas_i] == draw_set_canvas) {
			return (true);
		}
	}

	return (false);
}


/**
 * @brief SetDrawSet�֐�
 * @param draw_set_canvas (draw_set_canvas)
 */
inline void tml::graphic::Fog::SetDrawSet(const tml::graphic::Canvas *draw_set_canvas)
{
	if (this->draw_set_canvas_cnt_ >= this->draw_set_canvas_cont_.size()) {
		this->draw_set_canvas_cont_.resize(this->draw_set_canvas_cnt_ + 1U);
	}

	this->draw_set_canvas_cont_[this->draw_set_canvas_cnt_++] = draw_set_canvas;

	return;
}


/**
 * @brief ClearDrawSet�֐�
 */
inline void tml::graphic::Fog::ClearDrawSet(void)
{
	this->draw_set_canvas_cnt_ = 0U;

	return;
}


#if 0
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
#endif
