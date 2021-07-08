/**
 * @file
 * @brief Canvas2Dコードファイル
 */


#include "Canvas2D.h"
#include "Manager.h"
#include "ConfigShaderConstantBuffer.h"
#include "HeaderShaderConstantBuffer.h"
#include "CameraShaderStructuredBuffer.h"
#include "LightShaderStructuredBuffer.h"
#include "FogShaderStructuredBuffer.h"
#include "Texture.h"
#include "Sampler.h"
#include "Camera2D.h"
#include "Light.h"
#include "Fog.h"
#include "Model2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Canvas2DDesc::Canvas2DDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Canvas2DDesc::~Canvas2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Canvas2DDesc::Init(void)
{
	this->Release();

	tml::graphic::CanvasDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Canvas2DDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::CanvasDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Canvas2D Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"CANVAS_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Canvas2D::Canvas2D() :
	draw_camera_(nullptr),
	draw_light_cnt_(0U),
	draw_light_ary_{},
	draw_fog_cnt_(0U),
	draw_fog_ary_{},
	draw_model_cnt_(0U),
	draw_model_ary_{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Canvas2D::~Canvas2D()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Canvas2D::Init(void)
{
	this->Release();

	this->draw_camera_ = nullptr;
	this->draw_light_cnt_ = 0U;
	this->draw_fog_cnt_ = 0U;
	this->draw_model_cnt_ = 0U;

	tml::graphic::Canvas::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Canvas2D::Create(const tml::graphic::Canvas2DDesc &desc)
{
	this->Init();

	if (tml::graphic::Canvas::Create(desc, tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_2D) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief SetDrawCamera関数
 * @param camera (camera)
 */
void tml::graphic::Canvas2D::SetDrawCamera(tml::graphic::Camera2D *camera)
{
	this->draw_camera_ = camera;

	return;
}


/**
 * @brief SetDrawLight関数
 * @param light (light)
 */
void tml::graphic::Canvas2D::SetDrawLight(tml::graphic::Light *light)
{
	if ((light == nullptr)
	|| (this->draw_light_cnt_ >= tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT)) {
		return;
	}

	this->draw_light_ary_[this->draw_light_cnt_++] = light;

	return;
}


/**
 * @brief SetDrawFog関数
 * @param fog (fog)
 */
void tml::graphic::Canvas2D::SetDrawFog(tml::graphic::Fog *fog)
{
	if ((fog == nullptr)
	|| (this->draw_fog_cnt_ >= tml::ConstantUtil::GRAPHIC::FOG_LIMIT)) {
		return;
	}

	this->draw_fog_ary_[this->draw_fog_cnt_++] = fog;

	return;
}


/**
 * @brief SetDrawModel関数
 * @param model (model)
 */
void tml::graphic::Canvas2D::SetDrawModel(tml::graphic::Model2D *model)
{
	if ((model == nullptr)
	|| (this->draw_model_cnt_ >= tml::ConstantUtil::GRAPHIC::MODEL_LIMIT)) {
		return;
	}

	this->draw_model_ary_[this->draw_model_cnt_++] = model;

	return;
}


/**
 * @brief Draw関数
 */
void tml::graphic::Canvas2D::Draw(void)
{
	if (this->draw_camera_ != nullptr) {
		auto draw_camera = reinterpret_cast<tml::graphic::Camera2D *>(this->draw_camera_);

		DirectX::XMMATRIX v_mat;
		DirectX::XMMATRIX inv_v_mat;
		DirectX::XMMATRIX p_mat;

		this->GetManager()->GetViewMatrix(v_mat, (*draw_camera));
		inv_v_mat = DirectX::XMMatrixInverse(nullptr, v_mat);
		this->GetManager()->GetProjectionMatrix(p_mat, (*draw_camera));

		tml::graphic::DRAW_STAGE_DATA draw_stage_dat(v_mat, inv_v_mat, p_mat);

		this->GetManager()->SetDrawStageData(&draw_stage_dat);

		std::array<tml::graphic::ShaderConstantBuffer *, 2U> sys_scb_ary = {this->GetManager()->common.config_shader_constant_buffer.get(), this->GetManager()->common.header_shader_constant_buffer.get()};
		std::array<tml::graphic::ShaderStructuredBuffer *, 5U> sys_ssb_ary = {this->GetManager()->common.camera_shader_structured_buffer.get(), this->GetManager()->common.light_shader_structured_buffer.get(), this->GetManager()->common.fog_shader_structured_buffer.get(), nullptr, nullptr};

		while (draw_stage_dat.type != tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE) {
			switch (draw_stage_dat.type) {
			case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::INIT: {
				this->GetManager()->common.main_render_target_texture->ClearRenderTarget(tml::XMFLOAT4EX(0.0f, 0.0f, 0.0f, 1.0f));
				this->GetManager()->common.main_depth_target_texture->ClearDepthTarget();

				this->GetManager()->common.header_shader_constant_buffer->SetElement(2U, this->draw_light_cnt_, this->draw_fog_cnt_, this->draw_model_cnt_);
				this->GetManager()->common.header_shader_constant_buffer->UploadCPUBuffer();

				this->GetManager()->common.camera_shader_structured_buffer->SetElementCount(0U);
				this->GetManager()->common.camera_shader_structured_buffer->SetElement(0U, draw_stage_dat.view_matrix, draw_stage_dat.inverse_view_matrix, draw_stage_dat.projection_matrix);
				this->GetManager()->common.camera_shader_structured_buffer->UploadCPUBuffer();

				this->GetManager()->common.light_shader_structured_buffer->SetElementCount(0U);
				this->GetManager()->common.light_shader_structured_buffer->SetElement(0U, this->draw_light_cnt_, this->draw_light_ary_.data());
				this->GetManager()->common.light_shader_structured_buffer->UploadCPUBuffer();

				this->GetManager()->common.fog_shader_structured_buffer->SetElementCount(0U);
				this->GetManager()->common.fog_shader_structured_buffer->SetElement(0U, this->draw_fog_cnt_, this->draw_fog_ary_.data());
				this->GetManager()->common.fog_shader_structured_buffer->UploadCPUBuffer();

				for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
					this->draw_model_ary_[draw_model_i]->DrawStageInit();
				}

				this->GetManager()->SetDrawShaderConstantBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, sys_scb_ary.size(), sys_scb_ary.data());
				this->GetManager()->SetDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::SYSTEM, sys_ssb_ary.size(), sys_ssb_ary.data());

				draw_stage_dat.type = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D;

				break;
			}
			case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D: {
				this->GetManager()->SetDrawViewport(this->GetManager()->GetViewport());
				this->GetManager()->SetDrawTarget(this->GetManager()->common.main_render_target_texture.get(), nullptr);

				for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
					this->draw_model_ary_[draw_model_i]->DrawStageForward2D();
				}

				this->GetManager()->ClearDrawShaderConstantBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, sys_scb_ary.size());
				this->GetManager()->ClearDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::SYSTEM, sys_ssb_ary.size());

				draw_stage_dat.type = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE;

				break;
			}
			}

			this->GetManager()->ClearDrawViewport();
			this->GetManager()->ClearDrawTarget();
		}

		this->GetManager()->ClearDrawStageData();
	}

	this->ClearDrawCamera();
	this->ClearDrawLight();
	this->ClearDrawFog();
	this->ClearDrawModel();

	return;
}
