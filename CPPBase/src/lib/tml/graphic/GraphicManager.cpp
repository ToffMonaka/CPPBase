/**
 * @file
 * @brief GraphicManager�R�[�h�t�@�C��
 */


#include "GraphicManager.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::GraphicManager::GraphicManager() :
	factory_(nullptr),
	adapter_(nullptr),
	swap_chain_(nullptr),
	device_(nullptr),
	device_context_(nullptr),
	clear_rt_(nullptr),
	clear_rt_ary_{},
	clear_dt_(nullptr),
	clear_dt_ary_{},
	clear_tex_sr_(nullptr),
	clear_tex_sr_ary_{},
	clear_tex_ua_sr_(nullptr),
	clear_tex_ua_sr_ary_{},
	clear_tex_ua_sr_init_cnt_ary_{},
	clear_samp_sr_(nullptr),
	clear_samp_sr_ary_{},
	vsync_flg_(true)
{
	tml::MemoryUtil::Clear(&this->adapter_desc_, 1U);
	tml::MemoryUtil::Clear(&this->swap_chain_desc_, 1U);
	this->device_future_lv_ = static_cast<D3D_FEATURE_LEVEL>(0);

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::GraphicManager::~GraphicManager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::GraphicManager::Release(void)
{
	if (this->clear_samp_sr_ != nullptr) {
		this->clear_samp_sr_->Release();

		this->clear_samp_sr_ = nullptr;
		this->clear_samp_sr_ary_.fill(this->clear_samp_sr_);
	}

	if (this->clear_tex_ua_sr_ != nullptr) {
		this->clear_tex_ua_sr_->Release();

		this->clear_tex_ua_sr_ = nullptr;
		this->clear_tex_ua_sr_ary_.fill(this->clear_tex_ua_sr_);
		this->clear_tex_ua_sr_init_cnt_ary_.fill(static_cast<UINT>(-1));
	}

	if (this->clear_tex_sr_ != nullptr) {
		this->clear_tex_sr_->Release();

		this->clear_tex_sr_ = nullptr;
		this->clear_tex_sr_ary_.fill(this->clear_tex_sr_);
	}

	if (this->clear_dt_ != nullptr) {
		this->clear_dt_->Release();

		this->clear_dt_ = nullptr;
		this->clear_dt_ary_.fill(this->clear_dt_);
	}

	if (this->clear_rt_ != nullptr) {
		this->clear_rt_->Release();

		this->clear_rt_ = nullptr;
		this->clear_rt_ary_.fill(this->clear_rt_);
	}

	if (this->swap_chain_ != nullptr) {
		this->swap_chain_->Release();

		this->swap_chain_ = nullptr;
	}

	if (this->device_context_ != nullptr) {
		this->device_context_->Release();

		this->device_context_ = nullptr;
	}

	if (this->device_ != nullptr) {
		this->device_->Release();

		this->device_ = nullptr;
	}

	if (this->adapter_ != nullptr) {
		this->adapter_->Release();

		this->adapter_ = nullptr;
	}

	if (this->factory_ != nullptr) {
		this->factory_->Release();

		this->factory_ = nullptr;
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::GraphicManager::Init(void)
{
	this->Release();

	tml::MemoryUtil::Clear(&this->adapter_desc_, 1U);
	tml::MemoryUtil::Clear(&this->swap_chain_desc_, 1U);
	this->device_future_lv_ = static_cast<D3D_FEATURE_LEVEL>(0);
	this->vsync_flg_ = false;

	return;
}


/**
 * @brief Create�֐�
 * @param wnd_handle (window_handle)
 * @param wnd_w (window_width)
 * @param wnd_h (window_height)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::GraphicManager::Create(const HWND wnd_handle, const UINT wnd_w, const UINT wnd_h)
{
	this->Init();

	{// Factory Create
		if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&this->factory_)))) {
			this->Init();

			return (-1);
		}
	}

	{// Adapter Create
		UINT adapter_index = 0U;

		while (SUCCEEDED(this->factory_->EnumAdapters1(adapter_index, &this->adapter_))) {
			this->adapter_->GetDesc1(&this->adapter_desc_);

			if (this->adapter_desc_.Flags == DXGI_ADAPTER_FLAG_NONE) {
				break;
			}

			this->adapter_->Release();

			this->adapter_ = nullptr;

			++adapter_index;
		}

		if (this->adapter_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// Device Create
		UINT device_flg = 0U;

		if (tml::ConstantUtil::LIBRARY::DEBUG_FLAG) {
			device_flg = D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG;
		} else {
			device_flg = D3D11_CREATE_DEVICE_SINGLETHREADED;
		}

		std::array<D3D_FEATURE_LEVEL, 1U> device_future_lv_ary = {
			D3D_FEATURE_LEVEL_11_0
		};

		if (FAILED(D3D11CreateDevice(this->adapter_, D3D_DRIVER_TYPE_UNKNOWN, nullptr, device_flg, device_future_lv_ary.data(), device_future_lv_ary.size(), D3D11_SDK_VERSION, &this->device_, &this->device_future_lv_, &this->device_context_))) {
			this->Init();

			return (-1);
		}
	}

	{// SwapChain Create
		DXGI_MODE_DESC mode_desc = {};

		mode_desc.Width = wnd_w;
		mode_desc.Height = wnd_h;
		mode_desc.RefreshRate.Numerator = 60U;
		mode_desc.RefreshRate.Denominator = 1U;
		mode_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		mode_desc.Scaling = DXGI_MODE_SCALING_CENTERED;

		DXGI_SAMPLE_DESC ms_desc = {};
		UINT ms_max_cnt = 1U;
		//UINT ms_max_cnt = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;

		for (UINT ms_cnt = 1U; ms_cnt <= ms_max_cnt; ms_cnt <<= 1) {
			UINT ms_quality = 0U;

			if (SUCCEEDED(this->device_->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, ms_cnt, &ms_quality))) {
				if (ms_quality > 0) {
					ms_desc.Count = ms_cnt;
					ms_desc.Quality = ms_quality - 1U;
				}
			}
		}

		if (ms_desc.Count <= 0U) {
			this->Init();

			return (-1);
		}

		this->swap_chain_desc_.BufferDesc = mode_desc;
		this->swap_chain_desc_.SampleDesc = ms_desc;
		this->swap_chain_desc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_UNORDERED_ACCESS;
		this->swap_chain_desc_.BufferCount = 1U;
		this->swap_chain_desc_.OutputWindow = wnd_handle;
		this->swap_chain_desc_.Windowed = true;
		this->swap_chain_desc_.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		this->swap_chain_desc_.Flags = 0U;

		if (FAILED(this->factory_->CreateSwapChain(this->device_, &this->swap_chain_desc_, &this->swap_chain_))) {
			this->Init();

			return (-1);
		}
	}

	{// ClearRT Create
		this->clear_rt_ = nullptr;
		this->clear_rt_ary_.fill(this->clear_rt_);
	}

	{// ClearDT Create
		this->clear_dt_ = nullptr;
		this->clear_dt_ary_.fill(this->clear_dt_);
	}

	{// ClearTextureSR Create
		this->clear_tex_sr_ = nullptr;
		this->clear_tex_sr_ary_.fill(this->clear_tex_sr_);
	}

	{// ClearTextureUASR Create
		this->clear_tex_ua_sr_ = nullptr;
		this->clear_tex_ua_sr_ary_.fill(this->clear_tex_ua_sr_);
		this->clear_tex_ua_sr_init_cnt_ary_.fill(static_cast<UINT>(-1));
	}

	{// ClearSamplerSR Create
		CD3D11_SAMPLER_DESC clear_samp_sr_desc = CD3D11_SAMPLER_DESC(CD3D11_DEFAULT());

		clear_samp_sr_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

		if (FAILED(this->device_->CreateSamplerState(&clear_samp_sr_desc, &this->clear_samp_sr_))) {
			this->Init();

			return (-1);
		}

		this->clear_samp_sr_ary_.fill(this->clear_samp_sr_);
	}

	this->device_context_->OMSetRenderTargets(this->clear_rt_ary_.size(), this->clear_rt_ary_.data(), this->clear_dt_ary_[0]);
	this->device_context_->VSSetShader(nullptr, nullptr, 0U);
	this->device_context_->HSSetShader(nullptr, nullptr, 0U);
	this->device_context_->DSSetShader(nullptr, nullptr, 0U);
	this->device_context_->GSSetShader(nullptr, nullptr, 0U);
	this->device_context_->PSSetShader(nullptr, nullptr, 0U);
	this->device_context_->PSSetShaderResources(0U, this->clear_tex_sr_ary_.size(), this->clear_tex_sr_ary_.data());
	this->device_context_->PSSetSamplers(0U, this->clear_samp_sr_ary_.size(), this->clear_samp_sr_ary_.data());
	this->device_context_->CSSetShader(nullptr, nullptr, 0U);
	this->device_context_->CSSetShaderResources(0U, this->clear_tex_sr_ary_.size(), this->clear_tex_sr_ary_.data());
	this->device_context_->CSSetUnorderedAccessViews(0U, this->clear_tex_ua_sr_ary_.size(), this->clear_tex_ua_sr_ary_.data(), this->clear_tex_ua_sr_init_cnt_ary_.data());
	this->device_context_->CSSetSamplers(0U, this->clear_samp_sr_ary_.size(), this->clear_samp_sr_ary_.data());

	return (0);
}


/**
 * @brief StartDraw�֐�
 * @return continue_flg (continue_flag)<br>
 * false=�p������,true=�p���L��
 */
bool tml::GraphicManager::StartDraw(void)
{
	bool continue_flg = false;

	return (continue_flg);
}


/**
 * @brief EndDraw�֐�
 */
void tml::GraphicManager::EndDraw(void)
{
	return;
}


/**
 * @brief SwapDraw�֐�
 */
void tml::GraphicManager::SwapDraw(void)
{
	this->swap_chain_->Present(this->vsync_flg_, 0U);

	return;
}
