/**
 * @file
 * @brief Fogコードファイル
 */


#include "Fog.h"
#include "Manager.h"
#include "Canvas.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::FogDesc::FogDesc() :
	draw_priority(0)
	/*
	mul_value(0.0f),
	near_range(0.0f),
	far_range(0.0f)
	*/
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FogDesc::~FogDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FogDesc::Init(void)
{
	this->Release();

	/*
	this->mul_value = 0.0f;
	this->near_range = 0.0f;
	this->far_range = 0.0f;
	*/

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::FogDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Fog Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FOG");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Fog::Fog() :
	type_(tml::ConstantUtil::GRAPHIC::FOG_TYPE::NONE),
	dimension_type_(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE),
	draw_priority_(0),
	draw_set_canvas_cnt_(0U)
	/*
	mul_val_(0.0f),
	near_rng_(0.0f),
	far_rng_(0.0f),
	rng_val1_(0.0f),
	rng_val2_(0.0f)
	*/
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
 * @brief Init関数
 */
void tml::graphic::Fog::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::FOG_TYPE::NONE;
	this->dimension_type_ = tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE;
	this->draw_priority_ = 0;
	this->draw_set_canvas_cnt_ = 0U;
	this->draw_set_canvas_cont_.clear();
	/*
	this->mul_val_ = 0.0f;
	this->near_rng_ = 0.0f;
	this->far_rng_ = 0.0f;
	this->rng_val1_ = 0.0f;
	this->rng_val2_ = 0.0f;
	*/

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param dimension_type (dimension_type)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Fog::Create(const tml::graphic::FogDesc &desc, const tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE dimension_type)
{
	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::GRAPHIC::FOG_TYPE>(this->GetResourceSubIndex());
	this->dimension_type_ = dimension_type;
	this->draw_priority_ = desc.draw_priority;
	/*
	this->mul_val_ = desc.mul_value;
	this->SetNearRange(desc.near_range);
	this->SetFarRange(desc.far_range);
	*/

	return (0);
}


#if 0
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
#endif


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::Fog::DrawStageInit(void)
{
	return;
}
