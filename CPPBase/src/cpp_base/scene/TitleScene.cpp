/**
 * @file
 * @brief TitleSceneコードファイル
 */


#include "TitleScene.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/Manager.h"
#include "../../lib/tml/input/MouseEvent.h"
#include "../../lib/tml/input/KeyboardEvent.h"
#include "../../lib/tml/graphic/Manager.h"
#include "../../lib/tml/graphic/Camera.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Object2DModel.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/sound/Manager.h"
#include "../../lib/tml/sound/BGMSound.h"
#include "../../lib/tml/sound/SESound.h"
#include "../../lib/tml/scene/Manager.h"


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

	tml::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::SceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// TitleScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"TITLE_SCENE");

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
	log_update_time_(0.0)
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
	tml::scene::Scene::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::TitleScene::Init(void)
{
	this->Release();

	this->camera_.reset();
	this->bg_model_.reset();
	this->logo_model_.reset();
	this->start_model_.reset();
	this->start_font_.reset();
	this->start_se_sound_.reset();
	this->footer_model_.reset();
	this->footer_font_.reset();
	this->bgm_sound_.reset();
	this->log_update_time_ = tml::TIME_REAL(0.0);
	this->log_model_.reset();
	this->log_font_.reset();

	tml::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleScene::Create(const cpp_base::scene::TitleSceneDesc &desc)
{
	this->Init();

	if (tml::scene::Scene::Create(desc, static_cast<tml::ConstantUtil::SCENE::SCENE_TYPE>(cpp_base::ConstantUtil::SCENE::SCENE_TYPE::TITLE)) < 0) {
		this->Init();

		return (-1);
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

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

	{// BackgroundModel Create
		tml::graphic::Object2DModelDesc desc;

		desc.manager = graphic_mgr;
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));

		auto read_desc = tml::INIFileReadDesc(L"res/obj_2d_model.ini");

		desc.Read(read_desc);

		graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->bg_model_, desc);

		if (this->bg_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = graphic_mgr;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = L"res/title_bg_img1.png";

			graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->bg_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	{// LogoModel Create
		tml::graphic::Object2DModelDesc desc;

		desc.manager = graphic_mgr;
		desc.position.Set(tml::XMFLOAT2EX(0.0f, 32.0f));

		auto read_desc = tml::INIFileReadDesc(L"res/obj_2d_model.ini");

		desc.Read(read_desc);

		graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->logo_model_, desc);

		if (this->logo_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->logo_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = graphic_mgr;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = L"res/title_logo_img1.png";

			graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->logo_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->logo_model_->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
		}
	}

	tml::XMUINT2EX start_tex_size = tml::XMUINT2EX(128U, 32U);
	tml::XMUINT2EX start_font_size = tml::XMUINT2EX(0U, 24U);

	{// StartModel Create
		tml::graphic::Object2DModelDesc desc;

		desc.manager = graphic_mgr;
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -192.0f));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/obj_2d_model.ini");

		desc.Read(read_desc);

		graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->start_model_, desc);

		if (this->start_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->start_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = graphic_mgr;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, start_tex_size);
			desc.cpu_buffer_flag = true;

			graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->start_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->start_model_->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
		}
	}

	{// StartFont Create
		tml::graphic::FontDesc desc;

		desc.manager = graphic_mgr;
		desc.SetFontDesc(start_font_size, L"ＭＳ ゴシック");

		graphic_mgr->GetResource<tml::graphic::Font>(this->start_font_, desc);

		if (this->start_font_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StartTexture Update
		auto tex = this->start_model_->GetTexture(this->start_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"スタート", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->start_font_.get());
		tex->UploadCPUBuffer();
	}

	{// StartSESound Create
		tml::sound::SESoundDesc desc;

		desc.manager = sound_mgr;
		desc.file_read_desc.data.file_path = L"res/title_start_se_sound1.mp3";

		sound_mgr->GetResource<tml::sound::SESound>(this->start_se_sound_, desc);

		if (this->start_se_sound_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	tml::XMUINT2EX footer_tex_size = tml::XMUINT2EX(graphic_mgr->GetSize().x, 24U);
	tml::XMUINT2EX footer_font_size = tml::XMUINT2EX(0U, 16U);

	{// FooterModel Create
		tml::graphic::Object2DModelDesc desc;

		desc.manager = graphic_mgr;
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -static_cast<FLOAT>(graphic_mgr->GetSize().GetHalfY()) + static_cast<FLOAT>(footer_tex_size.y >> 1)));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/obj_2d_model.ini");

		desc.Read(read_desc);

		graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->footer_model_, desc);

		if (this->footer_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->footer_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = graphic_mgr;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, footer_tex_size);
			desc.cpu_buffer_flag = true;

			graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->footer_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->footer_model_->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
		}
	}

	{// FooterFont Create
		tml::graphic::FontDesc desc;

		desc.manager = graphic_mgr;
		desc.SetFontDesc(footer_font_size, L"ＭＳ ゴシック");

		graphic_mgr->GetResource<tml::graphic::Font>(this->footer_font_, desc);

		if (this->footer_font_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FooterTexture Update
		std::wstring company_name;

		company_name = cpp_base::ConstantUtil::APPLICATION::COMPANY_NAME;

		std::wstring version_name;

		version_name = L"Version ";
		version_name += cpp_base::ConstantUtil::APPLICATION::VERSION_NAME;

		auto tex = this->footer_model_->GetTexture(this->footer_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(company_name.c_str(), tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(4, -4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::BOTTOM_LEFT, this->footer_font_.get());
		tex->DrawCPUBufferString(version_name.c_str(), tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(-4, -4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::BOTTOM_RIGHT, this->footer_font_.get());
		tex->UploadCPUBuffer();
	}

	{// BGMSound Create
		tml::sound::BGMSoundDesc desc;

		desc.manager = sound_mgr;
		desc.file_read_desc.data.file_path = L"res/title_bgm_sound1.mp3";

		sound_mgr->GetResource<tml::sound::BGMSound>(this->bgm_sound_, desc);

		if (this->bgm_sound_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	this->log_update_time_ = tml::TIME_REAL(1.0);

	tml::XMUINT2EX log_tex_size = graphic_mgr->GetSize();
	tml::XMUINT2EX log_font_size = tml::XMUINT2EX(0U, 16U);

	{// LogModel Create
		tml::graphic::Object2DModelDesc desc;

		desc.manager = graphic_mgr;
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/obj_2d_model.ini");

		desc.Read(read_desc);

		graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->log_model_, desc);

		if (this->log_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->log_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = graphic_mgr;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, log_tex_size);
			desc.cpu_buffer_flag = true;

			graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->log_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->log_model_->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
		}
	}

	{// LogFont Create
		tml::graphic::FontDesc desc;

		desc.manager = graphic_mgr;
		desc.SetFontDesc(log_font_size, L"ＭＳ ゴシック");

		graphic_mgr->GetResource<tml::graphic::Font>(this->log_font_, desc);

		if (this->log_font_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleScene::Start(void)
{
	auto sound_mgr = this->GetManager()->GetSoundManager();

	sound_mgr->Play(this->bgm_sound_.get(), true);

	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::scene::TitleScene::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::scene::TitleScene::Update(void)
{
	auto input_mgr = this->GetManager()->GetInputManager();
	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

	for (UINT event_i = 0U; event_i < input_mgr->GetEventCount(); ++event_i) {
		auto event = reinterpret_cast<tml::input::ManagerEvent *>(input_mgr->GetEventArray()[event_i].get());

		switch (event->GetEventType()) {
		case tml::ConstantUtil::INPUT::EVENT_TYPE::MOUSE: {
			auto &event_dat = reinterpret_cast<tml::input::MouseEvent *>(event)->GetData();

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
				if (this->start_model_->IsHitByMouse(input_mgr->GetMousePosition())) {
					sound_mgr->Play(this->start_se_sound_.get(), false);

					this->GetManager()->End();
				}
			}

			break;
		}
		}
	}

	if (this->start_model_->IsHitByMouse(input_mgr->GetMousePosition())) {
		this->start_model_->scale = tml::XMFLOAT2EX(1.2f, 1.2f);
		this->start_model_->color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), 1.0f);
	} else {
		this->start_model_->scale = tml::XMFLOAT2EX(1.0f, 1.0f);
		this->start_model_->color = tml::XMFLOAT4EX(1.0f, 1.0f, 1.0f, 1.0f);
	}

	this->log_update_time_ += this->GetManager()->GetFrameRate().GetElapsedTime();

	if (this->log_update_time_.count() >= 1.0) {
		{// LogTexture Update
			auto &frame_rate = this->GetManager()->GetFrameRate();
			auto mem_allocator_info = tml::MemoryUtil::GetAllocatorInfo();

			WCHAR log_str[1024];

			_snwprintf_s(log_str, sizeof(log_str) >> 1, _TRUNCATE, L"FPS=%.2f/%u\nMEM=%u/%u/%u", frame_rate.GetFPS(), frame_rate.GetLimit(), mem_allocator_info.use_size, mem_allocator_info.size, mem_allocator_info.use_count);

			auto tex = this->log_model_->GetTexture(this->log_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

			tex->ClearCPUBuffer();
			tex->DrawCPUBufferString(log_str, tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(4, 4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::TOP_LEFT, this->log_font_.get());
			tex->UploadCPUBuffer();
		}

		this->log_update_time_ = tml::TIME_REAL(0.0);
	}

	graphic_mgr->SetDrawCamera(this->camera_.get());
	graphic_mgr->SetDrawModel(this->bg_model_.get());
	graphic_mgr->SetDrawModel(this->logo_model_.get());
	graphic_mgr->SetDrawModel(this->start_model_.get());
	graphic_mgr->SetDrawModel(this->footer_model_.get());
	graphic_mgr->SetDrawModel(this->log_model_.get());

	return;
}
