/**
 * @file
 * @brief InitSceneコードファイル
 */


#include "InitScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Manager.h"
#include "../../lib/tml/graphic/Camera.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/SpriteModel.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/scene/Manager.h"
#include "../scene/TitleScene.h"


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

	tml::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::SceneDesc::ReadValue(ini_file) < 0) {
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
	wait_update_time_(0.0)
{
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
	if (this->GetManager() != nullptr) {
		auto graphic_mgr = this->GetManager()->GetGraphicManager();

		if (graphic_mgr != nullptr) {
			graphic_mgr->ReleaseResource(this->camera_);
			graphic_mgr->ReleaseResource(this->bg_sprite_model_);
			graphic_mgr->ReleaseResource(this->wait_sprite_model_);
			graphic_mgr->ReleaseResource(this->wait_font_);
		}
	}

	tml::scene::Scene::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitScene::Init(void)
{
	this->Release();

	this->wait_update_time_ = tml::TIME_REAL(0.0);

	tml::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitScene::Create(const cpp_base::scene::InitSceneDesc &desc)
{
	this->Init();

	if (tml::scene::Scene::Create(desc, static_cast<tml::ConstantUtil::SCENE::SCENE_TYPE>(cpp_base::ConstantUtil::SCENE::SCENE_TYPE::INIT)) < 0) {
		this->Init();

		return (-1);
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	{// Camera Create
		tml::graphic::CameraDesc desc;

		desc.manager = graphic_mgr;
		desc.type = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::PERSPECTIVE;
		desc.fov_angle = tml::MathUtil::GetAngleRadian(55.0f);
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));
		desc.near_clip = 0.1f;
		desc.far_clip = 1000.0f;

		graphic_mgr->GetResource<tml::graphic::Camera>(this->camera_, desc);

		if (this->camera_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackgroundSpriteModel Create
		tml::graphic::SpriteModelDesc desc;

		desc.manager = graphic_mgr;
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

		desc.Read(read_desc);

		graphic_mgr->GetResource<tml::graphic::SpriteModel>(this->bg_sprite_model_, desc);

		if (this->bg_sprite_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_sprite_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = graphic_mgr;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = L"res/bg_img1.png";

			graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->bg_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
			graphic_mgr->ReleaseResource(tex);
		}
	}

	tml::XMUINT2EX wait_tex_size = tml::XMUINT2EX(320U, 32U);
	tml::XMUINT2EX wait_font_size = tml::XMUINT2EX(0U, 24U);

	{// WaitSpriteModel Create
		tml::graphic::SpriteModelDesc desc;

		desc.manager = graphic_mgr;
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

		desc.Read(read_desc);

		graphic_mgr->GetResource<tml::graphic::SpriteModel>(this->wait_sprite_model_, desc);

		if (this->wait_sprite_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->wait_sprite_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = graphic_mgr;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, wait_tex_size);
			desc.cpu_buffer_flag = true;

			graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->wait_sprite_model_->SetSize(tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y)));

			this->wait_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
			graphic_mgr->ReleaseResource(tex);
		}
	}

	{// WaitFont Create
		tml::graphic::FontDesc desc;

		desc.manager = graphic_mgr;
		desc.SetFontDesc(wait_font_size, L"ＭＳ ゴシック");

		graphic_mgr->GetResource<tml::graphic::Font>(this->wait_font_, desc);

		if (this->wait_font_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WaitTexture Update
		auto tex = this->wait_sprite_model_->GetTexture(this->wait_sprite_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"ちょっと待ってね。", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->wait_font_.get());
		tex->UploadCPUBuffer();
	}

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitScene::Start(void)
{
	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::scene::InitScene::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::scene::InitScene::Update(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->wait_update_time_ += this->GetManager()->GetFrameRate().GetElapsedTime();

	if (this->wait_update_time_.count() >= 3.0) {
		{// TitleScene Start
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::TitleSceneDesc desc;

			desc.manager = this->GetManager();

			this->GetManager()->GetResource<cpp_base::scene::TitleScene>(scene, desc);

			if (scene == nullptr) {
				this->GetManager()->End();

				return;
			}

			if (this->GetManager()->Start(scene) < 0) {
				this->GetManager()->End();

				return;
			}

			this->GetManager()->ReleaseResource(scene);
		}
	}

	graphic_mgr->SetDrawCamera(this->camera_.get());
	graphic_mgr->SetDrawModel(this->bg_sprite_model_.get());
	graphic_mgr->SetDrawModel(this->wait_sprite_model_.get());

	return;
}
