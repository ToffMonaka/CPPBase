/**
 * @file
 * @brief GraphicManagerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#pragma warning(pop)


namespace tml {
namespace ConstantUtil {
namespace GRAPHIC {
	const UINT RT_LIMIT = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	const UINT DT_LIMIT = 1U;
	const UINT SCB_SR_LIMIT = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	const UINT SSB_SR_LIMIT = 16U;
	const UINT SSB_UA_SR_LIMIT = 4U;
	const UINT TEXTURE_SR_LIMIT = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 16U;
	const UINT TEXTURE_UA_SR_LIMIT = D3D11_PS_CS_UAV_REGISTER_COUNT - 4U;
	const UINT SAMPLER_SR_LIMIT = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;
}
}
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
	std::array<ID3D11RenderTargetView *, tml::ConstantUtil::GRAPHIC::RT_LIMIT> clear_rt_ary_;
	ID3D11DepthStencilView *clear_dt_;
	std::array<ID3D11DepthStencilView *, tml::ConstantUtil::GRAPHIC::DT_LIMIT> clear_dt_ary_;
	ID3D11ShaderResourceView *clear_tex_sr_;
	std::array<ID3D11ShaderResourceView *, tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT> clear_tex_sr_ary_;
	ID3D11UnorderedAccessView *clear_tex_ua_sr_;
	std::array<ID3D11UnorderedAccessView *, tml::ConstantUtil::GRAPHIC::TEXTURE_UA_SR_LIMIT> clear_tex_ua_sr_ary_;
	std::array<UINT, tml::ConstantUtil::GRAPHIC::TEXTURE_UA_SR_LIMIT> clear_tex_ua_sr_init_cnt_ary_;
	ID3D11SamplerState *clear_samp_sr_;
	std::array<ID3D11SamplerState *, tml::ConstantUtil::GRAPHIC::SAMPLER_SR_LIMIT> clear_samp_sr_ary_;
	bool vsync_flg_;

private:
	void Release(void);

public:
	GraphicManager();
	virtual ~GraphicManager();

	virtual void Init(void);
	INT Create(const HWND, const UINT, const UINT);

	bool StartDraw(void);
	void EndDraw(void);
	void SwapDraw(void);
};
}
