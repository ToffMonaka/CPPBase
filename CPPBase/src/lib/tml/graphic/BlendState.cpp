/**
 * @file
 * @brief BlendState�R�[�h�t�@�C��
 */


#include "BlendState.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::BlendStateDesc::BlendStateDesc() :
	desc(CD3D11_DEFAULT()),
	factor_array{}
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::BlendStateDesc::~BlendStateDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::BlendStateDesc::Init(void)
{
	this->desc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	this->factor_array.fill(0.0f);

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::BlendState::BlendState() :
	bs_(nullptr),
	factor_ary_{}
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::BlendState::~BlendState()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::BlendState::Release(void)
{
	if (this->bs_ != nullptr) {
		this->bs_->Release();

		this->bs_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::BlendState::Init(void)
{
	this->Release();

	this->factor_ary_.fill(0.0f);

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::BlendState::Create(tml::BlendStateDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateBlendState(&desc.desc, &this->bs_))) {
		this->Init();

		return (-1);
	}

	this->factor_ary_ = desc.factor_array;

	return (0);
}
