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
#include "ConfigShaderConstantBuffer.h"
#include "HeaderShaderConstantBuffer.h"
#include "CameraShaderStructuredBuffer.h"
#include "LightShaderStructuredBuffer.h"
#include "FogShaderStructuredBuffer.h"
#include "SpriteModelShaderStructuredBuffer.h"
#include "SpriteModelLayerShaderStructuredBuffer.h"
#include "Camera.h"
#include "Light.h"
#include "Fog.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Sampler.h"
#include "ScreenModel.h"
#include "SpriteModel.h"
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
 * @brief Release関数
 */
void tml::graphic::ManagerCommon::Release(void)
{
	if (this->mgr_ != nullptr) {
		this->mgr_->ReleaseResource(this->default_rasterizer_state);
		this->mgr_->ReleaseResource(this->wireframe_rasterizer_state);
		this->mgr_->ReleaseResource(this->front_culling_rasterizer_state);
		this->mgr_->ReleaseResource(this->back_culling_rasterizer_state);

		for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
			this->mgr_->ReleaseResource(this->default_blend_state_array[rt_i]);
			this->mgr_->ReleaseResource(this->alignment_blend_state_array[rt_i]);
			this->mgr_->ReleaseResource(this->add_blend_state_array[rt_i]);
			this->mgr_->ReleaseResource(this->sub_blend_state_array[rt_i]);
			this->mgr_->ReleaseResource(this->mul_blend_state_array[rt_i]);
			this->mgr_->ReleaseResource(this->reverse_blend_state_array[rt_i]);
			this->mgr_->ReleaseResource(this->total_blend_state_array[rt_i]);
		}

		this->mgr_->ReleaseResource(this->default_depth_state);
		this->mgr_->ReleaseResource(this->reference_depth_state);
		this->mgr_->ReleaseResource(this->screen_model_shader);
		this->mgr_->ReleaseResource(this->sprite_model_shader);
		this->mgr_->ReleaseResource(this->config_shader_constant_buffer);
		this->mgr_->ReleaseResource(this->camera_shader_structured_buffer);
		this->mgr_->ReleaseResource(this->light_shader_structured_buffer);
		this->mgr_->ReleaseResource(this->fog_shader_structured_buffer);
		this->mgr_->ReleaseResource(this->main_render_target_texture);
		this->mgr_->ReleaseResource(this->main_depth_target_texture);
		this->mgr_->ReleaseResource(this->cc_sampler);
		this->mgr_->ReleaseResource(this->cw_sampler);
		this->mgr_->ReleaseResource(this->wc_sampler);
		this->mgr_->ReleaseResource(this->ww_sampler);
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

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

		desc.manager = this->mgr_;
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::DEFAULT);

		this->mgr_->GetResource<tml::graphic::RasterizerState>(this->default_rasterizer_state, desc);

		if (this->default_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WireframeRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.manager = this->mgr_;
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::WIREFRAME);

		this->mgr_->GetResource<tml::graphic::RasterizerState>(this->wireframe_rasterizer_state, desc);

		if (this->wireframe_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FrontCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.manager = this->mgr_;
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::FRONT_CULLING);

		this->mgr_->GetResource<tml::graphic::RasterizerState>(this->front_culling_rasterizer_state, desc);

		if (this->front_culling_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.manager = this->mgr_;
		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::BACK_CULLING);

		this->mgr_->GetResource<tml::graphic::RasterizerState>(this->back_culling_rasterizer_state, desc);

		if (this->back_culling_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
		{// DefaultBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.manager = this->mgr_;
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::DEFAULT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::NONE, rt_i);

			this->mgr_->GetResource<tml::graphic::BlendState>(this->default_blend_state_array[rt_i], desc);

			if (this->default_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AlignmentBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.manager = this->mgr_;
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ALIGNMENT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->mgr_->GetResource<tml::graphic::BlendState>(this->alignment_blend_state_array[rt_i], desc);

			if (this->alignment_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AddBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.manager = this->mgr_;
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ADD, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->mgr_->GetResource<tml::graphic::BlendState>(this->add_blend_state_array[rt_i], desc);

			if (this->add_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// SubBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.manager = this->mgr_;
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::SUB, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->mgr_->GetResource<tml::graphic::BlendState>(this->sub_blend_state_array[rt_i], desc);

			if (this->sub_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// MulBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.manager = this->mgr_;
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::MUL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->mgr_->GetResource<tml::graphic::BlendState>(this->mul_blend_state_array[rt_i], desc);

			if (this->mul_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// ReverseBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.manager = this->mgr_;
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::REVERSE, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->mgr_->GetResource<tml::graphic::BlendState>(this->reverse_blend_state_array[rt_i], desc);

			if (this->reverse_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// TotalBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.manager = this->mgr_;
			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::TOTAL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::TOTAL, rt_i);

			this->mgr_->GetResource<tml::graphic::BlendState>(this->total_blend_state_array[rt_i], desc);

			if (this->total_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	{// DefaultDepthState Create
		tml::graphic::DepthStateDesc desc;

		desc.manager = this->mgr_;
		desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::DEFAULT);

		this->mgr_->GetResource<tml::graphic::DepthState>(this->default_depth_state, desc);

		if (this->default_depth_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ReferenceDepthState Create
		tml::graphic::DepthStateDesc desc;

		desc.manager = this->mgr_;
		desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::REFERENCE);

		this->mgr_->GetResource<tml::graphic::DepthState>(this->reference_depth_state, desc);

		if (this->reference_depth_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// MainRenderTargetTexture Create
		tml::graphic::TextureDesc desc;

		desc.manager = this->mgr_;
		desc.swap_chain = this->mgr_->GetSwapChain();
		desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::RENDER_TARGET | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::UASR);
		desc.render_target_desc_null_flag = true;
		desc.sr_desc_null_flag = true;
		desc.uasr_desc_null_flag = true;

		this->mgr_->GetResource<tml::graphic::Texture>(this->main_render_target_texture, desc);

		if (this->main_render_target_texture == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// MainDepthTargetTexture Create
		tml::graphic::TextureDesc desc;

		desc.manager = this->mgr_;
		desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::DEPTH_TARGET, DXGI_FORMAT_R24G8_TYPELESS, this->mgr_->GetSize());
		desc.depth_target_format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		this->mgr_->GetResource<tml::graphic::Texture>(this->main_depth_target_texture, desc);

		if (this->main_depth_target_texture == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ScreenModelShader Create
		tml::graphic::ShaderDesc desc;

		desc.manager = this->mgr_;
		desc.vertex_shader_input_element_desc_count = tml::ConstantUtil::GRAPHIC::SCREEN_MODEL_INPUT_ELEMENT_DESC_COUNT;
		desc.vertex_shader_input_element_desc_array = tml::ConstantUtil::GRAPHIC::SCREEN_MODEL_INPUT_ELEMENT_DESC_ARRAY;

		auto read_desc = tml::INIFileReadDesc(L"res/screen_model_shader.ini");

		desc.Read(read_desc);

		this->mgr_->GetResource<tml::graphic::Shader>(this->screen_model_shader, desc);

		if (this->screen_model_shader == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// SpriteModelShader Create
		tml::graphic::ShaderDesc desc;

		desc.manager = this->mgr_;
		desc.vertex_shader_input_element_desc_count = tml::ConstantUtil::GRAPHIC::SPRITE_MODEL_INPUT_ELEMENT_DESC_COUNT;
		desc.vertex_shader_input_element_desc_array = tml::ConstantUtil::GRAPHIC::SPRITE_MODEL_INPUT_ELEMENT_DESC_ARRAY;

		auto read_desc = tml::INIFileReadDesc(L"res/sprite_model_shader.ini");

		desc.Read(read_desc);

		this->mgr_->GetResource<tml::graphic::Shader>(this->sprite_model_shader, desc);

		if (this->sprite_model_shader == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ConfigShaderConstantBuffer Create
		tml::graphic::ConfigShaderConstantBufferDesc desc;

		desc.manager = this->mgr_;
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::ConfigShaderConstantBuffer::ELEMENT));

		this->mgr_->GetResource<tml::graphic::ConfigShaderConstantBuffer>(this->config_shader_constant_buffer, desc);

		if (this->config_shader_constant_buffer == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// HeaderShaderConstantBuffer Create
		tml::graphic::HeaderShaderConstantBufferDesc desc;

		desc.manager = this->mgr_;
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::HeaderShaderConstantBuffer::ELEMENT));

		this->mgr_->GetResource<tml::graphic::HeaderShaderConstantBuffer>(this->header_shader_constant_buffer, desc);

		if (this->header_shader_constant_buffer == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CameraShaderStructuredBuffer Create
		tml::graphic::CameraShaderStructuredBufferDesc desc;

		desc.manager = this->mgr_;
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::CameraShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::CAMERA_LIMIT);

		this->mgr_->GetResource<tml::graphic::CameraShaderStructuredBuffer>(this->camera_shader_structured_buffer, desc);

		if (this->camera_shader_structured_buffer == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LightShaderStructuredBuffer Create
		tml::graphic::LightShaderStructuredBufferDesc desc;

		desc.manager = this->mgr_;
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::LightShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT);

		this->mgr_->GetResource<tml::graphic::LightShaderStructuredBuffer>(this->light_shader_structured_buffer, desc);

		if (this->light_shader_structured_buffer == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FogShaderStructuredBuffer Create
		tml::graphic::FogShaderStructuredBufferDesc desc;

		desc.manager = this->mgr_;
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::FogShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::FOG_LIMIT);

		this->mgr_->GetResource<tml::graphic::FogShaderStructuredBuffer>(this->fog_shader_structured_buffer, desc);

		if (this->fog_shader_structured_buffer == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CCSampler Create
		tml::graphic::SamplerDesc desc;

		desc.manager = this->mgr_;
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CC);

		this->mgr_->GetResource<tml::graphic::Sampler>(this->cc_sampler, desc);

		if (this->cc_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CWSampler Create
		tml::graphic::SamplerDesc desc;

		desc.manager = this->mgr_;
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CW);

		this->mgr_->GetResource<tml::graphic::Sampler>(this->cw_sampler, desc);

		if (this->cw_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WCSampler Create
		tml::graphic::SamplerDesc desc;

		desc.manager = this->mgr_;
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WC);

		this->mgr_->GetResource<tml::graphic::Sampler>(this->wc_sampler, desc);

		if (this->wc_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WWSampler Create
		tml::graphic::SamplerDesc desc;

		desc.manager = this->mgr_;
		desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WW);

		this->mgr_->GetResource<tml::graphic::Sampler>(this->ww_sampler, desc);

		if (this->ww_sampler == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
