/**
 * @file
 * @brief DepthStateコードファイル
 */


#include "DepthState.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::DepthStateDesc::DepthStateDesc() :
	depth_state_desc(CD3D11_DEFAULT())
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::DepthStateDesc::~DepthStateDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::DepthStateDesc::Init(void)
{
	this->Release();

	this->depth_state_desc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::DepthStateDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// DepthState Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"DS");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetDepthStateDesc関数
 * @param type (type)
 */
void tml::graphic::DepthStateDesc::SetDepthStateDesc(const tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE type)
{
	this->depth_state_desc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

	if (type == tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::DEFAULT) {
		return;
	}

	switch (type) {
	case tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::REFERENCE: {
		this->depth_state_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

		break;
	}
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::DepthState::DepthState() :
	ds_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::DepthState::~DepthState()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::DepthState::Release(void)
{
	if (this->ds_ != nullptr) {
		this->ds_->Release();

		this->ds_ = nullptr;
	}

	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::DepthState::Init(void)
{
	this->Release();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::DepthState::Create(const tml::graphic::DepthStateDesc &desc)
{
	this->Init();

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::DEPTH_STATE, 1U) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilState(&desc.depth_state_desc, &this->ds_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
