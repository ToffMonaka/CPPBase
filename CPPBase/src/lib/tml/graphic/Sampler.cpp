/**
 * @file
 * @brief Sampler�R�[�h�t�@�C��
 */


#include "Sampler.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::SamplerDesc::SamplerDesc() :
	sampler_desc(CD3D11_DEFAULT())
{
	this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::SamplerDesc::~SamplerDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::SamplerDesc::Init(void)
{
	this->sampler_desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::Sampler::Sampler() :
	samp_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Sampler::~Sampler()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::Sampler::Release(void)
{
	if (this->samp_ != nullptr) {
		this->samp_->Release();

		this->samp_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::Sampler::Init(void)
{
	this->Release();

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::Sampler::Create(tml::SamplerDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateSamplerState(&desc.sampler_desc, &this->samp_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
