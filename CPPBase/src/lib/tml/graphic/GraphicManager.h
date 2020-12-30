/**
 * @file
 * @brief GraphicManagerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Viewport.h"


namespace tml {
/**
 * @brief GraphicManagerDescクラス
 */
class GraphicManagerDesc
{
public:
	HWND window_handle;
	UINT window_width;
	UINT window_height;

public:
	GraphicManagerDesc();
	virtual ~GraphicManagerDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief GraphicManagerクラス
 */
class GraphicManager
{
public: GraphicManager(const tml::GraphicManager &) = delete;
public: tml::GraphicManager &operator =(const tml::GraphicManager &) = delete;

private:
	IDXGIFactory1 *factory_;
	IDXGIAdapter1 *adapter_;
	DXGI_ADAPTER_DESC1 adapter_desc_;
	IDXGISwapChain *swap_chain_;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc_;
	ID3D11Device *device_;
	ID3D11DeviceContext *device_context_;
	D3D_FEATURE_LEVEL device_future_lv_;
	ID3D11RenderTargetView *clear_rt_;
	std::array<ID3D11RenderTargetView *, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> clear_rt_ary_;
	ID3D11DepthStencilView *clear_dt_;
	std::array<ID3D11DepthStencilView *, tml::ConstantUtil::GRAPHIC::DEPTH_TARGET_LIMIT> clear_dt_ary_;
	ID3D11ShaderResourceView *clear_tex_sr_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> clear_tex_sr_ary_;
	ID3D11UnorderedAccessView *clear_tex_uasr_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> clear_tex_uasr_ary_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT> clear_tex_uasr_init_cnt_ary_;
	ID3D11SamplerState *clear_samp_sr_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> clear_samp_sr_ary_;
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
	tml::Viewport shadow_vp_;
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

private:
	void Release(void);

public:
	GraphicManager();
	virtual ~GraphicManager();

	virtual void Init(void);
	INT Create(const tml::GraphicManagerDesc &);

	void Draw(void);
	IDXGIFactory1 *GetFactory(void) const;
	IDXGIAdapter1 *GetAdapter(void) const;
	const DXGI_ADAPTER_DESC1 &GetAdapterDesc(void) const;
	IDXGISwapChain *GetSwapChain(void) const;
	const DXGI_SWAP_CHAIN_DESC &GetSwapChainDesc(void) const;
	ID3D11Device *GetDevice(void) const;
	ID3D11DeviceContext *GetDeviceContext(void) const;
	D3D_FEATURE_LEVEL GetDeviceFeatureLevel(void) const;
};
}


/**
 * @brief GetFactory関数
 * @return factory (factory)
 */
inline IDXGIFactory1 *tml::GraphicManager::GetFactory(void) const
{
	return (this->factory_);
}


/**
 * @brief GetAdapter関数
 * @return adapter (adapter)
 */
inline IDXGIAdapter1 *tml::GraphicManager::GetAdapter(void) const
{
	return (this->adapter_);
}


/**
 * @brief GetAdapterDesc関数
 * @return adapter_desc (adapter_desc)
 */
inline const DXGI_ADAPTER_DESC1 &tml::GraphicManager::GetAdapterDesc(void) const
{
	return (this->adapter_desc_);
}


/**
 * @brief GetSwapChain関数
 * @return swap_chain (swap_chain)
 */
inline IDXGISwapChain *tml::GraphicManager::GetSwapChain(void) const
{
	return (this->swap_chain_);
}


/**
 * @brief GetSwapChainDesc関数
 * @return swap_chain_desc (swap_chain_desc)
 */
inline const DXGI_SWAP_CHAIN_DESC &tml::GraphicManager::GetSwapChainDesc(void) const
{
	return (this->swap_chain_desc_);
}


/**
 * @brief GetDevice関数
 * @return device (device)
 */
inline ID3D11Device *tml::GraphicManager::GetDevice(void) const
{
	return (this->device_);
}


/**
 * @brief GetDeviceContext関数
 * @return device_context (device_context)
 */
inline ID3D11DeviceContext *tml::GraphicManager::GetDeviceContext(void) const
{
	return (this->device_context_);
}


/**
 * @brief GetDeviceFeatureLevel関数
 * @return device_future_lv (device_future_level)
 */
inline D3D_FEATURE_LEVEL tml::GraphicManager::GetDeviceFeatureLevel(void) const
{
	return (this->device_future_lv_);
}
