/**
 * @file
 * @brief MainThreadコードファイル
 */


#include "MainThread.h"
#include <windowsx.h>
#include "../../lib/tml/memory/MemoryUtil.h"
#include "../../lib/tml/string/StringUtil.h"
#include "../../lib/tml/time/TimeUtil.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/random/RandomUtil.h"
#include "../../lib/tml/file/FileUtil.h"
#include "../../lib/tml/thread/ThreadUtil.h"
#include "../../lib/tml/input/MouseEvent.h"
#include "../../lib/tml/input/KeyboardEvent.h"
#include "../constant/ConstantUtil_FILE.h"
#include "../constant/ConstantUtil_WINDOW.h"
#include "../resource/resource.h"
#include "../thread/TestThread.h"

#include "../../lib/tml/graphic/Camera.h"
#include "../../lib/tml/graphic/Light.h"
#include "../../lib/tml/graphic/Fog.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/SpriteModel.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/sound/BGMSound.h"
#include "../../lib/tml/sound/SESound.h"


/**
 * @brief コンストラクタ
 */
cpp_base::MainThread::MainThread() :
	log_update_time_(0.0)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::MainThread::~MainThread()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::MainThread::Release(void)
{
	this->graphic_mgr_.ReleaseResource(this->camera_);
	this->graphic_mgr_.ReleaseResource(this->title_bg_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->title_logo_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->title_start_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->title_start_font_);
	this->graphic_mgr_.ReleaseResource(this->title_footer_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->title_footer_font_);
	this->graphic_mgr_.ReleaseResource(this->log_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->log_font_);
	this->sound_mgr_.ReleaseResource(this->title_bgm_sound_);
	this->sound_mgr_.ReleaseResource(this->title_start_se_sound_);

	this->input_mgr_.Init();
	this->graphic_mgr_.Init();
	this->sound_mgr_.Init();

	this->DeleteWindow_();
	this->DeleteCOM();

	tml::MainThread::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::MainThread::Init(void)
{
	this->Release();

	this->frame_rate_.Init();
	this->sys_conf_file_.Init();

	this->log_update_time_ = tml::TIME_REAL(0.0);

	tml::MainThread::Init();

	return;
}


/**
 * @brief Create関数
 * @param instance_handle (instance_handle)
 * @param wnd_name (window_name)
 * @param wnd_show_type (window_show_type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainThread::Create(const HINSTANCE instance_handle, const WCHAR *wnd_name, const INT wnd_show_type)
{
	this->Init();

	if (tml::MainThread::Create(instance_handle, wnd_name, wnd_show_type) < 0) {
		this->Init();

		return (-1);
	}

	{// SystemConfigFile Read
		this->sys_conf_file_.read_desc.data.file_path = cpp_base::ConstantUtil::FILE::SYSTEM_CONFIG_FILE_PATH;

		if (this->sys_conf_file_.Read() < 0) {
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
INT cpp_base::MainThread::Start(void)
{
	{// COM Create
		if (this->CreateCOM() < 0) {
			return (-1);
		}
	}

	{// Window Create
		WNDCLASSEX wnd_class = {};

		wnd_class.cbSize = sizeof(wnd_class);
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.lpfnWndProc = cpp_base::MainThread::WindowProcedure;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		wnd_class.hInstance = this->GetInstanceHandle();
		wnd_class.hIcon = LoadIcon(this->GetInstanceHandle(), MAKEINTRESOURCE(IDI_APPLICATION_ICON1));
		wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wnd_class.lpszMenuName = nullptr;
		wnd_class.lpszClassName = cpp_base::ConstantUtil::WINDOW::CLASS_NAME;
		wnd_class.hIconSm = nullptr;

		if (this->CreateWindow_(wnd_class, this->sys_conf_file_.data.window_position, this->sys_conf_file_.data.window_size) < 0) {
			return (-1);
		}
	}

	{// InputManager Create
		tml::input::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();

		if (this->input_mgr_.Create(desc) < 0) {
			this->Init();

			return (-1);
		}
	}

	{// GraphicManager Create
		tml::graphic::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.size = this->sys_conf_file_.data.window_size;
		desc.vsync_flag = this->sys_conf_file_.data.graphic_vsync_flag;
		desc.frame_rate_limit = this->sys_conf_file_.data.graphic_frame_rate_limit;

		if (this->graphic_mgr_.Create(desc) < 0) {
			this->Init();

			return (-1);
		}
	}

	{// SoundManager Create
		tml::sound::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_device_context_handle = this->GetWindowDeviceContextHandle();
		desc.SetVolume(tml::ConstantUtil::SOUND::SOUND_TYPE::BGM, this->sys_conf_file_.data.sound_bgm_volume);
		desc.SetMuteFlag(tml::ConstantUtil::SOUND::SOUND_TYPE::BGM, this->sys_conf_file_.data.sound_bgm_mute_flag);
		desc.SetVolume(tml::ConstantUtil::SOUND::SOUND_TYPE::SE, this->sys_conf_file_.data.sound_se_volume);
		desc.SetMuteFlag(tml::ConstantUtil::SOUND::SOUND_TYPE::SE, this->sys_conf_file_.data.sound_se_mute_flag);

		if (this->sound_mgr_.Create(desc) < 0) {
			this->Init();

			return (-1);
		}
	}

	{// TestThread Start
		std::unique_ptr<tml::SubThread> th = std::make_unique<cpp_base::TestThread>();

		if (dynamic_cast<cpp_base::TestThread *>(th.get())->Create() < 0) {
			return (-1);
		}

		if (tml::ThreadUtil::Start(th) < 0) {
			return (-1);
		}
	}

	{// Camera Create
		tml::graphic::CameraDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.type = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::PERSPECTIVE;
		desc.fov_angle = tml::MathUtil::GetAngleRadian(55.0f);
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->graphic_mgr_.GetSize().x), static_cast<FLOAT>(this->graphic_mgr_.GetSize().y));
		desc.near_clip = 0.1f;
		desc.far_clip = 1000.0f;

		this->graphic_mgr_.GetResource<tml::graphic::Camera>(this->camera_, desc);

		if (this->camera_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// TitleBackgroundSpriteModell Create
		tml::graphic::SpriteModelDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->graphic_mgr_.GetSize().x), static_cast<FLOAT>(this->graphic_mgr_.GetSize().y));

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

		desc.Read(read_desc);

		this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->title_bg_sprite_model_, desc);

		if (this->title_bg_sprite_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->title_bg_sprite_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = L"res/title_bg_img1.png";

			this->graphic_mgr_.GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->title_bg_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
			this->graphic_mgr_.ReleaseResource(tex);
		}
	}

	{// TitleLogoSpriteModel Create
		tml::graphic::SpriteModelDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.position.Set(tml::XMFLOAT2EX(0.0f, 32.0f));

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

		desc.Read(read_desc);

		this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->title_logo_sprite_model_, desc);

		if (this->title_logo_sprite_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->title_logo_sprite_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = L"res/title_logo_img1.png";

			this->graphic_mgr_.GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->title_logo_sprite_model_->SetSize(tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y)));

			this->title_logo_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
			this->graphic_mgr_.ReleaseResource(tex);
		}
	}

	tml::XMUINT2EX title_start_tex_size = tml::XMUINT2EX(128U, 32U);
	tml::XMUINT2EX title_start_font_size = tml::XMUINT2EX(0U, 24U);

	{// TitleStartSpriteModel Create
		tml::graphic::SpriteModelDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -192.0f));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

		desc.Read(read_desc);

		this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->title_start_sprite_model_, desc);

		if (this->title_start_sprite_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->title_start_sprite_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, title_start_tex_size);
			desc.cpu_buffer_flag = true;

			this->graphic_mgr_.GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->title_start_sprite_model_->SetSize(tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y)));

			this->title_start_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
			this->graphic_mgr_.ReleaseResource(tex);
		}
	}

	{// TitleStartFont Create
		tml::graphic::FontDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.SetFontDesc(title_start_font_size, L"ＭＳ ゴシック");

		this->graphic_mgr_.GetResource<tml::graphic::Font>(this->title_start_font_, desc);

		if (this->title_start_font_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// TitleStartTexture Update
		auto tex = this->title_start_sprite_model_->GetTexture(this->title_start_sprite_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"スタート", tml::XMINT2EX(0, 0), this->title_start_font_.get());
		tex->UploadCPUBuffer();
	}

	tml::XMUINT2EX title_footer_tex_size = tml::XMUINT2EX(this->graphic_mgr_.GetSize().x, 32U);
	tml::XMUINT2EX title_footer_font_size = tml::XMUINT2EX(0U, 16U);

	{// TitleFooterSpriteModel Create
		tml::graphic::SpriteModelDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -static_cast<FLOAT>(this->graphic_mgr_.GetSize().y >> 1) + static_cast<FLOAT>(title_footer_tex_size.y >> 1)));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

		desc.Read(read_desc);

		this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->title_footer_sprite_model_, desc);

		if (this->title_footer_sprite_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->title_footer_sprite_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, title_footer_tex_size);
			desc.cpu_buffer_flag = true;

			this->graphic_mgr_.GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->title_footer_sprite_model_->SetSize(tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y)));

			this->title_footer_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
			this->graphic_mgr_.ReleaseResource(tex);
		}
	}

	{// TitleFooterFont Create
		tml::graphic::FontDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.SetFontDesc(title_footer_font_size, L"ＭＳ ゴシック");

		this->graphic_mgr_.GetResource<tml::graphic::Font>(this->title_footer_font_, desc);

		if (this->title_footer_font_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// TitleFooterTexture Update
		std::wstring company_name;

		company_name += cpp_base::ConstantUtil::APPLICATION::COMPANY_NAME;

		std::wstring version_name;

		version_name += L"Version ";
		version_name += cpp_base::ConstantUtil::APPLICATION::VERSION_NAME;

		auto tex = this->title_footer_sprite_model_->GetTexture(this->title_footer_sprite_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(company_name.c_str(), tml::XMINT2EX(4, 4), this->title_footer_font_.get());
		tex->DrawCPUBufferString(version_name.c_str(), tml::XMINT2EX(this->graphic_mgr_.GetSize().x - 256 - 4, 4), this->title_footer_font_.get());
		tex->UploadCPUBuffer();
	}

	tml::XMUINT2EX log_tex_size = this->graphic_mgr_.GetSize();
	tml::XMUINT2EX log_font_size = tml::XMUINT2EX(0U, 16U);

	{// LogSpriteModel Create
		tml::graphic::SpriteModelDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

		desc.Read(read_desc);

		this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->log_sprite_model_, desc);

		if (this->log_sprite_model_ == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->log_sprite_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, log_tex_size);
			desc.cpu_buffer_flag = true;

			this->graphic_mgr_.GetResource<tml::graphic::Texture>(tex, desc);

			if (tex == nullptr) {
				this->Init();

				return (-1);
			}

			this->log_sprite_model_->SetSize(tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y)));

			this->log_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
			this->graphic_mgr_.ReleaseResource(tex);
		}
	}

	{// LogFont Create
		tml::graphic::FontDesc desc;

		desc.manager = &this->graphic_mgr_;
		desc.SetFontDesc(log_font_size, L"ＭＳ ゴシック");

		this->graphic_mgr_.GetResource<tml::graphic::Font>(this->log_font_, desc);

		if (this->log_font_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	this->log_update_time_ = tml::TIME_REAL(1.0);

	{// TitleBGMSound Create
		tml::sound::BGMSoundDesc desc;

		desc.manager = &this->sound_mgr_;
		desc.file_read_desc.data.file_path = L"res/title_bgm_sound1.mp3";

		this->sound_mgr_.GetResource<tml::sound::BGMSound>(this->title_bgm_sound_, desc);

		if (this->title_bgm_sound_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// TitleStartSESound Create
		tml::sound::SESoundDesc desc;

		desc.manager = &this->sound_mgr_;
		desc.file_read_desc.data.file_path = L"res/title_start_se_sound1.mp3";

		this->sound_mgr_.GetResource<tml::sound::SESound>(this->title_start_se_sound_, desc);

		if (this->title_start_se_sound_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	this->sound_mgr_.Play(this->title_bgm_sound_.get(), true);

	this->frame_rate_.Start(this->graphic_mgr_.GetFrameRateLimit());

	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::MainThread::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::MainThread::Update(void)
{
	this->input_mgr_.Update();

	for (UINT event_i = 0U; event_i < this->input_mgr_.GetEventCount(); ++event_i) {
		auto &event = this->input_mgr_.GetEventArray()[event_i];

		switch (event->GetEventType()) {
		case tml::ConstantUtil::INPUT::EVENT_TYPE::MOUSE: {
			auto &event_dat = reinterpret_cast<tml::input::MouseEvent *>(event.get())->GetData();

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
				this->sound_mgr_.Play(this->title_start_se_sound_.get(), false);
			}

			break;
		}
		}
	}

	this->log_update_time_ += this->frame_rate_.GetElapsedTime();

	if (this->log_update_time_ >= tml::TIME_REAL(1.0)) {
		{// LogTexture Update
			auto &frame_rate = this->frame_rate_;
			auto mem_allocator_info = tml::MemoryUtil::GetAllocatorInfo();

			WCHAR log_str[1024];

			_snwprintf_s(log_str, sizeof(log_str) >> 1, _TRUNCATE, L"FPS=%.2f/%u\nMEM=%u/%u/%u", frame_rate.GetFPS(), frame_rate.GetLimit(), mem_allocator_info.use_size, mem_allocator_info.size, mem_allocator_info.use_count);

			auto tex = this->log_sprite_model_->GetTexture(this->log_sprite_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

			tex->ClearCPUBuffer();
			tex->DrawCPUBufferString(log_str, tml::XMINT2EX(4, 4), this->log_font_.get());
			tex->UploadCPUBuffer();
		}

		this->log_update_time_ = tml::TIME_REAL(0.0);
	}

	this->graphic_mgr_.SetDrawCamera(this->camera_.get());
	this->graphic_mgr_.SetDrawModel(this->title_bg_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->title_logo_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->title_start_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->title_footer_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->log_sprite_model_.get());

	this->graphic_mgr_.Update();

	this->sound_mgr_.Update();

	this->frame_rate_.Update();

	return;
}


/**
 * @brief WindowProcedure関数
 * @param wnd_handle (window_handle)
 * @param msg_type (message_type)
 * @param msg_wp (message_wparameter)
 * @param msg_lp (message_lparameter)
 * @return res (result)<br>
 * 0未満=失敗
 */
LRESULT CALLBACK cpp_base::MainThread::WindowProcedure(HWND wnd_handle, UINT msg_type, WPARAM msg_wp, LPARAM msg_lp)
{
	static cpp_base::MainThread *th = nullptr;

	if (th == nullptr) {
		th = reinterpret_cast<cpp_base::MainThread *>(tml::ThreadUtil::Get());
	}

	switch (msg_type) {
	case WM_CREATE: {
		std::array<RAWINPUTDEVICE, 2U> rid_ary;

		// Mouse Set
		rid_ary[0].usUsagePage = 0x01;
		rid_ary[0].usUsage = 0x02;
		rid_ary[0].dwFlags = 0UL;
		rid_ary[0].hwndTarget = wnd_handle;
 
		// Keyboard Set
		rid_ary[1].usUsagePage = 0x01;
		rid_ary[1].usUsage = 0x06;
		rid_ary[1].dwFlags = 0UL;
		rid_ary[1].hwndTarget = wnd_handle;
 
		RegisterRawInputDevices(rid_ary.data(), rid_ary.size(), sizeof(RAWINPUTDEVICE));

		return (0);
	}
	case WM_DESTROY: {
		PostQuitMessage(0);

		return (0);
	}
	case WM_SETFOCUS: {
		return (0);
	}
	case WM_KILLFOCUS: {
		th->GetInputManager().SetMouseCodeState(false);
		th->GetInputManager().SetKeyboardCodeState(false);

		return (0);
	}
	case WM_INPUT: {
		RAWINPUT ri;
		UINT ri_size = 0U;

		GetRawInputData(reinterpret_cast<HRAWINPUT>(msg_lp), RID_INPUT, nullptr, &ri_size, sizeof(RAWINPUTHEADER));

		if ((ri_size <= 0U) || (ri_size > sizeof(RAWINPUT))) {
			return (0);
		}

		if (GetRawInputData(reinterpret_cast<HRAWINPUT>(msg_lp), RID_INPUT, &ri, &ri_size, sizeof(RAWINPUTHEADER)) != ri_size) {
			return (0);
		}

		switch (ri.header.dwType) {
		case RIM_TYPEMOUSE: {
			tml::input::MouseEventData event_dat;

			event_dat.SetRawInput(ri.data.mouse, th->GetInputManager().GetMousePosition());

			th->GetInputManager().AddEvent<tml::input::MouseEvent>(event_dat);

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::LEFT, true);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::LEFT_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::LEFT, false);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::RIGHT_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::RIGHT, true);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::RIGHT_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::RIGHT, false);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::MIDDLE_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::MIDDLE, true);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::MIDDLE_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::MIDDLE, false);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE1_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE1, true);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE1_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE1, false);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE2_BUTTON_DOWN)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE2, true);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::SIDE2_BUTTON_UP)) {
				th->GetInputManager().SetMouseCodeState(tml::ConstantUtil::INPUT::MOUSE_CODE::SIDE2, false);
			}

			break;
		}
		case RIM_TYPEKEYBOARD: {
			tml::input::KeyboardEventData event_dat;

			event_dat.SetRawInput(ri.data.keyboard);

			th->GetInputManager().AddEvent<tml::input::KeyboardEvent>(event_dat);

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::BUTTON_DOWN)) {
				th->GetInputManager().SetKeyboardCodeState(event_dat.code, true);
			}

			if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::BUTTON_UP)) {
				th->GetInputManager().SetKeyboardCodeState(event_dat.code, false);
			}

			break;
		}
		}

		return (0);
	}
	case WM_MOUSEMOVE: {
		th->GetInputManager().SetMousePosition(tml::XMINT2EX(GET_X_LPARAM(msg_lp), GET_Y_LPARAM(msg_lp)));

		return (0);
	}
	}

	return (DefWindowProc(wnd_handle, msg_type, msg_wp, msg_lp));
}
