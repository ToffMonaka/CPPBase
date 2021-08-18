/**
 * @file
 * @brief InitSceneコードファイル
 */


#include "InitScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Camera2D.h"
#include "../../lib/tml/graphic/Camera3D.h"
#include "../../lib/tml/graphic/Model2D.h"
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
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::SceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// InitScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"INIT_SCENE");

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
		tml::graphic::Model2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->GetGraphicManager()->GetSize().x), static_cast<FLOAT>(this->GetGraphicManager()->GetSize().y));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::Model2D>(this->bg_model, desc) == nullptr) {
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

	tml::XMUINT2EX wait_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX wait_model_size = tml::XMUINT2EX(320U, 32U);

	{// WaitFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.SetFontDesc(wait_font_size, L"ＭＳ ゴシック");

		if (this->GetGraphicManager()->GetResource<tml::graphic::Font>(this->wait_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WaitModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(this->GetGraphicManager());
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::Model2D>(this->wait_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->wait_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(this->GetGraphicManager());
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, wait_model_size);
			desc.cpu_buffer_flag = true;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->wait_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->wait_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
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
		if (this->GetRootNode()->GetChildNode(this->main_node, L"main") == nullptr) {
			return (-1);
		}
	}

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

				if (this->GetManager()->factory.scene_by_xml_file.Get(scene, tml::ConstantUtil::SCENE::CLASS_NAME::SCENE, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::TITLE_SCENE)) == nullptr) {
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

	this->canvas_2d->SetDrawCamera(this->camera_2d.get());
	this->canvas_2d->SetDrawModel(this->bg_model.get());
	this->canvas_2d->SetDrawModel(this->wait_model.get());

	this->GetGraphicManager()->SetDrawCanvas(this->canvas_2d.get());

	return;
}
