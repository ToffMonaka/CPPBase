/**
 * @file
 * @brief DepthState�R�[�h�t�@�C��
 */


#include "DepthState.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DepthStateDesc::DepthStateDesc() :
	depth_state_desc(CD3D11_DEFAULT())
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DepthStateDesc::~DepthStateDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::DepthStateDesc::Init(void)
{
	this->depth_state_desc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::DepthState::DepthState() :
	ds_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DepthState::~DepthState()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::DepthState::Release(void)
{
	if (this->ds_ != nullptr) {
		this->ds_->Release();

		this->ds_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DepthState::Init(void)
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
INT tml::DepthState::Create(tml::DepthStateDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilState(&desc.depth_state_desc, &this->ds_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
