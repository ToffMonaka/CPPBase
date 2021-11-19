/**
 * @file
 * @brief Fog3Dコードファイル
 */


#include "Fog3D.h"
#include "Manager.h"
#include "Fog3DShaderStructuredBuffer.h"
#include "Canvas3D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Fog3DDesc::Fog3DDesc() :
	effect_type(tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE::NONE),
	color(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Fog3DDesc::~Fog3DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Fog3DDesc::Init(void)
{
	this->Release();

	this->transform.Init();
	this->effect_type = tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE::NONE;
	this->color = 1.0f;

	tml::graphic::FogDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Fog3DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::FogDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Fog3D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FOG_3D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Fog3D::Fog3D() :
	effect_type_(tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE::NONE),
	col_(1.0f),
	draw_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Fog3D::~Fog3D()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Fog3D::Init(void)
{
	this->Release();

	this->effect_type_ = tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE::NONE;
	this->col_ = 1.0f;

	this->transform.Init();
	this->draw_data = nullptr;

	tml::graphic::Fog::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Fog3D::Create(const tml::graphic::Fog3DDesc &desc)
{
	this->Init();

	if (tml::graphic::Fog::Create(desc) < 0) {
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
void tml::graphic::Fog3D::DrawStageInit(void)
{
	this->draw_data->shader_structured_buffer->SetElement(this->draw_data->shader_structured_buffer_element_index, this);

	return;
}
