/**
 * @file
 * @brief Test2DStageNodeコードファイル
 */


#include "Test2DStageNode.h"
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
cpp_base::scene::Test2DStageNodeDesc::Test2DStageNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Test2DStageNodeDesc::~Test2DStageNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Test2DStageNodeDesc::Init(void)
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
INT cpp_base::scene::Test2DStageNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Test2DStageNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"TEST_2D_STAGE_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Test2DStageNode::Test2DStageNode()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Test2DStageNode::~Test2DStageNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Test2DStageNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Test2DStageNode::Init(void)
{
	this->Release();

	this->canvas_2d.reset();
	this->ground_model.reset();
	this->player_character_model.reset();
	this->ground_layout_node.reset();
	this->player_character_layout_node.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Test2DStageNode::Create(const cpp_base::scene::Test2DStageNodeDesc &desc)
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

	{// PlayerCharacterModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -128.0f));

		if (this->GetGraphicManager()->GetResource<tml::graphic::Model2D>(this->player_character_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->player_character_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::PLAYER_CHARACTER_2D_TEXTURE;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->player_character_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->player_character_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Test2DStageNode::OnStart(void)
{
	{// Canvas2D Create
		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"Canvas2D") == nullptr) {
			return (-1);
		}
	}

	{// GroundLayoutNode Create
		if (this->GetChildNode(this->ground_layout_node, L"ground_layout") == nullptr) {
			return (-1);
		}
	}

	{// PlayerCharacterLayoutNode Create
		if (this->GetChildNode(this->player_character_layout_node, L"pc_layout") == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Test2DStageNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Test2DStageNode::OnUpdate(void)
{
	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::W)) {
		this->player_character_model->position.SetY(this->player_character_model->position.GetY() + 2.0f);
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::S)) {
		this->player_character_model->position.SetY(this->player_character_model->position.GetY() - 2.0f);
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::A)) {
		this->player_character_model->position.SetX(this->player_character_model->position.GetX() - 2.0f);
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::D)) {
		this->player_character_model->position.SetX(this->player_character_model->position.GetX() + 2.0f);
	}

	this->canvas_2d->SetDrawModel(this->ground_model.get());
	this->canvas_2d->SetDrawModel(this->player_character_model.get());

	return;
}
