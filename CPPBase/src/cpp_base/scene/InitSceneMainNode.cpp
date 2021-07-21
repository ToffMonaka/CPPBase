/**
 * @file
 * @brief InitSceneMainNodeコードファイル
 */


#include "InitSceneMainNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Model2D.h"
#include "../../lib/tml/sound/BGMSound.h"
#include "../../lib/tml/sound/SESound.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::InitSceneMainNodeDesc::InitSceneMainNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitSceneMainNodeDesc::~InitSceneMainNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitSceneMainNodeDesc::Init(void)
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
INT cpp_base::scene::InitSceneMainNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseNodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// InitSceneMainNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"INIT_SCENE_MAIN_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::InitSceneMainNode::InitSceneMainNode() :
	progress_type_(0U),
	wait_update_time(0.0)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitSceneMainNode::~InitSceneMainNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::InitSceneMainNode::Release(void)
{
	cpp_base::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitSceneMainNode::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;
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
INT cpp_base::scene::InitSceneMainNode::Create(const cpp_base::scene::InitSceneMainNodeDesc &desc)
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
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitSceneMainNode::OnStart(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->progress_type_ = 1U;

	{// Canvas2D Create
		if (graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"Canvas2D") == nullptr) {
			return (-1);
		}
	}

	this->wait_update_time = tml::TIME_REAL(0.0);

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::InitSceneMainNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::InitSceneMainNode::OnUpdate(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

	switch (this->progress_type_) {
	case 1U: {
		{// TitleBGMSound Create
			tml::sound::BGMSoundDesc desc;

			desc.SetManager(sound_mgr);
			desc.file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::TITLE_BGM_SOUND;

			if (sound_mgr->GetResource<tml::sound::BGMSound>(sound_mgr->common2.title_bgm_sound, desc) == nullptr) {
				this->GetManager()->EndScene();

				return;
			}
		}

		this->wait_update_time += this->GetManager()->GetFrameRate().GetElapsedTime();

		this->progress_type_ = 2U;

		break;
	}
	case 2U: {
		{// SelectBGMSound Create
			tml::sound::BGMSoundDesc desc;

			desc.SetManager(sound_mgr);
			desc.file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::SELECT_BGM_SOUND;

			if (sound_mgr->GetResource<tml::sound::BGMSound>(sound_mgr->common2.select_bgm_sound, desc) == nullptr) {
				this->GetManager()->EndScene();

				return;
			}
		}

		this->wait_update_time += this->GetManager()->GetFrameRate().GetElapsedTime();

		this->progress_type_ = 3U;

		break;
	}
	case 3U: {
		{// StartSESound Create
			tml::sound::SESoundDesc desc;

			desc.SetManager(sound_mgr);
			desc.file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::START_SE_SOUND;

			if (sound_mgr->GetResource<tml::sound::SESound>(sound_mgr->common2.start_se_sound, desc) == nullptr) {
				this->GetManager()->EndScene();

				return;
			}
		}

		this->wait_update_time += this->GetManager()->GetFrameRate().GetElapsedTime();

		this->progress_type_ = 4U;

		break;
	}
	case 4U: {
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

			this->progress_type_ = 5U;
		}

		break;
	}
	case 5U: {
		break;
	}
	}

	this->canvas_2d->SetDrawModel(this->bg_model.get());
	this->canvas_2d->SetDrawModel(this->wait_model.get());

	return;
}
