/**
 * @file
 * @brief BlendState�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief BlendStateDesc�N���X
 */
class BlendStateDesc : public tml::GraphicResourceDesc
{
public:
	CD3D11_BLEND_DESC desc;
	std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> factor_array;

public:
	BlendStateDesc();
	virtual ~BlendStateDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BlendState�N���X
 */
class BlendState : public tml::GraphicResource
{
public: BlendState(const tml::BlendState &) = delete;
public: tml::BlendState &operator =(const tml::BlendState &) = delete;
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
	INT Create(tml::BlendStateDesc &);

	ID3D11BlendState *Get(void) const;
	const std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> &GetFactorArray(void) const;
};
}


/**
 * @brief Get�֐�
 * @return bs (blend_state)
 */
inline ID3D11BlendState *tml::BlendState::Get(void) const
{
	return (this->bs_);
}


/**
 * @brief GetFactorArray�֐�
 * @return factor_ary (factor_array)
 */
inline const std::array<FLOAT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_FACTOR_COUNT> &tml::BlendState::GetFactorArray(void) const
{
	return (this->factor_ary_);
}
