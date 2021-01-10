/**
 * @file
 * @brief RasterizerState�R�[�h�t�@�C��
 */


#include "RasterizerState.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::RasterizerStateDesc::RasterizerStateDesc() :
	rasterizer_state_desc(CD3D11_DEFAULT())
{
	this->rasterizer_state_desc.CullMode = D3D11_CULL_NONE;

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::RasterizerStateDesc::~RasterizerStateDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::RasterizerStateDesc::Init(void)
{
	this->rasterizer_state_desc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	this->rasterizer_state_desc.CullMode = D3D11_CULL_NONE;

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::RasterizerState::RasterizerState() :
	rs_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::RasterizerState::~RasterizerState()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::RasterizerState::Release(void)
{
	if (this->rs_ != nullptr) {
		this->rs_->Release();

		this->rs_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::RasterizerState::Init(void)
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
INT tml::RasterizerState::Create(tml::RasterizerStateDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateRasterizerState(&desc.rasterizer_state_desc, &this->rs_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
