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
	effect_type(tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE::NONE),
	color(1.0f)
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
	this->effect_type = tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE::NONE;
	this->color = 1.0f;

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
	effect_type_(tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE::NONE),
	col_(1.0f),
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
	this->col_ = 1.0f;

	this->transform.Init();
	this->draw_data = nullptr;

	tml::graphic::Fog::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Fog2D::Create(const tml::graphic::Fog2DDesc &desc)
{
	this->Init();

	if (tml::graphic::Fog::Create(desc, tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2) < 0) {
		this->Init();

		return (-1);
	}

	this->effect_type_ = desc.effect_type;
	this->col_ = desc.color;

	this->transform = desc.transform;

	return (0);
}


/**
 * @brief DrawStageInit�֐�
 */
void tml::graphic::Fog2D::DrawStageInit(void)
{
	this->draw_data->shader_structured_buffer->SetElement(this->draw_data->shader_structured_buffer_element_index, this);

	return;
}
