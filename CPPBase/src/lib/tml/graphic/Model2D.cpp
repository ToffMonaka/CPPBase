/**
 * @file
 * @brief Model2Dコードファイル
 */


#include "Model2D.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"
#include "Canvas2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Model2DLayer::Model2DLayer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model2DLayer::~Model2DLayer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model2DLayer::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model2DLayer::Init(void)
{
	this->Release();

	tml::graphic::ModelLayer::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model2DLayer::Create(tml::graphic::Manager *mgr)
{
	if (tml::graphic::ModelLayer::Create(mgr) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model2DStage::Model2DStage()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model2DStage::~Model2DStage()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model2DStage::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model2DStage::Init(void)
{
	this->Release();

	tml::graphic::ModelStage::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model2DStage::Create(tml::graphic::Manager *mgr)
{
	if (tml::graphic::ModelStage::Create(mgr) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model2DDesc::Model2DDesc() :
	color(1.0f),
	size(0.0f),
	size_auto_flag(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model2DDesc::~Model2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model2DDesc::Init(void)
{
	this->Release();

	this->transform.Init();
	this->color = 1.0f;
	this->size = 0.0f;
	this->size_auto_flag = true;

	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model2DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ModelDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Model2D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MODEL_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model2D::Model2D() :
	desc_(nullptr),
	color(1.0f),
	size(0.0f),
	draw_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model2D::~Model2D()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model2D::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model2D::Init(void)
{
	this->Release();

	this->transform.Init();
	this->color = 1.0f;
	this->size = 0.0f;
	this->draw_data = nullptr;

	tml::graphic::Model::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model2D::OnCreate(void)
{
	if (tml::graphic::Model::OnCreate() < 0) {
		return (-1);
	}

	this->SetDimensionType(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D);

	this->transform = this->desc_->transform;
	this->color = this->desc_->color;
	this->size = this->desc_->size;

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model2D::OnCreateDeferred(void)
{
	if (tml::graphic::Model::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Model2D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Model2DDesc *>(desc);

	tml::graphic::Model::OnSetDesc(this->desc_);

	return;
}
