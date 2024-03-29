/**
 * @file
 * @brief RasterizerStateコードファイル
 */


#include "RasterizerState.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::RasterizerStateDesc::RasterizerStateDesc() :
	rasterizer_state_desc(CD3D11_DEFAULT())
{
	this->rasterizer_state_desc.CullMode = D3D11_CULL_NONE;

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::RasterizerStateDesc::~RasterizerStateDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::RasterizerStateDesc::Init(void)
{
	this->Release();

	this->rasterizer_state_desc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	this->rasterizer_state_desc.CullMode = D3D11_CULL_NONE;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::RasterizerStateDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// RasterizerState Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"RS");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetRasterizerStateDesc関数
 * @param type (type)
 */
void tml::graphic::RasterizerStateDesc::SetRasterizerStateDesc(const tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE type)
{
	this->rasterizer_state_desc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	this->rasterizer_state_desc.CullMode = D3D11_CULL_NONE;

	if (type == tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::DEFAULT) {
		return;
	}

	switch (type) {
	case tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::WIREFRAME: {
		this->rasterizer_state_desc.FillMode = D3D11_FILL_WIREFRAME;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::FRONT_CULLING: {
		this->rasterizer_state_desc.CullMode = D3D11_CULL_FRONT;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::BACK_CULLING: {
		this->rasterizer_state_desc.CullMode = D3D11_CULL_BACK;

		break;
	}
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::RasterizerState::RasterizerState() :
	desc_(nullptr),
	rs_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::RasterizerState::~RasterizerState()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::RasterizerState::Release(void)
{
	if (this->rs_ != nullptr) {
		this->rs_->Release();

		this->rs_ = nullptr;
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::RasterizerState::Init(void)
{
	this->Release();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::RasterizerState::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateRasterizerState(&this->desc_->rasterizer_state_desc, &this->rs_))) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::RasterizerState::OnCreateDeferred(void)
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
void tml::graphic::RasterizerState::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::RasterizerStateDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}
