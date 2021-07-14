/**
 * @file
 * @brief SelectSceneNodeコードファイル
 */


#include "SelectSceneNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/MouseDeviceEvent.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Model2D.h"
#include "../../lib/tml/sound/BGMSound.h"
#include "../../lib/tml/sound/SESound.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::SelectSceneNodeDesc::SelectSceneNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::SelectSceneNodeDesc::~SelectSceneNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::SelectSceneNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::BaseNodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SelectSceneNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseNodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SelectSceneNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SELECT_SCENE_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::SelectSceneNode::SelectSceneNode()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::SelectSceneNode::~SelectSceneNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::SelectSceneNode::Release(void)
{
	cpp_base::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::SelectSceneNode::Init(void)
{
	this->Release();

	this->canvas_2d.reset();
	this->bg_model.reset();
	this->bgm_sound.reset();
	this->stage_font.reset();
	this->stage_model.reset();
	this->stage_se_sound.reset();

	cpp_base::scene::BaseNode::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SelectSceneNode::Create(const cpp_base::scene::SelectSceneNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::BaseNode::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

	{// BackgroundModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->bg_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = L"res/bg_img1.png";

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->bg_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	{// BGMSound Create
		if (sound_mgr->GetResource<tml::sound::BGMSound>(this->bgm_sound, sound_mgr->common2.select_bgm_sound1) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	tml::XMUINT2EX stage_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX stage_model_size = tml::XMUINT2EX(128U, 32U);

	{// StartFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(graphic_mgr);
		desc.SetFontDesc(stage_font_size, L"ＭＳ ゴシック");

		if (graphic_mgr->GetResource<tml::graphic::Font>(this->stage_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StageModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.position.Set(tml::XMFLOAT2EX(0.0f, 0.0f));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->stage_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->stage_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, stage_model_size);
			desc.cpu_buffer_flag = true;

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->stage_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->stage_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	{// StageModelTexture Update
		auto &tex = this->stage_model->GetTexture(this->stage_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"テスト2D", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->stage_font.get());
		tex->UploadCPUBuffer();
	}

	{// StageSESound Create
		if (sound_mgr->GetResource<tml::sound::SESound>(this->stage_se_sound, sound_mgr->common2.start_se_sound1) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SelectSceneNode::OnStart(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

	{// Canvas2D Create
		if (graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"canvas_2d") == nullptr) {
			return (-1);
		}
	}

	sound_mgr->PlaySound(this->bgm_sound.get(), true);

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::SelectSceneNode::OnEnd(void)
{
	auto sound_mgr = this->GetManager()->GetSoundManager();

	sound_mgr->StopSound(this->bgm_sound.get());

	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::SelectSceneNode::OnUpdate(void)
{
	auto input_mgr = this->GetManager()->GetInputManager();
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	for (UINT event_i = 0U; event_i < input_mgr->GetEventCount(tml::input::DeviceEvent::EVENT_MAIN_INDEX); ++event_i) {
		auto event = reinterpret_cast<tml::input::DeviceEvent *>(input_mgr->GetEventFast(tml::input::DeviceEvent::EVENT_MAIN_INDEX, event_i));

		switch (event->GetEventSubIndex()) {
		case tml::input::MouseDeviceEvent::EVENT_SUB_INDEX: {
			auto &event_dat = reinterpret_cast<tml::input::MouseDeviceEvent *>(event)->data;

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
				if (this->stage_model->IsHitByMouseDevice(input_mgr->GetMouseDevicePosition())) {
					{// StageScene Start
						tml::shared_ptr<tml::scene::Scene> scene;

						if (this->GetManager()->factory.scene_by_xml_file.Get(scene, tml::ConstantUtil::SCENE::CLASS_NAME::SCENE, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::STAGE_SCENE)) == nullptr) {
							this->GetManager()->EndScene();

							return;
						}

						if (this->GetManager()->StartScene(scene) < 0) {
							this->GetManager()->EndScene();

							return;
						}
					}
				}
			}

			break;
		}
		}
	}

	if (this->stage_model->IsHitByMouseDevice(input_mgr->GetMouseDevicePosition())) {
		this->stage_model->scale = tml::XMFLOAT2EX(1.2f, 1.2f);
		this->stage_model->color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), 1.0f);
	} else {
		this->stage_model->scale = tml::XMFLOAT2EX(1.0f, 1.0f);
		this->stage_model->color = tml::XMFLOAT4EX(1.0f, 1.0f, 1.0f, 1.0f);
	}

	this->canvas_2d->SetDrawModel(this->bg_model.get());
	this->canvas_2d->SetDrawModel(this->stage_model.get());

	return;
}
