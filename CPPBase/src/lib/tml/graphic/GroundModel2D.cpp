/**
 * @file
 * @brief GroundModel2Dコードファイル
 */


#include "GroundModel2D.h"
#include "../string/StringUtil.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "Model2DShaderStructuredBuffer.h"
#include "Model2DLayerShaderStructuredBuffer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DLayer::GroundModel2DLayer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DLayer::~GroundModel2DLayer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::GroundModel2DLayer::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DLayer::Init(void)
{
	this->Release();

	tml::graphic::Model2DLayer::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2DLayer::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::Model2DLayer::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DStage::GroundModel2DStage()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DStage::~GroundModel2DStage()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::GroundModel2DStage::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DStage::Init(void)
{
	this->Release();

	tml::graphic::Model2DStage::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2DStage::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::Model2DStage::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DDesc::GroundModel2DDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DDesc::~GroundModel2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DDesc::Init(void)
{
	this->Release();

	this->file_read_desc.Init();

	tml::graphic::Model2DDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::Model2DDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// GroundModel2D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"GROUND_MODEL_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2D::GroundModel2D() :
	mass_cnt_(0U),
	mass_size_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2D::~GroundModel2D()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::GroundModel2D::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2D::Init(void)
{
	this->Release();

	this->mass_cnt_ = 0U;
	this->mass_size_ = 0U;
	this->mass_type_cont_.clear();

	tml::graphic::Model2D::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2D::Create(const tml::graphic::GroundModel2DDesc &desc)
{
	this->Init();

	if (tml::graphic::Model2D::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto file_read_desc_dat = desc.file_read_desc.GetDataByParent();

	tml::XMLFile xml_file;

	xml_file.read_desc.parent_data = file_read_desc_dat;

	if (xml_file.Read() < 0) {
		this->Init();

		return (-1);
	}

	auto &xml_file_root_node = xml_file.data.GetRootNode();

	if (xml_file_root_node->GetChildNodeContainer().empty()) {
		this->Init();

		return (-1);
	}

	auto &xml_file_map_node = xml_file_root_node->GetChildNode(L"map");

	if (xml_file_map_node == nullptr) {
		this->Init();

		return (-1);
	}

	auto &xml_file_img_node = xml_file_root_node->GetChildNode(L"image");

	if (xml_file_img_node == nullptr) {
		this->Init();

		return (-1);
	}

	auto &xml_file_dat_node = xml_file_root_node->GetChildNode(L"data");

	if (xml_file_dat_node == nullptr) {
		this->Init();

		return (-1);
	}

	const std::wstring *val = nullptr;
	std::vector<std::wstring> val_cont;

	val = xml_file_map_node->GetValue(L"width");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->mass_cnt_.x, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	val = xml_file_map_node->GetValue(L"height");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->mass_cnt_.y, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	val = xml_file_map_node->GetValue(L"tilewidth");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->mass_size_.x, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	val = xml_file_map_node->GetValue(L"tileheight");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->mass_size_.y, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	tml::StringUtil::Split(val_cont, xml_file_dat_node->string.c_str(), L",");

	this->mass_type_cont_.resize(val_cont.size());

	for (size_t val_i = 0U; val_i < val_cont.size(); ++val_i) {
		tml::StringUtil::GetValue(this->mass_type_cont_[val_i], val_cont[val_i].c_str());
	}

	std::wstring mass_img_file_path;

	val = xml_file_img_node->GetValue(L"source");

	if (val != nullptr) {
		mass_img_file_path = L"res/";
		mass_img_file_path += (*val);
	} else {
		this->Init();

		return (-1);
	}

	{// Forward2DStage Create
		auto stage = tml::make_unique<tml::graphic::GroundModel2DStage>(1U);

		if (stage->Create(this->GetManager()) < 0) {
			this->Init();

			return (-1);
		}

		stage->SetRasterizerStateIndex(0U);
		stage->SetBlendStateIndex(0U);
		stage->SetDepthStateIndex(0U);
		stage->SetShaderIndex(0U);

		{// RasterizerState Create
			tml::shared_ptr<tml::graphic::RasterizerState> rs;

			if (this->GetManager()->GetResource<tml::graphic::RasterizerState>(rs, this->GetManager()->common.back_culling_rasterizer_state) == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetRasterizerState(stage->GetRasterizerStateIndex(), rs);
		}

		{// BlendState Create
			tml::shared_ptr<tml::graphic::BlendState> bs;

			if (this->GetManager()->GetResource<tml::graphic::BlendState>(bs, this->GetManager()->common.alignment_blend_state_array[1]) == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetBlendState(stage->GetBlendStateIndex(), bs);
		}

		{// DepthState Create
			tml::shared_ptr<tml::graphic::DepthState> ds;

			if (this->GetManager()->GetResource<tml::graphic::DepthState>(ds, this->GetManager()->common.reference_depth_state) == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetDepthState(stage->GetDepthStateIndex(), ds);
		}

		{// Shader Create
			tml::shared_ptr<tml::graphic::Shader> shader;

			if (this->GetManager()->GetResource<tml::graphic::Shader>(shader, this->GetManager()->common.figure_model_2d_shader) == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetShader(stage->GetShaderIndex(), shader);
		}

		{// Layer0 Create
			auto layer = tml::make_unique<tml::graphic::GroundModel2DLayer>(1U);

			if (layer->Create(this->GetManager()) < 0) {
				this->Init();

				return (-1);
			}

			layer->SetMeshIndex(0U);
			layer->SetDiffuseSamplerIndex(0U);

			{// Mesh Create
				tml::shared_ptr<tml::graphic::Mesh> mesh;

				if (this->GetManager()->GetResource<tml::graphic::Mesh>(mesh, this->GetManager()->common.model_2d_plane_mesh) == nullptr) {
					this->Init();

					return (-1);
				}

				this->SetMesh(layer->GetMeshIndex(), mesh);
			}

			{// DiffuseSampler Create
				tml::shared_ptr<tml::graphic::Sampler> samp;

				if (this->GetManager()->GetResource<tml::graphic::Sampler>(samp, this->GetManager()->common.cc_sampler) == nullptr) {
					this->Init();

					return (-1);
				}

				this->SetSampler(layer->GetDiffuseSamplerIndex(), samp);
			}

			stage->SetLayer(0U, layer);
		}

		this->SetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D, stage);
	}

	{// ShaderStructuredBuffer Create
		tml::graphic::Model2DShaderStructuredBufferDesc desc;

		desc.SetManager(this->GetManager());
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::Model2DShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::Model2DShaderStructuredBuffer>(this->ssb_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LayerShaderStructuredBuffer Create
		tml::graphic::Model2DLayerShaderStructuredBufferDesc desc;

		desc.SetManager(this->GetManager());
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::Model2DLayerShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::Model2DLayerShaderStructuredBuffer>(this->layer_ssb_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief IsHitByMouseDevice関数
 * @param mouse_device_pos (mouse_device_position)
 * @return hit_flg (hit_flag)
 */
bool tml::graphic::GroundModel2D::IsHitByMouseDevice(const tml::XMINT2EX &mouse_device_pos)
{
	tml::XMFLOAT2EX tmp_mouse_device_pos;

	tmp_mouse_device_pos.x = static_cast<FLOAT>(mouse_device_pos.x - static_cast<INT>(this->GetManager()->GetSize().GetHalfX()));
	tmp_mouse_device_pos.y = static_cast<FLOAT>(-mouse_device_pos.y + static_cast<INT>(this->GetManager()->GetSize().GetHalfY()));

	if ((tmp_mouse_device_pos.x >= (this->position.GetX() - (this->size.GetHalfX() * this->scale.x)))
	&& (tmp_mouse_device_pos.x <= (this->position.GetX() + (this->size.GetHalfX() * this->scale.x)))
	&& (tmp_mouse_device_pos.y >= (this->position.GetY() - (this->size.GetHalfY() * this->scale.y)))
	&& (tmp_mouse_device_pos.y <= (this->position.GetY() + (this->size.GetHalfY() * this->scale.y)))
	) {
		return (true);
	}

	return (false);
}


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::GroundModel2D::DrawStageInit(void)
{
	auto stage = this->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	auto layer = stage->GetLayerFast(0U);

	DirectX::XMMATRIX w_mat;

	this->GetManager()->GetWorldMatrix(w_mat, (*this));

	this->ssb_->SetElement(0U, w_mat, this->GetManager()->GetDrawStageData()->view_matrix, this->GetManager()->GetDrawStageData()->projection_matrix, this->color);
	this->ssb_->UploadCPUBuffer();

	this->layer_ssb_->SetElement(0U, this->GetTexture(layer->GetDiffuseTextureIndex()).get());
	this->layer_ssb_->UploadCPUBuffer();

	return;
}


/**
 * @brief DrawStageForward2D関数
 */
void tml::graphic::GroundModel2D::DrawStageForward2D(void)
{
	auto stage = this->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	auto layer = stage->GetLayerFast(0U);

	std::array<tml::graphic::ShaderStructuredBuffer *, 2U> ssb_ary = {this->ssb_.get(), this->layer_ssb_.get()};

	this->GetManager()->SetDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::MODEL, ssb_ary.size(), ssb_ary.data());

	this->GetManager()->SetDrawRasterizerState(this->GetRasterizerState(stage->GetRasterizerStateIndex()).get());
	this->GetManager()->SetDrawBlendState(this->GetBlendState(stage->GetBlendStateIndex()).get());
	this->GetManager()->SetDrawDepthState(this->GetDepthState(stage->GetDepthStateIndex()).get());
	this->GetManager()->SetDrawShader(this->GetShader(stage->GetShaderIndex()).get());
	this->GetManager()->SetDrawMesh(this->GetMesh(layer->GetMeshIndex()).get());

	this->GetManager()->SetDrawTextureSR(0U, this->GetTexture(layer->GetDiffuseTextureIndex()).get());
	this->GetManager()->SetDrawSamplerSR(0U, this->GetSampler(layer->GetDiffuseSamplerIndex()).get());

	this->GetManager()->Draw(1U);

	this->GetManager()->ClearDrawTextureSR(0U);
	this->GetManager()->ClearDrawSamplerSR(0U);

	return;
}
