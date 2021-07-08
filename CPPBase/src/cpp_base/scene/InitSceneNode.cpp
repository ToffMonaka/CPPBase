/**
 * @file
 * @brief InitSceneNodeコードファイル
 */


#include "InitSceneNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Model2D.h"
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
	wait_update_time(0.0)
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

	this->canvas_2d.reset();
	this->bg_model.reset();
	this->wait_update_time = tml::TIME_REAL(0.0);
	this->wait_font.reset();
	this->wait_model.reset();

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

	{// BackgroundModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->bg_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->bg_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
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

			this->bg_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	tml::XMUINT2EX wait_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX wait_model_size = tml::XMUINT2EX(320U, 32U);

	{// WaitFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(graphic_mgr);
		desc.SetFontDesc(wait_font_size, L"ＭＳ ゴシック");

		if (graphic_mgr->GetResource<tml::graphic::Font>(this->wait_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WaitModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->wait_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->wait_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, wait_model_size);
			desc.cpu_buffer_flag = true;

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->wait_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->wait_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
		}
	}

	{// WaitModelTexture Update
		auto tex = this->wait_model->GetTexture(this->wait_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"ちょっと待ってね。", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->wait_font.get());
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
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	if (this->canvas_2d == nullptr) {
		graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"canvas_2d");
	}

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

	this->wait_update_time += this->GetManager()->GetFrameRate().GetElapsedTime();

	if (this->wait_update_time.count() >= 3.0) {
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

	if (this->canvas_2d != nullptr) {
		this->canvas_2d->SetDrawModel(this->bg_model.get());
		this->canvas_2d->SetDrawModel(this->wait_model.get());
	}

	return;
}
