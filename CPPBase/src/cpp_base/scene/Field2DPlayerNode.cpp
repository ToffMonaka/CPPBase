/**
 * @file
 * @brief Field2DPlayerNodeコードファイル
 */


#include "Field2DPlayerNode.h"
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
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DPlayerNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DPlayerNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"FIELD_2D_PL_NODE");

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
		tml::graphic::FigureModel2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -128.0f));

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
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

			this->model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
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
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::S)) {
		this->model->position.SetY(this->model->position.GetY() - 2.0f);
	}

	if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::A)) {
		this->model->position.SetX(this->model->position.GetX() - 2.0f);
	} else if (this->GetInputManager()->GetKeyboardDeviceCodeState(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::D)) {
		this->model->position.SetX(this->model->position.GetX() + 2.0f);
	}

	this->canvas_2d->SetDrawModel(this->model.get());

	return;
}
