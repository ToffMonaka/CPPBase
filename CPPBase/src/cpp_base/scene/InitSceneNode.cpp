/**
 * @file
 * @brief InitSceneNodeコードファイル
 */


#include "InitSceneNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Camera.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Object2DModel.h"
#include "../../lib/tml/graphic/Font.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::InitSceneNodeDesc::InitSceneNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitSceneNodeDesc::~InitSceneNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitSceneNodeDesc::Init(void)
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
INT cpp_base::scene::InitSceneNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseNodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// InitSceneNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"INIT_SCENE_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::InitSceneNode::InitSceneNode() :
	wait_update_time_(0.0)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitSceneNode::~InitSceneNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::InitSceneNode::Release(void)
{
	cpp_base::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitSceneNode::Init(void)
{
	this->Release();

	this->camera_.reset();
	this->bg_model_.reset();
	this->wait_update_time_ = tml::TIME_REAL(0.0);
	this->wait_model_.reset();
	this->wait_font_.reset();

	cpp_base::scene::BaseNode::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitSceneNode::Create(const cpp_base::scene::InitSceneNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::BaseNode::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	{// Camera Create
		tml::graphic::CameraDesc desc;

		desc.SetManager(graphic_mgr);
		desc.type = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::PERSPECTIVE;
		desc.fov_angle = tml::MathUtil::GetAngleRadian(55.0f);
		desc.fov_size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));
		desc.near_clip = 0.1f;
		desc.far_clip = 1000.0f;

		if (graphic_mgr->GetResource<tml::graphic::Camera>(this->camera_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackgroundModel Create
		tml::graphic::Object2DModelDesc desc;

		desc.SetManager(graphic_mgr);
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->bg_model_, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
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

			this->bg_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	tml::XMUINT2EX wait_tex_size = tml::XMUINT2EX(320U, 32U);
	tml::XMUINT2EX wait_font_size = tml::XMUINT2EX(0U, 24U);

	{// WaitModel Create
		tml::graphic::Object2DModelDesc desc;

		desc.SetManager(graphic_mgr);
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->wait_model_, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->wait_model_->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, wait_tex_size);
			desc.cpu_buffer_flag = true;

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->wait_model_->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->wait_model_->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
		}
	}

	{// WaitFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(graphic_mgr);
		desc.SetFontDesc(wait_font_size, L"ＭＳ ゴシック");

		if (graphic_mgr->GetResource<tml::graphic::Font>(this->wait_font_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WaitTexture Update
		auto tex = this->wait_model_->GetTexture(this->wait_model_->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"ちょっと待ってね。", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->wait_font_.get());
		tex->UploadCPUBuffer();
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitSceneNode::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::InitSceneNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::InitSceneNode::OnUpdate(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->wait_update_time_ += this->GetManager()->GetFrameRate().GetElapsedTime();

	if (this->wait_update_time_.count() >= 3.0) {
		{// TitleScene Start
			tml::shared_ptr<tml::scene::Scene> scene;

			if (this->GetManager()->factory.scene_by_xml_file.Get(scene, L"Scene", tml::XMLFileReadDesc(L"res/title_scene.xml")) == nullptr) {
				this->GetManager()->EndScene();

				return;
			}

			if (this->GetManager()->StartScene(scene) < 0) {
				this->GetManager()->EndScene();

				return;
			}
		}
	}

	graphic_mgr->SetDrawCamera(this->camera_.get());
	graphic_mgr->SetDrawModel(this->bg_model_.get());
	graphic_mgr->SetDrawModel(this->wait_model_.get());

	if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
		this->GetManager()->common2.UpdateLog(this->GetManager()->GetFrameRate().GetElapsedTime());

		graphic_mgr->SetDrawModel(this->GetManager()->common2.log_model.get());
	}

	return;
}
