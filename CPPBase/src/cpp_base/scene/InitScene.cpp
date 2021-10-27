/**
 * @file
 * @brief InitSceneコードファイル
 */


#include "InitScene.h"
#include "../../lib/tml/math/MathUtil.h"
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
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::InitSceneDesc::InitSceneDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitSceneDesc::~InitSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitSceneDesc::Init(void)
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
INT cpp_base::scene::InitSceneDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::SceneDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// InitScene Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"INIT_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::InitScene::InitScene() :
	progress_type_(0U),
	wait_update_time(0.0)
{
	this->deferred_create_res_cont_.clear();
	this->deferred_create_res_itr_ = this->deferred_create_res_cont_.end();

	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitScene::~InitScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::InitScene::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitScene::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;
	this->deferred_create_res_cont_.clear();
	this->deferred_create_res_itr_ = this->deferred_create_res_cont_.end();

	this->canvas_2d.reset();
	this->canvas_3d.reset();
	this->camera_2d.reset();
	this->camera_3d.reset();
	this->bg_model.reset();
	this->wait_update_time = tml::TIME_REAL(0.0);
	this->wait_font.reset();
	this->wait_model.reset();
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
INT cpp_base::scene::InitScene::Create(const cpp_base::scene::InitSceneDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Scene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->deferred_create_res_cont_.push_back(this->GetSoundManager()->common2.title_bgm_sound);
	this->deferred_create_res_cont_.push_back(this->GetSoundManager()->common2.select_bgm_sound);
	this->deferred_create_res_cont_.push_back(this->GetSoundManager()->common2.start_se_sound);

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

	tml::XMUINT2EX wait_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX wait_model_size = tml::XMUINT2EX(320U, 32U);

	{// WaitFont Create
		tml::graphic::FontDesc font_desc;

		font_desc.SetManager(this->GetGraphicManager());
		font_desc.SetFontDesc(wait_font_size, L"ＭＳ ゴシック");

		if (this->GetGraphicManager()->GetResource<tml::graphic::Font>(this->wait_font, font_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WaitModel Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.position = tml::XMFLOAT2EX(0.0f, 0.0f);
		model_desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->wait_model, model_desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->wait_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayer(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;
			tml::graphic::TextureDesc tex_desc;

			tex_desc.SetManager(this->GetGraphicManager());
			tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, wait_model_size);
			tex_desc.cpu_buffer_flag = true;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, tex_desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->wait_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->wait_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetRect().GetSize().x), static_cast<FLOAT>(tex->GetRect().GetSize().y));
		}
	}

	{// WaitModelTexture Update
		auto &tex = this->wait_model->GetTexture(this->wait_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"ちょっと待ってね。", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->wait_font.get());
		tex->UploadCPUBuffer();
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitScene::OnStart(void)
{
	this->progress_type_ = 1U;

	this->deferred_create_res_itr_ = this->deferred_create_res_cont_.begin();

	this->wait_update_time = tml::TIME_REAL(0.0);

	{// MainNode Create
		this->main_node = this->GetRootNode()->GetChildNode(L"main");

		if (this->main_node == nullptr) {
			return (-1);
		}
	}

	this->SetCanvas(0U, this->canvas_2d);
	this->SetCanvas(1U, this->canvas_3d);
	this->SetModel(0U, this->bg_model);
	this->SetModel(1U, this->wait_model);

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::InitScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::InitScene::OnUpdate(void)
{
	switch (this->progress_type_) {
	case 1U: {
		if (this->deferred_create_res_itr_ != this->deferred_create_res_cont_.end()) {
			auto &res = (*this->deferred_create_res_itr_);

			if (res->IsDeferredCreated()) {
				++this->deferred_create_res_itr_;
			} else if (!res->IsDeferredCreating()) {
				if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
					OutputDebugString(L"Error: Resource Deferred Create\n");
				}

				this->GetManager()->EndScene();

				return;
			}
		}

		if (this->deferred_create_res_itr_ == this->deferred_create_res_cont_.end()) {
			this->progress_type_ = 2U;
		}

		this->wait_update_time += this->GetManager()->GetFrameRate().GetElapsedTime();

		break;
	}
	case 2U: {
		this->wait_update_time += this->GetManager()->GetFrameRate().GetElapsedTime();

		if (this->wait_update_time.count() >= 3.0) {
			{// TitleScene Start
				tml::shared_ptr<tml::scene::Scene> scene;

				if (this->GetManager()->GetScene(scene, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::TITLE_SCENE_PREFAB)) == nullptr) {
					if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
						OutputDebugString(L"Error: TitleScene Create\n");
					}

					this->GetManager()->EndScene();

					return;
				}

				if (this->GetManager()->StartScene(scene) < 0) {
					if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
						OutputDebugString(L"Error: TitleScene Start\n");
					}

					this->GetManager()->EndScene();

					return;
				}
			}

			this->progress_type_ = 3U;
		}

		break;
	}
	case 5U: {
		break;
	}
	}

	return;
}
