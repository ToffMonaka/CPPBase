/**
 * @file
 * @brief BlendState�R�[�h�t�@�C��
 */


#include "BlendState.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::BlendStateDesc::BlendStateDesc() :
	blend_state_desc(CD3D11_DEFAULT()),
	factor_array{}
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::BlendStateDesc::~BlendStateDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::BlendStateDesc::Init(void)
{
	this->blend_state_desc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	this->factor_array.fill(0.0f);

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::BlendState::BlendState() :
	bs_(nullptr),
	factor_ary_{}
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::BlendState::~BlendState()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::BlendState::Release(void)
{
	if (this->bs_ != nullptr) {
		this->bs_->Release();

		this->bs_ = nullptr;
	}

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::BlendState::Init(void)
{
	this->Release();

	this->factor_ary_.fill(0.0f);

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::BlendState::Create(tml::graphic::BlendStateDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::BLEND_STATE, desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateBlendState(&desc.blend_state_desc, &this->bs_))) {
		this->Init();

		return (-1);
	}

	this->factor_ary_ = desc.factor_array;

	return (0);
}
