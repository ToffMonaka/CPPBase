/**
 * @file
 * @brief DebugNodeコードファイル
 */


#include "DebugNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/FigureModel2D.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::DebugNodeDesc::DebugNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::DebugNodeDesc::~DebugNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::DebugNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::DebugNodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// DebugNode Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"DEBUG_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::DebugNode::DebugNode() :
	desc_(nullptr),
	update_time_(0.0),
	cpu_elapsed_time_(0.0),
	cpu_elapsed_cnt_(0U),
	gpu_elapsed_time_(0.0),
	gpu_elapsed_cnt_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::DebugNode::~DebugNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::DebugNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::DebugNode::Init(void)
{
	this->Release();

	this->update_time_ = tml::TIME_REAL(0.0);
	this->cpu_elapsed_time_ = tml::TIME_REAL(0.0);
	this->cpu_elapsed_cnt_ = 0U;
	this->gpu_elapsed_time_ = tml::TIME_REAL(0.0);
	this->gpu_elapsed_cnt_ = 0U;

	this->font.reset();
	this->model.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::DebugNode::OnCreate(void)
{
	if (cpp_base::scene::Node::OnCreate() < 0) {
		return (-1);
	}

	tml::XMUINT2EX font_size = tml::XMUINT2EX(0U, 16U);
	tml::XMUINT2EX model_size = this->GetGraphicManager()->GetSize();

	{// Font Create
		tml::graphic::FontDesc font_desc;

		font_desc.SetManager(this->GetGraphicManager());
		font_desc.SetFontDesc(font_size, L"ＭＳ ゴシック");

		if (this->GetGraphicManager()->GetResource<tml::graphic::Font>(this->font, font_desc) == nullptr) {
			return (-1);
		}
	}

	{// Model Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.transform.position = tml::XMFLOAT2EX(0.0f, 0.0f);
		model_desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->model, model_desc) == nullptr) {
			return (-1);
		}

		auto stage = this->model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayer(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;
			tml::graphic::TextureDesc tex_desc;

			tex_desc.SetManager(this->GetGraphicManager());
			tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, model_size);
			tex_desc.cpu_buffer_flag = true;

			if (this->GetGraphicManager()->GetResource<tml::graphic::Texture>(tex, tex_desc) == nullptr) {
				return (-1);
			}

			this->model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetRect().GetSize().x), static_cast<FLOAT>(tex->GetRect().GetSize().y));
		}
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::DebugNode::OnCreateDeferred(void)
{
	if (cpp_base::scene::Node::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::DebugNode::OnStart(void)
{
	this->update_time_ = tml::TIME_REAL(1.0);
	this->cpu_elapsed_time_ = tml::TIME_REAL(0.0);
	this->cpu_elapsed_cnt_ = 0U;
	this->gpu_elapsed_time_ = tml::TIME_REAL(0.0);
	this->gpu_elapsed_cnt_ = 0U;

	this->SetModel(0U, this->model);

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::DebugNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::DebugNode::OnUpdate(void)
{
	this->update_time_ += this->GetManager()->GetFrameRate().GetElapsedTime();
	this->cpu_elapsed_time_ += this->GetManager()->GetCPUElapsedTime();
	++this->cpu_elapsed_cnt_;
	this->gpu_elapsed_time_ += this->GetManager()->GetGPUElapsedTime();
	++this->gpu_elapsed_cnt_;

	if (this->update_time_.count() >= 1.0) {
		{// ModelTexture Update
			auto &frame_rate = this->GetManager()->GetFrameRate();
			auto cpu_elapsed_time = this->cpu_elapsed_time_ / this->cpu_elapsed_cnt_;
			auto gpu_elapsed_time = this->gpu_elapsed_time_ / this->gpu_elapsed_cnt_;
			auto mem_allocator_info = tml::MemoryUtil::GetAllocatorInfo();

			WCHAR sys_str[1024];

			_snwprintf_s(sys_str, sizeof(sys_str) >> 1, _TRUNCATE, L"F=%.2f/%u\nT=%f/%f\nM=%u/%u/%u",
				frame_rate.GetFPS(), frame_rate.GetLimit(),
				cpu_elapsed_time.count(), gpu_elapsed_time.count(),
				mem_allocator_info.use_size, mem_allocator_info.size, mem_allocator_info.use_count
			);

			auto &tex = this->model->GetTexture(this->model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

			tex->ClearCPUBuffer();
			tex->DrawCPUBufferString(sys_str, tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(4, 4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::TOP_LEFT, this->font.get());
			tex->UploadCPUBuffer();
		}

		this->update_time_ = tml::TIME_REAL(0.0);
		this->cpu_elapsed_time_ = tml::TIME_REAL(0.0);
		this->cpu_elapsed_cnt_ = 0U;
		this->gpu_elapsed_time_ = tml::TIME_REAL(0.0);
		this->gpu_elapsed_cnt_ = 0U;
	}

	return;
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void cpp_base::scene::DebugNode::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const cpp_base::scene::DebugNodeDesc *>(desc);

	cpp_base::scene::Node::OnSetDesc(this->desc_);

	return;
}
