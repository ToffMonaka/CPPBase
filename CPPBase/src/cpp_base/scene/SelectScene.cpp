/**
 * @file
 * @brief SelectSceneコードファイル
 */


#include "SelectScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/MouseDeviceEvent.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Camera2D.h"
#include "../../lib/tml/graphic/Camera3D.h"
#include "../../lib/tml/graphic/FigureModel2D.h"
#include "../../lib/tml/sound/BGMSound.h"
#include "../../lib/tml/sound/SESound.h"
#include "../../lib/tml/scene/Node.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::SelectSceneDesc::SelectSceneDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::SelectSceneDesc::~SelectSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::SelectSceneDesc::Init(void)
{
	this->Release();

	cpp_base::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SelectSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::SceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SelectScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SELECT_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::SelectScene::SelectScene() :
	progress_type_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::SelectScene::~SelectScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::SelectScene::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::SelectScene::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;

	this->canvas_2d.reset();
	this->camera_2d.reset();
	this->camera_3d.reset();
	this->bg_model.reset();
	this->bgm_sound.reset();
	this->stage_font.reset();
	this->stage_model.reset();
	this->stage_se_sound.reset();
	this->main_node.reset();

	cpp_base::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SelectScene::Create(const cpp_base::scene::SelectSceneDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Scene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// Canvas2D Create
		tml::graphic::Canvas2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.resource_name = L"Canvas2D";

		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		this->canvas_2d->SetRenderTargetTexture(this->GetGraphicManager()->common.main_render_target_texture);
		this->canvas_2d->SetRenderTargetTextureClearFlag(true);
	}

	{// Camera2D Create
		tml::graphic::Camera2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::ORTHOGRAPHIC;
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));

		if (this->GetGraphicManager()->GetResource<tml::graphic::Camera2D>(this->camera_2d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Camera3D Create
		tml::graphic::Camera3DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::PERSPECTIVE;
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));
		desc.fov_angle = tml::MathUtil::GetAngleRadian(55.0f);
		desc.near_clip = 0.1f;
		desc.far_clip = 1000.0f;

		if (this->GetGraphicManager()->GetResource<tml::graphic::Camera3D>(this->camera_3d, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackgroundModel Create
		tml::graphic::FigureModel2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->bg_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, this->GetGraphicManager()->common2.bg_tex) == nullptr) {
				this->Init();

				return (-1);
			}

			this->bg_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	{// BGMSound Create
		if (this->GetSoundManager()->GetResource<tml::sound::BGMSound>(this->bgm_sound, this->GetSoundManager()->common2.select_bgm_sound) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	tml::XMUINT2EX stage_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX stage_model_size = tml::XMUINT2EX(128U, 32U);

	{// StartFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.SetFontDesc(stage_font_size, L"ＭＳ ゴシック");

		if (this->GetGraphicManager()->GetResource<tml::graphic::Font>(this->stage_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StageModel Create
		tml::graphic::FigureModel2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position.Set(tml::XMFLOAT2EX(0.0f, 0.0f));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->stage_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->stage_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, stage_model_size);
			desc.cpu_buffer_flag = true;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
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
		if (this->GetSoundManager()->GetResource<tml::sound::SESound>(this->stage_se_sound, this->GetSoundManager()->common2.start_se_sound) == nullptr) {
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
INT cpp_base::scene::SelectScene::OnStart(void)
{
	this->progress_type_ = 1U;

	this->GetSoundManager()->PlaySound(this->bgm_sound.get(), true);

	{// MainNode Create
		this->main_node = this->GetRootNode()->GetChildNode(L"main");

		if (this->main_node == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::SelectScene::OnEnd(void)
{
	this->GetSoundManager()->StopSound(this->bgm_sound.get());

	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::SelectScene::OnUpdate(void)
{
	switch (this->progress_type_) {
	case 1U: {
		for (UINT event_i = 0U; event_i < this->GetInputManager()->GetEventCount(tml::input::DeviceEvent::EVENT_MAIN_INDEX); ++event_i) {
			auto event = reinterpret_cast<tml::input::DeviceEvent *>(this->GetInputManager()->GetEventFast(tml::input::DeviceEvent::EVENT_MAIN_INDEX, event_i));

			switch (event->GetEventSubIndex()) {
			case tml::input::MouseDeviceEvent::EVENT_SUB_INDEX: {
				auto &event_dat = reinterpret_cast<tml::input::MouseDeviceEvent *>(event)->data;

				if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
					if (this->stage_model->IsHitByMouseDevice(this->GetInputManager()->GetMouseDevicePosition())) {
						{// StageScene Start
							tml::shared_ptr<tml::scene::Scene> scene;

							if (this->GetManager()->factory.scene_by_xml_file.Get(scene, tml::ConstantUtil::SCENE::CLASS_NAME::SCENE, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::STAGE_SCENE)) == nullptr) {
								if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
									OutputDebugString(L"Error: StageScene Create\n");
								}

								this->GetManager()->EndScene();

								return;
							}

							if (this->GetManager()->StartScene(scene) < 0) {
								if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
									OutputDebugString(L"Error: StageScene Start\n");
								}

								this->GetManager()->EndScene();

								return;
							}
						}

						this->GetSoundManager()->PlaySound(this->stage_se_sound.get(), false);

						this->progress_type_ = 2U;
					}
				}

				break;
			}
			}
		}

		break;
	}
	case 2U: {
		break;
	}
	}

	if (this->stage_model->IsHitByMouseDevice(this->GetInputManager()->GetMouseDevicePosition())) {
		this->stage_model->scale = tml::XMFLOAT2EX(1.2f, 1.2f);
		this->stage_model->color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), 1.0f);
	} else {
		this->stage_model->scale = tml::XMFLOAT2EX(1.0f, 1.0f);
		this->stage_model->color = tml::XMFLOAT4EX(1.0f, 1.0f, 1.0f, 1.0f);
	}

	this->canvas_2d->SetDrawCamera(this->camera_2d.get());
	this->canvas_2d->SetDrawModel(this->bg_model.get());
	this->canvas_2d->SetDrawModel(this->stage_model.get());

	this->GetGraphicManager()->SetDrawCanvas(this->canvas_2d.get());

	return;
}
