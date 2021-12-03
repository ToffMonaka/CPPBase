/**
 * @file
 * @brief Field2DPlayerNodeコードファイル
 */


#include "Field2DPlayerNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/KeyboardDeviceEvent.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
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

	this->transform_2d = tml::Transform2D(tml::XMFLOAT2EX(0.0f, -128.0f));

	{// Model Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.diffuse_texture_desc = tml::make_shared<tml::graphic::TextureDesc>(1U);
		model_desc.diffuse_texture_desc->SetManager(this->GetGraphicManager());
		model_desc.diffuse_texture_desc->atlas_texture = this->GetGraphicManager()->common2.common_atlas->GetTexture();
		model_desc.diffuse_texture_desc->atlas_rect = (*this->GetGraphicManager()->common2.common_atlas->GetRect(L"pl_2d_img.png"));
		model_desc.draw_priority = 1;

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->model, model_desc) == nullptr) {
			this->Init();

			return (-1);
		}

		this->model->transform.position = tml::XMFLOAT2EX(0.0f, this->model->size.GetHalfY());
	}

	{// ShadowModel Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(0U), tml::MathUtil::GetColor1(0U), tml::MathUtil::GetColor1(0U), 0.5f);
		model_desc.size = tml::XMFLOAT2EX(96.0f, 64.0f);
		model_desc.size_auto_flag = false;
		model_desc.diffuse_texture_desc = tml::make_shared<tml::graphic::TextureDesc>(1U);
		model_desc.diffuse_texture_desc->SetManager(this->GetGraphicManager());
		model_desc.diffuse_texture_desc->atlas_texture = this->GetGraphicManager()->common2.common_atlas->GetTexture();
		model_desc.diffuse_texture_desc->atlas_rect = (*this->GetGraphicManager()->common2.common_atlas->GetRect(L"shadow_2d_img.png"));
		model_desc.draw_priority = 0;

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
	this->SetModel(0U, this->model);
	this->SetModel(1U, this->shadow_model);

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
		this->transform_2d.position.y += 2.0f;
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::S)) {
		this->transform_2d.position.y -= 2.0f;
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::A)) {
		this->transform_2d.position.x -= 2.0f;
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::D)) {
		this->transform_2d.position.x += 2.0f;
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::Q)) {
		this->transform_2d.angle = tml::Repeat(this->transform_2d.angle + tml::MathUtil::GetAngleRadian(1.0f), tml::ConstantUtil::MATH::PI * 2.0f);
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::E)) {
		this->transform_2d.angle = tml::Repeat(this->transform_2d.angle - tml::MathUtil::GetAngleRadian(1.0f), tml::ConstantUtil::MATH::PI * 2.0f);
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::Z)) {
		this->transform_2d.scale.x = tml::Max(this->transform_2d.scale.x - 0.01f, 0.0f);
		this->transform_2d.scale.y = this->transform_2d.scale.x;
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::C)) {
		this->transform_2d.scale.x = tml::Min(this->transform_2d.scale.x + 0.01f, 2.0f);
		this->transform_2d.scale.y = this->transform_2d.scale.x;
	}

	if (this->GetInputManager()->GetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::LEFT)) {
		this->transform_2d.SetDistance(tml::XMFLOAT2EX(0.0f, 128.0f), 256.0f);
	}

	if (this->GetInputManager()->GetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::RIGHT)) {
		this->transform_2d.Look(tml::XMFLOAT2EX(0.0f, 128.0f));
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::NUM1)) {
		this->color.y = tml::Max(this->color.y - 0.01f, 0.0f);
		this->color.z = this->color.y;
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::NUM2)) {
		this->color.y = tml::Min(this->color.y + 0.01f, 1.0f);
		this->color.z = this->color.y;
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::NUM3)) {
		this->color.w = tml::Max(this->color.w - 0.01f, 0.0f);
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::NUM4)) {
		this->color.w = tml::Min(this->color.w + 0.01f, 1.0f);
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::SPACE)) {
		this->transform_2d = tml::Transform2D(tml::XMFLOAT2EX(0.0f, -128.0f));
		this->color = tml::XMFLOAT4EX(1.0f);
	}

	return;
}
