/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathUINT.h"
#include "ManagerCommon.h"
#include "Event.h"
#include "Viewport.h"


namespace tml {
namespace graphic {
/**
 * @brief DRAW_STAGE_DATA構造体
 */
typedef struct DRAW_STAGE_DATA_
{
	XMMATRIX &view_matrix_3d;
	XMMATRIX &inverse_view_matrix_3d;
	XMMATRIX &projection_matrix_3d;
	XMMATRIX &view_matrix_2d;
	XMMATRIX &inverse_view_matrix_2d;
	XMMATRIX &projection_matrix_2d;

	/**
	 * @brief コンストラクタ
	 * @param v_mat_3d (view_matrix_3d)
	 * @param inv_v_mat_3d (inverse_view_matrix_3d)
	 * @param p_mat_3d (projection_matrix_3d)
	 * @param v_mat_2d (view_matrix_2d)
	 * @param inv_v_mat_2d (inverse_view_matrix_2d)
	 * @param p_mat_2d (projection_matrix_2d)
	 */
	DRAW_STAGE_DATA_(XMMATRIX &v_mat_3d, XMMATRIX &inv_v_mat_3d, XMMATRIX &p_mat_3d, XMMATRIX &v_mat_2d, XMMATRIX &inv_v_mat_2d, XMMATRIX &p_mat_2d) :
		view_matrix_3d(v_mat_3d),
		inverse_view_matrix_3d(inv_v_mat_3d),
		projection_matrix_3d(p_mat_3d),
		view_matrix_2d(v_mat_2d),
		inverse_view_matrix_2d(inv_v_mat_2d),
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
	HDC window_device_context_handle;
	tml::XMUINT2EX size;
	bool vsync_flag;

protected:
	void Release(void);

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
class Manager
{
public: Manager(const tml::graphic::Manager &) = delete;
public: tml::graphic::Manager &operator =(const tml::graphic::Manager &) = delete;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	tml::graphic::ManagerCommon common_;
	std::array<std::list<tml::shared_ptr<tml::graphic::Resource>>, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE_COUNT> res_cont_ary_;
	std::array<UINT, 2U> event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::graphic::Event>>, 2U> event_cont_ary_;
	UINT front_event_index_;
	UINT back_event_index_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::EVENT_TYPE_COUNT> stock_event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::graphic::Event>>, tml::ConstantUtil::GRAPHIC::EVENT_TYPE_COUNT> stock_event_cont_ary_;

	IDXGIFactory1 *factory_;
	IDXGIAdapter1 *adapter_;
	DXGI_ADAPTER_DESC1 adapter_desc_;
	IDXGISwapChain *swap_chain_;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc_;
	ID3D11Device *device_;
	ID3D11DeviceContext *device_context_;
	D3D_FEATURE_LEVEL device_future_lv_;
	tml::XMUINT2EX size_;
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
	D3D11_VIEWPORT null_vp_;
	std::array<D3D11_VIEWPORT, tml::ConstantUtil::GRAPHIC::VIEWPORT_LIMIT> null_vp_ary_;
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
	std::array<D3D11_VIEWPORT, tml::ConstantUtil::GRAPHIC::VIEWPORT_LIMIT> draw_vp_ary_;
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
	std::array<tml::graphic::Light *, tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT> draw_light_ary_;
	UINT draw_fog_cnt_;
	std::array<tml::graphic::Fog *, tml::ConstantUtil::GRAPHIC::FOG_LIMIT> draw_fog_ary_;
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
	UINT draw_model_cnt_;
	std::array<tml::graphic::Model *, tml::ConstantUtil::GRAPHIC::MODEL_LIMIT> draw_model_ary_;

	ID3D11ComputeShader *cmp_shader_cs_;
	std::array<ID3D11Buffer *, tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_LIMIT> cmp_scb_sr_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_SR_LIMIT> cmp_ssb_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_UASR_LIMIT> cmp_ssb_uasr_ary_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> cmp_tex_sr_ary_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> cmp_tex_uasr_ary_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> cmp_samp_sr_ary_;

private:
	void UpdateEvent(void);

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::graphic::ManagerDesc &);

	void Update(void);
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	tml::graphic::ManagerCommon &GetCommon(void);
	template <typename T1, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &);
	template <typename T1, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, tml::shared_ptr<T1> &);
	template <typename T>
	void ReleaseResource(tml::shared_ptr<T> &);
	UINT GetEventCount(void) const;
	const tml::unique_ptr<tml::graphic::Event> *GetEventArray(void) const;
	template <typename T, typename D>
	INT AddEvent(const D &);

	IDXGIFactory1 *GetFactory(void);
	IDXGIAdapter1 *GetAdapter(void);
	const DXGI_ADAPTER_DESC1 &GetAdapterDesc(void) const;
	IDXGISwapChain *GetSwapChain(void);
	const DXGI_SWAP_CHAIN_DESC &GetSwapChainDesc(void) const;
	ID3D11Device *GetDevice(void);
	ID3D11DeviceContext *GetDeviceContext(void);
	D3D_FEATURE_LEVEL GetDeviceFeatureLevel(void) const;
	const tml::XMUINT2EX &GetSize(void) const;
	tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE GetSamplerQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE GetMotionQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE GetShadowQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE GetAOQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE GetBloomQualityType(void) const;
	tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE GetAAQualityType(void) const;
	XMMATRIX &GetWorldMatrix3D(XMMATRIX &, const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &, const tml::XMFLOAT3EX &);
	XMMATRIX &GetWorldMatrix3D(XMMATRIX &, const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &, const tml::XMFLOAT3EX &);
	XMMATRIX &GetWorldMatrix2D(XMMATRIX &, const tml::XMFLOAT2EX &, const FLOAT, const tml::XMFLOAT2EX &);
	XMMATRIX &GetViewMatrix3D(XMMATRIX &, const tml::graphic::Camera *);
	XMMATRIX &GetViewMatrix2D(XMMATRIX &, const tml::graphic::Camera *);
	XMMATRIX &GetProjectionMatrix3D(XMMATRIX &, const tml::graphic::Camera *);
	XMMATRIX &GetProjectionMatrix2D(XMMATRIX &, const tml::graphic::Camera *);
	tml::DynamicBuffer &GetCPUBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Buffer *, INT *dst_res = nullptr);
	std::vector<tml::DynamicBuffer> &GetCPUBuffer(std::vector<tml::DynamicBuffer> &, std::vector<D3D11_MAPPED_SUBRESOURCE> &, ID3D11Texture2D *, INT *dst_res = nullptr);

	void Draw(const UINT);
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
	void SetDrawShaderConstantBufferSR(const UINT, const UINT, tml::graphic::ShaderConstantBuffer **);
	void ClearDrawShaderConstantBufferSR(const UINT);
	void ClearDrawShaderConstantBufferSR(const UINT, const UINT);
	void SetDrawShaderStructuredBufferSR(const UINT, tml::graphic::ShaderStructuredBuffer *);
	void SetDrawShaderStructuredBufferSR(const UINT, const UINT, tml::graphic::ShaderStructuredBuffer **);
	void ClearDrawShaderStructuredBufferSR(const UINT);
	void ClearDrawShaderStructuredBufferSR(const UINT, const UINT);
	void SetDrawCamera(tml::graphic::Camera *);
	void ClearDrawCamera(void);
	void SetDrawLight(tml::graphic::Light *);
	void ClearDrawLight(void);
	void SetDrawFog(tml::graphic::Fog *);
	void ClearDrawFog(void);
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
	void SetDrawModel(tml::graphic::Model *);
	void ClearDrawModel(void);

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
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::graphic::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::graphic::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetCommon関数
 * @return common (common)
 */
inline tml::graphic::ManagerCommon &tml::graphic::Manager::GetCommon(void)
{
	return (this->common_);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param desc (desc)
 * @return dst_res (dst_resource)
 */
template <typename T1, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::graphic::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc)
{
	this->ReleaseResource(dst_res);

	if (desc.manager != this) {
		return (dst_res);
	}

	auto res = tml::make_shared<T1>(1U);

	if (res->Create(desc) < 0) {
		return (dst_res);
	}

	auto res_index = static_cast<UINT>(res->GetResourceType());

	this->res_cont_ary_[res_index].push_back(res);

	dst_res = res;

	return (dst_res);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param res (resource)
 * @return dst_res (dst_resource)
 */
template <typename T1, typename T2>
inline tml::shared_ptr<T2> &tml::graphic::Manager::GetResource(tml::shared_ptr<T2> &dst_res, tml::shared_ptr<T1> &res)
{
	if (dst_res == res) {
		return (dst_res);
	}

	this->ReleaseResource(dst_res);

	dst_res = res;

	return (dst_res);
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

	auto res_index = static_cast<UINT>(res->GetResourceType());

	if (res.use_count() <= 2L) {
		this->res_cont_ary_[res_index].remove(res);
	}

	res.reset();

	return;
}


/**
 * @brief GetEventCount関数
 * @return event_cnt (event_count)
 */
inline UINT tml::graphic::Manager::GetEventCount(void) const
{
	return (this->event_cnt_ary_[this->front_event_index_]);
}


/**
 * @brief GetEventArray関数
 * @return event_ary (event_array)
 */
inline const tml::unique_ptr<tml::graphic::Event> *tml::graphic::Manager::GetEventArray(void) const
{
	return (this->event_cont_ary_[this->front_event_index_].data());
}


/**
 * @brief AddEvent関数
 * @param dat (data)
 * @return res (result)<br>
 * 0未満=失敗
 */
template <typename T, typename D>
inline INT tml::graphic::Manager::AddEvent(const D &dat)
{
	tml::unique_ptr<tml::graphic::Event> event;

	auto event_index = static_cast<UINT>(T::EVENT_TYPE);
	auto &stock_event_cnt = this->stock_event_cnt_ary_[event_index];
	auto &stock_event_cont = this->stock_event_cont_ary_[event_index];

	if (stock_event_cnt > 0U) {
		--stock_event_cnt;

		event = std::move(stock_event_cont[stock_event_cnt]);
	} else {
		event = tml::make_unique<T>(1U);

		if (reinterpret_cast<T *>(event.get())->Create(this) < 0) {
			return (-1);
		}
	}

	reinterpret_cast<T *>(event.get())->SetData(dat);

	auto &back_event_cnt = this->event_cnt_ary_[this->back_event_index_];
	auto &back_event_cont = this->event_cont_ary_[this->back_event_index_];

	if (back_event_cnt >= back_event_cont.size()) {
		back_event_cont.resize(back_event_cnt + 128U);
	}

	back_event_cont[back_event_cnt] = std::move(event);

	++back_event_cnt;

	return (0);
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

	this->draw_light_ary_[this->draw_light_cnt_++] = light;

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

	this->draw_fog_ary_[this->draw_fog_cnt_++] = fog;

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

	this->draw_model_ary_[this->draw_model_cnt_++] = model;

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
