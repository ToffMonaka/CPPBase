/**
 * @file
 * @brief BlendStateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief BlendStateDescクラス
 */
class BlendStateDesc : public tml::graphic::ResourceDesc
{
public:
	CD3D11_BLEND_DESC blend_state_desc;
	std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> factor_array;

public:
	BlendStateDesc();
	virtual ~BlendStateDesc();

	virtual void Init(void);

	void SetBlendStateDesc(const tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE, const tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE, const UINT);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief BlendStateクラス
 */
class BlendState : public tml::graphic::Resource
{
public: BlendState(const tml::graphic::BlendState &) = delete;
public: tml::graphic::BlendState &operator =(const tml::graphic::BlendState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11BlendState *bs_;
	std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> factor_ary_;

private:
	void Release(void);

public:
	BlendState();
	virtual ~BlendState();

	virtual void Init(void);
	INT Create(tml::graphic::BlendStateDesc &);

	ID3D11BlendState *GetBlendState(void) const;
	const std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> &GetFactorArray(void) const;
};
}
}


/**
 * @brief GetBlendState関数
 * @return bs (blend_state)
 */
inline ID3D11BlendState *tml::graphic::BlendState::GetBlendState(void) const
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
