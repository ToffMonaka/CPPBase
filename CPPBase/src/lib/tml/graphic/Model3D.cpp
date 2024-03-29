/**
 * @file
 * @brief Model3Dコードファイル
 */


#include "Model3D.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"
#include "Canvas3D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Model3DLayer::Model3DLayer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model3DLayer::~Model3DLayer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model3DLayer::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model3DLayer::Init(void)
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
INT tml::graphic::Model3DLayer::Create(tml::graphic::Manager *mgr)
{
	if (tml::graphic::ModelLayer::Create(mgr) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model3DStage::Model3DStage()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model3DStage::~Model3DStage()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model3DStage::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model3DStage::Init(void)
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
INT tml::graphic::Model3DStage::Create(tml::graphic::Manager *mgr)
{
	if (tml::graphic::ModelStage::Create(mgr) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model3DDesc::Model3DDesc() :
	color(1.0f),
	size(0.0f),
	size_auto_flag(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model3DDesc::~Model3DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model3DDesc::Init(void)
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
INT tml::graphic::Model3DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ModelDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Model3D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MODEL_3D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Model3D::Model3D() :
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
tml::graphic::Model3D::~Model3D()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model3D::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model3D::Init(void)
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
INT tml::graphic::Model3D::OnCreate(void)
{
	if (tml::graphic::Model::OnCreate() < 0) {
		return (-1);
	}

	this->SetDimensionType(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D);

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
INT tml::graphic::Model3D::OnCreateDeferred(void)
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
void tml::graphic::Model3D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Model3DDesc *>(desc);

	tml::graphic::Model::OnSetDesc(this->desc_);

	return;
}
