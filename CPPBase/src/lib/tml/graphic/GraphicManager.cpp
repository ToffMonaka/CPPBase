/**
 * @file
 * @brief GraphicManagerコードファイル
 */


#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::GraphicManager::GraphicManager() :
	dxgi_factory_(nullptr),
	dxgi_adapter_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::GraphicManager::~GraphicManager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::GraphicManager::Release(void)
{
	if (this->dxgi_adapter_ != nullptr) {
		this->dxgi_adapter_->Release();

		this->dxgi_adapter_ = nullptr;
	}

	if (this->dxgi_factory_ != nullptr) {
		this->dxgi_factory_->Release();

		this->dxgi_factory_ = nullptr;
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::GraphicManager::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::GraphicManager::Create(void)
{
	this->Release();

	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&this->dxgi_factory_)))) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->dxgi_factory_->EnumAdapters1(0U, &this->dxgi_adapter_))) {
		this->Init();

		return (-1);
	}

	DXGI_ADAPTER_DESC1 dxgi_adapter_desc;

	this->dxgi_adapter_->GetDesc1(&dxgi_adapter_desc);

	return (0);
}
