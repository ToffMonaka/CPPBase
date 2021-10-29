/**
 * @file
 * @brief SelectSceneコードファイル
 */


#include "SelectScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/MouseDeviceEvent.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Canvas3D.h"
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
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SelectSceneDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::SceneDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SelectScene Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SELECT_SCENE");

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
	this->canvas_3d.reset();
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

	{// Camera2D Create
		tml::graphic::Camera2DDesc camera_desc;

		camera_desc.SetManager(this->GetGraphicManager());
		camera_desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::ORTHOGRAPHIC;
		camera_desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));

		if (this->GetGraphicManager()->GetResource<tml::graphic::Camera2D>(this->camera_2d, camera_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Canvas2D Create
		tml::graphic::Canvas2DDesc canvas_desc;

		canvas_desc.SetManager(this->GetGraphicManager());

		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, canvas_desc) == nullptr) {
			this->Init();

			return (-1);
		}

		this->canvas_2d->SetCamera(this->camera_2d);
		this->canvas_2d->SetRenderTargetTexture(this->GetGraphicManager()->common.main_render_target_texture);
		this->canvas_2d->SetRenderTargetTextureClearFlag(true);
		this->canvas_2d->SetDrawPriority(1U);
	}

	{// Camera3D Create
		tml::graphic::Camera3DDesc camera_desc;

		camera_desc.SetManager(this->GetGraphicManager());
		camera_desc.projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::PERSPECTIVE;
		camera_desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));
		camera_desc.fov_angle = tml::MathUtil::GetAngleRadian(55.0f);
		camera_desc.near_clip = 0.1f;
		camera_desc.far_clip = 1000.0f;

		if (this->GetGraphicManager()->GetResource<tml::graphic::Camera3D>(this->camera_3d, camera_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Canvas3D Create
		tml::graphic::Canvas3DDesc canvas_desc;

		canvas_desc.SetManager(this->GetGraphicManager());

		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas3D>(this->canvas_3d, canvas_desc) == nullptr) {
			this->Init();

			return (-1);
		}

		this->canvas_3d->SetCamera(this->camera_3d);
		this->canvas_3d->SetRenderTargetTexture(this->GetGraphicManager()->common.main_render_target_texture);
		this->canvas_3d->SetRenderTargetTextureClearFlag(true);
		this->canvas_3d->SetDepthTargetTexture(this->GetGraphicManager()->common.main_depth_target_texture);
		this->canvas_3d->SetDepthTargetTextureClearFlag(true);
		this->canvas_3d->SetDrawPriority(0U);
	}

	{// BackgroundModel Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.position = tml::XMFLOAT2EX(0.0f, 0.0f);
		model_desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));
		model_desc.size_auto_flag = false;
		model_desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->bg_model, model_desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayer(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, this->GetGraphicManager()->common2.background_texture) == nullptr) {
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
		tml::graphic::FontDesc font_desc;

		font_desc.SetManager(this->GetGraphicManager());
		font_desc.SetFontDesc(stage_font_size, L"ＭＳ ゴシック");

		if (this->GetGraphicManager()->GetResource<tml::graphic::Font>(this->stage_font, font_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StageModel Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.position = tml::XMFLOAT2EX(0.0f, 0.0f);
		model_desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->stage_model, model_desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->stage_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayer(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;
			tml::graphic::TextureDesc tex_desc;

			tex_desc.SetManager(this->GetGraphicManager());
			tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, stage_model_size);
			tex_desc.cpu_buffer_flag = true;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, tex_desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->stage_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->stage_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetRect().GetSize().x), static_cast<FLOAT>(tex->GetRect().GetSize().y));
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

	this->SetCanvas(0U, this->canvas_2d);
	this->SetCanvas(1U, this->canvas_3d);
	this->SetModel(0U, this->bg_model);
	this->SetModel(1U, this->stage_model);

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

							if (this->GetManager()->GetScene(scene, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::STAGE_SCENE_PREFAB)) == nullptr) {
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

	return;
}
