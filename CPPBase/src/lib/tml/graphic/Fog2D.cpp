/**
 * @file
 * @brief Fog2D�R�[�h�t�@�C��
 */


#include "Fog2D.h"
#include "Manager.h"
#include "Fog2DShaderStructuredBuffer.h"
#include "Canvas2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Fog2DDesc::Fog2DDesc() :
	color(1.0f),
	effect_type(tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Fog2DDesc::~Fog2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Fog2DDesc::Init(void)
{
	this->Release();

	this->transform.Init();
	this->color = 1.0f;
	this->effect_type = tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE::NONE;

	tml::graphic::FogDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Fog2DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::FogDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Fog2D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FOG_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Fog2D::Fog2D() :
	desc_(nullptr),
	effect_type_(tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE::NONE),
	color(1.0f),
	draw_data(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Fog2D::~Fog2D()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Fog2D::Init(void)
{
	this->Release();

	this->effect_type_ = tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE::NONE;

	this->transform.Init();
	this->color = 1.0f;
	this->draw_data = nullptr;

	tml::graphic::Fog::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Fog2D::OnCreate(void)
{
	if (tml::graphic::Fog::OnCreate() < 0) {
		return (-1);
	}

	this->SetDimensionType(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D);

	this->effect_type_ = this->desc_->effect_type;

	this->transform = this->desc_->transform;
	this->color = this->desc_->color;

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Fog2D::OnCreateDeferred(void)
{
	if (tml::graphic::Fog::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::graphic::Fog2D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Fog2DDesc *>(desc);

	tml::graphic::Fog::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief DrawStageInit�֐�
 */
void tml::graphic::Fog2D::DrawStageInit(void)
{
	this->draw_data->shader_structured_buffer->SetElement(this->draw_data->shader_structured_buffer_element_index, this);

	return;
}
