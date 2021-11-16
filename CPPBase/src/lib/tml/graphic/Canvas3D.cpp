/**
 * @file
 * @brief Canvas3D�R�[�h�t�@�C��
 */


#include "Canvas3D.h"
#include "Manager.h"
#include "ConfigShaderConstantBuffer.h"
#include "HeaderShaderConstantBuffer.h"
#include "Camera3DShaderStructuredBuffer.h"
#include "Light3DShaderStructuredBuffer.h"
#include "Fog3DShaderStructuredBuffer.h"
#include "Texture.h"
#include "Sampler.h"
#include "Camera3D.h"
#include "Light3D.h"
#include "Fog3D.h"
#include "Model3D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Canvas3DDesc::Canvas3DDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Canvas3DDesc::~Canvas3DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Canvas3DDesc::Init(void)
{
	this->Release();

	tml::graphic::CanvasDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas3DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::CanvasDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Canvas3D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"CANVAS_3D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Canvas3D::Canvas3D() :
	rt_tex_clear_flg_(false),
	dt_tex_clear_flg_(false),
	vp_(0.0f, 0.0f, 1.0f, 1.0f),
	vp_x_(0.0f),
	vp_y_(0.0f),
	vp_w_(1.0f),
	vp_h_(1.0f),
	draw_light_cnt_(0U),
	draw_light_ary_{},
	draw_light_index_ary_{},
	draw_fog_cnt_(0U),
	draw_fog_ary_{},
	draw_fog_index_ary_{},
	draw_model_cnt_(0U),
	draw_model_ary_{},
	draw_model_index_ary_{}
{
	for (auto &draw_light_dat : this->draw_light_dat_ary_) {
		draw_light_dat.canvas = &this->draw_data;
	}

	for (auto &draw_fog_dat : this->draw_fog_dat_ary_) {
		draw_fog_dat.canvas = &this->draw_data;
	}

	for (auto &draw_model_dat : this->draw_model_dat_ary_) {
		draw_model_dat.canvas = &this->draw_data;
	}

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Canvas3D::~Canvas3D()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Canvas3D::Init(void)
{
	this->Release();

	this->camera_.reset();
	this->rt_tex_.reset();
	this->rt_tex_clear_flg_ = false;
	this->dt_tex_.reset();
	this->dt_tex_clear_flg_ = false;
	this->vp_.Init();
	this->vp_x_ = 0.0f;
	this->vp_y_ = 0.0f;
	this->vp_w_ = 1.0f;
	this->vp_h_ = 1.0f;
	this->draw_light_cnt_ = 0U;
	this->draw_fog_cnt_ = 0U;
	this->draw_model_cnt_ = 0U;

	tml::graphic::Canvas::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas3D::Create(const tml::graphic::Canvas3DDesc &desc)
{
	this->Init();

	if (tml::graphic::Canvas::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief SetCamera�֐�
 * @param camera (camera)
 */
void tml::graphic::Canvas3D::SetCamera(const tml::shared_ptr<tml::graphic::Camera3D> &camera)
{
	this->camera_ = camera;

	return;
}


/**
 * @brief SetRenderTargetTexture�֐�
 * @param rt_tex (render_target_texture)
 */
void tml::graphic::Canvas3D::SetRenderTargetTexture(const tml::shared_ptr<tml::graphic::Texture> &rt_tex)
{
	this->rt_tex_ = rt_tex;

	return;
}


/**
 * @brief SetDepthTargetTexture�֐�
 * @param dt_tex (depth_target_texture)
 */
void tml::graphic::Canvas3D::SetDepthTargetTexture(const tml::shared_ptr<tml::graphic::Texture> &dt_tex)
{
	this->dt_tex_ = dt_tex;

	return;
}


/**
 * @brief Draw�֐�
 */
void tml::graphic::Canvas3D::Draw(void)
{
	if (this->camera_ != nullptr) {
		auto rt_tex = this->GetRenderTargetTexture().get();
		auto rt_tex_clear_flg = this->GetRenderTargetTextureClearFlag();
		auto vp = &this->vp_;

		vp->SetX(static_cast<FLOAT>(rt_tex->GetRect().GetSize().x) * this->vp_x_);
		vp->SetY(static_cast<FLOAT>(rt_tex->GetRect().GetSize().y) * this->vp_y_);
		vp->SetWidth(static_cast<FLOAT>(rt_tex->GetRect().GetSize().x) * this->vp_w_);
		vp->SetHeight(static_cast<FLOAT>(rt_tex->GetRect().GetSize().y) * this->vp_h_);

		DirectX::XMMATRIX v_mat;
		DirectX::XMMATRIX inv_v_mat;
		DirectX::XMMATRIX p_mat;

		this->camera_->GetViewMatrix(v_mat);
		inv_v_mat = DirectX::XMMatrixInverse(nullptr, v_mat);
		this->camera_->GetProjectionMatrix(p_mat);

		tml::graphic::DRAW_STAGE_3D_DATA draw_stage_dat(v_mat, inv_v_mat, p_mat);

		this->draw_data.stage = &draw_stage_dat;

		std::array<tml::graphic::ShaderConstantBuffer *, 2U> sys_scb_ary = {this->GetManager()->common.config_shader_constant_buffer.get(), this->GetManager()->common.header_shader_constant_buffer.get()};
		std::array<tml::graphic::ShaderStructuredBuffer *, 5U> sys_ssb_ary = {this->GetManager()->common.camera_3d_shader_structured_buffer.get(), this->GetManager()->common.light_3d_shader_structured_buffer.get(), this->GetManager()->common.fog_3d_shader_structured_buffer.get(), nullptr, nullptr};
		tml::graphic::Light3D *draw_light = nullptr;
		tml::graphic::Fog3D *draw_fog = nullptr;
		tml::graphic::Model3D *draw_model = nullptr;

		while (draw_stage_dat.type != tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE) {
			switch (draw_stage_dat.type) {
			case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::INIT: {
				if (rt_tex_clear_flg) {
					rt_tex->ClearRenderTarget(tml::XMFLOAT4EX(0.0f, 0.0f, 0.0f, 1.0f));
				}

				this->GetManager()->common.header_shader_constant_buffer->SetElement(2U, this->draw_light_cnt_, this->draw_fog_cnt_, this->draw_model_cnt_);
				this->GetManager()->common.header_shader_constant_buffer->UploadCPUBuffer();

				this->GetManager()->common.camera_3d_shader_structured_buffer->SetElementCount(0U);
				this->GetManager()->common.camera_3d_shader_structured_buffer->SetElement(0U, draw_stage_dat.view_matrix, draw_stage_dat.inverse_view_matrix, draw_stage_dat.projection_matrix);
				this->GetManager()->common.camera_3d_shader_structured_buffer->UploadCPUBuffer();

				this->GetManager()->common.light_3d_shader_structured_buffer->SetElementCount(0U);

				for (UINT draw_light_i = 0U; draw_light_i < this->draw_light_cnt_; ++draw_light_i) {
					draw_light = this->draw_light_ary_[this->draw_light_index_ary_[draw_light_i]];

					draw_light->draw_data = &this->draw_light_dat_ary_[this->draw_light_index_ary_[draw_light_i]];
					draw_light->draw_data->shader_structured_buffer = this->GetManager()->common.light_3d_shader_structured_buffer.get();
					draw_light->draw_data->shader_structured_buffer_element_index = draw_light_i;

					draw_light->DrawStageInit();
				}

				this->GetManager()->common.light_3d_shader_structured_buffer->UploadCPUBuffer();

				this->GetManager()->common.fog_3d_shader_structured_buffer->SetElementCount(0U);

				for (UINT draw_fog_i = 0U; draw_fog_i < this->draw_fog_cnt_; ++draw_fog_i) {
					draw_fog = this->draw_fog_ary_[this->draw_fog_index_ary_[draw_fog_i]];

					draw_fog->draw_data = &this->draw_fog_dat_ary_[this->draw_fog_index_ary_[draw_fog_i]];
					draw_fog->draw_data->shader_structured_buffer = this->GetManager()->common.fog_3d_shader_structured_buffer.get();
					draw_fog->draw_data->shader_structured_buffer_element_index = draw_fog_i;

					draw_fog->DrawStageInit();
				}

				this->GetManager()->common.fog_3d_shader_structured_buffer->UploadCPUBuffer();

				for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
					draw_model = this->draw_model_ary_[this->draw_model_index_ary_[draw_model_i]];

					draw_model->draw_data = &this->draw_model_dat_ary_[this->draw_model_index_ary_[draw_model_i]];

					draw_model->DrawStageInit();
				}

				this->GetManager()->SetDrawShaderConstantBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, sys_scb_ary.size(), sys_scb_ary.data());
				this->GetManager()->SetDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::SYSTEM, sys_ssb_ary.size(), sys_ssb_ary.data());

				draw_stage_dat.type = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_3D;

				break;
			}
			case tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_3D: {
				this->GetManager()->SetDrawTargetTexture(rt_tex, nullptr);
				this->GetManager()->SetDrawViewport(vp);

				for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
					draw_model = this->draw_model_ary_[this->draw_model_index_ary_[draw_model_i]];

					draw_model->DrawStageForward3D();
				}

				this->GetManager()->ClearDrawTargetTexture();
				this->GetManager()->ClearDrawViewport();

				this->GetManager()->ClearDrawShaderConstantBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_SR_INDEX::SYSTEM, sys_scb_ary.size());
				this->GetManager()->ClearDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::SYSTEM, sys_ssb_ary.size());

				draw_stage_dat.type = tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::NONE;

				break;
			}
			}
		}
	}

	this->ClearDrawLight();
	this->ClearDrawFog();
	this->ClearDrawModel();

	return;
}


/**
 * @brief SetDrawLight�֐�
 * @param light (light)
 * @param transform (transform)
 */
void tml::graphic::Canvas3D::SetDrawLight(tml::graphic::Light3D *light, const tml::Transform3D &transform)
{
	if ((light == nullptr)
	|| (light->IsDrawSet(this))
	|| (this->draw_light_cnt_ >= tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT)) {
		return;
	}

	if ((this->draw_light_cnt_ <= 0U)
	|| (light->GetDrawPriority() >= this->draw_light_ary_[this->draw_light_index_ary_[this->draw_light_cnt_ - 1U]]->GetDrawPriority())) {
		this->draw_light_index_ary_[this->draw_light_cnt_] = this->draw_light_cnt_;
	} else {
		for (UINT draw_light_i = 0U; draw_light_i < this->draw_light_cnt_; ++draw_light_i) {
			if (light->GetDrawPriority() < this->draw_light_ary_[this->draw_light_index_ary_[draw_light_i]]->GetDrawPriority()) {
				memmove(&this->draw_light_index_ary_[draw_light_i + 1U], &this->draw_light_index_ary_[draw_light_i], sizeof(this->draw_light_index_ary_[0]) * (this->draw_light_cnt_ - draw_light_i));

				this->draw_light_index_ary_[draw_light_i] = this->draw_light_cnt_;

				break;
			}
		}
	}

	light->SetDrawSet(this);
	this->draw_light_dat_ary_[this->draw_light_cnt_].SetDrawSet(transform);

	this->draw_light_ary_[this->draw_light_cnt_++] = light;

	return;
}


/**
 * @brief ClearDrawLight�֐�
 */
void tml::graphic::Canvas3D::ClearDrawLight(void)
{
	for (UINT draw_light_i = 0U; draw_light_i < this->draw_light_cnt_; ++draw_light_i) {
		this->draw_light_ary_[this->draw_light_index_ary_[draw_light_i]]->ClearDrawSet(this);
	}

	this->draw_light_cnt_ = 0U;

	return;
}


/**
 * @brief SetDrawFog�֐�
 * @param fog (fog)
 * @param transform (transform)
 */
void tml::graphic::Canvas3D::SetDrawFog(tml::graphic::Fog3D *fog, const tml::Transform3D &transform)
{
	if ((fog == nullptr)
	|| (fog->IsDrawSet(this))
	|| (this->draw_fog_cnt_ >= tml::ConstantUtil::GRAPHIC::FOG_LIMIT)) {
		return;
	}

	if ((this->draw_fog_cnt_ <= 0U)
	|| (fog->GetDrawPriority() >= this->draw_fog_ary_[this->draw_fog_index_ary_[this->draw_fog_cnt_ - 1U]]->GetDrawPriority())) {
		this->draw_fog_index_ary_[this->draw_fog_cnt_] = this->draw_fog_cnt_;
	} else {
		for (UINT draw_fog_i = 0U; draw_fog_i < this->draw_fog_cnt_; ++draw_fog_i) {
			if (fog->GetDrawPriority() < this->draw_fog_ary_[this->draw_fog_index_ary_[draw_fog_i]]->GetDrawPriority()) {
				memmove(&this->draw_fog_index_ary_[draw_fog_i + 1U], &this->draw_fog_index_ary_[draw_fog_i], sizeof(this->draw_fog_index_ary_[0]) * (this->draw_fog_cnt_ - draw_fog_i));

				this->draw_fog_index_ary_[draw_fog_i] = this->draw_fog_cnt_;

				break;
			}
		}
	}

	fog->SetDrawSet(this);
	this->draw_fog_dat_ary_[this->draw_fog_cnt_].SetDrawSet(transform);

	this->draw_fog_ary_[this->draw_fog_cnt_++] = fog;

	return;
}


/**
 * @brief ClearDrawFog�֐�
 */
void tml::graphic::Canvas3D::ClearDrawFog(void)
{
	for (UINT draw_fog_i = 0U; draw_fog_i < this->draw_fog_cnt_; ++draw_fog_i) {
		this->draw_fog_ary_[this->draw_fog_index_ary_[draw_fog_i]]->ClearDrawSet(this);
	}

	this->draw_fog_cnt_ = 0U;

	return;
}


/**
 * @brief SetDrawModel�֐�
 * @param model (model)
 * @param transform (transform)
 */
void tml::graphic::Canvas3D::SetDrawModel(tml::graphic::Model3D *model, const tml::Transform3D &transform)
{
	if ((model == nullptr)
	|| (model->IsDrawSet(this))
	|| (this->draw_model_cnt_ >= tml::ConstantUtil::GRAPHIC::MODEL_LIMIT)) {
		return;
	}

	if ((this->draw_model_cnt_ <= 0U)
	|| (model->GetDrawPriority() >= this->draw_model_ary_[this->draw_model_index_ary_[this->draw_model_cnt_ - 1U]]->GetDrawPriority())) {
		this->draw_model_index_ary_[this->draw_model_cnt_] = this->draw_model_cnt_;
	} else {
		for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
			if (model->GetDrawPriority() < this->draw_model_ary_[this->draw_model_index_ary_[draw_model_i]]->GetDrawPriority()) {
				memmove(&this->draw_model_index_ary_[draw_model_i + 1U], &this->draw_model_index_ary_[draw_model_i], sizeof(this->draw_model_index_ary_[0]) * (this->draw_model_cnt_ - draw_model_i));

				this->draw_model_index_ary_[draw_model_i] = this->draw_model_cnt_;

				break;
			}
		}
	}

	model->SetDrawSet(this);
	this->draw_model_dat_ary_[this->draw_model_cnt_].SetDrawSet(transform);

	this->draw_model_ary_[this->draw_model_cnt_++] = model;

	return;
}


/**
 * @brief ClearDrawModel�֐�
 */
void tml::graphic::Canvas3D::ClearDrawModel(void)
{
	for (UINT draw_model_i = 0U; draw_model_i < this->draw_model_cnt_; ++draw_model_i) {
		this->draw_model_ary_[this->draw_model_index_ary_[draw_model_i]]->ClearDrawSet(this);
	}

	this->draw_model_cnt_ = 0U;

	return;
}
