/**
 * @file
 * @brief Lightヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/Transform.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief LightDescクラス
 */
class LightDesc : public tml::graphic::ManagerResourceDesc
{
public:
	INT draw_priority;
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
 * @brief Release関数
 */
inline void tml::graphic::LightDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Lightクラス
 *
 * インターフェースパターン
 */
class Light : public tml::graphic::ManagerResource
{
public: Light(const tml::graphic::Light &) = delete;
public: tml::graphic::Light &operator =(const tml::graphic::Light &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::LIGHT);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::BASE);

private:
	tml::ConstantUtil::GRAPHIC::LIGHT_TYPE type_;
	tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE dimension_type_;
	INT draw_priority_;
	UINT draw_set_canvas_cnt_;
	std::vector<const tml::graphic::Canvas *> draw_set_canvas_cont_;
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

private:
	void Release(void);

public:
	Light();
	virtual ~Light();

	virtual void Init(void);
	INT Create(const tml::graphic::LightDesc &, const tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE);

	tml::ConstantUtil::GRAPHIC::LIGHT_TYPE GetType(void) const;
	tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE GetDimensionType(void) const;
	INT GetDrawPriority(void) const;
	void SetDrawPriority(const INT);
	bool IsDrawSet(const tml::graphic::Canvas *) const;
	void SetDrawSet(const tml::graphic::Canvas *);
	void ClearDrawSet(const tml::graphic::Canvas *);
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

	virtual void DrawStageInit(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light::Release(void)
{
	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::LIGHT_TYPE tml::graphic::Light::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetDimensionType関数
 * @return dimension_type (dimension_type)
 */
inline tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE tml::graphic::Light::GetDimensionType(void) const
{
	return (this->dimension_type_);
}


/**
 * @brief GetDrawPriority関数
 * @return draw_priority (draw_priority)
 */
inline INT tml::graphic::Light::GetDrawPriority(void) const
{
	return (this->draw_priority_);
}


/**
 * @brief SetDrawPriority関数
 * @param draw_priority (draw_priority)
 */
inline void tml::graphic::Light::SetDrawPriority(const INT draw_priority)
{
	this->draw_priority_ = draw_priority;

	return;
}


/**
 * @brief IsDrawSet関数
 * @param draw_set_canvas (draw_set_canvas)
 * @return result_flg (result_flag)<br>
 * false=セット無し,true=セット有り
 */
inline bool tml::graphic::Light::IsDrawSet(const tml::graphic::Canvas *draw_set_canvas) const
{
	for (UINT draw_set_canvas_i = 0U; draw_set_canvas_i < this->draw_set_canvas_cnt_; ++draw_set_canvas_i) {
		if (this->draw_set_canvas_cont_[draw_set_canvas_i] == draw_set_canvas) {
			return (true);
		}
	}

	return (false);
}


/**
 * @brief SetDrawSet関数
 * @param draw_set_canvas (draw_set_canvas)
 */
inline void tml::graphic::Light::SetDrawSet(const tml::graphic::Canvas *draw_set_canvas)
{
	if (this->draw_set_canvas_cnt_ >= this->draw_set_canvas_cont_.size()) {
		this->draw_set_canvas_cont_.resize(this->draw_set_canvas_cnt_ + 1U);
	}

	this->draw_set_canvas_cont_[this->draw_set_canvas_cnt_++] = draw_set_canvas;

	return;
}


/**
 * @brief ClearDrawSet関数
 */
inline void tml::graphic::Light::ClearDrawSet(const tml::graphic::Canvas *draw_set_canvas)
{
	for (UINT draw_set_canvas_i = 0U; draw_set_canvas_i < this->draw_set_canvas_cnt_; ++draw_set_canvas_i) {
		if (this->draw_set_canvas_cont_[draw_set_canvas_i] == draw_set_canvas) {
			--this->draw_set_canvas_cnt_;

			this->draw_set_canvas_cont_[draw_set_canvas_i] = this->draw_set_canvas_cont_[this->draw_set_canvas_cnt_];

			break;
		}
	}

	return;
}


#if 0
/**
 * @brief GetMulValue得関数
 * @return mul_val (mul_value)
 */
inline FLOAT tml::graphic::Light::GetMulValue(void) const
{
	return (this->mul_val_);
}


/**
 * @brief SetMulValue関数
 * @param mul_val (mul_value)
 */
inline void tml::graphic::Light::SetMulValue(const FLOAT mul_val)
{
	this->mul_val_ = mul_val;

	return;
}


/**
 * @brief GetAddValue関数
 * @return add_val (add_value)
 */
inline FLOAT tml::graphic::Light::GetAddValue(void) const
{
	return (this->add_val_);
}


/**
 * @brief SetAddValue関数
 * @param add_val (add_value)
 */
inline void tml::graphic::Light::SetAddValue(const FLOAT add_val)
{
	this->add_val_ = add_val;

	return;
}


/**
 * @brief GetExpValue関数
 * @return exp_val (exp_value)
 */
inline FLOAT tml::graphic::Light::GetExpValue(void) const
{
	return (this->exp_val_);
}


/**
 * @brief SetExpValue関数
 * @param exp_val (exp_value)
 */
inline void tml::graphic::Light::SetExpValue(const FLOAT exp_val)
{
	this->exp_val_ = exp_val;

	return;
}


/**
 * @brief GetAttenuation関数
 * @return atten (attenuation)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Light::GetAttenuation(void) const
{
	return (this->atten_);
}


/**
 * @brief SetAttenuation関数
 * @param atten (attenuation)
 */
inline void tml::graphic::Light::SetAttenuation(const tml::XMFLOAT3EX &atten)
{
	this->atten_ = atten;

	return;
}


/**
 * @brief GetRange関数
 * @return rng (range)
 */
inline FLOAT tml::graphic::Light::GetRange(void) const
{
	return (this->rng_);
}


/**
 * @brief SetRange関数
 * @param rng (range)
 */
inline void tml::graphic::Light::SetRange(const FLOAT rng)
{
	this->rng_ = rng;

	return;
}


/**
 * @brief GetRangeExpValue関数
 * @return rng_exp_val (range_exp_value)
 */
inline FLOAT tml::graphic::Light::GetRangeExpValue(void) const
{
	return (this->rng_exp_val_);
}


/**
 * @brief SetRangeExpValue関数
 * @param rng_exp_val (range_exp_value)
 */
inline void tml::graphic::Light::SetRangeExpValue(const FLOAT rng_exp_val)
{
	this->rng_exp_val_ = rng_exp_val;

	return;
}


/**
 * @brief GetCutAngle関数
 * @return cut_angle (cut_angle)
 */
inline FLOAT tml::graphic::Light::GetCutAngle(void) const
{
	return (this->cut_angle_);
}


/**
 * @brief GetSoftAngle関数
 * @return soft_angle (soft_angle)
 */
inline FLOAT tml::graphic::Light::GetSoftAngle(void) const
{
	return (this->soft_angle_);
}


/**
 * @brief GetCutValue関数
 * @return cut_val (cut_value)
 */
inline FLOAT tml::graphic::Light::GetCutValue(void) const
{
	return (this->cut_val_);
}


/**
 * @brief GetSoftValue関数
 * @return soft_val (soft_value)
 */
inline FLOAT tml::graphic::Light::GetSoftValue(void) const
{
	return (this->soft_val_);
}
#endif
