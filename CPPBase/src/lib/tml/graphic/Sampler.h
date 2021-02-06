/**
 * @file
 * @brief Samplerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief SamplerDescクラス
 */
class SamplerDesc : public tml::graphic::ResourceDesc
{
public:
	CD3D11_SAMPLER_DESC sampler_desc;

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SamplerDesc();
	SamplerDesc(tml::graphic::Manager *);
	SamplerDesc(tml::graphic::Manager *, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE);
	virtual ~SamplerDesc();

	virtual void Init(void);

	void Set(tml::graphic::Manager *, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Samplerクラス
 */
class Sampler : public tml::graphic::Resource
{
public: Sampler(const tml::graphic::Sampler &) = delete;
public: tml::graphic::Sampler &operator =(const tml::graphic::Sampler &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11SamplerState *samp_;

private:
	void Release(void);

public:
	Sampler();
	virtual ~Sampler();

	virtual void Init(void);
	INT Create(const tml::graphic::SamplerDesc &);

	ID3D11SamplerState *GetSampler(void);
	ID3D11SamplerState *GetSR(void);
};
}
}


/**
 * @brief GetSampler関数
 * @return samp (sampler)
 */
inline ID3D11SamplerState *tml::graphic::Sampler::GetSampler(void)
{
	return (this->samp_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11SamplerState *tml::graphic::Sampler::GetSR(void)
{
	return (this->samp_);
}
