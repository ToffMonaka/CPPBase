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
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SamplerDesc::Init(void)
{
	this->Release();

	this->sampler_desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SamplerDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Sampler Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SAMP");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetSamplerDesc関数
 * @param bind_flg (bind_flag)
 * @param quality_type (quality_type)
 * @param wrap_type (wrap_type)
 */
void tml::graphic::SamplerDesc::SetSamplerDesc(const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG bind_flg, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE quality_type, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE wrap_type)
{
	this->sampler_desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	switch (quality_type) {
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE::BILINEAR: {
		this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE::TRILINEAR: {
		this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE::ANISOTROPIC2: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 2U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE::ANISOTROPIC4: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 4U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE::ANISOTROPIC8: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 8U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_QUALITY_TYPE::ANISOTROPIC16: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 16U;

		break;
	}
	}

	switch (wrap_type) {
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CC: {
		this->sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		this->sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CW: {
		this->sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		this->sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WC: {
		this->sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		this->sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WW: {
		this->sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		this->sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;

		break;
	}
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Sampler::Sampler() :
	desc_(nullptr),
	samp_(nullptr),
	samp_desc_(CD3D11_DEFAULT())
{
	this->current_ = this;
	this->samp_desc_.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

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

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Sampler::Init(void)
{
	this->Release();

	this->current_ = this;
	this->samp_desc_ = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	this->samp_desc_.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Sampler::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateSamplerState(&this->desc_->sampler_desc, &this->samp_))) {
		return (-1);
	}

	this->samp_->GetDesc(&this->samp_desc_);

	this->current_ = this;

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Sampler::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Sampler::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::SamplerDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}
