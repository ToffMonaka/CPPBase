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
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:
	HWND window_handle;
	tml::XMUINT2EX window_size;

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
	ID3D11RenderTargetView *clear_rt_;
	std::array<ID3D11RenderTargetView *, tml::ConstantUtil::GRAPHIC::DRAW_RENDER_TARGET_LIMIT> clear_rt_ary_;
	ID3D11DepthStencilView *clear_dt_;
	std::array<ID3D11DepthStencilView *, tml::ConstantUtil::GRAPHIC::DRAW_DEPTH_TARGET_LIMIT> clear_dt_ary_;
	ID3D11ShaderResourceView *clear_tex_sr_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT> clear_tex_sr_ary_;
	ID3D11UnorderedAccessView *clear_tex_uasr_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_UASR_LIMIT> clear_tex_uasr_ary_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_UASR_LIMIT> clear_tex_uasr_init_cnt_ary_;
	ID3D11SamplerState *clear_samp_sr_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::DRAW_SAMPLER_SR_LIMIT> clear_samp_sr_ary_;
	bool vsync_flg_;
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

	ID3D11VertexShader *draw_vs_;
	ID3D11InputLayout *draw_vs_input_layout_;
	ID3D11HullShader *draw_hs_;
	ID3D11DomainShader *draw_ds_;
	ID3D11GeometryShader *draw_gs_;
	ID3D11PixelShader *draw_ps_;
	tml::graphic::Camera *draw_camera_;
	UINT draw_light_cnt_;
	std::vector<tml::graphic::Light *> draw_light_cont_;
	UINT draw_fog_cnt_;
	std::vector<tml::graphic::Fog *> draw_fog_cont_;
	UINT draw_model_cnt_;
	std::vector<tml::graphic::Model *> draw_model_cont_;

	ID3D11ComputeShader *cmp_cs_;

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
	tml::DynamicBuffer &GetBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Buffer *, INT *dst_res = nullptr);
	tml::DynamicBuffer &GetBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Texture2D *, INT *dst_res = nullptr);
	std::vector<tml::DynamicBuffer> &GetBuffer(std::vector<tml::DynamicBuffer> &, std::vector<D3D11_MAPPED_SUBRESOURCE> &, ID3D11Texture2D *, INT *dst_res = nullptr);

	void SetDrawShader(tml::graphic::Shader *);
	void SetDrawShaderConstantBuffer(tml::graphic::ShaderConstantBuffer *, const tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG, const UINT);
	void SetDrawShaderStructuredBuffer(tml::graphic::ShaderStructuredBuffer *, const tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG, const UINT);
	void SetDrawCamera(tml::graphic::Camera *);
	void SetDrawLight(tml::graphic::Light *);
	void SetDrawFog(tml::graphic::Fog *);
	void SetDrawModel(tml::graphic::Model *);

	void SetComputeShader(tml::graphic::Shader *);
	void SetComputeShaderConstantBuffer(tml::graphic::ShaderConstantBuffer *, const UINT);
	void SetComputeShaderStructuredBuffer(tml::graphic::ShaderStructuredBuffer *, const UINT);
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
 * @brief SetDrawCamera関数
 * @param camera (camera)
 */
inline void tml::graphic::Manager::SetDrawCamera(tml::graphic::Camera *camera)
{
	this->draw_camera_ = camera;

	return;
}


/**
 * @brief SetDrawLight関数
 * @param light (light)
 */
inline void tml::graphic::Manager::SetDrawLight(tml::graphic::Light *light)
{
	if (this->draw_light_cnt_ >= this->draw_light_cont_.size()) {
		this->draw_light_cont_.resize(this->draw_light_cnt_ + 256U);
	}

	this->draw_light_cont_[this->draw_light_cnt_++] = light;

	return;
}


/**
 * @brief SetDrawFog関数
 * @param fog (fog)
 */
inline void tml::graphic::Manager::SetDrawFog(tml::graphic::Fog *fog)
{
	if (this->draw_fog_cnt_ >= this->draw_fog_cont_.size()) {
		this->draw_fog_cont_.resize(this->draw_fog_cnt_ + 256U);
	}

	this->draw_fog_cont_[this->draw_fog_cnt_++] = fog;

	return;
}


/**
 * @brief SetDrawModel関数
 * @param model (model)
 */
inline void tml::graphic::Manager::SetDrawModel(tml::graphic::Model *model)
{
	if (this->draw_model_cnt_ >= this->draw_model_cont_.size()) {
		this->draw_model_cont_.resize(this->draw_model_cnt_ + 256U);
	}

	this->draw_model_cont_[this->draw_model_cnt_++] = model;

	return;
}
