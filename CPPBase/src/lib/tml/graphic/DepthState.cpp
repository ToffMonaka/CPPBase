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
 * @brief �R���X�g���N�^
 * @param ds_desc_type (depth_state_desc_type)
 */
tml::graphic::DepthStateDesc::DepthStateDesc(const tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE ds_desc_type)
{
	this->Set(ds_desc_type);

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::DepthStateDesc::~DepthStateDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::DepthStateDesc::Init(void)
{
	this->depth_state_desc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief Set�֐�
 * @param ds_desc_type (depth_state_desc_type)
 */
void tml::graphic::DepthStateDesc::Set(const tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE ds_desc_type)
{
	this->Init();

	if (ds_desc_type == tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::DEFAULT) {
		return;
	}

	switch (ds_desc_type) {
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

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::DepthState::Init(void)
{
	this->Release();

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::DepthState::Create(tml::graphic::DepthStateDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::DEPTH_STATE, desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilState(&desc.depth_state_desc, &this->ds_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
