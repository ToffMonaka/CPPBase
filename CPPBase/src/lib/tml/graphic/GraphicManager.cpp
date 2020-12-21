/**
 * @file
 * @brief GraphicManagerコードファイル
 */


#include "GraphicManager.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::GraphicManager::GraphicManager() :
	dxgi_factory_(nullptr),
	dxgi_adapter_(nullptr)
{
	tml::MemoryUtil::Clear(&this->dxgi_adapter_desc_, 1U);

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
		tml::MemoryUtil::Clear(&this->dxgi_adapter_desc_, 1U);
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

	tml::MemoryUtil::Clear(&this->dxgi_adapter_desc_, 1U);

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

	UINT dxgi_adapter_index = 0U;

	while (!FAILED(this->dxgi_factory_->EnumAdapters1(dxgi_adapter_index, &this->dxgi_adapter_))) {
		this->dxgi_adapter_->GetDesc1(&this->dxgi_adapter_desc_);

		if (this->dxgi_adapter_desc_.Flags == DXGI_ADAPTER_FLAG_NONE) {
			break;
		}

		this->dxgi_adapter_->Release();

		this->dxgi_adapter_ = nullptr;
		tml::MemoryUtil::Clear(&this->dxgi_adapter_desc_, 1U);

		++dxgi_adapter_index;
	}

	return (0);
}
