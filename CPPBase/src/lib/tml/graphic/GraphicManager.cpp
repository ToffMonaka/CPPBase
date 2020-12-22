/**
 * @file
 * @brief GraphicManagerコードファイル
 */


#include "GraphicManager.h"
#include <array>
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::GraphicManager::GraphicManager() :
	dxgi_factory_(nullptr),
	dxgi_adapter_(nullptr),
	d3d_device_(nullptr),
	d3d_device_context_(nullptr),
	dxgi_swap_chain_(nullptr)
{
	tml::MemoryUtil::Clear(&this->dxgi_adapter_desc_, 1U);
	this->d3d_device_future_lv_ = static_cast<D3D_FEATURE_LEVEL>(0);
	tml::MemoryUtil::Clear(&this->dxgi_swap_chain_desc_, 1U);

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
	if (this->dxgi_swap_chain_ != nullptr) {
		this->dxgi_swap_chain_->Release();

		this->dxgi_swap_chain_ = nullptr;
	}

	if (this->d3d_device_context_ != nullptr) {
		this->d3d_device_context_->Release();

		this->d3d_device_context_ = nullptr;
	}

	if (this->d3d_device_ != nullptr) {
		this->d3d_device_->Release();

		this->d3d_device_ = nullptr;
	}

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

	tml::MemoryUtil::Clear(&this->dxgi_adapter_desc_, 1U);
	this->d3d_device_future_lv_ = static_cast<D3D_FEATURE_LEVEL>(0);
	tml::MemoryUtil::Clear(&this->dxgi_swap_chain_desc_, 1U);

	return;
}


/**
 * @brief Create関数
 * @param wnd_handle (window_handle)
 * @param wnd_w (window_width)
 * @param wnd_h (window_height)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::GraphicManager::Create(const HWND wnd_handle, const UINT wnd_w, const UINT wnd_h)
{
	this->Init();

	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&this->dxgi_factory_)))) {
		this->Init();

		return (-1);
	}

	UINT dxgi_adapter_index = 0U;

	while (SUCCEEDED(this->dxgi_factory_->EnumAdapters1(dxgi_adapter_index, &this->dxgi_adapter_))) {
		this->dxgi_adapter_->GetDesc1(&this->dxgi_adapter_desc_);

		if (this->dxgi_adapter_desc_.Flags == DXGI_ADAPTER_FLAG_NONE) {
			break;
		}

		this->dxgi_adapter_->Release();

		this->dxgi_adapter_ = nullptr;

		++dxgi_adapter_index;
	}

	if (this->dxgi_adapter_ == nullptr) {
		this->Init();

		return (-1);
	}

	UINT d3d_device_flg = 0U;

	if (tml::ConstantUtil::LIBRARY::DEBUG_FLAG) {
		d3d_device_flg = D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG;
	} else {
		d3d_device_flg = D3D11_CREATE_DEVICE_SINGLETHREADED;
	}

	std::array<D3D_FEATURE_LEVEL, 1U> d3d_device_future_lv_ary = {
		D3D_FEATURE_LEVEL_11_0
	};

	if (FAILED(D3D11CreateDevice(this->dxgi_adapter_, D3D_DRIVER_TYPE_UNKNOWN, nullptr, d3d_device_flg, d3d_device_future_lv_ary.data(), d3d_device_future_lv_ary.size(), D3D11_SDK_VERSION, &this->d3d_device_, &this->d3d_device_future_lv_, &this->d3d_device_context_))) {
		this->Init();

		return (-1);
	}

	DXGI_MODE_DESC dxgi_mode_desc = {};

	dxgi_mode_desc.Width = wnd_w;
	dxgi_mode_desc.Height = wnd_h;
	dxgi_mode_desc.RefreshRate.Numerator = 60U;
	dxgi_mode_desc.RefreshRate.Denominator = 1U;
	dxgi_mode_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgi_mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	dxgi_mode_desc.Scaling = DXGI_MODE_SCALING_CENTERED;

	DXGI_SAMPLE_DESC dxgi_ms_desc = {};
	UINT dxgi_ms_max_cnt = 1U;
	//UINT dxgi_ms_max_cnt = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;

	for (UINT dxgi_ms_cnt = 1U; dxgi_ms_cnt <= dxgi_ms_max_cnt; dxgi_ms_cnt <<= 1) {
		UINT dxgi_ms_quality = 0U;

		if (SUCCEEDED(this->d3d_device_->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, dxgi_ms_cnt, &dxgi_ms_quality))) {
			if (dxgi_ms_quality > 0) {
				dxgi_ms_desc.Count = dxgi_ms_cnt;
				dxgi_ms_desc.Quality = dxgi_ms_quality - 1U;
			}
		}
	}

	if (dxgi_ms_desc.Count <= 0U) {
		this->Init();

		return (-1);
	}

	this->dxgi_swap_chain_desc_.BufferDesc = dxgi_mode_desc;
	this->dxgi_swap_chain_desc_.SampleDesc = dxgi_ms_desc;
	this->dxgi_swap_chain_desc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_UNORDERED_ACCESS;
	this->dxgi_swap_chain_desc_.BufferCount = 1U;
	this->dxgi_swap_chain_desc_.OutputWindow = wnd_handle;
	this->dxgi_swap_chain_desc_.Windowed = true;
	this->dxgi_swap_chain_desc_.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	this->dxgi_swap_chain_desc_.Flags = 0U;

	if (FAILED(this->dxgi_factory_->CreateSwapChain(this->d3d_device_, &this->dxgi_swap_chain_desc_, &this->dxgi_swap_chain_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
