/**
 * @file
 * @brief StageSceneMainNodeコードファイル
 */


#include "StageSceneMainNode.h"
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
cpp_base::scene::StageSceneMainNodeDesc::StageSceneMainNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::StageSceneMainNodeDesc::~StageSceneMainNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::StageSceneMainNodeDesc::Init(void)
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
INT cpp_base::scene::StageSceneMainNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseNodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// StageSceneMainNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"STAGE_SCENE_MAIN_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::StageSceneMainNode::StageSceneMainNode() :
	progress_type_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::StageSceneMainNode::~StageSceneMainNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::StageSceneMainNode::Release(void)
{
	cpp_base::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::StageSceneMainNode::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;
	this->canvas_2d.reset();
	this->bg_model.reset();
	this->name_font.reset();
	this->name_model.reset();

	cpp_base::scene::BaseNode::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageSceneMainNode::Create(const cpp_base::scene::StageSceneMainNodeDesc &desc)
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

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, graphic_mgr->common2.bg_tex) == nullptr) {
				this->Init();

				return (-1);
			}

			this->bg_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}
	tml::XMUINT2EX name_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX name_model_size = tml::XMUINT2EX(128U, 92U);

	{// StartFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(graphic_mgr);
		desc.SetFontDesc(name_font_size, L"ＭＳ ゴシック");

		if (graphic_mgr->GetResource<tml::graphic::Font>(this->name_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StartModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.position.Set(tml::XMFLOAT2EX(0.0f, 0.0f));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->name_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->name_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, name_model_size);
			desc.cpu_buffer_flag = true;

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->name_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->name_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	{// StartModelTexture Update
		auto &tex = this->name_model->GetTexture(this->name_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"ステージ\n\nテスト2D", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->name_font.get());
		tex->UploadCPUBuffer();
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageSceneMainNode::OnStart(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->progress_type_ = 1U;

	{// Canvas2D Create
		if (graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"Canvas2D") == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::StageSceneMainNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::StageSceneMainNode::OnUpdate(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	switch (this->progress_type_) {
	case 1U: {
		break;
	}
	}

	this->canvas_2d->SetDrawModel(this->bg_model.get());
	this->canvas_2d->SetDrawModel(this->name_model.get());

	return;
}
