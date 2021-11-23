/**
 * @file
 * @brief Light3Dコードファイル
 */


#include "Light3D.h"
#include "Manager.h"
#include "Light3DShaderStructuredBuffer.h"
#include "Canvas3D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Light3DDesc::Light3DDesc() :
	effect_type(tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE::NONE),
	color(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Light3DDesc::~Light3DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Light3DDesc::Init(void)
{
	this->Release();

	this->transform.Init();
	this->effect_type = tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE::NONE;
	this->color = 1.0f;

	tml::graphic::LightDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Light3DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::LightDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Light3D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"LIGHT_3D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Light3D::Light3D() :
	effect_type_(tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE::NONE),
	col_(1.0f),
	draw_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Light3D::~Light3D()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Light3D::Init(void)
{
	this->Release();

	this->effect_type_ = tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE::NONE;
	this->col_ = 1.0f;

	this->transform.Init();
	this->draw_data = nullptr;

	tml::graphic::Light::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Light3D::Create(const tml::graphic::Light3DDesc &desc)
{
	this->Init();

	if (tml::graphic::Light::Create(desc, tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3) < 0) {
		this->Init();

		return (-1);
	}

	this->effect_type_ = desc.effect_type;
	this->col_ = desc.color;

	this->transform = desc.transform;

	return (0);
}


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::Light3D::DrawStageInit(void)
{
	this->draw_data->shader_structured_buffer->SetElement(this->draw_data->shader_structured_buffer_element_index, this);

	return;
}
