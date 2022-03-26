/**
 * @file
 * @brief Light2Dコードファイル
 */


#include "Light2D.h"
#include "Manager.h"
#include "Light2DShaderStructuredBuffer.h"
#include "Canvas2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Light2DDesc::Light2DDesc() :
	color(1.0f),
	effect_type(tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Light2DDesc::~Light2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Light2DDesc::Init(void)
{
	this->Release();

	this->transform.Init();
	this->color = 1.0f;
	this->effect_type = tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE::NONE;

	tml::graphic::LightDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Light2DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::LightDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Light2D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"LIGHT_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Light2D::Light2D() :
	desc_(nullptr),
	effect_type_(tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE::NONE),
	color(1.0f),
	draw_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Light2D::~Light2D()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Light2D::Init(void)
{
	this->Release();

	this->effect_type_ = tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE::NONE;

	this->transform.Init();
	this->color = 1.0f;
	this->draw_data = nullptr;

	tml::graphic::Light::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Light2D::OnCreate(void)
{
	if (tml::graphic::Light::OnCreate() < 0) {
		return (-1);
	}

	this->SetDimensionType(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D);

	this->effect_type_ = this->desc_->effect_type;

	this->transform = this->desc_->transform;
	this->color = this->desc_->color;

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Light2D::OnCreateDeferred(void)
{
	if (tml::graphic::Light::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Light2D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Light2DDesc *>(desc);

	tml::graphic::Light::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::Light2D::DrawStageInit(void)
{
	this->draw_data->shader_structured_buffer->SetElement(this->draw_data->shader_structured_buffer_element_index, this);

	return;
}
