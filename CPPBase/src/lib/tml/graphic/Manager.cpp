/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "Shader.h"
#include "SystemShaderConstantBuffer.h"
#include "ModelShaderConstantBuffer.h"
#include "CameraShaderStructuredBuffer.h"
#include "LightShaderStructuredBuffer.h"
#include "FogShaderStructuredBuffer.h"
#include "ModelLayerShaderStructuredBuffer.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_size(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerDesc::~ManagerDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerDesc::Init(void)
{
	this->window_handle = nullptr;
	this->window_size = 0U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Manager::Manager() :
	factory_(nullptr),
	adapter_(nullptr),
	adapter_desc_{},
	swap_chain_(nullptr),
	swap_chain_desc_{},
	device_(nullptr),
	device_context_(nullptr),
	device_future_lv_(static_cast<D3D_FEATURE_LEVEL>(0)),
	clear_rt_(nullptr),
	clear_rt_ary_{},
	clear_dt_(nullptr),
	clear_dt_ary_{},
	clear_tex_sr_(nullptr),
	clear_tex_sr_ary_{},
	clear_tex_uasr_(nullptr),
	clear_tex_uasr_ary_{},
	clear_samp_sr_(nullptr),
	clear_samp_sr_ary_{},
	vsync_flg_(true),
	samp_quality_type_(tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::NONE),
	motion_quality_type_(tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE::NONE),
	motion_frame_rate_limit_(0U),
	shadow_quality_type_(tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE::NONE),
	shadow_per_(0.0f),
	shadow_rng_(0.0f),
	shadow_rng_exponent_(0.0f),
	shadow_size_(0.0f),
	shadow_interval_cnt_(0U),
	shadow_blur_weight_cnt_(0U),
	shadow_blur_dispersion_val_(0.0f),
	ao_quality_type_(tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE::NONE),
	ao_per_(0.0f),
	ao_rng_(0.0f),
	ao_rng_exponent_(0.0f),
	ao_ray_cnt_(0U),
	ao_ray_radius_(0.0f),
	ao_ray_radius_scale_(0.0f),
	ao_blur_weight_cnt_(0U),
	ao_blur_dispersion_val_(0.0f),
	ao_blur_sharp_val_(0.0f),
	bloom_quality_type_(tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE::NONE),
	bloom_per_(0.0f),
	bloom_blur_weight_cnt_(0U),
	bloom_blur_dispersion_val_(0.0f),
	aa_quality_type_(tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE::NONE),
	draw_vs_(nullptr),
	draw_vs_input_layout_(nullptr),
	draw_hs_(nullptr),
	draw_ds_(nullptr),
	draw_gs_(nullptr),
	draw_ps_(nullptr),
	draw_camera_(nullptr),
	draw_light_cnt_(0U),
	draw_fog_cnt_(0U),
	draw_model_cnt_(0U),
	cmp_cs_(nullptr)
{
	this->clear_tex_uasr_init_cnt_ary_.fill(static_cast<UINT>(-1));

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Manager::Release(void)
{
	for (auto &res_cont : this->res_cont_ary_) {
		for (auto &res : res_cont) {
			res->Init();
		}

		res_cont.clear();
	}

	if (this->clear_samp_sr_ != nullptr) {
		this->clear_samp_sr_->Release();

		this->clear_samp_sr_ = nullptr;
		this->clear_samp_sr_ary_.fill(nullptr);
	}

	if (this->clear_tex_uasr_ != nullptr) {
		this->clear_tex_uasr_->Release();

		this->clear_tex_uasr_ = nullptr;
		this->clear_tex_uasr_ary_.fill(nullptr);
	}

	if (this->clear_tex_sr_ != nullptr) {
		this->clear_tex_sr_->Release();

		this->clear_tex_sr_ = nullptr;
		this->clear_tex_sr_ary_.fill(nullptr);
	}

	if (this->clear_dt_ != nullptr) {
		this->clear_dt_->Release();

		this->clear_dt_ = nullptr;
		this->clear_dt_ary_.fill(nullptr);
	}

	if (this->clear_rt_ != nullptr) {
		this->clear_rt_->Release();

		this->clear_rt_ = nullptr;
		this->clear_rt_ary_.fill(nullptr);
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
 * @brief Init関数
 */
void tml::graphic::Manager::Init(void)
{
	this->Release();

	this->common.Init();

	tml::MemoryUtil::Clear(&this->adapter_desc_, 1U);
	tml::MemoryUtil::Clear(&this->swap_chain_desc_, 1U);
	this->device_future_lv_ = static_cast<D3D_FEATURE_LEVEL>(0);
	this->vsync_flg_ = true;
	this->samp_quality_type_ = tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::NONE;
	this->motion_quality_type_ = tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE::NONE;
	this->motion_frame_rate_limit_ = 0U;
	this->shadow_quality_type_ = tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE::NONE;
	this->shadow_per_ = 0.0f;
	this->shadow_rng_ = 0.0f;
	this->shadow_rng_exponent_ = 0.0f;
	this->shadow_size_ = 0.0f;
	this->shadow_interval_cnt_ = 0U;
	this->shadow_blur_weight_cnt_ = 0U;
	this->shadow_blur_dispersion_val_ = 0.0f;
	this->shadow_vp_.Init();
	this->ao_quality_type_ = tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE::NONE;
	this->ao_per_ = 0.0f;
	this->ao_rng_ = 0.0f;
	this->ao_rng_exponent_ = 0.0f;
	this->ao_ray_cnt_ = 0U;
	this->ao_ray_radius_ = 0.0f;
	this->ao_ray_radius_scale_ = 0.0f;
	this->ao_blur_weight_cnt_ = 0U;
	this->ao_blur_dispersion_val_ = 0.0f;
	this->ao_blur_sharp_val_ = 0.0f;
	this->bloom_quality_type_ = tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE::NONE;
	this->bloom_per_ = 0.0f;
	this->bloom_blur_weight_cnt_ = 0U;
	this->bloom_blur_dispersion_val_ = 0.0f;
	this->aa_quality_type_ = tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE::NONE;
	this->draw_vs_ = nullptr;
	this->draw_vs_input_layout_ = nullptr;
	this->draw_hs_ = nullptr;
	this->draw_ds_ = nullptr;
	this->draw_gs_ = nullptr;
	this->draw_ps_ = nullptr;
	this->draw_camera_ = nullptr;
	this->draw_model_cnt_ = 0U;
	this->draw_model_cont_.clear();
	this->draw_light_cnt_ = 0U;
	this->draw_light_cont_.clear();
	this->draw_fog_cnt_ = 0U;
	this->draw_fog_cont_.clear();
	this->cmp_cs_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Manager::Create(const tml::graphic::ManagerDesc &desc)
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

		mode_desc.Width = desc.window_size.x;
		mode_desc.Height = desc.window_size.y;
		mode_desc.RefreshRate.Numerator = 60U;
		mode_desc.RefreshRate.Denominator = 1U;
		mode_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		mode_desc.Scaling = DXGI_MODE_SCALING_CENTERED;

		DXGI_SAMPLE_DESC ms_desc = {};
		UINT ms_limit = 1U;
		//UINT ms_limit = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;

		for (UINT ms_cnt = 1U; ms_cnt <= ms_limit; ms_cnt <<= 1) {
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
		this->swap_chain_desc_.OutputWindow = desc.window_handle;
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
		this->clear_tex_uasr_ = nullptr;
		this->clear_tex_uasr_ary_.fill(this->clear_tex_uasr_);
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
	this->device_context_->CSSetUnorderedAccessViews(0U, this->clear_tex_uasr_ary_.size(), this->clear_tex_uasr_ary_.data(), this->clear_tex_uasr_init_cnt_ary_.data());
	this->device_context_->CSSetSamplers(0U, this->clear_samp_sr_ary_.size(), this->clear_samp_sr_ary_.data());

	this->samp_quality_type_ = tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::ANISOTROPIC2;

	this->motion_quality_type_ = tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE::MEDIUM;

	switch (this->motion_quality_type_) {
	case tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE::LOW: {
		this->motion_frame_rate_limit_ = 30U;

		break;
	}
	case tml::ConstantUtil::GRAPHIC::MOTION_QUALITY_TYPE::MEDIUM: {
		this->motion_frame_rate_limit_ = 60U;

		break;
	}
	default: {
		this->Init();

		return (-1);
	}
	}

	this->shadow_quality_type_ = tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE::MEDIUM;

	switch (this->shadow_quality_type_) {
	case tml::ConstantUtil::GRAPHIC::SHADOW_QUALITY_TYPE::MEDIUM: {
		this->shadow_per_ = 1.0f;
		this->shadow_rng_ = 50.0f;
		this->shadow_rng_exponent_ = 4.0f;
		this->shadow_size_ = 1024.0f;
		this->shadow_interval_cnt_ = 3U;
		this->shadow_blur_weight_cnt_ = 3U;
		this->shadow_blur_dispersion_val_ = 1.0f;

		break;
	}
	}

	if (this->shadow_per_ > 0.0f) {
		this->shadow_vp_.Set(tml::XMFLOAT2EX(0.0f), tml::XMFLOAT2EX(this->shadow_size_));
	}

	this->ao_quality_type_ = tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE::MEDIUM;

	switch (this->ao_quality_type_) {
	case tml::ConstantUtil::GRAPHIC::AO_QUALITY_TYPE::MEDIUM: {
		this->ao_per_ = 1.0f;
		this->ao_rng_ = 20.0f;
		this->ao_rng_exponent_ = 4.0f;
		this->ao_ray_cnt_ = 10U;
		this->ao_ray_radius_ = 0.4f;
		this->ao_ray_radius_scale_ = 300.0f;
		this->ao_blur_weight_cnt_ = 4U;
		this->ao_blur_dispersion_val_ = 8.0f;
		this->ao_blur_sharp_val_ = 0.5f;

		break;
	}
	}

	this->bloom_quality_type_ = tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE::MEDIUM;

	switch (this->bloom_quality_type_) {
	case tml::ConstantUtil::GRAPHIC::BLOOM_QUALITY_TYPE::MEDIUM: {
		this->bloom_per_ = 1.0f;
		this->bloom_blur_weight_cnt_ = 8U;
		this->bloom_blur_dispersion_val_ = 4.0f;

		break;
	}
	}

	this->aa_quality_type_ = tml::ConstantUtil::GRAPHIC::AA_QUALITY_TYPE::FXAA;

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	this->SetDrawShaderConstantBuffer(this->common.system_shader_constant_buffer.get(), tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_ | tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_, tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM);

	return (0);
}


/**
 * @brief Update関数
 */
void tml::graphic::Manager::Update(void)
{
	this->swap_chain_->Present(this->vsync_flg_, 0U);

	this->draw_camera_ = nullptr;
	this->draw_light_cnt_ = 0U;
	this->draw_fog_cnt_ = 0U;
	this->draw_model_cnt_ = 0U;

	/*
	mpc_p::graphic::DrawStage draw_stage;

	this->SetDrawStage(&draw_stage);

	while (this->StartDraw()) {
		if (this->IsDrawStage(mpc_p::graphic::_DrawStage::_NUMBER::_INIT)) { //初期化の時
			this->SetDrawFinishTarget(this->item_storage.main_rt_tex);
			this->SetDrawCamera(this->item_storage.wait_camera);

			this->item_storage.light_scb->SetElement(this->item_storage.light_ssb->GetElementCount());
			this->item_storage.light_scb->UpdateBuffer();

			this->item_storage.fog_scb->SetElement(this->item_storage.fog_ssb->GetElementCount());
			this->item_storage.fog_scb->UpdateBuffer();

			this->item_storage.light_ssb->UpdateBuffer();
			this->item_storage.fog_ssb->UpdateBuffer();
			this->item_storage.shadow_ssb->UpdateBuffer();
			this->item_storage.model_material_ssb->UpdateBuffer();

			this->draw_finish_rt_tex->ClearRenderTarget(XMFLOAT4EX(0.0f, 0.0f, 0.0f, 1.0f));

			this->SetDrawStageNumber(mpc_p::graphic::_DrawStage::_NUMBER::_FORWARD_2D);
		}

		if (this->item_storage.sprite_model->IsDrawable()) { //描画可の時
			auto &sprite_model = this->item_storage.sprite_model;
			auto sprite_model_layer = sprite_model->GetLayerContainer().GetElementFast(0U);
			std::array<mpc_p::graphic::Texture *, mpc_p::graphic::_SpriteModel::_TEXTURE_INDEX::_COUNT> sprite_model_tex_ary = {
				this->item_storage.wait_tex
			};
			auto &sprite_model_tex_size = sprite_model_tex_ary[0]->GetSize();

			sprite_model->SetDrawTexture(sprite_model_tex_ary.size(), sprite_model_tex_ary.data());

			this->GetWorldMatrix2D(&this->GetDrawStage().GetWorldMatrix(), (this->GetProcess()->GetSize() * 0.5f) - (sprite_model_tex_size * 0.5f), 0.0f, sprite_model_tex_size);
			sprite_model->SetDrawTransparentPercent(0.8f);
			sprite_model->Draw(this->GetDrawStage().GetWorldMatrix());

			if (time_per > 0.0f) { //時間率有りの時
				this->GetWorldMatrix2D(&this->GetDrawStage().GetWorldMatrix(), (this->GetProcess()->GetSize() * 0.5f) - (sprite_model_tex_size * 0.5f), 0.0f, XMFLOAT2EX(sprite_model_tex_size.x * time_per, sprite_model_tex_size.y));
				sprite_model_layer->SetDrawTextureScale(XMFLOAT2EX(time_per, 1.0f));
				sprite_model->SetDrawTransparentPercent(0.0f);
				sprite_model->Draw(this->GetDrawStage().GetWorldMatrix());

				sprite_model_layer->ResetDrawTextureScale();
			}

			sprite_model->ResetDrawTransparentPercent();
			sprite_model->ResetDrawTexture();
		}
	}

	this->EndDraw();
	this->SwapDraw();
	*/

	return;
}


/**
 * @brief GetBuffer関数
 * @param dst_buf (dst_buffer)
 * @param dst_msr (dst_mapped_subresource)
 * @param buf (buffer)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_buf (dst_buffer)
 */
tml::DynamicBuffer &tml::graphic::Manager::GetBuffer(tml::DynamicBuffer &dst_buf, D3D11_MAPPED_SUBRESOURCE &dst_msr, ID3D11Buffer *buf, INT *dst_res)
{
	dst_buf.Init();
	tml::MemoryUtil::Clear(&dst_msr, 1U);

	if (buf == nullptr) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	ID3D11Buffer *cpu_buf = nullptr;
	D3D11_BUFFER_DESC cpu_buf_desc;

	buf->GetDesc(&cpu_buf_desc);

	cpu_buf_desc.Usage = D3D11_USAGE_STAGING;
	cpu_buf_desc.BindFlags = 0U;
	cpu_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	cpu_buf_desc.MiscFlags = 0U;

	if (FAILED(this->device_->CreateBuffer(&cpu_buf_desc, nullptr, &cpu_buf))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	this->device_context_->CopyResource(cpu_buf, buf);

	D3D11_MAPPED_SUBRESOURCE msr;

	if (FAILED(this->device_context_->Map(cpu_buf, 0U, D3D11_MAP_READ, 0U, &msr))) {
		cpu_buf->Release();

		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	dst_buf.Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
	dst_msr = msr;
	dst_msr.pData = nullptr;

	this->device_context_->Unmap(cpu_buf, 0U);

	cpu_buf->Release();

	tml::SetResult(dst_res, 0);

	return (dst_buf);
}


/**
 * @brief GetBuffer関数
 * @param dst_buf (dst_buffer)
 * @param dst_msr (dst_mapped_subresource)
 * @param tex (texture)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_buf (dst_buffer)
 */
tml::DynamicBuffer &tml::graphic::Manager::GetBuffer(tml::DynamicBuffer &dst_buf, D3D11_MAPPED_SUBRESOURCE &dst_msr, ID3D11Texture2D *tex, INT *dst_res)
{
	dst_buf.Init();
	tml::MemoryUtil::Clear(&dst_msr, 1U);

	if (tex == nullptr) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	ID3D11Texture2D *cpu_tex = nullptr;
	CD3D11_TEXTURE2D_DESC cpu_tex_desc;

	tex->GetDesc(&cpu_tex_desc);

	cpu_tex_desc.Usage = D3D11_USAGE_STAGING;
	cpu_tex_desc.BindFlags = 0U;
	cpu_tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	cpu_tex_desc.MiscFlags = 0U;

	if (FAILED(this->device_->CreateTexture2D(&cpu_tex_desc, nullptr, &cpu_tex))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	this->device_context_->CopyResource(cpu_tex, tex);

	D3D11_MAPPED_SUBRESOURCE msr;

	if (FAILED(this->device_context_->Map(cpu_tex, 0U, D3D11_MAP_READ, 0U, &msr))) {
		cpu_tex->Release();

		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	dst_buf.Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
	dst_msr = msr;
	dst_msr.pData = nullptr;

	this->device_context_->Unmap(cpu_tex, 0U);

	cpu_tex->Release();

	tml::SetResult(dst_res, 0);

	return (dst_buf);
}


/**
 * @brief GetBuffer関数
 * @param dst_buf_cont (dst_buffer_container)
 * @param dst_msr_cont (dst_mapped_subresource_container)
 * @param tex (texture)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_buf_cont (dst_buffer_container)
 */
std::vector<tml::DynamicBuffer> &tml::graphic::Manager::GetBuffer(std::vector<tml::DynamicBuffer> &dst_buf_cont, std::vector<D3D11_MAPPED_SUBRESOURCE> &dst_msr_cont, ID3D11Texture2D *tex, INT *dst_res)
{
	dst_buf_cont.clear();
	dst_buf_cont.clear();

	if (tex == nullptr) {
		tml::SetResult(dst_res, -1);

		return (dst_buf_cont);
	}

	ID3D11Texture2D *cpu_tex = nullptr;
	CD3D11_TEXTURE2D_DESC cpu_tex_desc;

	tex->GetDesc(&cpu_tex_desc);

	cpu_tex_desc.Usage = D3D11_USAGE_STAGING;
	cpu_tex_desc.BindFlags = 0U;
	cpu_tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	cpu_tex_desc.MiscFlags = 0U;

	if (FAILED(this->device_->CreateTexture2D(&cpu_tex_desc, nullptr, &cpu_tex))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf_cont);
	}

	this->device_context_->CopyResource(cpu_tex, tex);

	dst_buf_cont.resize(cpu_tex_desc.MipLevels);
	dst_msr_cont.resize(cpu_tex_desc.MipLevels);

	for (UINT mm_i = 0U; mm_i < cpu_tex_desc.MipLevels; ++mm_i) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (FAILED(this->device_context_->Map(cpu_tex, mm_i, D3D11_MAP_READ, 0U, &msr))) {
			cpu_tex->Release();

			dst_buf_cont.clear();
			dst_buf_cont.clear();

			tml::SetResult(dst_res, -1);

			return (dst_buf_cont);
		}

		dst_buf_cont[mm_i].Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
		dst_msr_cont[mm_i] = msr;
		dst_msr_cont[mm_i].pData = nullptr;

		this->device_context_->Unmap(cpu_tex, mm_i);
	}

	cpu_tex->Release();

	tml::SetResult(dst_res, 0);

	return (dst_buf_cont);
}


/**
 * @brief SetDrawShader関数
 * @param shader (shader)
 */
void tml::graphic::Manager::SetDrawShader(tml::graphic::Shader *shader)
{
	if (shader->GetVertexShader() != this->draw_vs_) {
		this->draw_vs_ = shader->GetVertexShader();
		this->draw_vs_input_layout_ = shader->GetVertexShaderInputLayout();

		this->device_context_->VSSetShader(this->draw_vs_, nullptr, 0U);
		this->device_context_->IASetInputLayout(this->draw_vs_input_layout_);
	}

	if (shader->GetHullShader() != this->draw_hs_) {
		this->draw_hs_ = shader->GetHullShader();

		this->device_context_->HSSetShader(this->draw_hs_, nullptr, 0U);
	}

	if (shader->GetDomainShader() != this->draw_ds_) {
		this->draw_ds_ = shader->GetDomainShader();

		this->device_context_->DSSetShader(this->draw_ds_, nullptr, 0U);
	}

	if (shader->GetGeometryShader() != this->draw_gs_) {
		this->draw_gs_ = shader->GetGeometryShader();

		this->device_context_->GSSetShader(this->draw_gs_, nullptr, 0U);
	}

	if (shader->GetPixelShader() != this->draw_ps_) {
		this->draw_ps_ = shader->GetPixelShader();

		this->device_context_->PSSetShader(this->draw_ps_, nullptr, 0U);
	}

	if (this->cmp_cs_ != nullptr) {
		this->cmp_cs_ = nullptr;

		this->device_context_->CSSetShader(this->cmp_cs_, nullptr, 0U);
	}

	return;
}


/**
 * @brief SetDrawShaderConstantBuffer関数
 * @param scb (shader_constant_buffer)
 * @param shader_type_flg (shader_type_flag)
 * @param sr_index (sr_index)
 */
void tml::graphic::Manager::SetDrawShaderConstantBuffer(tml::graphic::ShaderConstantBuffer *scb, const tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG shader_type_flg, const UINT sr_index)
{
	ID3D11Buffer *buf_ary[1] = {scb->GetBuffer()};

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_)) {
		this->device_context_->VSSetConstantBuffers(sr_index, 1U, buf_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::HULL_)) {
		this->device_context_->HSSetConstantBuffers(sr_index, 1U, buf_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::DOMAIN_)) {
		this->device_context_->DSSetConstantBuffers(sr_index, 1U, buf_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::GEOMETRY_)) {
		this->device_context_->GSSetConstantBuffers(sr_index, 1U, buf_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_)) {
		this->device_context_->PSSetConstantBuffers(sr_index, 1U, buf_ary);
	}

	return;
}


/**
 * @brief SetDrawShaderStructuredBuffer関数
 * @param ssb (shader_structured_buffer)
 * @param shader_type_flg (shader_type_flag)
 * @param sr_index (sr_index)
 */
void tml::graphic::Manager::SetDrawShaderStructuredBuffer(tml::graphic::ShaderStructuredBuffer *ssb, const tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG shader_type_flg, const UINT sr_index)
{
	ID3D11ShaderResourceView *sr_ary[1] = {ssb->GetSR()};

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_)) {
		this->device_context_->VSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + sr_index, 1U, sr_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::HULL_)) {
		this->device_context_->HSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + sr_index, 1U, sr_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::DOMAIN_)) {
		this->device_context_->DSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + sr_index, 1U, sr_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::GEOMETRY_)) {
		this->device_context_->GSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + sr_index, 1U, sr_ary);
	}

	if (static_cast<bool>(shader_type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_)) {
		this->device_context_->PSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + sr_index, 1U, sr_ary);
	}

	return;
}


/**
 * @brief SetComputeShader関数
 * @param shader (shader)
 */
void tml::graphic::Manager::SetComputeShader(tml::graphic::Shader *shader)
{
	if (this->draw_vs_ != nullptr) {
		this->draw_vs_ = nullptr;

		this->device_context_->VSSetShader(this->draw_vs_, nullptr, 0U);
	}

	if (this->draw_hs_ != nullptr) {
		this->draw_hs_ = nullptr;

		this->device_context_->HSSetShader(this->draw_hs_, nullptr, 0U);
	}

	if (this->draw_ds_ != nullptr) {
		this->draw_ds_ = nullptr;

		this->device_context_->DSSetShader(this->draw_ds_, nullptr, 0U);
	}

	if (this->draw_gs_ != nullptr) {
		this->draw_gs_ = nullptr;

		this->device_context_->GSSetShader(this->draw_gs_, nullptr, 0U);
	}

	if (this->draw_ps_ != nullptr) {
		this->draw_ps_ = nullptr;

		this->device_context_->PSSetShader(this->draw_ps_, nullptr, 0U);
	}

	if (shader->GetComputeShader() != this->cmp_cs_) {
		this->cmp_cs_ = shader->GetComputeShader();

		this->device_context_->CSSetShader(this->cmp_cs_, nullptr, 0U);
	}

	return;
}


/**
 * @brief SetComputeShaderConstantBuffer関数
 * @param scb (shader_constant_buffer)
 * @param sr_index (sr_index)
 */
void tml::graphic::Manager::SetComputeShaderConstantBuffer(tml::graphic::ShaderConstantBuffer *scb, const UINT sr_index)
{
	ID3D11Buffer *buf_ary[1] = {scb->GetBuffer()};

	this->device_context_->CSSetConstantBuffers(sr_index, 1U, buf_ary);

	return;
}


/**
 * @brief SetComputeShaderStructuredBuffer関数
 * @param ssb (shader_structured_buffer)
 * @param sr_index (sr_index)
 */
void tml::graphic::Manager::SetComputeShaderStructuredBuffer(tml::graphic::ShaderStructuredBuffer *ssb, const UINT sr_index)
{
	ID3D11ShaderResourceView *sr_ary[1] = {ssb->GetSR()};

	this->device_context_->CSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + sr_index, 1U, sr_ary);

	return;
}
