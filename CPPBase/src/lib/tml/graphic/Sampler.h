/**
 * @file
 * @brief Samplerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief SamplerDescクラス
 */
class SamplerDesc : public tml::GraphicResourceDesc
{
public:
	CD3D11_SAMPLER_DESC desc;

public:
	SamplerDesc();
	virtual ~SamplerDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Samplerクラス
 */
class Sampler : public tml::GraphicResource
{
public: Sampler(const tml::Sampler &) = delete;
public: tml::Sampler &operator =(const tml::Sampler &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11SamplerState *samp_;

private:
	void Release(void);

public:
	Sampler();
	virtual ~Sampler();

	virtual void Init(void);
	INT Create(const tml::SamplerDesc &);

	ID3D11SamplerState *Get(void) const;
};
}


/**
 * @brief Get関数
 * @return samp (sampler)
 */
inline ID3D11SamplerState *tml::Sampler::Get(void) const
{
	return (this->samp_);
}
