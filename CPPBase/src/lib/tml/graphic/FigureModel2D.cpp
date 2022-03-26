/**
 * @file
 * @brief FigureModel2Dコードファイル
 */


#include "FigureModel2D.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "FigureModel2DShaderStructuredBuffer.h"
#include "FigureModel2DLayerShaderStructuredBuffer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"
#include "Canvas2D.h"


const D3D11_INPUT_ELEMENT_DESC tml::graphic::FigureModel2D::INPUT_ELEMENT_DESC_ARRAY[tml::graphic::FigureModel2D::INPUT_ELEMENT_DESC_COUNT] = {
	{"POSITION", 0U, DXGI_FORMAT_R32G32B32A32_FLOAT, 0U, 0U, D3D11_INPUT_PER_VERTEX_DATA, 0U},
	{"TEXCOORD", 0U, DXGI_FORMAT_R32G32_FLOAT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U},
	{"LAYER_INDEX", 0U, DXGI_FORMAT_R32_UINT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U}
};


/**
 * @brief コンストラクタ
 */
tml::graphic::FigureModel2DLayer::FigureModel2DLayer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FigureModel2DLayer::~FigureModel2DLayer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::FigureModel2DLayer::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FigureModel2DLayer::Init(void)
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
INT tml::graphic::FigureModel2DLayer::Create(tml::graphic::Manager *mgr)
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
tml::graphic::FigureModel2DStage::FigureModel2DStage()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FigureModel2DStage::~FigureModel2DStage()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::FigureModel2DStage::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FigureModel2DStage::Init(void)
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
INT tml::graphic::FigureModel2DStage::Create(tml::graphic::Manager *mgr)
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
tml::graphic::FigureModel2DDesc::FigureModel2DDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FigureModel2DDesc::~FigureModel2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FigureModel2DDesc::Init(void)
{
	this->Release();

	this->diffuse_texture.reset();
	this->diffuse_texture_desc.reset();

	tml::graphic::Model2DDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::FigureModel2DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::Model2DDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// FigureModel2D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FIGURE_MODEL_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::FigureModel2D::FigureModel2D() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FigureModel2D::~FigureModel2D()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::FigureModel2D::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FigureModel2D::Init(void)
{
	this->Release();

	this->ssb_.reset();
	this->layer_ssb_.reset();

	tml::graphic::Model2D::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::FigureModel2D::OnCreate(void)
{
	if (tml::graphic::Model2D::OnCreate() < 0) {
		return (-1);
	}

	tml::XMFLOAT2EX size;

	{// Forward2DStage Create
		auto stage = tml::make_unique<tml::graphic::FigureModel2DStage>(1U);

		if (stage->Create(this->GetManager()) < 0) {
			return (-1);
		}

		stage->SetRasterizerStateIndex(0U);
		stage->SetBlendStateIndex(0U);
		stage->SetDepthStateIndex(0U);
		stage->SetShaderIndex(0U);

		{// RasterizerState Create
			tml::shared_ptr<tml::graphic::RasterizerState> rs;

			if (this->GetManager()->GetResource<tml::graphic::RasterizerState>(rs, this->GetManager()->common.back_culling_rasterizer_state) == nullptr) {
				return (-1);
			}

			this->SetRasterizerState(stage->GetRasterizerStateIndex(), rs);
		}

		{// BlendState Create
			tml::shared_ptr<tml::graphic::BlendState> bs;

			if (this->GetManager()->GetResource<tml::graphic::BlendState>(bs, this->GetManager()->common.alignment_blend_state_array[1]) == nullptr) {
				return (-1);
			}

			this->SetBlendState(stage->GetBlendStateIndex(), bs);
		}

		{// DepthState Create
			tml::shared_ptr<tml::graphic::DepthState> ds;

			if (this->GetManager()->GetResource<tml::graphic::DepthState>(ds, this->GetManager()->common.reference_depth_state) == nullptr) {
				return (-1);
			}

			this->SetDepthState(stage->GetDepthStateIndex(), ds);
		}

		{// Shader Create
			tml::shared_ptr<tml::graphic::Shader> shader;

			if (this->GetManager()->GetResource<tml::graphic::Shader>(shader, this->GetManager()->common.figure_model_2d_shader) == nullptr) {
				return (-1);
			}

			this->SetShader(stage->GetShaderIndex(), shader);
		}

		{// Layer0 Create
			auto layer = tml::make_unique<tml::graphic::FigureModel2DLayer>(1U);

			if (layer->Create(this->GetManager()) < 0) {
				return (-1);
			}

			layer->SetMeshIndex(0U);
			layer->SetDiffuseTextureIndex(0U);
			layer->SetDiffuseSamplerIndex(0U);

			{// Mesh Create
				tml::shared_ptr<tml::graphic::Mesh> mesh;

				if (this->GetManager()->GetResource<tml::graphic::Mesh>(mesh, this->GetManager()->common.figure_model_2d_mesh) == nullptr) {
					return (-1);
				}

				this->SetMesh(layer->GetMeshIndex(), mesh);
			}

			// DiffuseTexture Create
			if (this->desc_->diffuse_texture != nullptr) {
				tml::shared_ptr<tml::graphic::Texture> tex;

				if (this->GetManager()->GetResource<tml::graphic::Texture>(tex, this->desc_->diffuse_texture) == nullptr) {
					return (-1);
				}

				this->SetTexture(layer->GetDiffuseTextureIndex(), tex);

				size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetRect().GetSize().x), static_cast<FLOAT>(tex->GetRect().GetSize().y));
			} else if (this->desc_->diffuse_texture_desc != nullptr) {
				tml::shared_ptr<tml::graphic::Texture> tex;

				if (this->GetManager()->GetResource<tml::graphic::Texture>(tex, (*this->desc_->diffuse_texture_desc)) == nullptr) {
					return (-1);
				}

				this->SetTexture(layer->GetDiffuseTextureIndex(), tex);

				size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetRect().GetSize().x), static_cast<FLOAT>(tex->GetRect().GetSize().y));
			} else {
				this->SetTexture(layer->GetDiffuseTextureIndex(), tml::shared_ptr<tml::graphic::Texture>());
			}

			{// DiffuseSampler Create
				tml::shared_ptr<tml::graphic::Sampler> samp;

				if (this->GetManager()->GetResource<tml::graphic::Sampler>(samp, this->GetManager()->common.cc_sampler) == nullptr) {
					return (-1);
				}

				this->SetSampler(layer->GetDiffuseSamplerIndex(), samp);
			}

			stage->SetLayer(0U, layer);
		}

		this->SetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D, stage);
	}

	if (this->desc_->size_auto_flag) {
		this->size = size;
	} else {
		this->size = this->desc_->size;
	}

	{// ShaderStructuredBuffer Create
		tml::graphic::FigureModel2DShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->GetManager());
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::FigureModel2DShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::FigureModel2DShaderStructuredBuffer>(this->ssb_, ssb_desc) == nullptr) {
			return (-1);
		}
	}

	{// LayerShaderStructuredBuffer Create
		tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->GetManager());
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::FigureModel2DLayerShaderStructuredBuffer>(this->layer_ssb_, ssb_desc) == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::FigureModel2D::OnCreateDeferred(void)
{
	if (tml::graphic::Model2D::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::FigureModel2D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::FigureModel2DDesc *>(desc);

	tml::graphic::Model2D::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief IsHitByMouseDevice関数
 * @param mouse_device_pos (mouse_device_position)
 * @return hit_flg (hit_flag)
 */
bool tml::graphic::FigureModel2D::IsHitByMouseDevice(const tml::XMINT2EX &mouse_device_pos)
{
	tml::XMFLOAT2EX tmp_mouse_device_pos;

	tmp_mouse_device_pos.x = static_cast<FLOAT>(mouse_device_pos.x - static_cast<INT>(this->GetManager()->GetSize().GetHalfX()));
	tmp_mouse_device_pos.y = static_cast<FLOAT>(-mouse_device_pos.y + static_cast<INT>(this->GetManager()->GetSize().GetHalfY()));

	if ((tmp_mouse_device_pos.x >= (this->transform.position.x - (this->size.GetHalfX() * this->transform.scale.x)))
	&& (tmp_mouse_device_pos.x <= (this->transform.position.x + (this->size.GetHalfX() * this->transform.scale.x)))
	&& (tmp_mouse_device_pos.y >= (this->transform.position.y - (this->size.GetHalfY() * this->transform.scale.y)))
	&& (tmp_mouse_device_pos.y <= (this->transform.position.y + (this->size.GetHalfY() * this->transform.scale.y)))
	) {
		return (true);
	}

	return (false);
}


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::FigureModel2D::DrawStageInit(void)
{
	auto stage = this->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	auto layer = stage->GetLayer(0U);

	auto w_mat = DirectX::XMMatrixMultiply(
		DirectX::XMMatrixTransformation2D(DirectX::g_XMZero, 0.0f, DirectX::XMVectorSet(this->size.x * this->transform.scale.x, this->size.y * this->transform.scale.y, 0.0f, 0.0f), DirectX::g_XMZero, this->transform.angle, DirectX::XMVectorSet(this->transform.position.x, this->transform.position.y, 0.0f, 0.0f)),
		DirectX::XMMatrixTransformation2D(DirectX::g_XMZero, 0.0f, DirectX::XMVectorSet(this->draw_data->transform.scale.x, this->draw_data->transform.scale.y, 0.0f, 0.0f), DirectX::g_XMZero, this->draw_data->transform.angle, DirectX::XMVectorSet(this->draw_data->transform.position.x, this->draw_data->transform.position.y, 0.0f, 0.0f))
	);
	auto col = this->color * this->draw_data->color;

	this->ssb_->SetElement(0U, w_mat, this->draw_data->canvas->stage->view_matrix, this->draw_data->canvas->stage->projection_matrix, col);
	this->ssb_->UploadCPUBuffer();

	this->layer_ssb_->SetElement(0U, this->GetTexture(layer->GetDiffuseTextureIndex()).get());
	this->layer_ssb_->UploadCPUBuffer();

	return;
}


/**
 * @brief DrawStageForward2D関数
 */
void tml::graphic::FigureModel2D::DrawStageForward2D(void)
{
	auto stage = this->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	auto layer = stage->GetLayer(0U);

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
