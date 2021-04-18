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
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SamplerDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Sampler Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SAMP");

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
	samp_(nullptr),
	samp_desc_(CD3D11_DEFAULT())
{
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

	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Sampler::Init(void)
{
	this->Release();

	this->samp_desc_ = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());
	this->samp_desc_.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Sampler::Create(const tml::graphic::SamplerDesc &desc)
{
	this->Init();

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SAMPLER, 1U) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateSamplerState(&desc.sampler_desc, &this->samp_))) {
		this->Init();

		return (-1);
	}

	this->samp_->GetDesc(&this->samp_desc_);

	return (0);
}
