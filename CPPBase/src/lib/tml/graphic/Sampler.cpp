/**
 * @file
 * @brief Samplerコードファイル
 */


#include "Sampler.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::SamplerDesc::SamplerDesc() :
	sampler_desc(CD3D11_DEFAULT())
{
	this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SamplerDesc::~SamplerDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SamplerDesc::Init(void)
{
	this->sampler_desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief SetSamplerDesc関数
 * @param type (type)
 * @param wrap_type (wrap_type)
 */
void tml::graphic::SamplerDesc::SetSamplerDesc(const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE type, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE wrap_type)
{
	auto &desc = this->sampler_desc;

	desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	switch (type) {
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::BILINEAR: {
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::TRILINEAR: {
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC2: {
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		desc.MaxAnisotropy = 2U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC4: {
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		desc.MaxAnisotropy = 4U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC8: {
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		desc.MaxAnisotropy = 8U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC16: {
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		desc.MaxAnisotropy = 16U;

		break;
	}
	}

	switch (wrap_type) {
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CC: {
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CW: {
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WC: {
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WW: {
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;

		break;
	}
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Sampler::Sampler() :
	samp_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Sampler::~Sampler()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Sampler::Release(void)
{
	if (this->samp_ != nullptr) {
		this->samp_->Release();

		this->samp_ = nullptr;
	}

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Sampler::Init(void)
{
	this->Release();

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Sampler::Create(tml::graphic::SamplerDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SAMPLER, desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateSamplerState(&desc.sampler_desc, &this->samp_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
