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

	if (tml::graphic::Resource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateSamplerState(&desc.sampler_desc, &this->samp_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
