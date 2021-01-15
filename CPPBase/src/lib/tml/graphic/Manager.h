/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <list>
#include "../memory/DynamicBuffer.h"
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
	UINT window_width;
	UINT window_height;

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

public:
	tml::graphic::ManagerCommon common;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(tml::graphic::ManagerDesc &);

	template <typename T, typename D>
	tml::shared_ptr<T> GetResource(D &);
	template <typename T>
	tml::shared_ptr<T> &GetResource(tml::shared_ptr<T> &);
	template <typename T>
	void ReleaseResource(tml::shared_ptr<T> &);

	IDXGIFactory1 *GetFactory(void) const;
	IDXGIAdapter1 *GetAdapter(void) const;
	const DXGI_ADAPTER_DESC1 &GetAdapterDesc(void) const;
	IDXGISwapChain *GetSwapChain(void) const;
	const DXGI_SWAP_CHAIN_DESC &GetSwapChainDesc(void) const;
	ID3D11Device *GetDevice(void) const;
	ID3D11DeviceContext *GetDeviceContext(void) const;
	D3D_FEATURE_LEVEL GetDeviceFeatureLevel(void) const;
	tml::DynamicBuffer &GetBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Buffer *, INT *dst_res = nullptr);
	tml::DynamicBuffer &GetBuffer(tml::DynamicBuffer &, D3D11_MAPPED_SUBRESOURCE &, ID3D11Texture2D *, INT *dst_res = nullptr);
	std::vector<tml::DynamicBuffer> &GetBuffer(std::vector<tml::DynamicBuffer> &, std::vector<D3D11_MAPPED_SUBRESOURCE> &, ID3D11Texture2D *, INT *dst_res = nullptr);

	void Draw(void);
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
inline IDXGIFactory1 *tml::graphic::Manager::GetFactory(void) const
{
	return (this->factory_);
}


/**
 * @brief GetAdapter関数
 * @return adapter (adapter)
 */
inline IDXGIAdapter1 *tml::graphic::Manager::GetAdapter(void) const
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
inline IDXGISwapChain *tml::graphic::Manager::GetSwapChain(void) const
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
inline ID3D11Device *tml::graphic::Manager::GetDevice(void) const
{
	return (this->device_);
}


/**
 * @brief GetDeviceContext関数
 * @return device_context (device_context)
 */
inline ID3D11DeviceContext *tml::graphic::Manager::GetDeviceContext(void) const
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
