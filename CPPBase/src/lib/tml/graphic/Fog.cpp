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
	desc_(nullptr),
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
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Fog::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	this->draw_priority_ = this->desc_->draw_priority;

	/*
	this->mul_val_ = this->desc_->mul_value;
	this->SetNearRange(this->desc_->near_range);
	this->SetFarRange(this->desc_->far_range);
	*/

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Fog::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Fog::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::FogDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
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
