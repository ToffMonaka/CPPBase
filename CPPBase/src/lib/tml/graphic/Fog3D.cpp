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
	color(1.0f),
	effect_type(tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE::NONE)
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
	this->color = 1.0f;
	this->effect_type = tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE::NONE;

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
	desc_(nullptr),
	effect_type_(tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE::NONE),
	color(1.0f),
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

	this->transform.Init();
	this->color = 1.0f;
	this->draw_data = nullptr;

	tml::graphic::Fog::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Fog3D::OnCreate(void)
{
	if (tml::graphic::Fog::OnCreate() < 0) {
		return (-1);
	}

	this->SetDimensionType(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D);

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
INT tml::graphic::Fog3D::OnCreateDeferred(void)
{
	if (tml::graphic::Fog::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Fog3D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Fog3DDesc *>(desc);

	tml::graphic::Fog::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::Fog3D::DrawStageInit(void)
{
	this->draw_data->shader_structured_buffer->SetElement(this->draw_data->shader_structured_buffer_element_index, this);

	return;
}
