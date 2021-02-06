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
 * @brief コンストラクタ
 * @param mgr (manager)
 */
tml::graphic::SamplerDesc::SamplerDesc(tml::graphic::Manager *mgr) :
	tml::graphic::ResourceDesc(mgr),
	sampler_desc(CD3D11_DEFAULT())
{
	this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	return;
}


/**
 * @brief コンストラクタ
 * @param mgr (manager)
 * @param samp_desc_type (sampler_desc_type)
 * @param samp_desc_wrap_type (sampler_desc_wrap_type)
 */
tml::graphic::SamplerDesc::SamplerDesc(tml::graphic::Manager *mgr, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE samp_desc_type, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE samp_desc_wrap_type)
{
	this->Set(mgr, samp_desc_type, samp_desc_wrap_type);

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
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SamplerDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
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
 * @brief Set関数
 * @param mgr (manager)
 * @param samp_desc_type (sampler_desc_type)
 * @param samp_desc_wrap_type (sampler_desc_wrap_type)
 */
void tml::graphic::SamplerDesc::Set(tml::graphic::Manager *mgr, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE samp_desc_type, const tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE samp_desc_wrap_type)
{
	this->Init();

	this->manager = mgr;

	switch (samp_desc_type) {
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::BILINEAR: {
		this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::TRILINEAR: {
		this->sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC2: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 2U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC4: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 4U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC8: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 8U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC16: {
		this->sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		this->sampler_desc.MaxAnisotropy = 16U;

		break;
	}
	}

	switch (samp_desc_wrap_type) {
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
INT tml::graphic::Sampler::Create(const tml::graphic::SamplerDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SAMPLER) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateSamplerState(&desc.sampler_desc, &this->samp_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
