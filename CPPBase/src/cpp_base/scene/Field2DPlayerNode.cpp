/**
 * @file
 * @brief Field2DPlayerNodeコードファイル
 */


#include "Field2DPlayerNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/KeyboardDeviceEvent.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/FigureModel2D.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DPlayerNodeDesc::Field2DPlayerNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DPlayerNodeDesc::~Field2DPlayerNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DPlayerNodeDesc::Init(void)
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
INT cpp_base::scene::Field2DPlayerNodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DPlayerNode Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FIELD_2D_PL_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DPlayerNode::Field2DPlayerNode()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DPlayerNode::~Field2DPlayerNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Field2DPlayerNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DPlayerNode::Init(void)
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
INT cpp_base::scene::Field2DPlayerNode::Create(const cpp_base::scene::Field2DPlayerNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Node::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// Model Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.position = tml::XMFLOAT2EX(0.0f, -128.0f);
		model_desc.image_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::PLAYER_2D_IMAGE;

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
INT cpp_base::scene::Field2DPlayerNode::OnStart(void)
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
void cpp_base::scene::Field2DPlayerNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Field2DPlayerNode::OnUpdate(void)
{
	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::W)) {
		this->model->position.SetY(this->model->position.GetY() + 2.0f);
		this->shadow_model->position.SetY(this->model->position.GetY() - this->model->size.GetHalfY());
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::S)) {
		this->model->position.SetY(this->model->position.GetY() - 2.0f);
		this->shadow_model->position.SetY(this->model->position.GetY() - this->model->size.GetHalfY());
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::A)) {
		this->model->position.SetX(this->model->position.GetX() - 2.0f);
		this->shadow_model->position.SetX(this->model->position.GetX());
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::D)) {
		this->model->position.SetX(this->model->position.GetX() + 2.0f);
		this->shadow_model->position.SetX(this->model->position.GetX());
	}

	this->canvas_2d->SetDrawModel(this->shadow_model.get());
	this->canvas_2d->SetDrawModel(this->model.get());

	return;
}
