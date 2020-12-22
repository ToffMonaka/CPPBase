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
/**
 * @brief GraphicManagerクラス
 */
class GraphicManager
{
public: GraphicManager(const tml::GraphicManager &) = delete;
public: tml::GraphicManager &operator =(const tml::GraphicManager &) = delete;

private:
	IDXGIFactory1 *dxgi_factory_;
	IDXGIAdapter1 *dxgi_adapter_;
	DXGI_ADAPTER_DESC1 dxgi_adapter_desc_;
	ID3D11Device *d3d_device_;
	D3D_FEATURE_LEVEL d3d_device_future_lv_;
	ID3D11DeviceContext *d3d_device_context_;
	IDXGISwapChain *dxgi_swap_chain_;
	DXGI_SWAP_CHAIN_DESC dxgi_swap_chain_desc_;

private:
	void Release(void);

public:
	GraphicManager();
	virtual ~GraphicManager();

	virtual void Init(void);
	INT Create(const HWND, const UINT, const UINT);
};
}
