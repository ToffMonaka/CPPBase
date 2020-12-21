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

private:
	void Release(void);

public:
	GraphicManager();
	virtual ~GraphicManager();

	virtual void Init(void);
	INT Create(void);
};
}
