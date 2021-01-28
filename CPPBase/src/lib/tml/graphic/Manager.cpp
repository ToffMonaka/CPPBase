/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "SystemShaderConstantBuffer.h"
#include "ModelShaderConstantBuffer.h"
#include "CameraShaderStructuredBuffer.h"
#include "LightShaderStructuredBuffer.h"
#include "FogShaderStructuredBuffer.h"
#include "ModelLayerShaderStructuredBuffer.h"
#include "Camera.h"
#include "Light.h"
#include "Fog.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Sampler.h"
#include "ScreenModel.h"
#include "SpriteModel.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_size(0U),
	vsync_flag(true)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ManagerDesc::~ManagerDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ManagerDesc::Init(void)
{
	this->window_handle = nullptr;
	this->window_size = 0U;
	this->vsync_flag = true;

	return;
}


/**
 * @brief �R���X�g���N�^
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
	clear_rt_(nullptr),
	clear_rt_ary_{},
	clear_dt_(nullptr),
	clear_tex_sr_(nullptr),
	clear_tex_sr_ary_{},
	clear_tex_uasr_(nullptr),
	clear_tex_uasr_ary_{},
	clear_tex_uasr_init_cnt_ary_{},
	clear_samp_sr_(nullptr),
	clear_samp_sr_ary_{},
	draw_stage_type_(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE),
	draw_stage_dat_(nullptr),
	draw_vp_cnt_(0U),
	draw_vp_ary_{},
	draw_rt_cnt_(0U),
	draw_rt_ary_{},
	draw_dt_(nullptr),
	draw_rs_(nullptr),
	draw_bs_(nullptr),
	draw_ds_(nullptr),
	draw_shader_vs_(nullptr),
	draw_shader_vs_input_layout_(nullptr),
	draw_shader_hs_(nullptr),
	draw_shader_ds_(nullptr),
	draw_shader_gs_(nullptr),
	draw_shader_ps_(nullptr),
	draw_camera_(nullptr),
	draw_light_cnt_(0U),
	draw_fog_cnt_(0U),
	draw_model_cnt_(0U),
	cmp_shader_cs_(nullptr)
{
	this->clear_vp_ = CD3D11_VIEWPORT(0.0f, 0.0f, 0.0f, 0.0f, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH);
	this->clear_vp_ary_.fill(this->clear_vp_);

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
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
		this->clear_tex_uasr_init_cnt_ary_.fill(0U);
	}

	if (this->clear_tex_sr_ != nullptr) {
		this->clear_tex_sr_->Release();

		this->clear_tex_sr_ = nullptr;
		this->clear_tex_sr_ary_.fill(nullptr);
	}

	if (this->clear_dt_ != nullptr) {
		this->clear_dt_->Release();

		this->clear_dt_ = nullptr;
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
 * @brief Init�֐�
 */
void tml::graphic::Manager::Init(void)
{
	this->Release();

	this->common.Init();

	tml::MemoryUtil::Clear(&this->adapter_desc_, 1U);
	tml::MemoryUtil::Clear(&this->swap_chain_desc_, 1U);
	this->device_future_lv_ = static_cast<D3D_FEATURE_LEVEL>(0);
	this->vsync_flg_ = true;
	this->vp_.Init();
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
	this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE;
	this->draw_stage_dat_ = nullptr;
	this->draw_vp_cnt_ = 0U;
	this->draw_rt_cnt_ = 0U;
	this->draw_dt_ = nullptr;
	this->draw_rs_ = nullptr;
	this->draw_bs_ = nullptr;
	this->draw_ds_ = nullptr;
	this->draw_shader_vs_ = nullptr;
	this->draw_shader_vs_input_layout_ = nullptr;
	this->draw_shader_hs_ = nullptr;
	this->draw_shader_ds_ = nullptr;
	this->draw_shader_gs_ = nullptr;
	this->draw_shader_ps_ = nullptr;
	this->draw_camera_ = nullptr;
	this->draw_model_cnt_ = 0U;
	this->draw_model_cont_.clear();
	this->draw_light_cnt_ = 0U;
	this->draw_light_cont_.clear();
	this->draw_fog_cnt_ = 0U;
	this->draw_fog_cont_.clear();
	this->cmp_shader_cs_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
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

	this->vp_.Set(tml::XMFLOAT2EX(0.0f), tml::XMFLOAT2EX(static_cast<FLOAT>(desc.window_size.x), static_cast<FLOAT>(desc.window_size.y)));
	this->vsync_flg_ = desc.vsync_flag;

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

	{// ClearRT Create
		this->clear_rt_ = nullptr;
		this->clear_rt_ary_.fill(this->clear_rt_);
	}

	{// ClearDT Create
		this->clear_dt_ = nullptr;
	}

	{// ClearTextureSR Create
		this->clear_tex_sr_ = nullptr;
		this->clear_tex_sr_ary_.fill(this->clear_tex_sr_);
	}

	{// ClearTextureUASR Create
		this->clear_tex_uasr_ = nullptr;
		this->clear_tex_uasr_ary_.fill(this->clear_tex_uasr_);
		this->clear_tex_uasr_init_cnt_ary_.fill(static_cast<UINT>(-1));
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

	this->device_context_->OMSetRenderTargets(this->clear_rt_ary_.size(), this->clear_rt_ary_.data(), this->clear_dt_);
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

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	this->SetDrawShaderConstantBuffer(tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_ | tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_, tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, this->common.system_shader_constant_buffer.get());
	this->SetDrawShaderStructuredBuffer(tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_ | tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::CAMERA, this->common.camera_shader_structured_buffer.get());
	this->SetDrawShaderStructuredBuffer(tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_ | tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::LIGHT, this->common.light_shader_structured_buffer.get());
	this->SetDrawShaderStructuredBuffer(tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_ | tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_, tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::FOG, this->common.fog_shader_structured_buffer.get());

	this->SetComputeShaderConstantBuffer(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, this->common.system_shader_constant_buffer.get());
	this->SetComputeShaderStructuredBuffer(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::CAMERA, this->common.camera_shader_structured_buffer.get());
	this->SetComputeShaderStructuredBuffer(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::LIGHT, this->common.light_shader_structured_buffer.get());
	this->SetComputeShaderStructuredBuffer(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::FOG, this->common.fog_shader_structured_buffer.get());

	return (0);
}


/**
 * @brief Update�֐�
 */
void tml::graphic::Manager::Update(void)
{
	XMVECTOR determinant;

	XMMATRIX w_mat;
	XMMATRIX v_mat_3d;
	XMMATRIX inv_v_mat_3d;
	XMMATRIX p_mat_3d;
	XMMATRIX v_mat_2d;
	XMMATRIX inv_vi_mat_2d;
	XMMATRIX p_mat_2d;

	tml::graphic::DRAW_STAGE_DATA draw_stage_dat(w_mat, v_mat_3d, inv_v_mat_3d, p_mat_3d, v_mat_2d, inv_vi_mat_2d, p_mat_2d);

	this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::INIT;
	this->draw_stage_dat_ = &draw_stage_dat;

	while (this->draw_stage_type_ != tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE) {
		switch (this->draw_stage_type_) {
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::INIT: {
			this->GetViewMatrix3D(this->draw_stage_dat_->view_matrix_3d, this->draw_camera_);
			this->draw_stage_dat_->inverse_view_matrix_3d = XMMatrixInverse(&determinant, this->draw_stage_dat_->view_matrix_3d);
			this->GetProjectionMatrix3D(this->draw_stage_dat_->projection_matrix_3d, this->draw_camera_);

			this->GetViewMatrix2D(this->draw_stage_dat_->view_matrix_2d, this->draw_camera_);
			this->draw_stage_dat_->inverse_view_matrix_2d = XMMatrixInverse(&determinant, this->draw_stage_dat_->view_matrix_2d);
			this->GetProjectionMatrix2D(this->draw_stage_dat_->projection_matrix_2d, this->draw_camera_);

			this->common.main_render_target_texture->ClearRenderTarget(XMFLOAT4EX(0.0f, 0.0f, 0.0f, 1.0f));
			this->common.main_depth_target_texture->ClearDepthTarget();

			this->common.system_shader_constant_buffer->SetElement(this->draw_light_cnt_, this->draw_fog_cnt_);
			this->common.system_shader_constant_buffer->UpdateBuffer();

			this->common.camera_shader_structured_buffer->SetElementCount(0U);
			this->common.camera_shader_structured_buffer->SetElement(0U, this->draw_camera_, this->draw_stage_dat_->view_matrix_3d, this->draw_stage_dat_->inverse_view_matrix_3d);
			this->common.camera_shader_structured_buffer->SetElement(1U, this->draw_camera_,this->draw_stage_dat_->view_matrix_2d, this->draw_stage_dat_->inverse_view_matrix_2d);
			this->common.camera_shader_structured_buffer->UpdateBuffer();

			this->common.light_shader_structured_buffer->SetElementCount(0U);

			for (UINT draw_light_i = 0U; draw_light_i < this->draw_light_cnt_; ++draw_light_i) {
				this->common.light_shader_structured_buffer->SetElement(draw_light_i, this->draw_light_cont_[draw_light_i]);
			}

			this->common.light_shader_structured_buffer->UpdateBuffer();

			this->common.fog_shader_structured_buffer->SetElementCount(0U);

			for (UINT draw_fog_i = 0U; draw_fog_i < this->draw_fog_cnt_; ++draw_fog_i) {
				this->common.fog_shader_structured_buffer->SetElement(draw_fog_i, this->draw_fog_cont_[draw_fog_i]);
			}

			this->common.fog_shader_structured_buffer->UpdateBuffer();

			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_cont_[draw_model_i]->DrawStageInit();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_3D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_3D: {
			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_cont_[draw_model_i]->DrawStageDeferred3D();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_SHADOW_3D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_SHADOW_3D: {
			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_cont_[draw_model_i]->DrawStageDeferredShadow3D();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_3D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_3D: {
			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_cont_[draw_model_i]->DrawStageForward3D();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D: {
			this->draw_stage_dat_->view_matrix = &this->draw_stage_dat_->view_matrix_2d;
			this->draw_stage_dat_->projection_matrixt = &this->draw_stage_dat_->projection_matrix_2d;

			this->PushDrawViewport(0U, &this->vp_);
			this->SetDrawViewport();
			this->PushDrawRenderTarget(0U, this->common.main_render_target_texture.get());
			this->SetDrawTarget();

			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_cont_[draw_model_i]->DrawStageForward2D();
			}

			this->ClearDrawViewport();
			this->ClearDrawTarget();

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE;
			this->draw_stage_dat_ = nullptr;

			break;
		}
		}
	}

	this->swap_chain_->Present(this->vsync_flg_, 0U);

	this->ClearDrawCamera();
	this->ClearDrawLight();
	this->ClearDrawFog();
	this->ClearDrawModel();

	return;
}


/**
 * @brief GetWorldMatrix3D�֐�
 * @param dst_mat (dst_matrix)
 * @param pos (position)
 * @param angle (angle)
 * @param scale (scale)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetWorldMatrix3D(XMMATRIX &dst_mat, const tml::XMFLOAT3EX &pos, const tml::XMFLOAT3EX &angle, const tml::XMFLOAT3EX &scale)
{
	dst_mat = XMMatrixTransformation(g_XMZero, g_XMIdentityR3, XMLoadFloat3(&scale), g_XMZero, XMQuaternionRotationRollPitchYaw(angle.x, angle.y, angle.z), XMLoadFloat3(&pos));

	return (dst_mat);
}


/**
 * @brief GetWorldMatrix3D�֐�
 * @param dst_mat (dst_matrix)
 * @param pos (position)
 * @param quat (quaternion)
 * @param scale (scale)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetWorldMatrix3D(XMMATRIX &dst_mat, const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat, const tml::XMFLOAT3EX &scale)
{
	dst_mat = XMMatrixTransformation(g_XMZero, g_XMIdentityR3, XMLoadFloat3(&scale), g_XMZero, XMLoadFloat4(&quat), XMLoadFloat3(&pos));

	return (dst_mat);
}


/**
 * @brief GetWorldMatrix2D�֐�
 * @param dst_mat (dst_matrix)
 * @param pos (position)
 * @param angle (angle)
 * @param scale (scale)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetWorldMatrix2D(XMMATRIX &dst_mat, const tml::XMFLOAT2EX &pos, const FLOAT angle, const tml::XMFLOAT2EX &scale)
{
	dst_mat = XMMatrixTransformation2D(g_XMZero, 0.0f, XMVectorSet(scale.x, scale.y, 1.0f, 0.0f), XMVectorSet(scale.x * 0.5f, -scale.y * 0.5f, 0.0f, 0.0f), angle, XMVectorSet(pos.x, -pos.y, 0.0f, 0.0f));

	return (dst_mat);
}


/**
 * @brief GetViewMatrix3D�֐�
 * @param dst_mat (dst_matrix)
 * @param camera (camera)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetViewMatrix3D(XMMATRIX &dst_mat, const tml::graphic::Camera *camera)
{
	dst_mat = XMMatrixLookToLH(XMLoadFloat3(&camera->position->Get()), XMLoadFloat3(&camera->position->GetZAxisVector()), XMLoadFloat3(&camera->position->GetYAxisVector()));

	return (dst_mat);
}


/**
 * @brief GetViewMatrix2D�֐�
 * @param dst_mat (dst_matrix)
 * @param camera (camera)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetViewMatrix2D(XMMATRIX &dst_mat, const tml::graphic::Camera *camera)
{
	dst_mat = XMMatrixIdentity();

	return (dst_mat);
}


/**
 * @brief GetProjectionMatrix3D�֐�
 * @param dst_mat (dst_matrix)
 * @param camera (camera)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetProjectionMatrix3D(XMMATRIX &dst_mat, const tml::graphic::Camera *camera)
{
	switch (camera->GetType()) {
	case tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::PERSPECTIVE: {
		dst_mat = XMMatrixPerspectiveFovLH(camera->GetFOVAngle(), camera->GetFOVSize().x / camera->GetFOVSize().y, camera->GetNearClip(), camera->GetFarClip());

		break;
	}
	case tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::ORTHOGRAPHIC: {
		dst_mat = XMMatrixOrthographicLH(camera->GetFOVSize().x, camera->GetFOVSize().y, camera->GetNearClip(), camera->GetFarClip());

		break;
	}
	default: {
		dst_mat = XMMatrixIdentity();

		break;
	}
	}

	return (dst_mat);
}


/**
 * @brief GetProjectionMatrix2D�֐�
 * @param dst_mat (dst_matrix)
 * @param camera (camera)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetProjectionMatrix2D(XMMATRIX &dst_mat, const tml::graphic::Camera *camera)
{
	switch (camera->GetType()) {
	case tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::PERSPECTIVE: {
		dst_mat = XMMatrixOrthographicOffCenterLH(0.0f, camera->GetFOVSize().x, -camera->GetFOVSize().y, 0.0f, 0.0f, 1.0f);

		break;
	}
	case tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::ORTHOGRAPHIC: {
		dst_mat = XMMatrixOrthographicOffCenterLH(0.0f, camera->GetFOVSize().x, -camera->GetFOVSize().y, 0.0f, 0.0f, 1.0f);

		break;
	}
	default: {
		dst_mat = XMMatrixIdentity();

		break;
	}
	}

	return (dst_mat);
}


/**
 * @brief GetBuffer�֐�
 * @param dst_buf (dst_buffer)
 * @param dst_msr (dst_mapped_subresource)
 * @param buf (buffer)
 * @param dst_res (dst_result)<br>
 * nullptr=�w�薳��,0����=���s
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
 * @brief GetBuffer�֐�
 * @param dst_buf (dst_buffer)
 * @param dst_msr (dst_mapped_subresource)
 * @param tex (texture)
 * @param dst_res (dst_result)<br>
 * nullptr=�w�薳��,0����=���s
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
 * @brief GetBuffer�֐�
 * @param dst_buf_cont (dst_buffer_container)
 * @param dst_msr_cont (dst_mapped_subresource_container)
 * @param tex (texture)
 * @param dst_res (dst_result)<br>
 * nullptr=�w�薳��,0����=���s
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
 * @brief PushDrawViewport�֐�
 * @param index (index)
 * @param vp (viewport)
 */
void tml::graphic::Manager::PushDrawViewport(const UINT index, tml::graphic::Viewport *vp)
{
	for (UINT index_i = this->draw_vp_cnt_; index_i < index; ++index_i) {
		this->draw_vp_ary_[index] = this->clear_vp_;
	}

	if (vp != nullptr) {
		this->draw_vp_cnt_ = index + 1U;
		this->draw_vp_ary_[index] = (*vp);
	} else {
		this->draw_vp_cnt_ = index + 1U;
		this->draw_vp_ary_[index] = this->clear_vp_;
	}

	return;
}


/**
 * @brief SetDrawViewport�֐�
 */
void tml::graphic::Manager::SetDrawViewport(void)
{
	if (this->draw_vp_cnt_ > 0U) {
		this->device_context_->RSSetViewports(this->draw_vp_cnt_, this->draw_vp_ary_.data());
	} else {
		this->device_context_->RSSetViewports(0U, nullptr);
	}

	return;
}


/**
 * @brief ClearDrawViewport�֐�
 */
void tml::graphic::Manager::ClearDrawViewport(void)
{
	if (this->draw_vp_cnt_ > 0U) {
		this->device_context_->RSSetViewports(0U, nullptr);

		this->draw_vp_cnt_ = 0U;
	}

	return;
}


/**
 * @brief PushDrawRenderTarget�֐�
 * @param index (index)
 * @param rt_tex (render_target_texture)
 */
void tml::graphic::Manager::PushDrawRenderTarget(const UINT index, tml::graphic::Texture *rt_tex)
{
	for (UINT index_i = this->draw_rt_cnt_; index_i < index; ++index_i) {
		this->draw_rt_ary_[index] = this->clear_rt_;
	}

	if (rt_tex != nullptr) {
		this->draw_rt_cnt_ = index + 1U;
		this->draw_rt_ary_[index] = rt_tex->GetRenderTarget();
	} else {
		this->draw_rt_cnt_ = index + 1U;
		this->draw_rt_ary_[index] = this->clear_rt_;
	}

	return;
}


/**
 * @brief PushDrawDepthTarget�֐�
 * @param dt_tex (depth_target_texture)
 */
void tml::graphic::Manager::PushDrawDepthTarget(tml::graphic::Texture *dt_tex)
{
	if (dt_tex != nullptr) {
		this->draw_dt_ = dt_tex->GetDepthTarget();
	} else {
		this->draw_dt_ = this->clear_dt_;
	}

	return;
}


/**
 * @brief SetDrawTarget�֐�
 */
void tml::graphic::Manager::SetDrawTarget(void)
{
	if (this->draw_rt_cnt_ > 0U) {
		this->device_context_->OMSetRenderTargets(this->draw_rt_cnt_, this->draw_rt_ary_.data(), this->draw_dt_);
	} else {
		this->device_context_->OMSetRenderTargets(0U, nullptr, this->draw_dt_);
	}

	return;
}


/**
 * @brief ClearDrawTarget�֐�
 */
void tml::graphic::Manager::ClearDrawTarget(void)
{
	if (this->draw_rt_cnt_ > 0U) {
		this->device_context_->OMSetRenderTargets(this->draw_rt_cnt_, this->clear_rt_ary_.data(), this->clear_dt_);

		this->draw_rt_cnt_ = 0U;
	} else {
		this->device_context_->OMSetRenderTargets(0U, nullptr, this->clear_dt_);
	}

	this->draw_dt_ = this->clear_dt_;

	return;
}


/**
 * @brief SetDrawRasterizerState�֐�
 * @param rs (rasterizer_state)
 */
void tml::graphic::Manager::SetDrawRasterizerState(tml::graphic::RasterizerState *rs)
{
	if (this->draw_rs_ != rs->GetRasterizerState()) {
		this->draw_rs_ = rs->GetRasterizerState();

		this->device_context_->RSSetState(this->draw_rs_);
	}

	return;
}


/**
 * @brief ClearDrawRasterizerState�֐�
 */
void tml::graphic::Manager::ClearDrawRasterizerState(void)
{
	if (this->draw_rs_ != nullptr) {
		this->device_context_->RSSetState(nullptr);

		this->draw_rs_ = nullptr;
	}

	return;
}


/**
 * @brief SetDrawBlendState�֐�
 * @param bs (blend_state)
 */
void tml::graphic::Manager::SetDrawBlendState(tml::graphic::BlendState *bs)
{
	if (this->draw_bs_ != bs->GetBlendState()) {
		this->draw_bs_ = bs->GetBlendState();

		this->device_context_->OMSetBlendState(this->draw_bs_, bs->GetFactorArray().data(), 0xFFFFFFFFU);
	}

	return;
}


/**
 * @brief ClearDrawBlendState�֐�
 */
void tml::graphic::Manager::ClearDrawBlendState(void)
{
	if (this->draw_bs_ != nullptr) {
		this->device_context_->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFFU);

		this->draw_bs_ = nullptr;
	}

	return;
}


/**
 * @brief SetDrawDepthState�֐�
 * @param ds (depth_state)
 */
void tml::graphic::Manager::SetDrawDepthState(tml::graphic::DepthState *ds)
{
	if (this->draw_ds_ != ds->GetDepthState()) {
		this->draw_ds_ = ds->GetDepthState();

		this->device_context_->OMSetDepthStencilState(this->draw_ds_, 0U);
	}

	return;
}


/**
 * @brief ClearDrawDepthState�֐�
 */
void tml::graphic::Manager::ClearDrawDepthState(void)
{
	if (this->draw_ds_ != nullptr) {
		this->device_context_->OMSetDepthStencilState(nullptr, 0U);

		this->draw_ds_ = nullptr;
	}

	return;
}


/**
 * @brief SetDrawShader�֐�
 * @param shader (shader)
 */
void tml::graphic::Manager::SetDrawShader(tml::graphic::Shader *shader)
{
	if (this->draw_shader_vs_ != shader->GetVertexShader()) {
		this->draw_shader_vs_ = shader->GetVertexShader();

		this->device_context_->VSSetShader(this->draw_shader_vs_, nullptr, 0U);
	}

	if (this->draw_shader_vs_input_layout_ != shader->GetVertexShaderInputLayout()) {
		this->draw_shader_vs_input_layout_ = shader->GetVertexShaderInputLayout();

		this->device_context_->IASetInputLayout(this->draw_shader_vs_input_layout_);
	}

	if (this->draw_shader_hs_ != shader->GetHullShader()) {
		this->draw_shader_hs_ = shader->GetHullShader();

		this->device_context_->HSSetShader(this->draw_shader_hs_, nullptr, 0U);
	}

	if (this->draw_shader_ds_ != shader->GetDomainShader()) {
		this->draw_shader_ds_ = shader->GetDomainShader();

		this->device_context_->DSSetShader(this->draw_shader_ds_, nullptr, 0U);
	}

	if (this->draw_shader_gs_ != shader->GetGeometryShader()) {
		this->draw_shader_gs_ = shader->GetGeometryShader();

		this->device_context_->GSSetShader(this->draw_shader_gs_, nullptr, 0U);
	}

	if (this->draw_shader_ps_ != shader->GetPixelShader()) {
		this->draw_shader_ps_ = shader->GetPixelShader();

		this->device_context_->PSSetShader(this->draw_shader_ps_, nullptr, 0U);
	}

	if (this->cmp_shader_cs_ != nullptr) {
		this->device_context_->CSSetShader(nullptr, nullptr, 0U);

		this->cmp_shader_cs_ = nullptr;
	}

	return;
}


/**
 * @brief ClearDrawShader�֐�
 */
void tml::graphic::Manager::ClearDrawShader(void)
{
	if (this->draw_shader_vs_ != nullptr) {
		this->device_context_->VSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_vs_ = nullptr;
	}

	if (this->draw_shader_vs_input_layout_ != nullptr) {
		this->device_context_->IASetInputLayout(nullptr);

		this->draw_shader_vs_input_layout_ = nullptr;
	}

	if (this->draw_shader_hs_ != nullptr) {
		this->device_context_->HSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_hs_ = nullptr;
	}

	if (this->draw_shader_ds_ != nullptr) {
		this->device_context_->DSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_ds_ = nullptr;
	}

	if (this->draw_shader_gs_ != nullptr) {
		this->device_context_->GSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_gs_ = nullptr;
	}

	if (this->draw_shader_ps_ != nullptr) {
		this->device_context_->PSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_ps_ = nullptr;
	}

	if (this->draw_ds_ != nullptr) {
		this->device_context_->OMSetDepthStencilState(nullptr, 0U);

		this->draw_ds_ = nullptr;
	}

	return;
}


/**
 * @brief SetDrawShaderConstantBuffer�֐�
 * @param type_flg (type_flag)
 * @param index (index)
 * @param scb (shader_constant_buffer)
 */
void tml::graphic::Manager::SetDrawShaderConstantBuffer(const tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG type_flg, const UINT index, tml::graphic::ShaderConstantBuffer *scb)
{
	ID3D11Buffer *buf_ary[1] = {scb->GetBuffer()};

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_)) {
		this->device_context_->VSSetConstantBuffers(index, 1U, buf_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::HULL_)) {
		this->device_context_->HSSetConstantBuffers(index, 1U, buf_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::DOMAIN_)) {
		this->device_context_->DSSetConstantBuffers(index, 1U, buf_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::GEOMETRY_)) {
		this->device_context_->GSSetConstantBuffers(index, 1U, buf_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_)) {
		this->device_context_->PSSetConstantBuffers(index, 1U, buf_ary);
	}

	return;
}


/**
 * @brief SetDrawShaderStructuredBuffer�֐�
 * @param type_flg (type_flag)
 * @param index (index)
 * @param ssb (shader_structured_buffer)
 */
void tml::graphic::Manager::SetDrawShaderStructuredBuffer(const tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG type_flg, const UINT index, tml::graphic::ShaderStructuredBuffer *ssb)
{
	ID3D11ShaderResourceView *sr_ary[1] = {ssb->GetSR()};

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::VERTEX_)) {
		this->device_context_->VSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + index, 1U, sr_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::HULL_)) {
		this->device_context_->HSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + index, 1U, sr_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::DOMAIN_)) {
		this->device_context_->DSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + index, 1U, sr_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::GEOMETRY_)) {
		this->device_context_->GSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + index, 1U, sr_ary);
	}

	if (static_cast<bool>(type_flg & tml::ConstantUtil::GRAPHIC::SHADER_TYPE_FLAG::PIXEL_)) {
		this->device_context_->PSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + index, 1U, sr_ary);
	}

	return;
}


/**
 * @brief SetComputeShader�֐�
 * @param shader (shader)
 */
void tml::graphic::Manager::SetComputeShader(tml::graphic::Shader *shader)
{
	if (this->draw_shader_vs_ != nullptr) {
		this->device_context_->VSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_vs_ = nullptr;
	}

	if (this->draw_shader_vs_input_layout_ != nullptr) {
		this->device_context_->IASetInputLayout(nullptr);

		this->draw_shader_vs_input_layout_ = nullptr;
	}

	if (this->draw_shader_hs_ != nullptr) {
		this->device_context_->HSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_hs_ = nullptr;
	}

	if (this->draw_shader_ds_ != nullptr) {
		this->device_context_->DSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_ds_ = nullptr;
	}

	if (this->draw_shader_gs_ != nullptr) {
		this->device_context_->GSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_gs_ = nullptr;
	}

	if (this->draw_shader_ps_ != nullptr) {
		this->device_context_->PSSetShader(nullptr, nullptr, 0U);

		this->draw_shader_ps_ = nullptr;
	}

	if (this->cmp_shader_cs_ != shader->GetComputeShader()) {
		this->cmp_shader_cs_ = shader->GetComputeShader();

		this->device_context_->CSSetShader(this->cmp_shader_cs_, nullptr, 0U);
	}

	return;
}


/**
 * @brief ClearComputeShader�֐�
 */
void tml::graphic::Manager::ClearComputeShader(void)
{
	if (this->cmp_shader_cs_ != nullptr) {
		this->device_context_->CSSetShader(nullptr, nullptr, 0U);

		this->cmp_shader_cs_ = nullptr;
	}

	return;
}


/**
 * @brief SetComputeShaderConstantBuffer�֐�
 * @param index (index)
 * @param scb (shader_constant_buffer)
 */
void tml::graphic::Manager::SetComputeShaderConstantBuffer(const UINT index, tml::graphic::ShaderConstantBuffer *scb)
{
	ID3D11Buffer *buf_ary[1] = {scb->GetBuffer()};

	this->device_context_->CSSetConstantBuffers(index, 1U, buf_ary);

	return;
}


/**
 * @brief SetComputeShaderStructuredBuffer�֐�
 * @param index (index)
 * @param ssb (shader_structured_buffer)
 */
void tml::graphic::Manager::SetComputeShaderStructuredBuffer(const UINT index, tml::graphic::ShaderStructuredBuffer *ssb)
{
	ID3D11ShaderResourceView *sr_ary[1] = {ssb->GetSR()};

	this->device_context_->CSSetShaderResources(tml::ConstantUtil::GRAPHIC::DRAW_TEXTURE_SR_LIMIT + index, 1U, sr_ary);

	return;
}
