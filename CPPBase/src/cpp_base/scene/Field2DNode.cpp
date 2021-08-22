/**
 * @file
 * @brief Field2DNodeコードファイル
 */


#include "Field2DNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/KeyboardDeviceEvent.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Model2D.h"
#include "../../lib/tml/scene/Node.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DNodeDesc::Field2DNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DNodeDesc::~Field2DNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"FIELD_2D_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DNode::Field2DNode()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DNode::~Field2DNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Field2DNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DNode::Init(void)
{
	this->Release();

	this->canvas_2d.reset();
	this->ground_model.reset();
	this->player_model.reset();
	this->mob_model.reset();
	this->ground_layout_node.reset();
	this->player_layout_node.reset();
	this->mob_layout_node.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::Create(const cpp_base::scene::Field2DNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Node::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// GroundModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));

		if (this->GetGraphicManager()->GetResource<tml::graphic::Model2D>(this->ground_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->ground_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::GROUND_2D_TEXTURE;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->ground_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	{// PlayerModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -128.0f));

		if (this->GetGraphicManager()->GetResource<tml::graphic::Model2D>(this->player_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->player_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::PLAYER_2D_TEXTURE;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->player_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->player_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	{// MobModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position.Set(tml::XMFLOAT2EX(0.0f, 128.0f));

		if (this->GetGraphicManager()->GetResource<tml::graphic::Model2D>(this->mob_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->mob_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::MOB_2D_TEXTURE;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->mob_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->mob_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::OnStart(void)
{
	{// Canvas2D Create
		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"Canvas2D") == nullptr) {
			return (-1);
		}
	}

	{// GroundLayoutNode Create
		this->ground_layout_node = this->GetChildNode(L"ground_layout");

		if (this->ground_layout_node == nullptr) {
			return (-1);
		}
	}

	{// PlayerLayoutNode Create
		this->player_layout_node = this->GetChildNode(L"pl_layout");

		if (this->player_layout_node == nullptr) {
			return (-1);
		}
	}

	{// MobLayoutNode Create
		this->mob_layout_node = this->GetChildNode(L"mob_layout");

		if (this->mob_layout_node == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Field2DNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Field2DNode::OnUpdate(void)
{
	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::W)) {
		this->player_model->position.SetY(this->player_model->position.GetY() + 2.0f);
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::S)) {
		this->player_model->position.SetY(this->player_model->position.GetY() - 2.0f);
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::A)) {
		this->player_model->position.SetX(this->player_model->position.GetX() - 2.0f);
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::D)) {
		this->player_model->position.SetX(this->player_model->position.GetX() + 2.0f);
	}

	this->canvas_2d->SetDrawModel(this->ground_model.get());
	this->canvas_2d->SetDrawModel(this->mob_model.get());
	this->canvas_2d->SetDrawModel(this->player_model.get());

	return;
}
