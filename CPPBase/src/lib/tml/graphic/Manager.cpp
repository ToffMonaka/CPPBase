/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "ConfigShaderConstantBuffer.h"
#include "HeaderShaderConstantBuffer.h"
#include "CameraShaderStructuredBuffer.h"
#include "LightShaderStructuredBuffer.h"
#include "FogShaderStructuredBuffer.h"
#include "SpriteModelShaderStructuredBuffer.h"
#include "SpriteModelLayerShaderStructuredBuffer.h"
#include "Camera.h"
#include "Light.h"
#include "Fog.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Sampler.h"
#include "ScreenModel.h"
#include "SpriteModel.h"
#include "Font.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_device_context_handle(nullptr),
	size(0U),
	vsync_flag(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerDesc::Init(void)
{
	this->Release();

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;
	this->size = 0U;
	this->vsync_flag = true;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	factory_(nullptr),
	adapter_(nullptr),
	adapter_desc_{},
	swap_chain_(nullptr),
	swap_chain_desc_{},
	device_(nullptr),
	device_context_(nullptr),
	device_future_lv_(static_cast<D3D_FEATURE_LEVEL>(0)),
	size_(0U),
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
	draw_scb_sr_ary_{},
	draw_ssb_sr_ary_{},
	draw_camera_(nullptr),
	draw_light_cnt_(0U),
	draw_light_ary_{},
	draw_fog_cnt_(0U),
	draw_fog_ary_{},
	draw_mesh_vb_(nullptr),
	draw_mesh_vb_element_size_(0U),
	draw_mesh_vb_element_cnt_(0U),
	draw_mesh_ib_(nullptr),
	draw_mesh_ib_element_size_(0U),
	draw_mesh_ib_element_cnt_(0U),
	draw_mesh_ib_format_(DXGI_FORMAT_UNKNOWN),
	draw_mesh_pt_(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
	draw_tex_sr_ary_{},
	draw_samp_sr_ary_{},
	draw_model_cnt_(0U),
	draw_model_ary_{},
	cmp_shader_cs_(nullptr),
	cmp_scb_sr_ary_{},
	cmp_ssb_sr_ary_{},
	cmp_ssb_uasr_ary_{},
	cmp_tex_sr_ary_{},
	cmp_tex_uasr_ary_{},
	cmp_samp_sr_ary_{}
{
	this->null_vp_.TopLeftX = 0.0f;
	this->null_vp_.TopLeftY = 0.0f;
	this->null_vp_.Width = 0.0f;
	this->null_vp_.Height = 0.0f;
	this->null_vp_.MinDepth = D3D11_MIN_DEPTH;
	this->null_vp_.MaxDepth = D3D11_MAX_DEPTH;
	this->null_vp_ary_.fill(this->null_vp_);
	this->null_rt_ary_.fill(nullptr);
	this->null_scb_sr_ary_.fill(nullptr);
	this->null_ssb_sr_ary_.fill(nullptr);
	this->null_ssb_uasr_ary_.fill(nullptr);
	this->null_ssb_uasr_init_cnt_ary_.fill(static_cast<UINT>(-1));
	this->null_tex_sr_ary_.fill(nullptr);
	this->null_tex_uasr_ary_.fill(nullptr);
	this->null_tex_uasr_init_cnt_ary_.fill(static_cast<UINT>(-1));
	this->null_samp_sr_ary_.fill(nullptr);

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

	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;
	this->common.Init();

	tml::MemoryUtil::Clear(&this->adapter_desc_, 1U);
	tml::MemoryUtil::Clear(&this->swap_chain_desc_, 1U);
	this->device_future_lv_ = static_cast<D3D_FEATURE_LEVEL>(0);
	this->size_ = 0U;
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
	this->draw_scb_sr_ary_.fill(nullptr);
	this->draw_ssb_sr_ary_.fill(nullptr);
	this->draw_camera_ = nullptr;
	this->draw_light_cnt_ = 0U;
	this->draw_fog_cnt_ = 0U;
	this->draw_mesh_vb_ = nullptr;
	this->draw_mesh_vb_element_size_ = 0U;
	this->draw_mesh_vb_element_cnt_ = 0U;
	this->draw_mesh_ib_ = nullptr;
	this->draw_mesh_ib_element_size_ = 0U;
	this->draw_mesh_ib_element_cnt_ = 0U;
	this->draw_mesh_ib_format_ = DXGI_FORMAT_UNKNOWN;
	this->draw_mesh_pt_ = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	this->draw_tex_sr_ary_.fill(nullptr);
	this->draw_samp_sr_ary_.fill(nullptr);
	this->draw_model_cnt_ = 0U;
	this->cmp_shader_cs_ = nullptr;
	this->cmp_scb_sr_ary_.fill(nullptr);
	this->cmp_ssb_sr_ary_.fill(nullptr);
	this->cmp_ssb_uasr_ary_.fill(nullptr);
	this->cmp_tex_sr_ary_.fill(nullptr);
	this->cmp_tex_uasr_ary_.fill(nullptr);
	this->cmp_samp_sr_ary_.fill(nullptr);

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
	if ((desc.window_handle == nullptr)
	|| (desc.window_device_context_handle == nullptr)) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->wnd_handle_ = desc.window_handle;
	this->wnd_dc_handle_ = desc.window_device_context_handle;

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

		mode_desc.Width = desc.size.x;
		mode_desc.Height = desc.size.y;
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

	this->size_ = tml::XMUINT2EX(this->swap_chain_desc_.BufferDesc.Width, this->swap_chain_desc_.BufferDesc.Height);
	this->vsync_flg_ = desc.vsync_flag;
	this->vp_.Init(tml::XMFLOAT2EX(0.0f), tml::XMFLOAT2EX(static_cast<FLOAT>(this->swap_chain_desc_.BufferDesc.Width), static_cast<FLOAT>(this->swap_chain_desc_.BufferDesc.Height)));

	this->samp_quality_type_ = tml::ConstantUtil::GRAPHIC::SAMPLER_QUALITY_TYPE::ANISOTROPIC4;

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
		this->shadow_vp_.Init(tml::XMFLOAT2EX(0.0f), tml::XMFLOAT2EX(this->shadow_size_));
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

	this->device_context_->RSSetViewports(0U, nullptr);
	this->device_context_->OMSetRenderTargets(0U, nullptr, nullptr);
	this->device_context_->RSSetState(nullptr);
	this->device_context_->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFFU);
	this->device_context_->OMSetDepthStencilState(nullptr, 0U);
	this->device_context_->VSSetShader(nullptr, nullptr, 0U);
	this->device_context_->IASetInputLayout(nullptr);
	this->device_context_->HSSetShader(nullptr, nullptr, 0U);
	this->device_context_->DSSetShader(nullptr, nullptr, 0U);
	this->device_context_->GSSetShader(nullptr, nullptr, 0U);
	this->device_context_->PSSetShader(nullptr, nullptr, 0U);
	this->device_context_->VSSetConstantBuffers(0U, this->null_scb_sr_ary_.size(), this->null_scb_sr_ary_.data());
	this->device_context_->HSSetConstantBuffers(0U, this->null_scb_sr_ary_.size(), this->null_scb_sr_ary_.data());
	this->device_context_->DSSetConstantBuffers(0U, this->null_scb_sr_ary_.size(), this->null_scb_sr_ary_.data());
	this->device_context_->GSSetConstantBuffers(0U, this->null_scb_sr_ary_.size(), this->null_scb_sr_ary_.data());
	this->device_context_->PSSetConstantBuffers(0U, this->null_scb_sr_ary_.size(), this->null_scb_sr_ary_.data());
	this->device_context_->VSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + 0U, this->null_ssb_sr_ary_.size(), this->null_ssb_sr_ary_.data());
	this->device_context_->HSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + 0U, this->null_ssb_sr_ary_.size(), this->null_ssb_sr_ary_.data());
	this->device_context_->DSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + 0U, this->null_ssb_sr_ary_.size(), this->null_ssb_sr_ary_.data());
	this->device_context_->GSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + 0U, this->null_ssb_sr_ary_.size(), this->null_ssb_sr_ary_.data());
	this->device_context_->PSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + 0U, this->null_ssb_sr_ary_.size(), this->null_ssb_sr_ary_.data());
	this->device_context_->IASetVertexBuffers(0U, 0U, nullptr, nullptr, nullptr);
	this->device_context_->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0U);
	this->device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->device_context_->PSSetShaderResources(0U, this->null_tex_sr_ary_.size(), this->null_tex_sr_ary_.data());
	this->device_context_->PSSetSamplers(0U, this->null_samp_sr_ary_.size(), this->null_samp_sr_ary_.data());

	this->device_context_->CSSetShader(nullptr, nullptr, 0U);
	this->device_context_->CSSetConstantBuffers(0U, this->null_scb_sr_ary_.size(), this->null_scb_sr_ary_.data());
	this->device_context_->CSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + 0U, this->null_ssb_sr_ary_.size(), this->null_ssb_sr_ary_.data());
	this->device_context_->CSSetUnorderedAccessViews(tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT + 0U, this->null_ssb_uasr_ary_.size(), this->null_ssb_uasr_ary_.data(), this->null_ssb_uasr_init_cnt_ary_.data());
	this->device_context_->CSSetShaderResources(0U, this->null_tex_sr_ary_.size(), this->null_tex_sr_ary_.data());
	this->device_context_->CSSetUnorderedAccessViews(0U, this->null_tex_uasr_ary_.size(), this->null_tex_uasr_ary_.data(), this->null_tex_uasr_init_cnt_ary_.data());
	this->device_context_->CSSetSamplers(0U, this->null_samp_sr_ary_.size(), this->null_samp_sr_ary_.data());

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::graphic::Manager::Update(void)
{
	XMVECTOR determinant;

	XMMATRIX v_mat_3d;
	XMMATRIX inv_v_mat_3d;
	XMMATRIX p_mat_3d;
	XMMATRIX v_mat_2d;
	XMMATRIX inv_v_mat_2d;
	XMMATRIX p_mat_2d;

	tml::graphic::DRAW_STAGE_DATA draw_stage_dat(v_mat_3d, inv_v_mat_3d, p_mat_3d, v_mat_2d, inv_v_mat_2d, p_mat_2d);

	this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::INIT;
	this->draw_stage_dat_ = &draw_stage_dat;

	this->GetViewMatrix3D(this->draw_stage_dat_->view_matrix_3d, this->draw_camera_);
	this->draw_stage_dat_->inverse_view_matrix_3d = XMMatrixInverse(&determinant, this->draw_stage_dat_->view_matrix_3d);
	this->GetProjectionMatrix3D(this->draw_stage_dat_->projection_matrix_3d, this->draw_camera_);

	this->GetViewMatrix2D(this->draw_stage_dat_->view_matrix_2d, this->draw_camera_);
	this->draw_stage_dat_->inverse_view_matrix_2d = XMMatrixInverse(&determinant, this->draw_stage_dat_->view_matrix_2d);
	this->GetProjectionMatrix2D(this->draw_stage_dat_->projection_matrix_2d, this->draw_camera_);

	std::array<tml::graphic::ShaderConstantBuffer *, 2U> sys_scb_ary = {this->common.config_shader_constant_buffer.get(), this->common.header_shader_constant_buffer.get()};
	std::array<tml::graphic::ShaderStructuredBuffer *, 5U> sys_ssb_ary = {this->common.camera_shader_structured_buffer.get(), this->common.light_shader_structured_buffer.get(), this->common.fog_shader_structured_buffer.get(), nullptr, nullptr};

	while (this->draw_stage_type_ != tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE) {
		switch (this->draw_stage_type_) {
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::INIT: {
			this->common.main_render_target_texture->ClearRenderTarget(tml::XMFLOAT4EX(0.0f, 0.0f, 0.0f, 1.0f));
			this->common.main_depth_target_texture->ClearDepthTarget();

			this->common.header_shader_constant_buffer->SetElement(2U, this->draw_light_cnt_, this->draw_fog_cnt_, this->draw_model_cnt_);
			this->common.header_shader_constant_buffer->UploadCPUBuffer();

			this->common.camera_shader_structured_buffer->SetElementCount(0U);
			this->common.camera_shader_structured_buffer->SetElement(0U, this->draw_camera_, this->draw_stage_dat_->view_matrix_3d, this->draw_stage_dat_->inverse_view_matrix_3d, this->draw_stage_dat_->projection_matrix_3d);
			this->common.camera_shader_structured_buffer->SetElement(1U, this->draw_camera_,this->draw_stage_dat_->view_matrix_2d, this->draw_stage_dat_->inverse_view_matrix_2d, this->draw_stage_dat_->projection_matrix_2d);
			this->common.camera_shader_structured_buffer->UploadCPUBuffer();

			this->common.light_shader_structured_buffer->SetElementCount(0U);
			this->common.light_shader_structured_buffer->SetElement(0U, this->draw_light_cnt_, this->draw_light_ary_.data());
			this->common.light_shader_structured_buffer->UploadCPUBuffer();

			this->common.fog_shader_structured_buffer->SetElementCount(0U);
			this->common.fog_shader_structured_buffer->SetElement(0U, this->draw_fog_cnt_, this->draw_fog_ary_.data());
			this->common.fog_shader_structured_buffer->UploadCPUBuffer();

			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_ary_[draw_model_i]->DrawStageInit();
			}

			this->SetDrawShaderConstantBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, sys_scb_ary.size(), sys_scb_ary.data());
			this->SetDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::SYSTEM, sys_ssb_ary.size(), sys_ssb_ary.data());

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_3D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_3D: {
			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_ary_[draw_model_i]->DrawStageDeferred3D();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_SHADOW_3D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::DEFERRED_SHADOW_3D: {
			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_ary_[draw_model_i]->DrawStageDeferredShadow3D();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_3D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_3D: {
			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_ary_[draw_model_i]->DrawStageForward3D();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D;

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D: {
			this->SetDrawViewport(&this->vp_);
			this->SetDrawTarget(this->common.main_render_target_texture.get(), nullptr);

			for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
				this->draw_model_ary_[draw_model_i]->DrawStageForward2D();
			}

			this->draw_stage_type_ = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE;
			this->draw_stage_dat_ = nullptr;

			break;
		}
		}

		this->ClearDrawViewport();
		this->ClearDrawTarget();
	}

	this->swap_chain_->Present(this->vsync_flg_, 0U);

	this->ClearDrawRasterizerState();
	this->ClearDrawBlendState();
	this->ClearDrawDepthState();
	this->ClearDrawShader();
	this->ClearDrawShaderConstantBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, sys_scb_ary.size());
	this->ClearDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::SYSTEM, sys_ssb_ary.size());
	this->ClearDrawCamera();
	this->ClearDrawLight();
	this->ClearDrawFog();
	this->ClearDrawMesh();
	this->ClearDrawModel();

	return;
}


/**
 * @brief GetWorldMatrix3D関数
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
 * @brief GetWorldMatrix3D関数
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
 * @brief GetWorldMatrix2D関数
 * @param dst_mat (dst_matrix)
 * @param pos (position)
 * @param angle (angle)
 * @param scale (scale)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetWorldMatrix2D(XMMATRIX &dst_mat, const tml::XMFLOAT2EX &pos, const FLOAT angle, const tml::XMFLOAT2EX &scale)
{
	dst_mat = XMMatrixTransformation2D(g_XMZero, 0.0f, XMVectorSet(scale.x, scale.y, 0.0f, 0.0f), g_XMZero, angle, XMVectorSet(pos.x, pos.y, 0.0f, 0.0f));

	return (dst_mat);
}


/**
 * @brief GetViewMatrix3D関数
 * @param dst_mat (dst_matrix)
 * @param camera (camera)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetViewMatrix3D(XMMATRIX &dst_mat, const tml::graphic::Camera *camera)
{
	dst_mat = XMMatrixLookToLH(XMLoadFloat3(&camera->position.Get()), XMLoadFloat3(&camera->position.GetZAxisVector()), XMLoadFloat3(&camera->position.GetYAxisVector()));

	return (dst_mat);
}


/**
 * @brief GetViewMatrix2D関数
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
 * @brief GetProjectionMatrix3D関数
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
 * @brief GetProjectionMatrix2D関数
 * @param dst_mat (dst_matrix)
 * @param camera (camera)
 * @return dst_mat (dst_matrix)
 */
XMMATRIX &tml::graphic::Manager::GetProjectionMatrix2D(XMMATRIX &dst_mat, const tml::graphic::Camera *camera)
{
	switch (camera->GetType()) {
	case tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::PERSPECTIVE: {
		dst_mat = XMMatrixOrthographicLH(camera->GetFOVSize().x, camera->GetFOVSize().y, 0.0f, 1.0f);

		break;
	}
	case tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::ORTHOGRAPHIC: {
		dst_mat = XMMatrixOrthographicLH(camera->GetFOVSize().x, camera->GetFOVSize().y, 0.0f, 1.0f);

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

	ID3D11Buffer *tmp_buf = nullptr;
	D3D11_BUFFER_DESC tmp_buf_desc;

	buf->GetDesc(&tmp_buf_desc);

	tmp_buf_desc.BindFlags = 0U;
	tmp_buf_desc.Usage = D3D11_USAGE_STAGING;
	tmp_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	tmp_buf_desc.MiscFlags = 0U;

	if (FAILED(this->device_->CreateBuffer(&tmp_buf_desc, nullptr, &tmp_buf))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	this->device_context_->CopyResource(tmp_buf, buf);

	D3D11_MAPPED_SUBRESOURCE msr;

	if (FAILED(this->device_context_->Map(tmp_buf, 0U, D3D11_MAP_READ, 0U, &msr))) {
		tmp_buf->Release();

		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	dst_buf.Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
	dst_msr = msr;
	dst_msr.pData = nullptr;

	this->device_context_->Unmap(tmp_buf, 0U);

	tmp_buf->Release();

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

	ID3D11Texture2D *tmp_tex = nullptr;
	CD3D11_TEXTURE2D_DESC tmp_tex_desc;

	tex->GetDesc(&tmp_tex_desc);

	tmp_tex_desc.BindFlags = 0U;
	tmp_tex_desc.Usage = D3D11_USAGE_STAGING;
	tmp_tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	tmp_tex_desc.MiscFlags = 0U;

	if (FAILED(this->device_->CreateTexture2D(&tmp_tex_desc, nullptr, &tmp_tex))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	this->device_context_->CopyResource(tmp_tex, tex);

	D3D11_MAPPED_SUBRESOURCE msr;

	if (FAILED(this->device_context_->Map(tmp_tex, 0U, D3D11_MAP_READ, 0U, &msr))) {
		tmp_tex->Release();

		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	dst_buf.Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
	dst_msr = msr;
	dst_msr.pData = nullptr;

	this->device_context_->Unmap(tmp_tex, 0U);

	tmp_tex->Release();

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
	dst_msr_cont.clear();

	if (tex == nullptr) {
		tml::SetResult(dst_res, -1);

		return (dst_buf_cont);
	}

	ID3D11Texture2D *tmp_tex = nullptr;
	CD3D11_TEXTURE2D_DESC tmp_tex_desc;

	tex->GetDesc(&tmp_tex_desc);

	tmp_tex_desc.BindFlags = 0U;
	tmp_tex_desc.Usage = D3D11_USAGE_STAGING;
	tmp_tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	tmp_tex_desc.MiscFlags = 0U;

	if (FAILED(this->device_->CreateTexture2D(&tmp_tex_desc, nullptr, &tmp_tex))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf_cont);
	}

	this->device_context_->CopyResource(tmp_tex, tex);

	dst_buf_cont.resize(tmp_tex_desc.MipLevels);
	dst_msr_cont.resize(tmp_tex_desc.MipLevels);

	for (UINT mm_i = 0U; mm_i < tmp_tex_desc.MipLevels; ++mm_i) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (FAILED(this->device_context_->Map(tmp_tex, mm_i, D3D11_MAP_READ, 0U, &msr))) {
			tmp_tex->Release();

			dst_buf_cont.clear();
			dst_msr_cont.clear();

			tml::SetResult(dst_res, -1);

			return (dst_buf_cont);
		}

		dst_buf_cont[mm_i].Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
		dst_msr_cont[mm_i] = msr;
		dst_msr_cont[mm_i].pData = nullptr;

		this->device_context_->Unmap(tmp_tex, mm_i);
	}

	tmp_tex->Release();

	tml::SetResult(dst_res, 0);

	return (dst_buf_cont);
}


/**
 * @brief Draw関数
 * @param instance_cnt (instance_count)
 */
void tml::graphic::Manager::Draw(const UINT instance_cnt)
{
	this->device_context_->DrawIndexedInstanced(this->draw_mesh_ib_element_cnt_, instance_cnt, 0U, 0U, 0U);

	return;
}


/**
 * @brief SetDrawViewport関数
 * @param vp (viewport)
 */
void tml::graphic::Manager::SetDrawViewport(tml::graphic::Viewport *vp)
{
	this->draw_vp_cnt_ = 1U;

	this->draw_vp_ary_[0] = vp->Get();

	this->device_context_->RSSetViewports(this->draw_vp_cnt_, this->draw_vp_ary_.data());

	return;
}


/**
 * @brief SetDrawViewport関数
 * @param vp_cnt (viewport_count)
 * @param vp_ary (viewport_array)
 */
void tml::graphic::Manager::SetDrawViewport(const UINT vp_cnt, tml::graphic::Viewport *vp_ary)
{
	this->draw_vp_cnt_ = vp_cnt;

	for (UINT vp_i = 0U; vp_i < vp_cnt; ++vp_i) {
		this->draw_vp_ary_[vp_i] = vp_ary[vp_i].Get();
	}

	this->device_context_->RSSetViewports(this->draw_vp_cnt_, (this->draw_vp_cnt_ > 0U) ? this->draw_vp_ary_.data() : nullptr);

	return;
}


/**
 * @brief ClearDrawViewport関数
 */
void tml::graphic::Manager::ClearDrawViewport(void)
{
	if (this->draw_vp_cnt_ > 0U) {
		this->draw_vp_cnt_ = 0U;

		this->device_context_->RSSetViewports(this->draw_vp_cnt_, nullptr);
	}

	return;
}


/**
 * @brief SetDrawTarget関数
 * @param rt_tex (render_target_texture)
 * @param dt_tex (depth_target_texture)
 */
void tml::graphic::Manager::SetDrawTarget(tml::graphic::Texture *rt_tex, tml::graphic::Texture *dt_tex)
{
	this->draw_rt_cnt_ = 1U;

	this->draw_rt_ary_[0] = (rt_tex != nullptr) ? rt_tex->GetRenderTarget() : nullptr;

	this->draw_dt_ = (dt_tex != nullptr) ? dt_tex->GetDepthTarget() : nullptr;

	this->device_context_->OMSetRenderTargets(this->draw_rt_cnt_, this->draw_rt_ary_.data(), this->draw_dt_);

	return;
}


/**
 * @brief SetDrawTarget関数
 * @param rt_tex_cnt (render_target_texture_count)
 * @param rt_tex_ary (render_target_texture_array)
 * @param dt_tex (depth_target_texture)
 */
void tml::graphic::Manager::SetDrawTarget(const UINT rt_tex_cnt, tml::graphic::Texture **rt_tex_ary, tml::graphic::Texture *dt_tex)
{
	this->draw_rt_cnt_ = rt_tex_cnt;

	for (UINT rt_tex_i = 0U; rt_tex_i < rt_tex_cnt; ++rt_tex_i) {
		this->draw_rt_ary_[rt_tex_i] = (rt_tex_ary[rt_tex_i] != nullptr) ? rt_tex_ary[rt_tex_i]->GetRenderTarget() : nullptr;
	}

	this->draw_dt_ = (dt_tex != nullptr) ? dt_tex->GetDepthTarget() : nullptr;

	this->device_context_->OMSetRenderTargets(this->draw_rt_cnt_, (this->draw_rt_cnt_ > 0U) ? this->draw_rt_ary_.data() : nullptr, this->draw_dt_);

	return;
}


/**
 * @brief ClearDrawTarget関数
 */
void tml::graphic::Manager::ClearDrawTarget(void)
{
	if ((this->draw_rt_cnt_ > 0U)
	|| (this->draw_dt_ != nullptr)) {
		this->draw_rt_cnt_ = 0U;
		this->draw_dt_ = nullptr;

		this->device_context_->OMSetRenderTargets(this->draw_rt_cnt_, nullptr, this->draw_dt_);
	}

	return;
}


/**
 * @brief SetDrawRasterizerState関数
 * @param rs (rasterizer_state)
 */
void tml::graphic::Manager::SetDrawRasterizerState(tml::graphic::RasterizerState *rs)
{
	if (rs == nullptr) {
		this->ClearDrawRasterizerState();

		return;
	}

	if (this->draw_rs_ != rs->GetRasterizerState()) {
		this->draw_rs_ = rs->GetRasterizerState();

		this->device_context_->RSSetState(this->draw_rs_);
	}

	return;
}


/**
 * @brief ClearDrawRasterizerState関数
 */
void tml::graphic::Manager::ClearDrawRasterizerState(void)
{
	if (this->draw_rs_ != nullptr) {
		this->draw_rs_ = nullptr;

		this->device_context_->RSSetState(this->draw_rs_);
	}

	return;
}


/**
 * @brief SetDrawBlendState関数
 * @param bs (blend_state)
 */
void tml::graphic::Manager::SetDrawBlendState(tml::graphic::BlendState *bs)
{
	if (bs == nullptr) {
		this->ClearDrawBlendState();

		return;
	}

	if (this->draw_bs_ != bs->GetBlendState()) {
		this->draw_bs_ = bs->GetBlendState();

		this->device_context_->OMSetBlendState(this->draw_bs_, (this->draw_bs_ != nullptr) ? bs->GetFactorArray().data() : nullptr, 0xFFFFFFFFU);
	}

	return;
}


/**
 * @brief ClearDrawBlendState関数
 */
void tml::graphic::Manager::ClearDrawBlendState(void)
{
	if (this->draw_bs_ != nullptr) {
		this->draw_bs_ = nullptr;

		this->device_context_->OMSetBlendState(this->draw_bs_, nullptr, 0xFFFFFFFFU);
	}

	return;
}


/**
 * @brief SetDrawDepthState関数
 * @param ds (depth_state)
 */
void tml::graphic::Manager::SetDrawDepthState(tml::graphic::DepthState *ds)
{
	if (ds == nullptr) {
		this->ClearDrawDepthState();

		return;
	}

	if (this->draw_ds_ != ds->GetDepthState()) {
		this->draw_ds_ = ds->GetDepthState();

		this->device_context_->OMSetDepthStencilState(this->draw_ds_, 0U);
	}

	return;
}


/**
 * @brief ClearDrawDepthState関数
 */
void tml::graphic::Manager::ClearDrawDepthState(void)
{
	if (this->draw_ds_ != nullptr) {
		this->draw_ds_ = nullptr;

		this->device_context_->OMSetDepthStencilState(this->draw_ds_, 0U);
	}

	return;
}


/**
 * @brief SetDrawShader関数
 * @param shader (shader)
 */
void tml::graphic::Manager::SetDrawShader(tml::graphic::Shader *shader)
{
	if (shader == nullptr) {
		this->ClearDrawShader();

		return;
	}

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

	return;
}


/**
 * @brief ClearDrawShader関数
 */
void tml::graphic::Manager::ClearDrawShader(void)
{
	if (this->draw_shader_vs_ != nullptr) {
		this->draw_shader_vs_ = nullptr;

		this->device_context_->VSSetShader(this->draw_shader_vs_, nullptr, 0U);
	}

	if (this->draw_shader_vs_input_layout_ != nullptr) {
		this->draw_shader_vs_input_layout_ = nullptr;

		this->device_context_->IASetInputLayout(this->draw_shader_vs_input_layout_);
	}

	if (this->draw_shader_hs_ != nullptr) {
		this->draw_shader_hs_ = nullptr;

		this->device_context_->HSSetShader(this->draw_shader_hs_, nullptr, 0U);
	}

	if (this->draw_shader_ds_ != nullptr) {
		this->draw_shader_ds_ = nullptr;

		this->device_context_->DSSetShader(this->draw_shader_ds_, nullptr, 0U);
	}

	if (this->draw_shader_gs_ != nullptr) {
		this->draw_shader_gs_ = nullptr;

		this->device_context_->GSSetShader(this->draw_shader_gs_, nullptr, 0U);
	}

	if (this->draw_shader_ps_ != nullptr) {
		this->draw_shader_ps_ = nullptr;

		this->device_context_->PSSetShader(this->draw_shader_ps_, nullptr, 0U);
	}

	return;
}


/**
 * @brief SetDrawShaderConstantBufferSR関数
 * @param index (index)
 * @param scb (shader_constant_buffer)
 */
void tml::graphic::Manager::SetDrawShaderConstantBufferSR(const UINT index, tml::graphic::ShaderConstantBuffer *scb)
{
	if (scb == nullptr) {
		this->ClearDrawShaderConstantBufferSR(index);

		return;
	}

	if (this->draw_scb_sr_ary_[index] != scb->GetSR()) {
		this->draw_scb_sr_ary_[index] = scb->GetSR();

		this->device_context_->VSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->HSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->DSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->GSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->PSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetDrawShaderConstantBufferSR関数
 * @param index (index)
 * @param scb_cnt (shader_constant_buffer_count)
 * @param scb_ary (shader_constant_buffer_array)
 */
void tml::graphic::Manager::SetDrawShaderConstantBufferSR(const UINT index, const UINT scb_cnt, tml::graphic::ShaderConstantBuffer **scb_ary)
{
	if (scb_cnt <= 1U) {
		if (scb_cnt <= 0U) {
			return;
		}

		this->SetDrawShaderConstantBufferSR(index, scb_ary[0]);

		return;
	}

	for (UINT scb_i = 0U; scb_i < scb_cnt; ++scb_i) {
		this->draw_scb_sr_ary_[index + scb_i] = (scb_ary[scb_i] != nullptr) ? scb_ary[scb_i]->GetSR() : nullptr;
	}

	this->device_context_->VSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->HSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->DSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->GSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->PSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);

	return;
}


/**
 * @brief ClearDrawShaderConstantBufferSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearDrawShaderConstantBufferSR(const UINT index)
{
	if (this->draw_scb_sr_ary_[index] != nullptr) {
		this->draw_scb_sr_ary_[index] = nullptr;

		this->device_context_->VSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->HSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->DSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->GSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
		this->device_context_->PSSetConstantBuffers(index, 1U, &this->draw_scb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearDrawShaderConstantBufferSR関数
 * @param index (index)
 * @param scb_cnt (shader_constant_buffer_count)
 */
void tml::graphic::Manager::ClearDrawShaderConstantBufferSR(const UINT index, const UINT scb_cnt)
{
	if (scb_cnt <= 1U) {
		if (scb_cnt <= 0U) {
			return;
		}

		this->ClearDrawShaderConstantBufferSR(index);

		return;
	}

	for (UINT scb_i = 0U; scb_i < scb_cnt; ++scb_i) {
		this->draw_scb_sr_ary_[index + scb_i] = nullptr;
	}

	this->device_context_->VSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->HSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->DSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->GSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);
	this->device_context_->PSSetConstantBuffers(index, scb_cnt, &this->draw_scb_sr_ary_[index]);

	return;
}


/**
 * @brief SetDrawShaderStructuredBufferSR関数
 * @param index (index)
 * @param ssb (shader_structured_buffer)
 */
void tml::graphic::Manager::SetDrawShaderStructuredBufferSR(const UINT index, tml::graphic::ShaderStructuredBuffer *ssb)
{
	if (ssb == nullptr) {
		this->ClearDrawShaderStructuredBufferSR(index);

		return;
	}

	if (this->draw_ssb_sr_ary_[index] != ssb->GetSR()) {
		this->draw_ssb_sr_ary_[index] = ssb->GetSR();

		this->device_context_->VSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->HSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->DSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->GSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->PSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetDrawShaderStructuredBufferSR関数
 * @param index (index)
 * @param ssb_cnt (shader_structured_buffer_count)
 * @param ssb_ary (shader_structured_buffer_array)
 */
void tml::graphic::Manager::SetDrawShaderStructuredBufferSR(const UINT index, const UINT ssb_cnt, tml::graphic::ShaderStructuredBuffer **ssb_ary)
{
	if (ssb_cnt <= 1U) {
		if (ssb_cnt <= 0U) {
			return;
		}

		this->SetDrawShaderStructuredBufferSR(index, ssb_ary[0]);

		return;
	}

	for (UINT ssb_i = 0U; ssb_i < ssb_cnt; ++ssb_i) {
		this->draw_ssb_sr_ary_[index + ssb_i] = (ssb_ary[ssb_i] != nullptr) ? ssb_ary[ssb_i]->GetSR() : nullptr;
	}

	this->device_context_->VSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->HSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->DSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->GSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->PSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);

	return;
}


/**
 * @brief ClearDrawShaderStructuredBufferSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearDrawShaderStructuredBufferSR(const UINT index)
{
	if (this->draw_ssb_sr_ary_[index] != nullptr) {
		this->draw_ssb_sr_ary_[index] = nullptr;

		this->device_context_->VSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->HSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->DSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->GSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
		this->device_context_->PSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->draw_ssb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearDrawShaderStructuredBufferSR関数
 * @param index (index)
 * @param ssb_cnt (shader_structured_buffer_count)
 */
void tml::graphic::Manager::ClearDrawShaderStructuredBufferSR(const UINT index, const UINT ssb_cnt)
{
	if (ssb_cnt <= 1U) {
		if (ssb_cnt <= 0U) {
			return;
		}

		this->ClearDrawShaderStructuredBufferSR(index);

		return;
	}

	for (UINT ssb_i = 0U; ssb_i < ssb_cnt; ++ssb_i) {
		this->draw_ssb_sr_ary_[index + ssb_i] = nullptr;
	}

	this->device_context_->VSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->HSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->DSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->GSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);
	this->device_context_->PSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->draw_ssb_sr_ary_[index]);

	return;
}


/**
 * @brief SetDrawMesh関数
 * @param mesh (mesh)
 */
void tml::graphic::Manager::SetDrawMesh(tml::graphic::Mesh *mesh)
{
	if (mesh == nullptr) {
		this->ClearDrawMesh();

		return;
	}

	if (this->draw_mesh_vb_ != mesh->GetVertexBuffer()) {
		this->draw_mesh_vb_ = mesh->GetVertexBuffer();
		this->draw_mesh_vb_element_size_ = mesh->GetVertexBufferElementSize();
		this->draw_mesh_vb_element_cnt_ = mesh->GetVertexBufferElementCount();

		UINT offset = 0U;

		this->device_context_->IASetVertexBuffers(0U, 1U, &this->draw_mesh_vb_, &this->draw_mesh_vb_element_size_, &offset);
	}

	if (this->draw_mesh_ib_ != mesh->GetIndexBuffer()) {
		this->draw_mesh_ib_ = mesh->GetIndexBuffer();
		this->draw_mesh_ib_element_size_ = mesh->GetIndexBufferElementSize();
		this->draw_mesh_ib_element_cnt_ = mesh->GetIndexBufferElementCount();
		this->draw_mesh_ib_format_ = mesh->GetIndexBufferFormat();

		this->device_context_->IASetIndexBuffer(this->draw_mesh_ib_, this->draw_mesh_ib_format_, 0U);
	}

	if (this->draw_mesh_pt_ != mesh->GetPrimitiveTopology()) {
		this->draw_mesh_pt_ = mesh->GetPrimitiveTopology();

		this->device_context_->IASetPrimitiveTopology(this->draw_mesh_pt_);
	}

	return;
}


/**
 * @brief ClearDrawMesh関数
 */
void tml::graphic::Manager::ClearDrawMesh(void)
{
	if (this->draw_mesh_vb_ != nullptr) {
		this->draw_mesh_vb_ = nullptr;
		this->draw_mesh_vb_element_size_ = 0U;
		this->draw_mesh_vb_element_cnt_ = 0U;

		UINT offset = 0U;

		this->device_context_->IASetVertexBuffers(0U, 1U, &this->draw_mesh_vb_, &this->draw_mesh_vb_element_size_, &offset);
	}

	if (this->draw_mesh_ib_ != nullptr) {
		this->draw_mesh_ib_ = nullptr;
		this->draw_mesh_ib_element_size_ = 0U;
		this->draw_mesh_ib_element_cnt_ = 0U;
		this->draw_mesh_ib_format_ = DXGI_FORMAT_UNKNOWN;

		this->device_context_->IASetIndexBuffer(this->draw_mesh_ib_, this->draw_mesh_ib_format_, 0U);
	}

	if (this->draw_mesh_pt_ != D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {
		this->draw_mesh_pt_ = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		this->device_context_->IASetPrimitiveTopology(this->draw_mesh_pt_);
	}

	return;
}


/**
 * @brief SetDrawTextureSR関数
 * @param index (index)
 * @param tex (texture)
 */
void tml::graphic::Manager::SetDrawTextureSR(const UINT index, tml::graphic::Texture *tex)
{
	if (tex == nullptr) {
		this->ClearDrawTextureSR(index);

		return;
	}

	if (this->draw_tex_sr_ary_[index] != tex->GetSR()) {
		this->draw_tex_sr_ary_[index] = tex->GetSR();

		this->device_context_->PSSetShaderResources(index, 1U, &this->draw_tex_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetDrawTextureSR関数
 * @param index (index)
 * @param tex_cnt (texture_count)
 * @param tex_ary (texture_array)
 */
void tml::graphic::Manager::SetDrawTextureSR(const UINT index, const UINT tex_cnt, tml::graphic::Texture **tex_ary)
{
	if (tex_cnt <= 1U) {
		if (tex_cnt <= 0U) {
			return;
		}

		this->SetDrawTextureSR(index, tex_ary[0]);

		return;
	}

	for (UINT tex_i = 0U; tex_i < tex_cnt; ++tex_i) {
		this->draw_tex_sr_ary_[index + tex_i] = (tex_ary[tex_i] != nullptr) ? tex_ary[tex_i]->GetSR() : nullptr;
	}

	this->device_context_->PSSetShaderResources(index, tex_cnt, &this->draw_tex_sr_ary_[index]);

	return;
}


/**
 * @brief ClearDrawTextureSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearDrawTextureSR(const UINT index)
{
	if (this->draw_tex_sr_ary_[index] != nullptr) {
		this->draw_tex_sr_ary_[index] = nullptr;

		this->device_context_->PSSetShaderResources(index, 1U, &this->draw_tex_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearDrawTextureSR関数
 * @param index (index)
 * @param tex_cnt (texture_count)
 */
void tml::graphic::Manager::ClearDrawTextureSR(const UINT index, const UINT tex_cnt)
{
	if (tex_cnt <= 1U) {
		if (tex_cnt <= 0U) {
			return;
		}

		this->ClearDrawTextureSR(index);

		return;
	}

	for (UINT tex_i = 0U; tex_i < tex_cnt; ++tex_i) {
		this->draw_tex_sr_ary_[index + tex_i] = nullptr;
	}

	this->device_context_->PSSetShaderResources(index, tex_cnt, &this->draw_tex_sr_ary_[index]);

	return;
}


/**
 * @brief SetDrawSamplerSR関数
 * @param index (index)
 * @param samp (sampler)
 */
void tml::graphic::Manager::SetDrawSamplerSR(const UINT index, tml::graphic::Sampler *samp)
{
	if (samp == nullptr) {
		this->ClearDrawSamplerSR(index);

		return;
	}

	if (this->draw_samp_sr_ary_[index] != samp->GetSR()) {
		this->draw_samp_sr_ary_[index] = samp->GetSR();

		this->device_context_->PSSetSamplers(index, 1U, &this->draw_samp_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetDrawSamplerSR関数
 * @param index (index)
 * @param samp_cnt (sampler_count)
 * @param samp_ary (sampler_array)
 */
void tml::graphic::Manager::SetDrawSamplerSR(const UINT index, const UINT samp_cnt, tml::graphic::Sampler **samp_ary)
{
	if (samp_cnt <= 1U) {
		if (samp_cnt <= 0U) {
			return;
		}

		this->SetDrawSamplerSR(index, samp_ary[0]);

		return;
	}

	for (UINT samp_i = 0U; samp_i < samp_cnt; ++samp_i) {
		this->draw_samp_sr_ary_[index + samp_i] = (samp_ary[samp_i] != nullptr) ? samp_ary[samp_i]->GetSR() : nullptr;
	}

	this->device_context_->PSSetSamplers(index, samp_cnt, &this->draw_samp_sr_ary_[index]);

	return;
}


/**
 * @brief ClearDrawSamplerSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearDrawSamplerSR(const UINT index)
{
	if (this->draw_samp_sr_ary_[index] != nullptr) {
		this->draw_samp_sr_ary_[index] = nullptr;

		this->device_context_->PSSetSamplers(index, 1U, &this->draw_samp_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearDrawSamplerSR関数
 * @param index (index)
 * @param samp_cnt (sampler_count)
 */
void tml::graphic::Manager::ClearDrawSamplerSR(const UINT index, const UINT samp_cnt)
{
	if (samp_cnt <= 1U) {
		if (samp_cnt <= 0U) {
			return;
		}

		this->ClearDrawSamplerSR(index);

		return;
	}

	for (UINT samp_i = 0U; samp_i < samp_cnt; ++samp_i) {
		this->draw_samp_sr_ary_[index + samp_i] = nullptr;
	}

	this->device_context_->PSSetSamplers(index, samp_cnt, &this->draw_samp_sr_ary_[index]);

	return;
}


/**
 * @brief SetComputeShader関数
 * @param shader (shader)
 */
void tml::graphic::Manager::SetComputeShader(tml::graphic::Shader *shader)
{
	if (shader == nullptr) {
		this->ClearComputeShader();

		return;
	}

	if (this->cmp_shader_cs_ != shader->GetComputeShader()) {
		this->cmp_shader_cs_ = shader->GetComputeShader();

		this->device_context_->CSSetShader(this->cmp_shader_cs_, nullptr, 0U);
	}

	return;
}


/**
 * @brief ClearComputeShader関数
 */
void tml::graphic::Manager::ClearComputeShader(void)
{
	if (this->cmp_shader_cs_ != nullptr) {
		this->cmp_shader_cs_ = nullptr;

		this->device_context_->CSSetShader(this->cmp_shader_cs_, nullptr, 0U);
	}

	return;
}


/**
 * @brief SetComputeShaderConstantBufferSR関数
 * @param index (index)
 * @param scb (shader_constant_buffer)
 */
void tml::graphic::Manager::SetComputeShaderConstantBufferSR(const UINT index, tml::graphic::ShaderConstantBuffer *scb)
{
	if (scb == nullptr) {
		this->ClearComputeShaderConstantBufferSR(index);

		return;
	}

	if (this->cmp_scb_sr_ary_[index] != scb->GetSR()) {
		this->cmp_scb_sr_ary_[index] = scb->GetSR();

		this->device_context_->CSSetConstantBuffers(index, 1U, &this->cmp_scb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetComputeShaderConstantBufferSR関数
 * @param index (index)
 * @param scb_cnt (shader_constant_buffer_count)
 * @param scb_ary (shader_constant_buffer_array)
 */
void tml::graphic::Manager::SetComputeShaderConstantBufferSR(const UINT index, const UINT scb_cnt, tml::graphic::ShaderConstantBuffer **scb_ary)
{
	if (scb_cnt <= 1U) {
		if (scb_cnt <= 0U) {
			return;
		}

		this->SetComputeShaderConstantBufferSR(index, scb_ary[0]);

		return;
	}

	for (UINT scb_i = 0U; scb_i < scb_cnt; ++scb_i) {
		this->cmp_scb_sr_ary_[index + scb_i] = (scb_ary[scb_i] != nullptr) ? scb_ary[scb_i]->GetSR() : nullptr;
	}

	this->device_context_->CSSetConstantBuffers(index, scb_cnt, &this->cmp_scb_sr_ary_[index]);

	return;
}


/**
 * @brief ClearComputeShaderConstantBufferSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearComputeShaderConstantBufferSR(const UINT index)
{
	if (this->cmp_scb_sr_ary_[index] != nullptr) {
		this->cmp_scb_sr_ary_[index] = nullptr;

		this->device_context_->CSSetConstantBuffers(index, 1U, &this->cmp_scb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearComputeShaderConstantBufferSR関数
 * @param index (index)
 * @param scb_cnt (shader_constant_buffer_count)
 */
void tml::graphic::Manager::ClearComputeShaderConstantBufferSR(const UINT index, const UINT scb_cnt)
{
	if (scb_cnt <= 1U) {
		if (scb_cnt <= 0U) {
			return;
		}

		this->ClearComputeShaderConstantBufferSR(index);

		return;
	}

	for (UINT scb_i = 0U; scb_i < scb_cnt; ++scb_i) {
		this->cmp_scb_sr_ary_[index + scb_i] = nullptr;
	}

	this->device_context_->CSSetConstantBuffers(index, scb_cnt, &this->cmp_scb_sr_ary_[index]);

	return;
}


/**
 * @brief SetComputeShaderStructuredBufferSR関数
 * @param index (index)
 * @param ssb (shader_structured_buffer)
 */
void tml::graphic::Manager::SetComputeShaderStructuredBufferSR(const UINT index, tml::graphic::ShaderStructuredBuffer *ssb)
{
	if (ssb == nullptr) {
		this->ClearComputeShaderStructuredBufferSR(index);

		return;
	}

	if (this->cmp_ssb_sr_ary_[index] != ssb->GetSR()) {
		this->cmp_ssb_sr_ary_[index] = ssb->GetSR();

		this->device_context_->CSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->cmp_ssb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetComputeShaderStructuredBufferSR関数
 * @param index (index)
 * @param ssb_cnt (shader_structured_buffer_count)
 * @param ssb_ary (shader_structured_buffer_array)
 */
void tml::graphic::Manager::SetComputeShaderStructuredBufferSR(const UINT index, const UINT ssb_cnt, tml::graphic::ShaderStructuredBuffer **ssb_ary)
{
	if (ssb_cnt <= 1U) {
		if (ssb_cnt <= 0U) {
			return;
		}

		this->SetComputeShaderStructuredBufferSR(index, ssb_ary[0]);

		return;
	}

	for (UINT ssb_i = 0U; ssb_i < ssb_cnt; ++ssb_i) {
		this->cmp_ssb_sr_ary_[index + ssb_i] = (ssb_ary[ssb_i] != nullptr) ? ssb_ary[ssb_i]->GetSR() : nullptr;
	}

	this->device_context_->CSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->cmp_ssb_sr_ary_[index]);

	return;
}


/**
 * @brief ClearComputeShaderStructuredBufferSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearComputeShaderStructuredBufferSR(const UINT index)
{
	if (this->cmp_ssb_sr_ary_[index] != nullptr) {
		this->cmp_ssb_sr_ary_[index] = nullptr;

		this->device_context_->CSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, 1U, &this->cmp_ssb_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearComputeShaderStructuredBufferSR関数
 * @param index (index)
 * @param ssb_cnt (shader_structured_buffer_count)
 */
void tml::graphic::Manager::ClearComputeShaderStructuredBufferSR(const UINT index, const UINT ssb_cnt)
{
	if (ssb_cnt <= 1U) {
		if (ssb_cnt <= 0U) {
			return;
		}

		this->ClearComputeShaderStructuredBufferSR(index);

		return;
	}

	for (UINT ssb_i = 0U; ssb_i < ssb_cnt; ++ssb_i) {
		this->cmp_ssb_sr_ary_[index + ssb_i] = nullptr;
	}

	this->device_context_->CSSetShaderResources(tml::ConstantUtil::GRAPHIC::TEXTURE_SR_LIMIT + index, ssb_cnt, &this->cmp_ssb_sr_ary_[index]);

	return;
}


/**
 * @brief SetComputeShaderStructuredBufferUASR関数
 * @param index (index)
 * @param ssb (shader_structured_buffer)
 */
void tml::graphic::Manager::SetComputeShaderStructuredBufferUASR(const UINT index, tml::graphic::ShaderStructuredBuffer *ssb)
{
	if (ssb == nullptr) {
		this->ClearComputeShaderStructuredBufferUASR(index);

		return;
	}

	if (this->cmp_ssb_uasr_ary_[index] != ssb->GetUASR()) {
		this->cmp_ssb_uasr_ary_[index] = ssb->GetUASR();

		this->device_context_->CSSetUnorderedAccessViews(tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT + index, 1U, &this->cmp_ssb_uasr_ary_[index], this->null_ssb_uasr_init_cnt_ary_.data());
	}

	return;
}


/**
 * @brief SetComputeShaderStructuredBufferUASR関数
 * @param index (index)
 * @param ssb_cnt (shader_structured_buffer_count)
 * @param ssb_ary (shader_structured_buffer_array)
 */
void tml::graphic::Manager::SetComputeShaderStructuredBufferUASR(const UINT index, const UINT ssb_cnt, tml::graphic::ShaderStructuredBuffer **ssb_ary)
{
	if (ssb_cnt <= 1U) {
		if (ssb_cnt <= 0U) {
			return;
		}

		this->SetComputeShaderStructuredBufferUASR(index, ssb_ary[0]);

		return;
	}

	for (UINT ssb_i = 0U; ssb_i < ssb_cnt; ++ssb_i) {
		this->cmp_ssb_uasr_ary_[index + ssb_i] = (ssb_ary[ssb_i] != nullptr) ? ssb_ary[ssb_i]->GetUASR() : nullptr;
	}

	this->device_context_->CSSetUnorderedAccessViews(tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT + index, ssb_cnt, &this->cmp_ssb_uasr_ary_[index], this->null_ssb_uasr_init_cnt_ary_.data());

	return;
}


/**
 * @brief ClearComputeShaderStructuredBufferUASR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearComputeShaderStructuredBufferUASR(const UINT index)
{
	if (this->cmp_ssb_uasr_ary_[index] != nullptr) {
		this->cmp_ssb_uasr_ary_[index] = nullptr;

		this->device_context_->CSSetUnorderedAccessViews(tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT + index, 1U, &this->cmp_ssb_uasr_ary_[index], this->null_ssb_uasr_init_cnt_ary_.data());
	}

	return;
}


/**
 * @brief ClearComputeShaderStructuredBufferUASR関数
 * @param index (index)
 * @param ssb_cnt (shader_structured_buffer_count)
 */
void tml::graphic::Manager::ClearComputeShaderStructuredBufferUASR(const UINT index, const UINT ssb_cnt)
{
	if (ssb_cnt <= 1U) {
		if (ssb_cnt <= 0U) {
			return;
		}

		this->ClearComputeShaderStructuredBufferUASR(index);

		return;
	}

	for (UINT ssb_i = 0U; ssb_i < ssb_cnt; ++ssb_i) {
		this->cmp_ssb_uasr_ary_[index + ssb_i] = nullptr;
	}

	this->device_context_->CSSetUnorderedAccessViews(tml::ConstantUtil::GRAPHIC::TEXTURE_UASR_LIMIT + index, ssb_cnt, &this->cmp_ssb_uasr_ary_[index], this->null_ssb_uasr_init_cnt_ary_.data());

	return;
}


/**
 * @brief SetComputeTextureSR関数
 * @param index (index)
 * @param tex (texture)
 */
void tml::graphic::Manager::SetComputeTextureSR(const UINT index, tml::graphic::Texture *tex)
{
	if (tex == nullptr) {
		this->ClearComputeTextureSR(index);

		return;
	}

	if (this->cmp_tex_sr_ary_[index] != tex->GetSR()) {
		this->cmp_tex_sr_ary_[index] = tex->GetSR();

		this->device_context_->CSSetShaderResources(index, 1U, &this->cmp_tex_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetComputeTextureSR関数
 * @param index (index)
 * @param tex_cnt (texture_count)
 * @param tex_ary (texture_array)
 */
void tml::graphic::Manager::SetComputeTextureSR(const UINT index, const UINT tex_cnt, tml::graphic::Texture **tex_ary)
{
	if (tex_cnt <= 1U) {
		if (tex_cnt <= 0U) {
			return;
		}

		this->SetComputeTextureSR(index, tex_ary[0]);

		return;
	}

	for (UINT tex_i = 0U; tex_i < tex_cnt; ++tex_i) {
		this->cmp_tex_sr_ary_[index + tex_i] = (tex_ary[tex_i] != nullptr) ? tex_ary[tex_i]->GetSR() : nullptr;
	}

	this->device_context_->CSSetShaderResources(index, tex_cnt, &this->cmp_tex_sr_ary_[index]);

	return;
}


/**
 * @brief ClearComputeTextureSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearComputeTextureSR(const UINT index)
{
	if (this->cmp_tex_sr_ary_[index] != nullptr) {
		this->cmp_tex_sr_ary_[index] = nullptr;

		this->device_context_->CSSetShaderResources(index, 1U, &this->cmp_tex_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearComputeTextureSR関数
 * @param index (index)
 * @param tex_cnt (texture_count)
 */
void tml::graphic::Manager::ClearComputeTextureSR(const UINT index, const UINT tex_cnt)
{
	if (tex_cnt <= 1U) {
		if (tex_cnt <= 0U) {
			return;
		}

		this->ClearComputeTextureSR(index);

		return;
	}

	for (UINT tex_i = 0U; tex_i < tex_cnt; ++tex_i) {
		this->cmp_tex_sr_ary_[index + tex_i] = nullptr;
	}

	this->device_context_->CSSetShaderResources(index, tex_cnt, &this->cmp_tex_sr_ary_[index]);

	return;
}


/**
 * @brief SetComputeTextureUASR関数
 * @param index (index)
 * @param tex (texture)
 */
void tml::graphic::Manager::SetComputeTextureUASR(const UINT index, tml::graphic::Texture *tex)
{
	if (tex == nullptr) {
		this->ClearComputeTextureUASR(index);

		return;
	}

	if (this->cmp_tex_uasr_ary_[index] != tex->GetUASR()) {
		this->cmp_tex_uasr_ary_[index] = tex->GetUASR();

		this->device_context_->CSSetUnorderedAccessViews(index, 1U, &this->cmp_tex_uasr_ary_[index], this->null_tex_uasr_init_cnt_ary_.data());
	}

	return;
}


/**
 * @brief SetComputeTextureUASR関数
 * @param index (index)
 * @param tex_cnt (texture_count)
 * @param tex_ary (texture_array)
 */
void tml::graphic::Manager::SetComputeTextureUASR(const UINT index, const UINT tex_cnt, tml::graphic::Texture **tex_ary)
{
	if (tex_cnt <= 1U) {
		if (tex_cnt <= 0U) {
			return;
		}

		this->SetComputeTextureUASR(index, tex_ary[0]);

		return;
	}

	for (UINT tex_i = 0U; tex_i < tex_cnt; ++tex_i) {
		this->cmp_tex_uasr_ary_[index + tex_i] = (tex_ary[tex_i] != nullptr) ? tex_ary[tex_i]->GetUASR() : nullptr;
	}

	this->device_context_->CSSetUnorderedAccessViews(index, tex_cnt, &this->cmp_tex_uasr_ary_[index], this->null_tex_uasr_init_cnt_ary_.data());

	return;
}


/**
 * @brief ClearComputeTextureUASR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearComputeTextureUASR(const UINT index)
{
	if (this->cmp_tex_uasr_ary_[index] != nullptr) {
		this->cmp_tex_uasr_ary_[index] = nullptr;

		this->device_context_->CSSetUnorderedAccessViews(index, 1U, &this->cmp_tex_uasr_ary_[index], this->null_tex_uasr_init_cnt_ary_.data());
	}

	return;
}


/**
 * @brief ClearComputeTextureUASR関数
 * @param index (index)
 * @param tex_cnt (texture_count)
 */
void tml::graphic::Manager::ClearComputeTextureUASR(const UINT index, const UINT tex_cnt)
{
	if (tex_cnt <= 1U) {
		if (tex_cnt <= 0U) {
			return;
		}

		this->ClearComputeTextureUASR(index);

		return;
	}

	for (UINT tex_i = 0U; tex_i < tex_cnt; ++tex_i) {
		this->cmp_tex_uasr_ary_[index + tex_i] = nullptr;
	}

	this->device_context_->CSSetUnorderedAccessViews(index, tex_cnt, &this->cmp_tex_uasr_ary_[index], this->null_tex_uasr_init_cnt_ary_.data());

	return;
}


/**
 * @brief SetComputeSamplerSR関数
 * @param index (index)
 * @param samp (sampler)
 */
void tml::graphic::Manager::SetComputeSamplerSR(const UINT index, tml::graphic::Sampler *samp)
{
	if (samp == nullptr) {
		this->ClearComputeSamplerSR(index);

		return;
	}

	if (this->cmp_samp_sr_ary_[index] != samp->GetSR()) {
		this->cmp_samp_sr_ary_[index] = samp->GetSR();

		this->device_context_->CSSetSamplers(index, 1U, &this->cmp_samp_sr_ary_[index]);
	}

	return;
}


/**
 * @brief SetComputeSamplerSR関数
 * @param index (index)
 * @param samp_cnt (sampler_count)
 * @param samp_ary (sampler_array)
 */
void tml::graphic::Manager::SetComputeSamplerSR(const UINT index, const UINT samp_cnt, tml::graphic::Sampler **samp_ary)
{
	if (samp_cnt <= 1U) {
		if (samp_cnt <= 0U) {
			return;
		}

		this->SetComputeSamplerSR(index, samp_ary[0]);

		return;
	}

	for (UINT samp_i = 0U; samp_i < samp_cnt; ++samp_i) {
		this->cmp_samp_sr_ary_[index + samp_i] = (samp_ary[samp_i] != nullptr) ? samp_ary[samp_i]->GetSR() : nullptr;
	}

	this->device_context_->CSSetSamplers(index, samp_cnt, &this->cmp_samp_sr_ary_[index]);

	return;
}


/**
 * @brief ClearComputeSamplerSR関数
 * @param index (index)
 */
void tml::graphic::Manager::ClearComputeSamplerSR(const UINT index)
{
	if (this->cmp_samp_sr_ary_[index] != nullptr) {
		this->cmp_samp_sr_ary_[index] = nullptr;

		this->device_context_->CSSetSamplers(index, 1U, &this->cmp_samp_sr_ary_[index]);
	}

	return;
}


/**
 * @brief ClearComputeSamplerSR関数
 * @param index (index)
 * @param samp_cnt (sampler_count)
 */
void tml::graphic::Manager::ClearComputeSamplerSR(const UINT index, const UINT samp_cnt)
{
	if (samp_cnt <= 1U) {
		if (samp_cnt <= 0U) {
			return;
		}

		this->ClearComputeSamplerSR(index);

		return;
	}

	for (UINT samp_i = 0U; samp_i < samp_cnt; ++samp_i) {
		this->cmp_samp_sr_ary_[index + samp_i] = nullptr;
	}

	this->device_context_->CSSetSamplers(index, samp_cnt, &this->cmp_samp_sr_ary_[index]);

	return;
}
