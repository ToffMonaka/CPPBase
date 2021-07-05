/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "Manager.h"
#include "Canvas.h"
#include "Canvas2D.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "ShaderConstantBuffer.h"
#include "ConfigShaderConstantBuffer.h"
#include "HeaderShaderConstantBuffer.h"
#include "ShaderStructuredBuffer.h"
#include "CameraShaderStructuredBuffer.h"
#include "LightShaderStructuredBuffer.h"
#include "FogShaderStructuredBuffer.h"
#include "Model2DShaderStructuredBuffer.h"
#include "Model2DLayerShaderStructuredBuffer.h"
#include "Camera.h"
#include "Light.h"
#include "Fog.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"
#include "Model.h"
#include "Model2D.h"
#include "Font.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

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
	this->model_2d_shader.reset();
	this->config_shader_constant_buffer.reset();
	this->header_shader_constant_buffer.reset();
	this->camera_shader_structured_buffer.reset();
	this->light_shader_structured_buffer.reset();
	this->fog_shader_structured_buffer.reset();
	this->main_render_target_texture.reset();
	this->main_depth_target_texture.reset();
	this->cc_sampler.reset();
	this->cw_sampler.reset();
	this->wc_sampler.reset();
	this->ww_sampler.reset();

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
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	{// DefaultRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::DEFAULT);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->default_rasterizer_state, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WireframeRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::WIREFRAME);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->wireframe_rasterizer_state, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FrontCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::FRONT_CULLING);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->front_culling_rasterizer_state, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::BACK_CULLING);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->back_culling_rasterizer_state, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
		{// DefaultBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetManager(this->mgr_);
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::DEFAULT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::NONE, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->default_blend_state_array[rt_i], desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AlignmentBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetManager(this->mgr_);
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ALIGNMENT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->alignment_blend_state_array[rt_i], desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AddBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetManager(this->mgr_);
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ADD, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->add_blend_state_array[rt_i], desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// SubBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetManager(this->mgr_);
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::SUB, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->sub_blend_state_array[rt_i], desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// MulBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetManager(this->mgr_);
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::MUL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->mul_blend_state_array[rt_i], desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// ReverseBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetManager(this->mgr_);
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::REVERSE, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->reverse_blend_state_array[rt_i], desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// TotalBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetManager(this->mgr_);
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::TOTAL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::TOTAL, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->total_blend_state_array[rt_i], desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	{// DefaultDepthState Create
		tml::graphic::DepthStateDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::DEFAULT);

		if (this->mgr_->GetResource<tml::graphic::DepthState>(this->default_depth_state, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ReferenceDepthState Create
		tml::graphic::DepthStateDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::REFERENCE);

		if (this->mgr_->GetResource<tml::graphic::DepthState>(this->reference_depth_state, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// MainRenderTargetTexture Create
		tml::graphic::TextureDesc desc;

		desc.SetManager(this->mgr_);
		desc.swap_chain = this->mgr_->GetSwapChain();
		desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::RENDER_TARGET | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::UASR);
		desc.render_target_desc_null_flag = true;
		desc.sr_desc_null_flag = true;
		desc.uasr_desc_null_flag = true;

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->main_render_target_texture, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// MainDepthTargetTexture Create
		tml::graphic::TextureDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::DEPTH_TARGET, DXGI_FORMAT_R24G8_TYPELESS, this->mgr_->GetSize());
		desc.depth_target_format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->main_depth_target_texture, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Model2DShader Create
		tml::graphic::ShaderDesc desc;

		desc.SetManager(this->mgr_);
		desc.Read(tml::INIFileReadDesc(L"res/model_2d_shader.ini"));
		desc.vertex_shader_input_element_desc_count = tml::ConstantUtil::GRAPHIC::MODEL_2D_INPUT_ELEMENT_DESC_COUNT;
		desc.vertex_shader_input_element_desc_array = tml::ConstantUtil::GRAPHIC::MODEL_2D_INPUT_ELEMENT_DESC_ARRAY;

		if (this->mgr_->GetResource<tml::graphic::Shader>(this->model_2d_shader, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ConfigShaderConstantBuffer Create
		tml::graphic::ConfigShaderConstantBufferDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::ConfigShaderConstantBuffer::ELEMENT));

		if (this->mgr_->GetResource<tml::graphic::ConfigShaderConstantBuffer>(this->config_shader_constant_buffer, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// HeaderShaderConstantBuffer Create
		tml::graphic::HeaderShaderConstantBufferDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::HeaderShaderConstantBuffer::ELEMENT));

		if (this->mgr_->GetResource<tml::graphic::HeaderShaderConstantBuffer>(this->header_shader_constant_buffer, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CameraShaderStructuredBuffer Create
		tml::graphic::CameraShaderStructuredBufferDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::CameraShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::CAMERA_LIMIT);

		if (this->mgr_->GetResource<tml::graphic::CameraShaderStructuredBuffer>(this->camera_shader_structured_buffer, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LightShaderStructuredBuffer Create
		tml::graphic::LightShaderStructuredBufferDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::LightShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT);

		if (this->mgr_->GetResource<tml::graphic::LightShaderStructuredBuffer>(this->light_shader_structured_buffer, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FogShaderStructuredBuffer Create
		tml::graphic::FogShaderStructuredBufferDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::FogShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::FOG_LIMIT);

		if (this->mgr_->GetResource<tml::graphic::FogShaderStructuredBuffer>(this->fog_shader_structured_buffer, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CCSampler Create
		tml::graphic::SamplerDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CC);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->cc_sampler, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CWSampler Create
		tml::graphic::SamplerDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CW);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->cw_sampler, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WCSampler Create
		tml::graphic::SamplerDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WC);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->wc_sampler, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WWSampler Create
		tml::graphic::SamplerDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WW);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->ww_sampler, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
