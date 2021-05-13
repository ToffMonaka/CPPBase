/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Object2DModel.h"
#include "../../lib/tml/graphic/Font.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::ManagerCommon::ManagerCommon() :
	mgr_(nullptr),
	log_update_time(0.0)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	this->log_update_time = tml::TIME_REAL(0.0);
	this->log_model.reset();
	this->log_font.reset();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::ManagerCommon::Create(cpp_base::scene::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
		this->log_update_time = tml::TIME_REAL(1.0);

		tml::XMUINT2EX log_tex_size = graphic_mgr->GetSize();
		tml::XMUINT2EX log_font_size = tml::XMUINT2EX(0U, 16U);

		{// LogModel Create
			tml::graphic::Object2DModelDesc desc;

			desc.manager = graphic_mgr;
			desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

			graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->log_model, desc);

			if (this->log_model == nullptr) {
				this->Init();

				return (-1);
			}

			auto stage = this->log_model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
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

				this->log_model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

				this->log_model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
			}
		}

		{// LogFont Create
			tml::graphic::FontDesc desc;

			desc.manager = graphic_mgr;
			desc.SetFontDesc(log_font_size, L"ＭＳ ゴシック");

			graphic_mgr->GetResource<tml::graphic::Font>(this->log_font, desc);

			if (this->log_font == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	return (0);
}


/**
 * @brief UpdateLog関数
 * @param time (time)
 */
void cpp_base::scene::ManagerCommon::UpdateLog(const tml::TIME_REAL &time)
{
	this->log_update_time += time;

	if (this->log_update_time.count() < 1.0) {
		return;
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	{// LogTexture Update
		auto &frame_rate = this->GetManager()->GetFrameRate();
		auto mem_allocator_info = tml::MemoryUtil::GetAllocatorInfo();

		WCHAR log_str[1024];

		_snwprintf_s(log_str, sizeof(log_str) >> 1, _TRUNCATE, L"FPS=%.2f/%u\nMEM=%u/%u/%u", frame_rate.GetFPS(), frame_rate.GetLimit(), mem_allocator_info.use_size, mem_allocator_info.size, mem_allocator_info.use_count);

		auto tex = this->log_model->GetTexture(this->log_model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

		tex->ClearCPUBuffer();
		tex->DrawCPUBufferString(log_str, tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(4, 4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::TOP_LEFT, this->log_font.get());
		tex->UploadCPUBuffer();
	}

	this->log_update_time = tml::TIME_REAL(0.0);

	return;
}
