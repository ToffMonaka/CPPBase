/**
 * @file
 * @brief DepthState�R�[�h�t�@�C��
 */


#include "DepthState.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::DepthStateDesc::DepthStateDesc() :
	depth_state_desc(CD3D11_DEFAULT())
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::DepthStateDesc::~DepthStateDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::DepthStateDesc::Init(void)
{
	this->Release();

	this->depth_state_desc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::DepthStateDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// DepthState Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"DS");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetDepthStateDesc�֐�
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
 * @brief �R���X�g���N�^
 */
tml::graphic::DepthState::DepthState() :
	desc_(nullptr),
	ds_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::DepthState::~DepthState()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::DepthState::Release(void)
{
	if (this->ds_ != nullptr) {
		this->ds_->Release();

		this->ds_ = nullptr;
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::DepthState::Init(void)
{
	this->Release();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::DepthState::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilState(&this->desc_->depth_state_desc, &this->ds_))) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::DepthState::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::graphic::DepthState::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::DepthStateDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}
