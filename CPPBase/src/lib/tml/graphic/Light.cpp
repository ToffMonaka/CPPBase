/**
 * @file
 * @brief Light�R�[�h�t�@�C��
 */


#include "Light.h"
#include "Manager.h"
#include "Canvas.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::LightDesc::LightDesc() :
	draw_priority(0)
	/*
	mul_value(0.0f),
	add_value(0.0f),
	exp_value(1.0f),
	attenuation(0.0f),
	range(0.0f),
	range_exp_value(1.0f),
	cut_angle(0.0f),
	soft_angle(0.0f),
	shadow_flag(false)
	*/
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::LightDesc::~LightDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::LightDesc::Init(void)
{
	this->Release();

	/*
	this->mul_value = 0.0f;
	this->add_value = 0.0f;
	this->exp_value = 1.0f;
	this->attenuation = 0.0f;
	this->range = 0.0f;
	this->range_exp_value = 1.0f;
	this->cut_angle = 0.0f;
	this->soft_angle = 0.0f;
	this->shadow_flag = false;
	*/

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::LightDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Light Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"LIGHT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Light::Light() :
	desc_(nullptr),
	dimension_type_(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE),
	draw_priority_(0),
	draw_set_canvas_cnt_(0U)
	/*
	mul_val_(0.0f),
	add_val_(0.0f),
	exp_val_(1.0f),
	atten_(0.0f),
	rng_(0.0f),
	rng_exp_val_(1.0f),
	cut_angle_(0.0f),
	soft_angle_(0.0f),
	cut_val_(0.0f),
	soft_val_(0.0f),
	shadow_flg_(false)
	*/
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Light::~Light()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Light::Init(void)
{
	this->Release();

	this->dimension_type_ = tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE;
	this->draw_priority_ = 0;
	this->draw_set_canvas_cnt_ = 0U;
	this->draw_set_canvas_cont_.clear();
	/*
	this->mul_val_ = 0.0f;
	this->add_val_ = 0.0f;
	this->exp_val_ = 1.0f;
	this->atten_ = 0.0f;
	this->rng_ = 0.0f;
	this->rng_exp_val_ = 1.0f;
	this->cut_angle_ = 0.0f;
	this->soft_angle_ = 0.0f;
	this->cut_val_ = 0.0f;
	this->soft_val_ = 0.0f;
	this->shadow_flg_ = false;
	*/

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Light::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	this->draw_priority_ = this->desc_->draw_priority;

	/*
	this->mul_val_ = this->desc_->mul_value;
	this->add_val_ = this->desc_->add_value;
	this->exp_val_ = this->desc_->exp_value;
	this->atten_ = this->desc_->attenuation;
	this->rng_ = this->desc_->range;
	this->rng_exp_val_ = this->desc_->range_exp_value;
	this->SetCutAngle(this->desc_->cut_angle);
	this->SetSoftAngle(this->desc_->soft_angle);
	this->shadow_flg_ = this->desc_->shadow_flag;
	*/

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Light::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::graphic::Light::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::LightDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}


#if 0
/**
 * @brief SetCutAngle�֐�
 * @param cut_angle (cut_angle)
 */
void tml::graphic::Light::SetCutAngle(const FLOAT cut_angle)
{
	this->cut_angle_ = cut_angle;

	switch (this->type_) {
	case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::POINT:
	case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::SPOT: {
		this->cut_val_ = cos(this->cut_angle_ * 0.5f);
		this->soft_val_ = cos(this->cut_angle_ * 0.5f - this->soft_angle_ * 0.5f);

		break;
	}
	default: {
		this->cut_val_ = this->cut_angle_;

		break;
	}
	}

	return;
}


/**
 * @brief SetSoftAngle�֐�
 * @param soft_angle (soft_angle)
 */
void tml::graphic::Light::SetSoftAngle(const FLOAT soft_angle)
{
	this->soft_angle_ = soft_angle;

	switch (this->type_) {
	case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::POINT:
	case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::SPOT: {
		this->soft_val_ = cos(this->cut_angle_ * 0.5f - this->soft_angle_ * 0.5f);

		break;
	}
	default: {
		this->soft_val_ = this->soft_angle_;

		break;
	}
	}

	return;
}
#endif


/**
 * @brief DrawStageInit�֐�
 */
void tml::graphic::Light::DrawStageInit(void)
{
	return;
}
