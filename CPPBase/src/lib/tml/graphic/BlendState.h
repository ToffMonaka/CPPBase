/**
 * @file
 * @brief BlendStateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief BlendStateDescクラス
 */
class BlendStateDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_BLEND_DESC blend_state_desc;
	std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> factor_array;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	BlendStateDesc();
	virtual ~BlendStateDesc();

	virtual void Init(void);

	void SetBlendStateDesc(const tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE, const tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE, const UINT);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::BlendStateDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief BlendStateクラス
 */
class BlendState : public tml::graphic::ManagerResource
{
public: BlendState(const tml::graphic::BlendState &) = delete;
public: tml::graphic::BlendState &operator =(const tml::graphic::BlendState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::BLEND_STATE);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::BLEND_STATE_TYPE::BASE);

private:
	ID3D11BlendState *bs_;
	std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> factor_ary_;

private:
	void Release(void);

public:
	BlendState();
	virtual ~BlendState();

	virtual void Init(void);
	INT Create(const tml::graphic::BlendStateDesc &);

	ID3D11BlendState *GetBlendState(void);
	const std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> &GetFactorArray(void) const;
	void SetFactorArray(const std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> &);
	FLOAT GetFactor(const UINT) const;
	void SetFactor(const UINT, FLOAT);
};
}
}


/**
 * @brief GetBlendState関数
 * @return bs (blend_state)
 */
inline ID3D11BlendState *tml::graphic::BlendState::GetBlendState(void)
{
	return (this->bs_);
}


/**
 * @brief GetFactorArray関数
 * @return factor_ary (factor_array)
 */
inline const std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> &tml::graphic::BlendState::GetFactorArray(void) const
{
	return (this->factor_ary_);
}


/**
 * @brief SetFactorArray関数
 * @param factor_ary (factor_array)
 */
inline void tml::graphic::BlendState::SetFactorArray(const std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> &factor_ary)
{
	this->factor_ary_ = factor_ary;

	return;
}


/**
 * @brief GetFactor関数
 * @param index (index)
 * @return factor (factor)
 */
inline FLOAT tml::graphic::BlendState::GetFactor(const UINT index) const
{
	return (this->factor_ary_[index]);
}


/**
 * @brief SetFactor関数
 * @param index (index)
 * @param factor (factor)
 */
inline void tml::graphic::BlendState::SetFactor(const UINT index, const FLOAT factor)
{
	this->factor_ary_[index] = factor;

	return;
}
