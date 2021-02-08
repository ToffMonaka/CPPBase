/**
 * @file
 * @brief Light�R�[�h�t�@�C��
 */


#include "Light.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::LightDesc::LightDesc() :
	type(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE),
	position_set_flag(true),
	color(0.0f),
	mul_value(0.0f),
	add_value(0.0f),
	exp_value(1.0f),
	attenuation(0.0f),
	range(0.0f),
	range_exp_value(1.0f),
	cut_angle(0.0f),
	soft_angle(0.0f),
	shadow_flag(false)
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

	this->type = tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE;
	this->position.Init();
	this->position_set_flag = true;
	this->color = 0.0f;
	this->mul_value = 0.0f;
	this->add_value = 0.0f;
	this->exp_value = 1.0f;
	this->attenuation = 0.0f;
	this->range = 0.0f;
	this->range_exp_value = 1.0f;
	this->cut_angle = 0.0f;
	this->soft_angle = 0.0f;
	this->shadow_flag = false;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::LightDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Light Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"LIGHT");

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
	type_(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE),
	col_(0.0f),
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

	this->type_ = tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE;
	this->position.reset();
	this->col_ = 0.0f;
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

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param pos (position)<br>
 * nullptr=�w�薳��
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Light::Create(const tml::graphic::LightDesc &desc, tml::shared_ptr<tml::XMPosition> *pos)
{
	if (desc.type == tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::LIGHT) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = desc.type;

	if ((pos != nullptr)
	&& ((*pos) != nullptr)) {
		this->position = (*pos);
	} else {
		this->position = tml::make_shared<tml::XMPosition>(1U);
	}

	if (desc.position_set_flag) {
		(*this->position) = desc.position;
	}

	this->col_ = desc.color;
	this->mul_val_ = desc.mul_value;
	this->add_val_ = desc.add_value;
	this->exp_val_ = desc.exp_value;
	this->atten_ = desc.attenuation;
	this->rng_ = desc.range;
	this->rng_exp_val_ = desc.range_exp_value;
	this->SetCutAngle(desc.cut_angle);
	this->SetSoftAngle(desc.soft_angle);
	this->shadow_flg_ = desc.shadow_flag;

	return (0);
}


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
