/**
 * @file
 * @brief Fogコードファイル
 */


#include "Fog.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::FogDesc::FogDesc() :
	type(tml::ConstantUtil::GRAPHIC::FOG_TYPE::NONE),
	color(0.0f),
	mul_value(0.0f),
	near_range(0.0f),
	far_range(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FogDesc::~FogDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FogDesc::Init(void)
{
	this->type = tml::ConstantUtil::GRAPHIC::FOG_TYPE::NONE;
	this->position.Init();
	this->color = 0.0f;
	this->mul_value = 0.0f;
	this->near_range = 0.0f;
	this->far_range = 0.0f;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Fog::Fog() :
	type_(tml::ConstantUtil::GRAPHIC::FOG_TYPE::NONE),
	col_(0.0f),
	mul_val_(0.0f),
	near_rng_(0.0f),
	far_rng_(0.0f),
	rng_val1_(0.0f),
	rng_val2_(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Fog::~Fog()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Fog::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Fog::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::FOG_TYPE::NONE;
	this->position.Init();
	this->col_ = 0.0f;
	this->mul_val_ = 0.0f;
	this->near_rng_ = 0.0f;
	this->far_rng_ = 0.0f;
	this->rng_val1_ = 0.0f;
	this->rng_val2_ = 0.0f;

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Fog::Create(tml::graphic::FogDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::FOG, desc) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = tml::ConstantUtil::GRAPHIC::FOG_TYPE::NONE;
	this->position.Init();
	this->col_ = 0.0f;
	this->mul_val_ = 0.0f;
	this->SetNearRange(desc.near_range);
	this->SetFarRange(desc.far_range);

	return (0);
}


/**
 * @brief SetNearRange関数
 * @param near_rng (near_range)
 */
void tml::graphic::Fog::SetNearRange(const FLOAT near_rng)
{
	this->near_rng_ = near_rng;

	switch (this->type_) {
	case tml::ConstantUtil::GRAPHIC::FOG_TYPE::WIDTH:
	case tml::ConstantUtil::GRAPHIC::FOG_TYPE::HEIGHT: {
		if ((this->far_rng_ - this->near_rng_) != 0.0f) {
			this->rng_val1_ = this->far_rng_ / (this->far_rng_ - this->near_rng_);
			this->rng_val2_ = -1.0f / (this->far_rng_ - this->near_rng_);
		} else {
			this->rng_val1_ = this->far_rng_;
			this->rng_val2_ = -1.0f;
		}

		break;
	}
	default: {
		this->rng_val1_ = this->near_rng_;

		break;
	}
	}

	return;
}


/**
 * @brief SetFarRange関数
 * @param far_rng (far_range)
 */
void tml::graphic::Fog::SetFarRange(const FLOAT far_rng)
{
	this->far_rng_ = far_rng;

	switch (this->type_) {
	case tml::ConstantUtil::GRAPHIC::FOG_TYPE::WIDTH:
	case tml::ConstantUtil::GRAPHIC::FOG_TYPE::HEIGHT: {
		if ((this->far_rng_ - this->near_rng_) != 0.0f) {
			this->rng_val1_ = this->far_rng_ / (this->far_rng_ - this->near_rng_);
			this->rng_val2_ = -1.0f / (this->far_rng_ - this->near_rng_);
		} else {
			this->rng_val1_ = this->far_rng_;
			this->rng_val2_ = -1.0f;
		}

		break;
	}
	default: {
		this->rng_val2_ = this->far_rng_;

		break;
	}
	}

	return;
}
