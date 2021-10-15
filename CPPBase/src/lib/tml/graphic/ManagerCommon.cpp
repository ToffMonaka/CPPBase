/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "Manager.h"
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
#include "FigureModel2DShaderStructuredBuffer.h"
#include "FigureModel2DLayerShaderStructuredBuffer.h"
#include "GroundModel2DShaderStructuredBuffer.h"
#include "GroundModel2DLayerShaderStructuredBuffer.h"
#include "GroundModel2DBlockShaderStructuredBuffer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"
#include "Font.h"
#include "Atlas.h"
#include "Map.h"
#include "Canvas.h"
#include "Canvas2D.h"
#include "Camera.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "Light.h"
#include "Fog.h"
#include "Model.h"
#include "Model2D.h"
#include "FigureModel2D.h"
#include "GroundModel2D.h"


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

	this->main_render_target_texture.reset();
	this->main_depth_target_texture.reset();
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
	this->figure_model_2d_shader.reset();
	this->ground_model_2d_shader.reset();
	this->figure_model_3d_shader.reset();
	this->ground_model_3d_shader.reset();
	this->config_shader_constant_buffer.reset();
	this->header_shader_constant_buffer.reset();
	this->camera_shader_structured_buffer.reset();
	this->light_shader_structured_buffer.reset();
	this->fog_shader_structured_buffer.reset();
	this->figure_model_2d_mesh.reset();
	this->figure_model_3d_mesh.reset();
	this->cc_sampler.reset();
	this->cw_sampler.reset();
	this->wc_sampler.reset();
	this->ww_sampler.reset();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
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

	{// MainRenderTargetTexture Create
		tml::graphic::TextureDesc tex_desc;

		tex_desc.SetManager(this->mgr_);
		tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::RENDER_TARGET | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR | tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::UASR);
		tex_desc.render_target_desc_null_flag = true;
		tex_desc.sr_desc_null_flag = true;
		tex_desc.uasr_desc_null_flag = true;
		tex_desc.swap_chain = this->mgr_->GetSwapChain();

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->main_render_target_texture, tex_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// MainDepthTargetTexture Create
		tml::graphic::TextureDesc tex_desc;

		tex_desc.SetManager(this->mgr_);
		tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::DEPTH_TARGET, DXGI_FORMAT_R24G8_TYPELESS, this->mgr_->GetSize());
		tex_desc.depth_target_format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->main_depth_target_texture, tex_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// DefaultRasterizerState Create
		tml::graphic::RasterizerStateDesc rs_desc;

		rs_desc.SetManager(this->mgr_);
		rs_desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::DEFAULT);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->default_rasterizer_state, rs_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WireframeRasterizerState Create
		tml::graphic::RasterizerStateDesc rs_desc;

		rs_desc.SetManager(this->mgr_);
		rs_desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::WIREFRAME);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->wireframe_rasterizer_state, rs_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FrontCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc rs_desc;

		rs_desc.SetManager(this->mgr_);
		rs_desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::FRONT_CULLING);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->front_culling_rasterizer_state, rs_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc rs_desc;

		rs_desc.SetManager(this->mgr_);
		rs_desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::BACK_CULLING);

		if (this->mgr_->GetResource<tml::graphic::RasterizerState>(this->back_culling_rasterizer_state, rs_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
		{// DefaultBlendState Create
			tml::graphic::BlendStateDesc bs_desc;

			bs_desc.SetManager(this->mgr_);
			bs_desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::DEFAULT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::NONE, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->default_blend_state_array[rt_i], bs_desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AlignmentBlendState Create
			tml::graphic::BlendStateDesc bs_desc;

			bs_desc.SetManager(this->mgr_);
			bs_desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ALIGNMENT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->alignment_blend_state_array[rt_i], bs_desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AddBlendState Create
			tml::graphic::BlendStateDesc bs_desc;

			bs_desc.SetManager(this->mgr_);
			bs_desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ADD, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->add_blend_state_array[rt_i], bs_desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// SubBlendState Create
			tml::graphic::BlendStateDesc bs_desc;

			bs_desc.SetManager(this->mgr_);
			bs_desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::SUB, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->sub_blend_state_array[rt_i], bs_desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// MulBlendState Create
			tml::graphic::BlendStateDesc bs_desc;

			bs_desc.SetManager(this->mgr_);
			bs_desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::MUL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->mul_blend_state_array[rt_i], bs_desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// ReverseBlendState Create
			tml::graphic::BlendStateDesc bs_desc;

			bs_desc.SetManager(this->mgr_);
			bs_desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::REVERSE, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->reverse_blend_state_array[rt_i], bs_desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// TotalBlendState Create
			tml::graphic::BlendStateDesc bs_desc;

			bs_desc.SetManager(this->mgr_);
			bs_desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::TOTAL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::TOTAL, rt_i);

			if (this->mgr_->GetResource<tml::graphic::BlendState>(this->total_blend_state_array[rt_i], bs_desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	{// DefaultDepthState Create
		tml::graphic::DepthStateDesc ds_desc;

		ds_desc.SetManager(this->mgr_);
		ds_desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::DEFAULT);

		if (this->mgr_->GetResource<tml::graphic::DepthState>(this->default_depth_state, ds_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ReferenceDepthState Create
		tml::graphic::DepthStateDesc ds_desc;

		ds_desc.SetManager(this->mgr_);
		ds_desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::REFERENCE);

		if (this->mgr_->GetResource<tml::graphic::DepthState>(this->reference_depth_state, ds_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FigureModel2DShader Create
		tml::graphic::ShaderDesc shader_desc;

		shader_desc.SetManager(this->mgr_);
		shader_desc.Read(tml::INIFileReadDesc(tml::ConstantUtil::FILE_PATH::FIGURE_MODEL_2D_SHADER_CONFIG));
		shader_desc.vertex_shader_input_element_desc_count = tml::graphic::FigureModel2D::INPUT_ELEMENT_DESC_COUNT;
		shader_desc.vertex_shader_input_element_desc_array = tml::graphic::FigureModel2D::INPUT_ELEMENT_DESC_ARRAY;

		if (this->mgr_->GetResource<tml::graphic::Shader>(this->figure_model_2d_shader, shader_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// GroundModel2DShader Create
		tml::graphic::ShaderDesc shader_desc;

		shader_desc.SetManager(this->mgr_);
		shader_desc.Read(tml::INIFileReadDesc(tml::ConstantUtil::FILE_PATH::GROUND_MODEL_2D_SHADER_CONFIG));
		shader_desc.vertex_shader_input_element_desc_count = tml::graphic::GroundModel2D::INPUT_ELEMENT_DESC_COUNT;
		shader_desc.vertex_shader_input_element_desc_array = tml::graphic::GroundModel2D::INPUT_ELEMENT_DESC_ARRAY;

		if (this->mgr_->GetResource<tml::graphic::Shader>(this->ground_model_2d_shader, shader_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FigureModel3DShader Create
	}

	{// GroundModel3DShader Create
	}

	{// ConfigShaderConstantBuffer Create
		tml::graphic::ConfigShaderConstantBufferDesc scb_desc;

		scb_desc.SetManager(this->mgr_);
		scb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::ConfigShaderConstantBuffer::ELEMENT));

		if (this->mgr_->GetResource<tml::graphic::ConfigShaderConstantBuffer>(this->config_shader_constant_buffer, scb_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// HeaderShaderConstantBuffer Create
		tml::graphic::HeaderShaderConstantBufferDesc scb_desc;

		scb_desc.SetManager(this->mgr_);
		scb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::HeaderShaderConstantBuffer::ELEMENT));

		if (this->mgr_->GetResource<tml::graphic::HeaderShaderConstantBuffer>(this->header_shader_constant_buffer, scb_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CameraShaderStructuredBuffer Create
		tml::graphic::CameraShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->mgr_);
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::CameraShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::CAMERA_LIMIT);

		if (this->mgr_->GetResource<tml::graphic::CameraShaderStructuredBuffer>(this->camera_shader_structured_buffer, ssb_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LightShaderStructuredBuffer Create
		tml::graphic::LightShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->mgr_);
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::LightShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT);

		if (this->mgr_->GetResource<tml::graphic::LightShaderStructuredBuffer>(this->light_shader_structured_buffer, ssb_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FogShaderStructuredBuffer Create
		tml::graphic::FogShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->mgr_);
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::FogShaderStructuredBuffer::ELEMENT), tml::ConstantUtil::GRAPHIC::FOG_LIMIT);

		if (this->mgr_->GetResource<tml::graphic::FogShaderStructuredBuffer>(this->fog_shader_structured_buffer, ssb_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FigureModel2DMesh Create
		tml::graphic::MeshDesc mesh_desc;
		std::array<tml::graphic::FigureModel2D::VERTEX_BUFFER_ELEMENT, 4U> vb_element_ary = {
			tml::graphic::FigureModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX(-0.5f,  0.5f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  0.0f), 0U),
			tml::graphic::FigureModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.5f,  0.5f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  0.0f), 0U),
			tml::graphic::FigureModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX(-0.5f, -0.5f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  1.0f), 0U),
			tml::graphic::FigureModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.5f, -0.5f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  1.0f), 0U)
		};
		std::array<UINT, 4U> ib_element_ary = {0U, 1U, 2U, 3U};

		mesh_desc.SetManager(this->mgr_);
		mesh_desc.SetVertexBufferDesc(sizeof(tml::graphic::FigureModel2D::VERTEX_BUFFER_ELEMENT), vb_element_ary.size(), reinterpret_cast<BYTE *>(vb_element_ary.data()));
		mesh_desc.SetIndexBufferDesc(sizeof(UINT), ib_element_ary.size(), reinterpret_cast<BYTE *>(ib_element_ary.data()), DXGI_FORMAT_R32_UINT);
		mesh_desc.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

		if (this->mgr_->GetResource<tml::graphic::Mesh>(figure_model_2d_mesh, mesh_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FigureModel3DMesh Create
	}

	{// CCSampler Create
		tml::graphic::SamplerDesc samp_desc;

		samp_desc.SetManager(this->mgr_);
		samp_desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CC);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->cc_sampler, samp_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CWSampler Create
		tml::graphic::SamplerDesc samp_desc;

		samp_desc.SetManager(this->mgr_);
		samp_desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::CW);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->cw_sampler, samp_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WCSampler Create
		tml::graphic::SamplerDesc samp_desc;

		samp_desc.SetManager(this->mgr_);
		samp_desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WC);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->wc_sampler, samp_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WWSampler Create
		tml::graphic::SamplerDesc samp_desc;

		samp_desc.SetManager(this->mgr_);
		samp_desc.SetSamplerDesc(tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_BIND_FLAG::SR, this->mgr_->GetSamplerQualityType(), tml::ConstantUtil::GRAPHIC::SAMPLER_DESC_WRAP_TYPE::WW);

		if (this->mgr_->GetResource<tml::graphic::Sampler>(this->ww_sampler, samp_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
