/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathUINT.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"
#include "Viewport.h"


namespace tml {
namespace graphic {
/**
 * @brief DRAW_STAGE_DATA構造体
 */
typedef struct DRAW_STAGE_DATA_
{
	tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type;
	DirectX::XMMATRIX &view_matrix;
	DirectX::XMMATRIX &inverse_view_matrix;
	DirectX::XMMATRIX &projection_matrix;

	/**
	 * @brief コンストラクタ
	 * @param v_mat (view_matrix_2d)
	 * @param inv_v_mat (inverse_view_matrix)
	 * @param p_mat (projection_matrix)
	 */
	DRAW_STAGE_DATA_(DirectX::XMMATRIX &v_mat, DirectX::XMMATRIX &inv_v_mat, DirectX::XMMATRIX &p_mat) :
		type(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::INIT),
		view_matrix(v_mat),
		inverse_view_matrix(inv_v_mat),
		projection_matrix(p_mat)
	{
		return;
	};
} DRAW_STAGE_DATA;
}
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::ManagerDesc
{
public:
	tml::XMUINT2EX size;
	bool vsync_flag;
	UINT frame_rate_limit;

private:
	void Release(void);

protected:
	void InitResourceCount(void);
	void InitEventCount(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Managerクラス
 */
class Manager : public tml::Manager
{
public: Manager(const tml::graphic::Manager &) = delete;
public: tml::graphic::Manager &operator =(const tml::graphic::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	IDXGIFactory1 *factory_;
	IDXGIAdapter1 *adapter_;
	DXGI_ADAPTER_DESC1 adapter_desc_;
	ID3D11Device *device_;
	ID3D11DeviceContext *device_context_;
	D3D_FEATURE_LEVEL device_future_lv_;
	IDXGISwapChain *swap_chain_;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc_;
	tml::XMUINT2EX size_;
	bool vsync_flg_;
	UINT frame_rate_limit_;
	tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE samp_quality_type_;
	tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE motion_quality_type_;
	UINT motion_frame_rate_limit_;
	tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE shadow_quality_type_;
	FLOAT shadow_per_;
	FLOAT shadow_rng_;
	FLOAT shadow_rng_exponent_;
	FLOAT shadow_size_;
	UINT shadow_interval_cnt_;
	UINT shadow_blur_weight_cnt_;
	FLOAT shadow_blur_dispersion_val_;
	tml::graphic::Viewport shadow_vp_;
	tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE ao_quality_type_;
	FLOAT ao_per_;
	FLOAT ao_rng_;
	FLOAT ao_rng_exponent_;
	UINT ao_ray_cnt_;
	FLOAT ao_ray_radius_;
	FLOAT ao_ray_radius_scale_;
	UINT ao_blur_weight_cnt_;
	FLOAT ao_blur_dispersion_val_;
	FLOAT ao_blur_sharp_val_;
	tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE bloom_quality_type_;
	FLOAT bloom_per_;
	UINT bloom_blur_weight_cnt_;
	FLOAT bloom_blur_dispersion_val_;
	tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE aa_quality_type_;
	std::array<ID3D11Buffer *, tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_LIMIT> null_scb_sr_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_SR_LIMIT> null_ssb_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_UASR_LIMIT> null_ssb_uasr_ary_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_UASR_LIMIT> null_ssb_uasr_init_cnt_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> null_tex_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> null_tex_uasr_ary_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> null_tex_uasr_init_cnt_ary_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> null_samp_sr_ary_;

	tml::graphic::DRAW_STAGE_DATA *draw_stage_dat_;
	UINT draw_rt_cnt_;
	std::array<ID3D11RenderTargetView *, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> draw_rt_ary_;
	ID3D11DepthStencilView *draw_dt_;
	UINT draw_vp_cnt_;
	std::array<D3D11_VIEWPORT, tml::ConstantUtil::GRAPHIC::VIEWPORT_LIMIT> draw_vp_ary_;
	ID3D11RasterizerState *draw_rs_;
	ID3D11BlendState *draw_bs_;
	ID3D11DepthStencilState *draw_ds_;
	ID3D11VertexShader *draw_shader_vs_;
	ID3D11InputLayout *draw_shader_vs_input_layout_;
	ID3D11HullShader *draw_shader_hs_;
	ID3D11DomainShader *draw_shader_ds_;
	ID3D11GeometryShader *draw_shader_gs_;
	ID3D11PixelShader *draw_shader_ps_;
	std::array<ID3D11Buffer *, tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_LIMIT> draw_scb_sr_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_SR_LIMIT> draw_ssb_sr_ary_;
	ID3D11Buffer *draw_mesh_vb_;
	UINT draw_mesh_vb_element_size_;
	UINT draw_mesh_vb_element_cnt_;
	ID3D11Buffer *draw_mesh_ib_;
	UINT draw_mesh_ib_element_size_;
	UINT draw_mesh_ib_element_cnt_;
	DXGI_FORMAT draw_mesh_ib_format_;
	D3D11_PRIMITIVE_TOPOLOGY draw_mesh_pt_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> draw_tex_sr_ary_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> draw_samp_sr_ary_;
	UINT draw_canvas_cnt_;
	std::array<tml::graphic::Canvas *, tml::ConstantUtil::GRAPHIC::CANVAS_LIMIT> draw_canvas_ary_;

	ID3D11ComputeShader *cmp_shader_cs_;
	std::array<ID3D11Buffer *, tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_LIMIT> cmp_scb_sr_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_SR_LIMIT> cmp_ssb_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_UASR_LIMIT> cmp_ssb_uasr_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> cmp_tex_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> cmp_tex_uasr_ary_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> cmp_samp_sr_ary_;

public:
	tml::graphic::ManagerCommon common;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::graphic::ManagerDesc &);

	void Update(void);

	IDXGIFactory1 *GetFactory(void);
	IDXGIAdapter1 *GetAdapter(void);
	const DXGI_ADAPTER_DESC1 &GetAdapterDesc(void) const;
	IDXGISwapChain *GetSwapChain(void);
	const DXGI_SWAP_CHAIN_DESC &GetSwapChainDesc(void) const;
	ID3D11Device *GetDevice(void);
	ID3D11DeviceContext *GetDeviceContext(void);
	D3D_FEATURE_LEVEL GetDeviceFeatureLevel(void) const;
	const tml::XMUINT2EX &GetSize(void) const;
	bool GetVsyncFlag(void) const;
	UINT GetFrameRateLimit(void) const;
	tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE GetSamplerQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE GetMotionQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE GetShadowQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE GetAOQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE GetBloomQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE GetAAQualityType(void) const;
	tml::DynamicBuffer &GetCPUBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Buffer *, INT *dst_result = nullptr);
	std::vector<tml::DynamicBuffer> &GetCPUBuffer(std::vector<tml::DynamicBuffer> &, std::vector<D3D11_MAPPED_SUBRESOURCE> &, ID3D11Texture2D *, INT *dst_result = nullptr);

	void Draw(const UINT);
	tml::graphic::DRAW_STAGE_DATA *GetDrawStageData(void);
	void SetDrawStageData(tml::graphic::DRAW_STAGE_DATA *);
	void ClearDrawStageData(void);
	void SetDrawTargetTexture(tml::graphic::Texture *, tml::graphic::Texture *);
	void SetDrawTargetTexture(const UINT, tml::graphic::Texture **, tml::graphic::Texture *);
	void ClearDrawTargetTexture(void);
	void SetDrawViewport(tml::graphic::Viewport *);
	void SetDrawViewport(const UINT, tml::graphic::Viewport *);
	void ClearDrawViewport(void);
	void SetDrawRasterizerState(tml::graphic::RasterizerState *);
	void ClearDrawRasterizerState(void);
	void SetDrawBlendState(tml::graphic::BlendState *);
	void ClearDrawBlendState(void);
	void SetDrawDepthState(tml::graphic::DepthState *);
	void ClearDrawDepthState(void);
	void SetDrawShader(tml::graphic::Shader *);
	void ClearDrawShader(void);
	void SetDrawShaderConstantBufferSR(const UINT, tml::graphic::ShaderConstantBuffer *);
	void SetDrawShaderConstantBufferSR(const UINT, const UINT, tml::graphic::ShaderConstantBuffer **);
	void ClearDrawShaderConstantBufferSR(const UINT);
	void ClearDrawShaderConstantBufferSR(const UINT, const UINT);
	void SetDrawShaderStructuredBufferSR(const UINT, tml::graphic::ShaderStructuredBuffer *);
	void SetDrawShaderStructuredBufferSR(const UINT, const UINT, tml::graphic::ShaderStructuredBuffer **);
	void ClearDrawShaderStructuredBufferSR(const UINT);
	void ClearDrawShaderStructuredBufferSR(const UINT, const UINT);
	void SetDrawMesh(tml::graphic::Mesh *);
	void ClearDrawMesh(void);
	void SetDrawTextureSR(const UINT, tml::graphic::Texture *);
	void SetDrawTextureSR(const UINT, const UINT, tml::graphic::Texture **);
	void ClearDrawTextureSR(const UINT);
	void ClearDrawTextureSR(const UINT, const UINT);
	void SetDrawSamplerSR(const UINT, tml::graphic::Sampler *);
	void SetDrawSamplerSR(const UINT, const UINT, tml::graphic::Sampler **);
	void ClearDrawSamplerSR(const UINT);
	void ClearDrawSamplerSR(const UINT, const UINT);
	void SetDrawCanvas(tml::graphic::Canvas *);
	void ClearDrawCanvas(void);

	void SetComputeShader(tml::graphic::Shader *);
	void ClearComputeShader(void);
	void SetComputeShaderConstantBufferSR(const UINT, tml::graphic::ShaderConstantBuffer *);
	void SetComputeShaderConstantBufferSR(const UINT, const UINT, tml::graphic::ShaderConstantBuffer **);
	void ClearComputeShaderConstantBufferSR(const UINT);
	void ClearComputeShaderConstantBufferSR(const UINT, const UINT);
	void SetComputeShaderStructuredBufferSR(const UINT, tml::graphic::ShaderStructuredBuffer *);
	void SetComputeShaderStructuredBufferSR(const UINT, const UINT, tml::graphic::ShaderStructuredBuffer **);
	void ClearComputeShaderStructuredBufferSR(const UINT);
	void ClearComputeShaderStructuredBufferSR(const UINT, const UINT);
	void SetComputeShaderStructuredBufferUASR(const UINT, tml::graphic::ShaderStructuredBuffer *);
	void SetComputeShaderStructuredBufferUASR(const UINT, const UINT, tml::graphic::ShaderStructuredBuffer **);
	void ClearComputeShaderStructuredBufferUASR(const UINT);
	void ClearComputeShaderStructuredBufferUASR(const UINT, const UINT);
	void SetComputeTextureSR(const UINT, tml::graphic::Texture *);
	void SetComputeTextureSR(const UINT, const UINT, tml::graphic::Texture **);
	void ClearComputeTextureSR(const UINT);
	void ClearComputeTextureSR(const UINT, const UINT);
	void SetComputeTextureUASR(const UINT, tml::graphic::Texture *);
	void SetComputeTextureUASR(const UINT, const UINT, tml::graphic::Texture **);
	void ClearComputeTextureUASR(const UINT);
	void ClearComputeTextureUASR(const UINT, const UINT);
	void SetComputeSamplerSR(const UINT, tml::graphic::Sampler *);
	void SetComputeSamplerSR(const UINT, const UINT, tml::graphic::Sampler **);
	void ClearComputeSamplerSR(const UINT);
	void ClearComputeSamplerSR(const UINT, const UINT);
};
}
}


/**
 * @brief GetFactory関数
 * @return factory (factory)
 */
inline IDXGIFactory1 *tml::graphic::Manager::GetFactory(void)
{
	return (this->factory_);
}


/**
 * @brief GetAdapter関数
 * @return adapter (adapter)
 */
inline IDXGIAdapter1 *tml::graphic::Manager::GetAdapter(void)
{
	return (this->adapter_);
}


/**
 * @brief GetAdapterDesc関数
 * @return adapter_desc (adapter_desc)
 */
inline const DXGI_ADAPTER_DESC1 &tml::graphic::Manager::GetAdapterDesc(void) const
{
	return (this->adapter_desc_);
}


/**
 * @brief GetSwapChain関数
 * @return swap_chain (swap_chain)
 */
inline IDXGISwapChain *tml::graphic::Manager::GetSwapChain(void)
{
	return (this->swap_chain_);
}


/**
 * @brief GetSwapChainDesc関数
 * @return swap_chain_desc (swap_chain_desc)
 */
inline const DXGI_SWAP_CHAIN_DESC &tml::graphic::Manager::GetSwapChainDesc(void) const
{
	return (this->swap_chain_desc_);
}


/**
 * @brief GetDevice関数
 * @return device (device)
 */
inline ID3D11Device *tml::graphic::Manager::GetDevice(void)
{
	return (this->device_);
}


/**
 * @brief GetDeviceContext関数
 * @return device_context (device_context)
 */
inline ID3D11DeviceContext *tml::graphic::Manager::GetDeviceContext(void)
{
	return (this->device_context_);
}


/**
 * @brief GetDeviceFeatureLevel関数
 * @return device_future_lv (device_future_level)
 */
inline D3D_FEATURE_LEVEL tml::graphic::Manager::GetDeviceFeatureLevel(void) const
{
	return (this->device_future_lv_);
}


/**
 * @brief GetSize関数
 * @return size (size)
 */
inline const tml::XMUINT2EX &tml::graphic::Manager::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief GetVsyncFlag関数
 * @return vsync_flg (vsync_flag)
 */
inline bool tml::graphic::Manager::GetVsyncFlag(void) const
{
	return (this->vsync_flg_);
}


/**
 * @brief GetFrameRateLimit関数
 * @return frame_rate_limit (frame_rate_limit)
 */
inline UINT tml::graphic::Manager::GetFrameRateLimit(void) const
{
	return (this->frame_rate_limit_);
}


/**
 * @brief GetSamplerQualityType関数
 * @return samp_quality_type (sampler_quality_type)
 */
inline tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE tml::graphic::Manager::GetSamplerQualityType(void) const
{
	return (this->samp_quality_type_);
}


/**
 * @brief GetMotionQualityType関数
 * @return motion_quality_type (motion_quality_type)
 */
inline tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE tml::graphic::Manager::GetMotionQualityType(void) const
{
	return (this->motion_quality_type_);
}


/**
 * @brief GetShadowQualityType関数
 * @return shadow_quality_type (shadow_quality_type)
 */
inline tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE tml::graphic::Manager::GetShadowQualityType(void) const
{
	return (this->shadow_quality_type_);
}


/**
 * @brief GetAOQualityType関数
 * @return ao_quality_type (ao_quality_type)
 */
inline tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE tml::graphic::Manager::GetAOQualityType(void) const
{
	return (this->ao_quality_type_);
}


/**
 * @brief GetBloomQualityType関数
 * @return bloom_quality_type (bloom_quality_type)
 */
inline tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE tml::graphic::Manager::GetBloomQualityType(void) const
{
	return (this->bloom_quality_type_);
}


/**
 * @brief GetAAQualityType関数
 * @return aa_quality_type (aa_quality_type)
 */
inline tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE tml::graphic::Manager::GetAAQualityType(void) const
{
	return (this->aa_quality_type_);
}


/**
 * @brief GetDrawStageData関数
 * @return draw_stage_dat (draw_stage_data)
 */
inline tml::graphic::DRAW_STAGE_DATA *tml::graphic::Manager::GetDrawStageData(void)
{
	return (this->draw_stage_dat_);
}


/**
 * @brief SetDrawStageData関数
 * @param draw_stage_dat (draw_stage_data)
 */
inline void tml::graphic::Manager::SetDrawStageData(tml::graphic::DRAW_STAGE_DATA *draw_stage_dat)
{
	this->draw_stage_dat_ = draw_stage_dat;

	return;
}


/**
 * @brief ClearDrawStageData関数
 */
inline void tml::graphic::Manager::ClearDrawStageData(void)
{
	this->draw_stage_dat_ = nullptr;

	return;
}


/**
 * @brief SetDrawCanvas関数
 * @param canvas (canvas)
 */
inline void tml::graphic::Manager::SetDrawCanvas(tml::graphic::Canvas *canvas)
{
	if ((canvas == nullptr)
	|| (this->draw_canvas_cnt_ >= tml::ConstantUtil::GRAPHIC::CANVAS_LIMIT)) {
		return;
	}

	this->draw_canvas_ary_[this->draw_canvas_cnt_++] = canvas;

	return;
}


/**
 * @brief ClearDrawCanvas関数
 */
inline void tml::graphic::Manager::ClearDrawCanvas(void)
{
	this->draw_canvas_cnt_ = 0U;

	return;
}
