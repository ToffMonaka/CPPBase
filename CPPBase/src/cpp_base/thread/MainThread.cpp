/**
 * @file
 * @brief MainThreadコードファイル
 */


#include "MainThread.h"
#include "../../lib/tml/memory/MemoryUtil.h"
#include "../../lib/tml/string/StringUtil.h"
#include "../../lib/tml/time/TimeUtil.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/random/RandomUtil.h"
#include "../../lib/tml/file/FileUtil.h"
#include "../../lib/tml/thread/ThreadUtil.h"
#include "../constant/ConstantUtil_WINDOW.h"
#include "../constant/ConstantUtil_FILE.h"
#include "../resource/resource.h"
#include "../thread/TestThread.h"

#include "../../lib/tml/graphic/Camera.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/SpriteModel.h"


/**
 * @brief コンストラクタ
 */
cpp_base::MainThread::MainThread()
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
	this->graphic_mgr_.ReleaseResource(this->test_camera_);
	this->graphic_mgr_.ReleaseResource(this->test1_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->test2_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->test3_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->title_bg_sprite_model_);
	this->graphic_mgr_.ReleaseResource(this->title_logo_sprite_model_);

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
	this->input_mgr_.Init();
	this->graphic_mgr_.Init();
	this->sound_mgr_.Init();

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
	{// Window Create
		WNDCLASSEX wnd_class = {};

		wnd_class.cbSize = sizeof(wnd_class);
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.lpfnWndProc = cpp_base::MainThread::WindowProcedure;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		wnd_class.hInstance = this->GetInstanceHandle();
		wnd_class.hIcon = LoadIcon(this->GetInstanceHandle(), MAKEINTRESOURCE(IDI_APPLICATION_ICON1));
		wnd_class.hCursor = LoadCursor(this->GetInstanceHandle(), IDC_ARROW);
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

		if (this->input_mgr_.Create(desc) < 0) {
			this->Init();

			return (-1);
		}
	}

	{// GraphicManager Create
		tml::graphic::ManagerDesc desc;

		desc.window_handle = this->GetWindowHandle();
		desc.window_size = this->sys_conf_file_.data.window_size;

		if (this->graphic_mgr_.Create(desc) < 0) {
			this->Init();

			return (-1);
		}
	}

	{// SoundManager Create
		tml::sound::ManagerDesc desc;

		if (this->sound_mgr_.Create(desc) < 0) {
			this->Init();

			return (-1);
		}
	}

	{// Test
		{// TestThread Start
			std::unique_ptr<tml::SubThread> th = std::make_unique<cpp_base::TestThread>();

			if (dynamic_cast<cpp_base::TestThread *>(th.get())->Create() < 0) {
				return (-1);
			}

			if (tml::ThreadUtil::Start(th) < 0) {
				return (-1);
			}
		}

		{// TestCamera Create
			tml::graphic::CameraDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.type = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::PERSPECTIVE;
			desc.fov_angle = XMConvertToRadians(55.0f);
			desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->graphic_mgr_.GetSwapChainDesc().BufferDesc.Width), static_cast<FLOAT>(this->graphic_mgr_.GetSwapChainDesc().BufferDesc.Height));
			desc.near_clip = 0.1f;
			desc.far_clip = 1000.0f;

			this->graphic_mgr_.GetResource<tml::graphic::Camera>(this->test_camera_, desc);

			if (this->test_camera_ == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// Test1SpriteModell Create
			tml::graphic::SpriteModelDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.size = 128.0f;
			desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(255U), tml::MathUtil::GetColor1(0U), tml::MathUtil::GetColor1(0U), 1.0f);

			auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

			desc.Read(read_desc);

			this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->test1_sprite_model_, desc);

			if (this->test1_sprite_model_ == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// Test2SpriteModell Create
			tml::graphic::SpriteModelDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.size = 128.0f;
			desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(255U), tml::MathUtil::GetColor1(0U), tml::MathUtil::GetColor1(0U), 1.0f);

			auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

			desc.Read(read_desc);

			this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->test2_sprite_model_, desc);

			if (this->test2_sprite_model_ == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// Test3SpriteModell Create
			tml::graphic::SpriteModelDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.size = 128.0f;
			desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(255U), tml::MathUtil::GetColor1(0U), tml::MathUtil::GetColor1(0U), 1.0f);

			auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

			desc.Read(read_desc);

			this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->test3_sprite_model_, desc);

			if (this->test3_sprite_model_ == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// TitleBackgroundSpriteModell Create
			tml::graphic::SpriteModelDesc desc;

			desc.manager = &this->graphic_mgr_;
			desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->graphic_mgr_.GetSwapChainDesc().BufferDesc.Width), static_cast<FLOAT>(this->graphic_mgr_.GetSwapChainDesc().BufferDesc.Height));

			auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

			desc.Read(read_desc);

			this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->title_bg_sprite_model_, desc);

			if (this->title_bg_sprite_model_ == nullptr) {
				this->Init();

				return (-1);
			}

			auto stage = this->title_bg_sprite_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
			auto layer = stage->GetLayer(0U);

			layer->SetDiffuseTextureIndex(0U);

			{// DiffuseTexture Create
				tml::shared_ptr<tml::graphic::Texture> tex;

				tml::graphic::TextureDesc desc;

				desc.manager = &this->graphic_mgr_;
				desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::SR);
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

			auto read_desc = tml::INIFileReadDesc(L"res/sprite_model.ini");

			desc.Read(read_desc);

			this->graphic_mgr_.GetResource<tml::graphic::SpriteModel>(this->title_logo_sprite_model_, desc);

			if (this->title_logo_sprite_model_ == nullptr) {
				this->Init();

				return (-1);
			}

			auto stage = this->title_logo_sprite_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
			auto layer = stage->GetLayer(0U);

			layer->SetDiffuseTextureIndex(0U);

			{// DiffuseTexture Create
				tml::shared_ptr<tml::graphic::Texture> tex;

				tml::graphic::TextureDesc desc;

				desc.manager = &this->graphic_mgr_;
				desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::SR);
				desc.file_read_desc_container[0].data.file_path = L"res/title_logo_img1.png";

				this->graphic_mgr_.GetResource<tml::graphic::Texture>(tex, desc);

				if (tex == nullptr) {
					this->Init();

					return (-1);
				}

				this->title_logo_sprite_model_->SetSize(tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize().x), static_cast<FLOAT>(tex->GetSize().y)));

				this->title_logo_sprite_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
				this->graphic_mgr_.ReleaseResource(tex);
			}
		}

		int a = 0;
	}

	this->frame_rate_.Start(60U);

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

	auto test1_sprite_model_pos_x = this->test1_sprite_model_->position.GetX() + 2.0f;

	if (test1_sprite_model_pos_x >= 512.0f) {
		test1_sprite_model_pos_x = -512.0f;
	}

	this->test1_sprite_model_->position.SetX(test1_sprite_model_pos_x);
	this->test1_sprite_model_->position.SetY(-256.0f);
	this->test2_sprite_model_->position.SetX(this->test1_sprite_model_->position.GetX() - 128.0f - 1.0f);
	this->test2_sprite_model_->position.SetY(this->test1_sprite_model_->position.GetY());
	this->test3_sprite_model_->position.SetX(this->test1_sprite_model_->position.GetX() + 128.0f + 1.0f);
	this->test3_sprite_model_->position.SetY(this->test1_sprite_model_->position.GetY());

	this->graphic_mgr_.SetDrawCamera(this->test_camera_.get());
	this->graphic_mgr_.SetDrawModel(this->title_bg_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->title_logo_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->test1_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->test2_sprite_model_.get());
	this->graphic_mgr_.SetDrawModel(this->test3_sprite_model_.get());

	this->graphic_mgr_.Update();

	this->sound_mgr_.Update();

	this->frame_rate_.Update();

	return;
}


/**
 * @brief WindowProcedure関数
 * @param wnd_handle (window_handle)
 * @param msg_type (message_type)
 * @param msg_param1 (message_parameter1)
 * @param msg_param2 (message_parameter2)
 * @return res (result)<br>
 * 0未満=失敗
 */
LRESULT CALLBACK cpp_base::MainThread::WindowProcedure(HWND wnd_handle, UINT msg_type, WPARAM msg_param1, LPARAM msg_param2)
{
	switch (msg_type) {
	case WM_DESTROY: {
		PostQuitMessage(0);

		return (0);
	}
	}

	return (DefWindowProc(wnd_handle, msg_type, msg_param1, msg_param2));
}
