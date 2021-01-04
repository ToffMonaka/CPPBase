/**
 * @file
 * @brief Lightコードファイル
 */


#include "Light.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::LightDesc::LightDesc() :
	type(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE),
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
 * @brief デストラクタ
 */
tml::LightDesc::~LightDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::LightDesc::Init(void)
{
	this->type = tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE;
	this->position.Init();
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

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Light::Light() :
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
 * @brief デストラクタ
 */
tml::Light::~Light()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Light::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Light::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::NONE;
	this->position.Init();
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

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Light::Create(const tml::LightDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = desc.type;
	this->position = desc.position;
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
 * @brief SetCutAngle関数
 * @param cut_angle (cut_angle)
 */
void tml::Light::SetCutAngle(const FLOAT cut_angle)
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
 * @brief SetSoftAngle関数
 * @param soft_angle (soft_angle)
 */
void tml::Light::SetSoftAngle(const FLOAT soft_angle)
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
