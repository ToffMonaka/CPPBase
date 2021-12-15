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
#include "Field2DNode.h"
#include "Field2DBulletNode.h"


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
cpp_base::scene::Field2DPlayerNode::Field2DPlayerNode() :
	field_node_(nullptr),
	attack_cool_time_(0.0)
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

	this->field_node_ = nullptr;
	this->attack_cool_time_ = tml::TIME_REAL(0.0);

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
		model_desc.diffuse_texture_desc = tml::make_shared<tml::graphic::TextureDesc>(1U);
		model_desc.diffuse_texture_desc->SetManager(this->GetGraphicManager());
		model_desc.diffuse_texture_desc->atlas_texture = this->GetGraphicManager()->common2.common_atlas->GetTexture();
		model_desc.diffuse_texture_desc->atlas_rect = (*this->GetGraphicManager()->common2.common_atlas->GetRect(L"pl_2d_img.png"));
		model_desc.draw_priority = 3;

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
		model_desc.draw_priority = 1;

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
	this->field_node_ = dynamic_cast<cpp_base::scene::Field2DNode *>(this->GetParentNode(L"field"));

	if (this->field_node_ == nullptr) {
		return (-1);
	}

	this->attack_cool_time_ = tml::TIME_REAL(0.0);

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
	this->attack_cool_time_ = tml::Max(this->attack_cool_time_ - this->GetManager()->GetFrameRate().GetElapsedTime(), tml::TIME_REAL(0.0));

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::W)) {
		this->Move(tml::XMFLOAT2EX(0.0f, 2.0f));
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::S)) {
		this->Move(tml::XMFLOAT2EX(0.0f, -2.0f));
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::A)) {
		this->Move(tml::XMFLOAT2EX(-2.0f, 0.0f));
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::D)) {
		this->Move(tml::XMFLOAT2EX(2.0f, 0.0f));
	}

	if (this->GetInputManager()->GetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::LEFT)) {
		this->Attack(tml::XMFLOAT2EX(
			static_cast<FLOAT>(this->GetInputManager()->GetMouseDevicePosition().x - static_cast<INT>(this->GetGraphicManager()->GetSize().GetHalfX())),
			static_cast<FLOAT>(-this->GetInputManager()->GetMouseDevicePosition().y + static_cast<INT>(this->GetGraphicManager()->GetSize().GetHalfY()))
		));
	}

	return;
}


/**
 * @brief Move関数
 * @param pos (position)
 */
void cpp_base::scene::Field2DPlayerNode::Move(const tml::XMFLOAT2EX &pos)
{
	this->transform_2d.position += pos;

	return;
}


/**
 * @brief Attack関数
 * @param pos (position)
 */
void cpp_base::scene::Field2DPlayerNode::Attack(const tml::XMFLOAT2EX &pos)
{
	if (this->attack_cool_time_.count() > 0.0) {
		return;
	}

	{// BulletNode Create
		tml::shared_ptr<tml::scene::Node> node;
		cpp_base::scene::Field2DBulletNodeDesc node_desc;

		node_desc.SetManager(this->GetManager());
		node_desc.transform_2d = tml::Transform2D(this->transform_2d.position);
		node_desc.transform_2d.Look(pos);

		if (this->GetManager()->GetResource<cpp_base::scene::Field2DBulletNode>(node, node_desc) == nullptr) {
			return;
		}

		this->field_node_->AddBulletNode(node);
	}

	this->attack_cool_time_ = tml::TIME_REAL(0.5);

	return;
}
