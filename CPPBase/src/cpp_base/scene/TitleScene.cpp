/**
 * @file
 * @brief TitleSceneコードファイル
 */


#include "TitleScene.h"
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
cpp_base::scene::TitleSceneDesc::TitleSceneDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::TitleSceneDesc::~TitleSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::TitleSceneDesc::Init(void)
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
INT cpp_base::scene::TitleSceneDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::SceneDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// TitleScene Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"TITLE_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::TitleScene::TitleScene() :
	progress_type_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::TitleScene::~TitleScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::TitleScene::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::TitleScene::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;

	this->canvas_2d.reset();
	this->camera_2d.reset();
	this->camera_3d.reset();
	this->bg_model.reset();
	this->bgm_sound.reset();
	this->logo_model.reset();
	this->start_font.reset();
	this->start_model.reset();
	this->start_se_sound.reset();
	this->footer_font.reset();
	this->footer_model.reset();
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
INT cpp_base::scene::TitleScene::Create(const cpp_base::scene::TitleSceneDesc &desc)
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
		desc.position = tml::XMFLOAT2EX(0.0f, 0.0f);
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));
		desc.size_flag = true;

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->bg_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.image_file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::TITLE_BACKGROUND_IMAGE;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->bg_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	{// BGMSound Create
		if (this->GetSoundManager()->GetResource<tml::sound::BGMSound>(this->bgm_sound, this->GetSoundManager()->common2.title_bgm_sound) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LogoModel Create
		tml::graphic::FigureModel2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position = tml::XMFLOAT2EX(0.0f, 32.0f);
		desc.image_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::TITLE_LOGO_IMAGE;

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->logo_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	tml::XMUINT2EX start_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX start_model_size = tml::XMUINT2EX(128U, 32U);

	{// StartFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.SetFontDesc(start_font_size, L"ＭＳ ゴシック");

		if (this->GetGraphicManager()->GetResource<tml::graphic::Font>(this->start_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StartModel Create
		tml::graphic::FigureModel2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position = tml::XMFLOAT2EX(0.0f, -192.0f);
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->start_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->start_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, start_model_size);
			desc.cpu_buffer_flag = true;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->start_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->start_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	{// StartModelTexture Update
		auto &tex = this->start_model->GetTexture(this->start_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"スタート", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->start_font.get());
		tex->UploadCPUBuffer();
	}

	{// StartSESound Create
		if (this->GetSoundManager()->GetResource<tml::sound::SESound>(this->start_se_sound, this->GetSoundManager()->common2.start_se_sound) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	tml::XMUINT2EX footer_font_size = tml::XMUINT2EX(0U, 16U);
	tml::XMUINT2EX footer_model_size = tml::XMUINT2EX(this->GetGraphicManager()->GetSize().x, 24U);

	{// FooterFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.SetFontDesc(footer_font_size, L"ＭＳ ゴシック");

		if (this->GetGraphicManager()->GetResource<tml::graphic::Font>(this->footer_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FooterModel Create
		tml::graphic::FigureModel2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.position = tml::XMFLOAT2EX(0.0f, -static_cast<FLOAT>(this->GetGraphicManager()->GetSize().GetHalfY()) + static_cast<FLOAT>(footer_model_size.y >> 1));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->footer_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->footer_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, footer_model_size);
			desc.cpu_buffer_flag = true;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->footer_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->footer_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	{// FooterModelTexture Update
		std::wstring company_name;

		company_name = cpp_base::ConstantUtil::APPLICATION::COMPANY_NAME;

		std::wstring version_name;

		version_name = L"Version ";
		version_name += cpp_base::ConstantUtil::APPLICATION::VERSION_NAME;

		auto &tex = this->footer_model->GetTexture(this->footer_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(company_name.c_str(), tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(4, -4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::BOTTOM_LEFT, this->footer_font.get());
		tex->DrawCPUBufferString(version_name.c_str(), tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(-4, -4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::BOTTOM_RIGHT, this->footer_font.get());
		tex->UploadCPUBuffer();
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleScene::OnStart(void)
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
void cpp_base::scene::TitleScene::OnEnd(void)
{
	this->GetSoundManager()->StopSound(this->bgm_sound.get());

	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::TitleScene::OnUpdate(void)
{
	switch (this->progress_type_) {
	case 1U: {
		for (UINT event_i = 0U; event_i < this->GetInputManager()->GetEventCount(tml::input::DeviceEvent::EVENT_MAIN_INDEX); ++event_i) {
			auto event = reinterpret_cast<tml::input::DeviceEvent *>(this->GetInputManager()->GetEventFast(tml::input::DeviceEvent::EVENT_MAIN_INDEX, event_i));

			switch (event->GetEventSubIndex()) {
			case tml::input::MouseDeviceEvent::EVENT_SUB_INDEX: {
				auto &event_dat = reinterpret_cast<tml::input::MouseDeviceEvent *>(event)->data;

				if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
					if (this->start_model->IsHitByMouseDevice(this->GetInputManager()->GetMouseDevicePosition())) {
						{// SelectScene Start
							tml::shared_ptr<tml::scene::Scene> scene;

							if (this->GetManager()->GetScene(scene, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::SELECT_SCENE_PREFAB)) == nullptr) {
								if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
									OutputDebugString(L"Error: SelectScene Create\n");
								}

								this->GetManager()->EndScene();

								return;
							}

							if (this->GetManager()->StartScene(scene) < 0) {
								if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
									OutputDebugString(L"Error: SelectScene Start\n");
								}

								this->GetManager()->EndScene();

								return;
							}
						}

						this->GetSoundManager()->PlaySound(this->start_se_sound.get(), false);

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

	if (this->start_model->IsHitByMouseDevice(this->GetInputManager()->GetMouseDevicePosition())) {
		this->start_model->scale = tml::XMFLOAT2EX(1.2f, 1.2f);
		this->start_model->color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), 1.0f);
	} else {
		this->start_model->scale = tml::XMFLOAT2EX(1.0f, 1.0f);
		this->start_model->color = tml::XMFLOAT4EX(1.0f, 1.0f, 1.0f, 1.0f);
	}

	this->canvas_2d->SetDrawCamera(this->camera_2d.get());
	this->canvas_2d->SetDrawModel(this->bg_model.get());
	this->canvas_2d->SetDrawModel(this->logo_model.get());
	this->canvas_2d->SetDrawModel(this->start_model.get());
	this->canvas_2d->SetDrawModel(this->footer_model.get());

	this->GetGraphicManager()->SetDrawCanvas(this->canvas_2d.get());

	return;
}
