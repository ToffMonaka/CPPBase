/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "ManagerCommon.h"
#include "Viewport.h"


namespace tml {
namespace graphic {
/**
 * @brief DRAW_STAGE_DATA構造体
 */
typedef struct DRAW_STAGE_DATA_
{
	XMMATRIX &world_matrix;
	XMMATRIX *view_matrix;
	XMMATRIX *projection_matrixt;
	XMMATRIX &view_matrix_3d;
	XMMATRIX &inverse_view_matrix_3d;
	XMMATRIX &projection_matrix_3d;
	XMMATRIX &view_matrix_2d;
	XMMATRIX &inverse_view_matrix_2d;
	XMMATRIX &projection_matrix_2d;

	/**
	 * @brief コンストラクタ
	 * @param w_mat (world_matrix)
	 * @param v_mat_3d (view_matrix_3d)
	 * @param inv_v_mat_3d (inverse_view_matrix_3d)
	 * @param p_mat_3d (projection_matrix_3d)
	 * @param v_mat_2d (view_matrix_2d)
	 * @param inv_v_mat_2d (inverse_view_matrix_2d)
	 * @param p_mat_2d (projection_matrix_2d)
	 */
	DRAW_STAGE_DATA_(XMMATRIX &w_mat, XMMATRIX &v_mat_3d, XMMATRIX &inv_v_mat_3d, XMMATRIX &p_mat_3d, XMMATRIX &v_mat_2d, XMMATRIX &inv_vi_mat_2d, XMMATRIX &p_mat_2d) :
		world_matrix(w_mat),
		view_matrix(nullptr),
		projection_matrixt(nullptr),
		view_matrix_3d(v_mat_3d),
		inverse_view_matrix_3d(inv_v_mat_3d),
		projection_matrix_3d(p_mat_3d),
		view_matrix_2d(v_mat_2d),
		inverse_view_matrix_2d(inv_vi_mat_2d),
		projection_matrix_2d(p_mat_2d)
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
class ManagerDesc
{
public:
	HWND window_handle;
	tml::XMUINT2EX window_size;
	bool vsync_flag;

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Managerクラス
 */
class Manager
{
public: Manager(const tml::graphic::Manager &) = delete;
public: tml::graphic::Manager &operator =(const tml::graphic::Manager &) = delete;

private:
	std::array<std::list<tml::shared_ptr<tml::graphic::Resource>>, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE_COUNT> res_cont_ary_;

	IDXGIFactory1 *factory_;
	IDXGIAdapter1 *adapter_;
	DXGI_ADAPTER_DESC1 adapter_desc_;
	IDXGISwapChain *swap_chain_;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc_;
	ID3D11Device *device_;
	ID3D11DeviceContext *device_context_;
	D3D_FEATURE_LEVEL device_future_lv_;
	bool vsync_flg_;
	tml::graphic::Viewport vp_;
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
	CD3D11_VIEWPORT null_vp_;
	std::array<CD3D11_VIEWPORT, tml::ConstantUtil::GRAPHIC::VIEWPORT_LIMIT> null_vp_ary_;
	std::array<ID3D11RenderTargetView *, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> null_rt_ary_;
	std::array<ID3D11Buffer *, tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_LIMIT> null_scb_sr_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_SR_LIMIT> null_ssb_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_UASR_LIMIT> null_ssb_uasr_ary_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_UASR_LIMIT> null_ssb_uasr_init_cnt_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> null_tex_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> null_tex_uasr_ary_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> null_tex_uasr_init_cnt_ary_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> null_samp_sr_ary_;

	tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE draw_stage_type_;
	tml::graphic::DRAW_STAGE_DATA *draw_stage_dat_;
	UINT draw_vp_cnt_;
	std::array<CD3D11_VIEWPORT, tml::ConstantUtil::GRAPHIC::VIEWPORT_LIMIT> draw_vp_ary_;
	UINT draw_rt_cnt_;
	std::array<ID3D11RenderTargetView *, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> draw_rt_ary_;
	ID3D11DepthStencilView *draw_dt_;
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
	tml::graphic::Camera *draw_camera_;
	UINT draw_light_cnt_;
	std::vector<tml::graphic::Light *> draw_light_cont_;
	UINT draw_fog_cnt_;
	std::vector<tml::graphic::Fog *> draw_fog_cont_;
	ID3D11Buffer *draw_mesh_vb_;
	UINT draw_mesh_vb_element_size_;
	ID3D11Buffer *draw_mesh_ib_;
	UINT draw_mesh_ib_element_size_;
	DXGI_FORMAT draw_mesh_ib_format_;
	D3D11_PRIMITIVE_TOPOLOGY draw_mesh_pt_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> draw_tex_sr_ary_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> draw_samp_sr_ary_;
	UINT draw_model_cnt_;
	std::vector<tml::graphic::Model *> draw_model_cont_;

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
	template <typename T, typename D>
	tml::shared_ptr<T> GetResource(D &);
	template <typename T>
	tml::shared_ptr<T> &GetResource(tml::shared_ptr<T> &);
	template <typename T>
	void ReleaseResource(tml::shared_ptr<T> &);

	IDXGIFactory1 *GetFactory(void);
	IDXGIAdapter1 *GetAdapter(void);
	const DXGI_ADAPTER_DESC1 &GetAdapterDesc(void) const;
	IDXGISwapChain *GetSwapChain(void);
	const DXGI_SWAP_CHAIN_DESC &GetSwapChainDesc(void) const;
	ID3D11Device *GetDevice(void);
	ID3D11DeviceContext *GetDeviceContext(void);
	D3D_FEATURE_LEVEL GetDeviceFeatureLevel(void) const;
	tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE GetSamplerQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE GetMotionQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE GetShadowQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE GetAOQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE GetBloomQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE GetAAQualityType(void) const;
	XMMATRIX &GetWorldMatrix3D(XMMATRIX &, const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &);
	XMMATRIX &GetWorldMatrix3D(XMMATRIX &, const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &, const tml::XMFLOAT3EX &);
	XMMATRIX &GetWorldMatrix2D(XMMATRIX &, const tml::XMFLOAT2EX &, const FLOAT, const tml::XMFLOAT2EX &);
	XMMATRIX &GetViewMatrix3D(XMMATRIX &, const tml::graphic::Camera *);
	XMMATRIX &GetViewMatrix2D(XMMATRIX &, const tml::graphic::Camera *);
	XMMATRIX &GetProjectionMatrix3D(XMMATRIX &, const tml::graphic::Camera *);
	XMMATRIX &GetProjectionMatrix2D(XMMATRIX &, const tml::graphic::Camera *);
	tml::DynamicBuffer &GetBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Buffer *, INT *dst_res = nullptr);
	tml::DynamicBuffer &GetBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Texture2D *, INT *dst_res = nullptr);
	std::vector<tml::DynamicBuffer> &GetBuffer(std::vector<tml::DynamicBuffer> &, std::vector<D3D11_MAPPED_SUBRESOURCE> &, ID3D11Texture2D *, INT *dst_res = nullptr);

	tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE GetDrawStageType(void) const;
	tml::graphic::DRAW_STAGE_DATA *GetDrawStageData(void);
	void SetDrawViewport(tml::graphic::Viewport *);
	void SetDrawViewport(const UINT, tml::graphic::Viewport *);
	void ClearDrawViewport(void);
	void SetDrawTarget(tml::graphic::Texture *, tml::graphic::Texture *);
	void SetDrawTarget(const UINT, tml::graphic::Texture **, tml::graphic::Texture *);
	void ClearDrawTarget(void);
	void SetDrawRasterizerState(tml::graphic::RasterizerState *);
	void ClearDrawRasterizerState(void);
	void SetDrawBlendState(tml::graphic::BlendState *);
	void ClearDrawBlendState(void);
	void SetDrawDepthState(tml::graphic::DepthState *);
	void ClearDrawDepthState(void);
	void SetDrawShader(tml::graphic::Shader *);
	void ClearDrawShader(void);
	void SetDrawShaderConstantBufferSR(const UINT, tml::graphic::ShaderConstantBuffer *);
	void ClearDrawShaderConstantBufferSR(const UINT);
	void SetDrawShaderStructuredBufferSR(const UINT, tml::graphic::ShaderStructuredBuffer *);
	void ClearDrawShaderStructuredBufferSR(const UINT);
	void SetDrawCamera(tml::graphic::Camera *);
	void ClearDrawCamera(void);
	void SetDrawLight(tml::graphic::Light *);
	void ClearDrawLight(void);
	void SetDrawFog(tml::graphic::Fog *);
	void ClearDrawFog(void);
	void SetDrawMesh(tml::graphic::Mesh *);
	void ClearDrawMesh(void);
	void SetDrawTextureSR(const UINT, tml::graphic::Texture *);
	void ClearDrawTextureSR(const UINT);
	void SetDrawSamplerSR(const UINT, tml::graphic::Sampler *);
	void ClearDrawSamplerSR(const UINT);
	void SetDrawModel(tml::graphic::Model *);
	void ClearDrawModel(void);

	void SetComputeShader(tml::graphic::Shader *);
	void ClearComputeShader(void);
	void SetComputeShaderConstantBufferSR(const UINT, tml::graphic::ShaderConstantBuffer *);
	void ClearComputeShaderConstantBufferSR(const UINT);
	void SetComputeShaderStructuredBufferSR(const UINT, tml::graphic::ShaderStructuredBuffer *);
	void ClearComputeShaderStructuredBufferSR(const UINT);
	void SetComputeShaderStructuredBufferUASR(const UINT, tml::graphic::ShaderStructuredBuffer *);
	void ClearComputeShaderStructuredBufferUASR(const UINT);
	void SetComputeTextureSR(const UINT, tml::graphic::Texture *);
	void ClearComputeTextureSR(const UINT);
	void SetComputeTextureUASR(const UINT, tml::graphic::Texture *);
	void ClearComputeTextureUASR(const UINT);
	void SetComputeSamplerSR(const UINT, tml::graphic::Sampler *);
	void ClearComputeSamplerSR(const UINT);
};
}
}


/**
 * @brief GetResource関数
 * @param desc (desc)
 * @return res (resource)
 */
template <typename T, typename D>
inline tml::shared_ptr<T> tml::graphic::Manager::GetResource(D &desc)
{
	desc.manager = this;

	auto res = tml::make_shared<T>(1U);

	if (res->Create(desc) < 0) {
		res.reset();

		return (res);
	}

	UINT res_type = static_cast<UINT>(res->GetResourceType());

	if (res_type >= tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE_COUNT) {
		res.reset();

		return (res);
	}

	this->res_cont_ary_[res_type].push_back(res);

	return (res);
}


/**
 * @brief GetResource関数
 * @param res (resource)
 * @return res (resource)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::graphic::Manager::GetResource(tml::shared_ptr<T> &res)
{
	return (res);
}


/**
 * @brief ReleaseResource関数
 * @param res (resource)
 */
template <typename T>
inline void tml::graphic::Manager::ReleaseResource(tml::shared_ptr<T> &res)
{
	if (res == nullptr) {
		return;
	}

	UINT res_type = static_cast<UINT>(res->GetResourceType());

	if (res_type >= tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE_COUNT) {
		return;
	}

	if (res.use_count() <= 2L) {
		this->res_cont_ary_[res_type].remove(res);
	}

	res.reset();

	return;
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
 * @brief GetDrawStageType関数
 * @return draw_stage_type (draw_stage_type)
 */
inline tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE tml::graphic::Manager::GetDrawStageType(void) const
{
	return (this->draw_stage_type_);
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
 * @brief SetDrawCamera関数
 * @param camera (camera)
 */
inline void tml::graphic::Manager::SetDrawCamera(tml::graphic::Camera *camera)
{
	this->draw_camera_ = camera;

	return;
}


/**
 * @brief ClearDrawCamera関数
 */
inline void tml::graphic::Manager::ClearDrawCamera(void)
{
	this->draw_camera_ = nullptr;

	return;
}


/**
 * @brief SetDrawLight関数
 * @param light (light)
 */
inline void tml::graphic::Manager::SetDrawLight(tml::graphic::Light *light)
{
	if ((light == nullptr)
	|| (this->draw_light_cnt_ >= tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT)) {
		return;
	}

	if (this->draw_light_cnt_ >= this->draw_light_cont_.size()) {
		this->draw_light_cont_.resize(this->draw_light_cnt_ + 256U);
	}

	this->draw_light_cont_[this->draw_light_cnt_++] = light;

	return;
}


/**
 * @brief ClearDrawLight関数
 */
inline void tml::graphic::Manager::ClearDrawLight(void)
{
	this->draw_light_cnt_ = 0U;

	return;
}


/**
 * @brief SetDrawFog関数
 * @param fog (fog)
 */
inline void tml::graphic::Manager::SetDrawFog(tml::graphic::Fog *fog)
{
	if ((fog == nullptr)
	|| (this->draw_fog_cnt_ >= tml::ConstantUtil::GRAPHIC::FOG_LIMIT)) {
		return;
	}

	if (this->draw_fog_cnt_ >= this->draw_fog_cont_.size()) {
		this->draw_fog_cont_.resize(this->draw_fog_cnt_ + 256U);
	}

	this->draw_fog_cont_[this->draw_fog_cnt_++] = fog;

	return;
}


/**
 * @brief ClearDrawFog関数
 */
inline void tml::graphic::Manager::ClearDrawFog(void)
{
	this->draw_fog_cnt_ = 0U;

	return;
}


/**
 * @brief SetDrawModel関数
 * @param model (model)
 */
inline void tml::graphic::Manager::SetDrawModel(tml::graphic::Model *model)
{
	if ((model == nullptr)
	|| (this->draw_model_cnt_ >= tml::ConstantUtil::GRAPHIC::MODEL_LIMIT)) {
		return;
	}

	if (this->draw_model_cnt_ >= this->draw_model_cont_.size()) {
		this->draw_model_cont_.resize(this->draw_model_cnt_ + 256U);
	}

	this->draw_model_cont_[this->draw_model_cnt_++] = model;

	return;
}


/**
 * @brief ClearDrawModel関数
 */
inline void tml::graphic::Manager::ClearDrawModel(void)
{
	this->draw_model_cnt_ = 0U;

	return;
}
