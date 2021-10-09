/**
 * @file
 * @brief Field2DMobNodeコードファイル
 */


#include "Field2DMobNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/FigureModel2D.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DMobNodeDesc::Field2DMobNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DMobNodeDesc::~Field2DMobNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DMobNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DMobNodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DMobNode Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FIELD_2D_MOB_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DMobNode::Field2DMobNode()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DMobNode::~Field2DMobNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Field2DMobNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DMobNode::Init(void)
{
	this->Release();

	this->canvas_2d.reset();
	this->model.reset();
	this->shadow_model.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DMobNode::Create(const cpp_base::scene::Field2DMobNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Node::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// Model Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.position = tml::XMFLOAT2EX(0.0f, 128.0f);
		model_desc.image_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::MOB_2D_IMAGE;

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->model, model_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ShadowModel Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.position = tml::XMFLOAT2EX(this->model->position.GetX(), this->model->position.GetY() - this->model->size.GetHalfY());
		model_desc.size = tml::XMFLOAT2EX(96.0f, 64.0f);
		model_desc.size_auto_flag = false;
		model_desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(0U), tml::MathUtil::GetColor1(0U), tml::MathUtil::GetColor1(0U), 0.5f);
		model_desc.image_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::SHADOW_2D_IMAGE;

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->shadow_model, model_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DMobNode::OnStart(void)
{
	{// Canvas2D Create
		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"Canvas2D") == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Field2DMobNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Field2DMobNode::OnUpdate(void)
{
	this->canvas_2d->SetDrawModel(this->shadow_model.get());
	this->canvas_2d->SetDrawModel(this->model.get());

	return;
}
