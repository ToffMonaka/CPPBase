/**
 * @file
 * @brief Samplerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief SamplerDescクラス
 */
class SamplerDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_SAMPLER_DESC sampler_desc;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SamplerDesc();
	virtual ~SamplerDesc();

	virtual void Init(void);

	void SetSamplerDesc(const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::SamplerDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Samplerクラス
 */
class Sampler : public tml::graphic::ManagerResource
{
public: Sampler(const tml::graphic::Sampler &) = delete;
public: tml::graphic::Sampler &operator =(const tml::graphic::Sampler &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SAMPLER);

private:
	const tml::graphic::SamplerDesc *desc_;
	tml::graphic::Sampler *current_;
	ID3D11SamplerState *samp_;
	CD3D11_SAMPLER_DESC samp_desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Sampler();
	virtual ~Sampler();

	virtual void Init(void);

	const tml::graphic::SamplerDesc *GetDesc(void) const;
	ID3D11SamplerState *GetSampler(void);
	const CD3D11_SAMPLER_DESC &GetSamplerDesc(void) const;
	ID3D11SamplerState *GetSR(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::SamplerDesc *tml::graphic::Sampler::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetSampler関数
 * @return samp (sampler)
 */
inline ID3D11SamplerState *tml::graphic::Sampler::GetSampler(void)
{
	return (this->current_->samp_);
}


/**
 * @brief GetSamplerDesc関数
 * @return samp_desc (sampler_desc)
 */
inline const CD3D11_SAMPLER_DESC &tml::graphic::Sampler::GetSamplerDesc(void) const
{
	return (this->current_->samp_desc_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11SamplerState *tml::graphic::Sampler::GetSR(void)
{
	return (this->current_->samp_);
}
