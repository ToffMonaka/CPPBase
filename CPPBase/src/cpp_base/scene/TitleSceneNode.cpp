/**
 * @file
 * @brief TitleSceneNodeコードファイル
 */


#include "TitleSceneNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/input/MouseDeviceEvent.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/graphic/Model2D.h"
#include "../../lib/tml/sound/BGMSound.h"
#include "../../lib/tml/sound/SESound.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::TitleSceneNodeDesc::TitleSceneNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::TitleSceneNodeDesc::~TitleSceneNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::TitleSceneNodeDesc::Init(void)
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
INT cpp_base::scene::TitleSceneNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseNodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// TitleSceneNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"TITLE_SCENE_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::TitleSceneNode::TitleSceneNode() :
	progress_type_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::TitleSceneNode::~TitleSceneNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::TitleSceneNode::Release(void)
{
	cpp_base::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::TitleSceneNode::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;
	this->canvas_2d.reset();
	this->bg_model.reset();
	this->bgm_sound.reset();
	this->logo_model.reset();
	this->start_font.reset();
	this->start_model.reset();
	this->start_se_sound.reset();
	this->footer_font.reset();
	this->footer_model.reset();

	cpp_base::scene::BaseNode::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleSceneNode::Create(const cpp_base::scene::TitleSceneNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::BaseNode::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

	{// BackgroundModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.size = tml::XMFLOAT2EX(static_cast<FLOAT>(graphic_mgr->GetSize().x), static_cast<FLOAT>(graphic_mgr->GetSize().y));

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
			desc.file_read_desc_container[0].data.file_path = L"res/title_bg_img1.png";

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->bg_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);
		}
	}

	{// BGMSound Create
		if (sound_mgr->GetResource<tml::sound::BGMSound>(this->bgm_sound, sound_mgr->common2.title_bgm_sound1) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LogoModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.position.Set(tml::XMFLOAT2EX(0.0f, 32.0f));

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->logo_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->logo_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
			desc.file_read_desc_container[0].data.file_path = L"res/title_logo_img1.png";

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->logo_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->logo_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	tml::XMUINT2EX start_font_size = tml::XMUINT2EX(0U, 24U);
	tml::XMUINT2EX start_model_size = tml::XMUINT2EX(128U, 32U);

	{// StartFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(graphic_mgr);
		desc.SetFontDesc(start_font_size, L"ＭＳ ゴシック");

		if (graphic_mgr->GetResource<tml::graphic::Font>(this->start_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StartModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -192.0f));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(252U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->start_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->start_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, start_model_size);
			desc.cpu_buffer_flag = true;

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->start_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->start_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	{// StartModelTexture Update
		auto &tex = this->start_model->GetTexture(this->start_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(L"スタート", tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(0, 0), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::CENTER, this->start_font.get());
		tex->UploadCPUBuffer();
	}

	{// StartSESound Create
		if (sound_mgr->GetResource<tml::sound::SESound>(this->start_se_sound, sound_mgr->common2.start_se_sound1) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	tml::XMUINT2EX footer_font_size = tml::XMUINT2EX(0U, 16U);
	tml::XMUINT2EX footer_model_size = tml::XMUINT2EX(graphic_mgr->GetSize().x, 24U);

	{// FooterFont Create
		tml::graphic::FontDesc desc;

		desc.SetManager(graphic_mgr);
		desc.SetFontDesc(footer_font_size, L"ＭＳ ゴシック");

		if (graphic_mgr->GetResource<tml::graphic::Font>(this->footer_font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FooterModel Create
		tml::graphic::Model2DDesc desc;

		desc.SetManager(graphic_mgr);
		desc.position.Set(tml::XMFLOAT2EX(0.0f, -static_cast<FLOAT>(graphic_mgr->GetSize().GetHalfY()) + static_cast<FLOAT>(footer_model_size.y >> 1)));
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Model2D>(this->footer_model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->footer_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, footer_model_size);
			desc.cpu_buffer_flag = true;

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->footer_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->footer_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
		}
	}

	{// FooterModelTexture Update
		std::wstring company_name;

		company_name = cpp_base::ConstantUtil::APPLICATION::COMPANY_NAME;

		std::wstring version_name;

		version_name = L"Version ";
		version_name += cpp_base::ConstantUtil::APPLICATION::VERSION_NAME;

		auto &tex = this->footer_model->GetTexture(this->footer_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(company_name.c_str(), tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(4, -4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::BOTTOM_LEFT, this->footer_font.get());
		tex->DrawCPUBufferString(version_name.c_str(), tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(-4, -4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::BOTTOM_RIGHT, this->footer_font.get());
		tex->UploadCPUBuffer();
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::TitleSceneNode::OnStart(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

	this->progress_type_ = 1U;

	{// Canvas2D Create
		if (graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"canvas_2d") == nullptr) {
			return (-1);
		}
	}

	sound_mgr->PlaySound(this->bgm_sound.get(), true);

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::TitleSceneNode::OnEnd(void)
{
	auto sound_mgr = this->GetManager()->GetSoundManager();

	sound_mgr->StopSound(this->bgm_sound.get());

	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::TitleSceneNode::OnUpdate(void)
{
	auto input_mgr = this->GetManager()->GetInputManager();
	auto graphic_mgr = this->GetManager()->GetGraphicManager();
	auto sound_mgr = this->GetManager()->GetSoundManager();

	switch (this->progress_type_) {
	case 1U: {
		for (UINT event_i = 0U; event_i < input_mgr->GetEventCount(tml::input::DeviceEvent::EVENT_MAIN_INDEX); ++event_i) {
			auto event = reinterpret_cast<tml::input::DeviceEvent *>(input_mgr->GetEventFast(tml::input::DeviceEvent::EVENT_MAIN_INDEX, event_i));

			switch (event->GetEventSubIndex()) {
			case tml::input::MouseDeviceEvent::EVENT_SUB_INDEX: {
				auto &event_dat = reinterpret_cast<tml::input::MouseDeviceEvent *>(event)->data;

				if (static_cast<bool>(event_dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
					if (this->start_model->IsHitByMouseDevice(input_mgr->GetMouseDevicePosition())) {
						{// SelectScene Start
							tml::shared_ptr<tml::scene::Scene> scene;

							if (this->GetManager()->factory.scene_by_xml_file.Get(scene, tml::ConstantUtil::SCENE::CLASS_NAME::SCENE, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::SELECT_SCENE)) == nullptr) {
								this->GetManager()->EndScene();

								return;
							}

							if (this->GetManager()->StartScene(scene) < 0) {
								this->GetManager()->EndScene();

								return;
							}
						}

						sound_mgr->PlaySound(this->start_se_sound.get(), false);

						this->progress_type_ = 2U;
					}
				}

				break;
			}
			}
		}

		break;
	}
	case 2U: {
		break;
	}
	}

	if (this->start_model->IsHitByMouseDevice(input_mgr->GetMouseDevicePosition())) {
		this->start_model->scale = tml::XMFLOAT2EX(1.2f, 1.2f);
		this->start_model->color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), 1.0f);
	} else {
		this->start_model->scale = tml::XMFLOAT2EX(1.0f, 1.0f);
		this->start_model->color = tml::XMFLOAT4EX(1.0f, 1.0f, 1.0f, 1.0f);
	}

	this->canvas_2d->SetDrawModel(this->bg_model.get());
	this->canvas_2d->SetDrawModel(this->logo_model.get());
	this->canvas_2d->SetDrawModel(this->start_model.get());
	this->canvas_2d->SetDrawModel(this->footer_model.get());

	return;
}
