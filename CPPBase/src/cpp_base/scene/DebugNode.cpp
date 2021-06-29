/**
 * @file
 * @brief DebugNode�R�[�h�t�@�C��
 */


#include "DebugNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Object2DModel.h"
#include "../../lib/tml/graphic/Font.h"
#include "../graphic/Manager.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::DebugNodeDesc::DebugNodeDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::DebugNodeDesc::~DebugNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::DebugNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::BaseNodeDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::DebugNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::BaseNodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// DebugNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"DEBUG_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::DebugNode::DebugNode() :
	update_time(0.0)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::DebugNode::~DebugNode()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::DebugNode::Release(void)
{
	cpp_base::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::DebugNode::Init(void)
{
	this->Release();

	this->update_time = tml::TIME_REAL(0.0);
	this->model.reset();
	this->font.reset();

	cpp_base::scene::BaseNode::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::DebugNode::Create(const cpp_base::scene::DebugNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::BaseNode::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->update_time = tml::TIME_REAL(1.0);

	tml::XMUINT2EX model_size = graphic_mgr->GetSize();
	tml::XMUINT2EX font_size = tml::XMUINT2EX(0U, 16U);

	{// Model Create
		tml::graphic::Object2DModelDesc desc;

		desc.SetManager(graphic_mgr);
		desc.color = tml::XMFLOAT4EX(tml::MathUtil::GetColor1(252U), tml::MathUtil::GetColor1(8U), tml::MathUtil::GetColor1(8U), 1.0f);

		if (graphic_mgr->GetResource<tml::graphic::Object2DModel>(this->model, desc) == nullptr) {
			this->Init();

			return (-1);
		}

		auto stage = this->model->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
		auto layer = stage->GetLayerFast(0U);

		layer->SetDiffuseTextureIndex(0U);

		{// DiffuseTexture Create
			tml::shared_ptr<tml::graphic::Texture> tex;

			tml::graphic::TextureDesc desc;

			desc.SetManager(graphic_mgr);
			desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR, DXGI_FORMAT_R8G8B8A8_UNORM, model_size);
			desc.cpu_buffer_flag = true;

			if (graphic_mgr->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
				this->Init();

				return (-1);
			}

			this->model->SetTexture(layer->GetDiffuseTextureIndex(), tex);

			this->model->size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSize(0U)->x), static_cast<FLOAT>(tex->GetSize(0U)->y));
		}
	}

	{// Font Create
		tml::graphic::FontDesc desc;

		desc.SetManager(graphic_mgr);
		desc.SetFontDesc(font_size, L"�l�r �S�V�b�N");

		if (graphic_mgr->GetResource<tml::graphic::Font>(this->font, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::DebugNode::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::scene::DebugNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::DebugNode::OnUpdate(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->update_time += this->GetManager()->GetFrameRate().GetElapsedTime();

	if (this->update_time.count() >= 1.0) {
		{// ModelTexture Update
			auto &frame_rate = this->GetManager()->GetFrameRate();
			auto mem_allocator_info = tml::MemoryUtil::GetAllocatorInfo();

			WCHAR sys_str[1024];

			_snwprintf_s(sys_str, sizeof(sys_str) >> 1, _TRUNCATE, L"FPS=%.2f/%u\nMEM=%u/%u/%u", frame_rate.GetFPS(), frame_rate.GetLimit(), mem_allocator_info.use_size, mem_allocator_info.size, mem_allocator_info.use_count);

			auto tex = this->model->GetTexture(this->model->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D)->GetLayer(0U)->GetDiffuseTextureIndex());

			tex->ClearCPUBuffer();
			tex->DrawCPUBufferString(sys_str, tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE::LEFT, tml::XMINT2EX(4, 4), tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE::TOP_LEFT, this->font.get());
			tex->UploadCPUBuffer();
		}

		this->update_time = tml::TIME_REAL(0.0);
	}

	graphic_mgr->SetDrawModel(this->model.get());

	return;
}
