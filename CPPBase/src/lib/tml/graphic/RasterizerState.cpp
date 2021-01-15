/**
 * @file
 * @brief RasterizerState�R�[�h�t�@�C��
 */


#include "RasterizerState.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::RasterizerStateDesc::RasterizerStateDesc() :
	rasterizer_state_desc(CD3D11_DEFAULT())
{
	this->rasterizer_state_desc.CullMode = D3D11_CULL_NONE;

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::RasterizerStateDesc::~RasterizerStateDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::RasterizerStateDesc::Init(void)
{
	this->rasterizer_state_desc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	this->rasterizer_state_desc.CullMode = D3D11_CULL_NONE;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief SetRasterizerStateDesc�֐�
 * @param type (type)
 */
void tml::graphic::RasterizerStateDesc::SetRasterizerStateDesc(const tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE type)
{
	auto &desc = this->rasterizer_state_desc;

	desc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	desc.CullMode = D3D11_CULL_NONE;

	if (type == tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::DEFAULT) {
		return;
	}

	switch (type) {
	case tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::WIREFRAME: {
		desc.FillMode = D3D11_FILL_WIREFRAME;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::FRONT_CULLING: {
		desc.CullMode = D3D11_CULL_FRONT;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::BACK_CULLING: {
		desc.CullMode = D3D11_CULL_BACK;

		break;
	}
	}

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::RasterizerState::RasterizerState() :
	rs_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::RasterizerState::~RasterizerState()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::RasterizerState::Release(void)
{
	if (this->rs_ != nullptr) {
		this->rs_->Release();

		this->rs_ = nullptr;
	}

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::RasterizerState::Init(void)
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
INT tml::graphic::RasterizerState::Create(tml::graphic::RasterizerStateDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::RASTERIZER_STATE, desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateRasterizerState(&desc.rasterizer_state_desc, &this->rs_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
