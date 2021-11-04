/**
 * @file
 * @brief Fogヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
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
	INT draw_priority;
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
 *
 * インターフェースパターン
 */
class Fog : public tml::graphic::ManagerResource
{
public: Fog(const tml::graphic::Fog &) = delete;
public: tml::graphic::Fog &operator =(const tml::graphic::Fog &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::FOG);

private:
	tml::ConstantUtil::GRAPHIC::FOG_TYPE type_;
	INT draw_priority_;
	UINT draw_set_canvas_cnt_;
	std::vector<const tml::graphic::Canvas *> draw_set_canvas_cont_;
	/*
	FLOAT mul_val_;
	FLOAT near_rng_;
	FLOAT far_rng_;
	FLOAT rng_val1_;
	FLOAT rng_val2_;
	*/

private:
	void Release(void);

public:
	Fog();
	virtual ~Fog();

	virtual void Init(void);
	INT Create(const tml::graphic::FogDesc &);

	tml::ConstantUtil::GRAPHIC::FOG_TYPE GetType(void) const;
	INT GetDrawPriority(void) const;
	void SetDrawPriority(const INT);
	bool IsDrawSet(const tml::graphic::Canvas *) const;
	void SetDrawSet(const tml::graphic::Canvas *);
	void ClearDrawSet(const tml::graphic::Canvas *);
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
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_TYPE tml::graphic::Fog::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetDrawPriority関数
 * @return draw_priority (draw_priority)
 */
inline INT tml::graphic::Fog::GetDrawPriority(void) const
{
	return (this->draw_priority_);
}


/**
 * @brief SetDrawPriority関数
 * @param draw_priority (draw_priority)
 */
inline void tml::graphic::Fog::SetDrawPriority(const INT draw_priority)
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
 * @brief SetDrawSet関数
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
 * @brief ClearDrawSet関数
 */
inline void tml::graphic::Fog::ClearDrawSet(const tml::graphic::Canvas *draw_set_canvas)
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
