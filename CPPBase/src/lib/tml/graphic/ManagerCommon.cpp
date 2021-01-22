/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerCommon::ManagerCommon()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerCommon::~ManagerCommon()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::ManagerCommon::Init(void)
{
	this->default_rasterizer_state.reset();
	this->wireframe_rasterizer_state.reset();
	this->front_culling_rasterizer_state.reset();
	this->back_culling_rasterizer_state.reset();

	for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
		this->default_blend_state_array[rt_i].reset();
		this->alignment_blend_state_array[rt_i].reset();
		this->add_blend_state_array[rt_i].reset();
		this->sub_blend_state_array[rt_i].reset();
		this->mul_blend_state_array[rt_i].reset();
		this->reverse_blend_state_array[rt_i].reset();
		this->total_blend_state_array[rt_i].reset();
	}

	this->default_depth_state.reset();
	this->reference_depth_state.reset();
	this->main_render_target_texture.reset();
	this->main_depth_target_texture.reset();
	this->model_cc_sampler.reset();
	this->model_cw_sampler.reset();
	this->model_wc_sampler.reset();
	this->model_ww_sampler.reset();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ManagerCommon::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	{// DefaultRasterizerState Create
		tml::graphic::RasterizerStateDesc desc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::DEFAULT);

		this->default_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->default_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WireframeRasterizerState Create
		tml::graphic::RasterizerStateDesc desc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::WIREFRAME);

		this->wireframe_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->wireframe_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FrontCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::FRONT_CULLING);

		this->front_culling_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->front_culling_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::BACK_CULLING);

		this->back_culling_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->back_culling_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
		{// DefaultBlendState Create
			tml::graphic::BlendStateDesc desc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::DEFAULT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::NONE, rt_i);

			this->default_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->default_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AlignmentBlendState Create
			tml::graphic::BlendStateDesc desc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ALIGNMENT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->alignment_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->alignment_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AddBlendState Create
			tml::graphic::BlendStateDesc desc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ADD, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->add_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->add_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// SubBlendState Create
			tml::graphic::BlendStateDesc desc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::SUB, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->sub_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->sub_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// MulBlendState Create
			tml::graphic::BlendStateDesc desc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::MUL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->mul_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->mul_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// ReverseBlendState Create
			tml::graphic::BlendStateDesc desc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::REVERSE, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->reverse_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->reverse_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// TotalBlendState Create
			tml::graphic::BlendStateDesc desc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::TOTAL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::TOTAL, rt_i);

			this->total_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->total_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	{// DefaultDepthState Create
		tml::graphic::DepthStateDesc desc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::DEFAULT);

		this->default_depth_state = mgr->GetResource<tml::graphic::DepthState>(desc);

		if (this->default_depth_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ReferenceDepthState Create
		tml::graphic::DepthStateDesc desc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::REFERENCE);

		this->reference_depth_state = mgr->GetResource<tml::graphic::DepthState>(desc);

		if (this->reference_depth_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE samp_desc_type = tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::NONE;

	switch (mgr->GetSamplerQualityType()) {
	case tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::BILINEAR: {
		samp_desc_type = tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::BILINEAR;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::TRILINEAR: {
		samp_desc_type = tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::TRILINEAR;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::ANISOTROPIC2: {
		samp_desc_type = tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC2;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::ANISOTROPIC4: {
		samp_desc_type = tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC4;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::ANISOTROPIC8: {
		samp_desc_type = tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC8;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::ANISOTROPIC16: {
		samp_desc_type = tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_TYPE::ANISOTROPIC16;

		break;
	}
	}

	{// MainRenderTargetTexture Create
		tml::graphic::TextureDesc desc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::RENDER_TARGET | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::SR | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::UASR);

		desc.swap_chain = mgr->GetSwapChain();
		desc.render_target_desc_null_flag = true;
		desc.sr_desc_null_flag = true;
		desc.uasr_desc_null_flag = true;

		this->main_render_target_texture = mgr->GetResource<tml::graphic::Texture>(desc);

		if (this->main_render_target_texture == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// MainDepthTargetTexture Create
		tml::graphic::TextureDesc desc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::DEPTH_TARGET, DXGI_FORMAT_R24G8_TYPELESS, tml::XMUINT2EX(mgr->GetSwapChainDesc().BufferDesc.Width, mgr->GetSwapChainDesc().BufferDesc.Height), 1U, 1U, mgr->GetSwapChainDesc().SampleDesc);

		desc.depth_target_format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		this->main_depth_target_texture = mgr->GetResource<tml::graphic::Texture>(desc);

		if (this->main_depth_target_texture == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ScreenModelShader Create
		tml::graphic::ShaderDesc desc;
		auto read_desc = tml::INIFileReadDesc(L"res/screen_model_shader.ini");

		desc.Read(read_desc);
		desc.vertex_shader_input_element_desc_count = tml::ConstantUtil::GRAPHIC::SCREEN_MODEL_INPUT_ELEMENT_DESC_COUNT;
		desc.vertex_shader_input_element_desc_array = tml::ConstantUtil::GRAPHIC::SCREEN_MODEL_INPUT_ELEMENT_DESC_ARRAY;

		this->screen_model_shader = mgr->GetResource<tml::graphic::Shader>(desc);

		if (this->screen_model_shader == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// SpriteModelShader Create
		tml::graphic::ShaderDesc desc;
		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model_shader.ini");

		desc.Read(read_desc);
		desc.vertex_shader_input_element_desc_count = tml::ConstantUtil::GRAPHIC::SPRITE_MODEL_INPUT_ELEMENT_DESC_COUNT;
		desc.vertex_shader_input_element_desc_array = tml::ConstantUtil::GRAPHIC::SPRITE_MODEL_INPUT_ELEMENT_DESC_ARRAY;

		this->sprite_model_shader = mgr->GetResource<tml::graphic::Shader>(desc);

		if (this->sprite_model_shader == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ModelCCSampler Create
		tml::graphic::SamplerDesc desc(samp_desc_type, tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CC);

		this->model_cc_sampler = mgr->GetResource<tml::graphic::Sampler>(desc);

		if (this->model_cc_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ModelCWSampler Create
		tml::graphic::SamplerDesc desc(samp_desc_type, tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CW);

		this->model_cw_sampler = mgr->GetResource<tml::graphic::Sampler>(desc);

		if (this->model_cw_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ModelWCSampler Create
		tml::graphic::SamplerDesc desc(samp_desc_type, tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WC);

		this->model_wc_sampler = mgr->GetResource<tml::graphic::Sampler>(desc);

		if (this->model_wc_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ModelWWSampler Create
		tml::graphic::SamplerDesc desc(samp_desc_type, tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WW);

		this->model_ww_sampler = mgr->GetResource<tml::graphic::Sampler>(desc);

		if (this->model_ww_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
