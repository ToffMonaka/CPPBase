/**
 * @file
 * @brief SpriteModelコードファイル
 */


#include "SpriteModel.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "ModelShaderStructuredBuffer.h"
#include "ModelLayerShaderStructuredBuffer.h"
#include "Mesh.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModelLayer::SpriteModelLayer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModelLayer::~SpriteModelLayer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModelLayer::Init(void)
{
	this->Release();

	tml::graphic::ModelLayer::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModelLayer::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::ModelLayer::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModelStage::SpriteModelStage()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModelStage::~SpriteModelStage()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModelStage::Init(void)
{
	this->Release();

	tml::graphic::ModelStage::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModelStage::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::ModelStage::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModelDesc::SpriteModelDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModelDesc::~SpriteModelDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModelDesc::Init(void)
{
	this->Release();

	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModelDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ModelDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SpriteModel Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SPRITE_MODEL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModel::SpriteModel()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModel::~SpriteModel()
{
	if (this->GetManager() != nullptr) {
		this->GetManager()->ReleaseResource(this->ssb_);
		this->GetManager()->ReleaseResource(this->layer_ssb_);
	}

	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModel::Init(void)
{
	this->Release();

	tml::graphic::Model::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param pos (position)<br>
 * nullptr=指定無し
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModel::Create(const tml::graphic::SpriteModelDesc &desc, tml::shared_ptr<tml::XMPosition> *pos)
{
	this->Init();

	if (tml::graphic::Model::Create(desc, tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SPRITE, pos) < 0) {
		this->Init();

		return (-1);
	}

	{// Forward2DStage Create
		auto stage = tml::make_unique<tml::graphic::SpriteModelStage>(1U);

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

			this->GetManager()->GetResource(rs, this->GetManager()->common.back_culling_rasterizer_state);

			if (rs == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetRasterizerState(stage->GetRasterizerStateIndex(), rs);
			this->GetManager()->ReleaseResource(rs);
		}

		{// BlendState Create
			tml::shared_ptr<tml::graphic::BlendState> bs;

			this->GetManager()->GetResource(bs, this->GetManager()->common.alignment_blend_state_array[1]);

			if (bs == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetBlendState(stage->GetBlendStateIndex(), bs);
			this->GetManager()->ReleaseResource(bs);
		}

		{// DepthState Create
			tml::shared_ptr<tml::graphic::DepthState> ds;

			this->GetManager()->GetResource(ds, this->GetManager()->common.reference_depth_state);

			if (ds == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetDepthState(stage->GetDepthStateIndex(), ds);
			this->GetManager()->ReleaseResource(ds);
		}

		{// Shader Create
			tml::shared_ptr<tml::graphic::Shader> shader;

			this->GetManager()->GetResource(shader, this->GetManager()->common.sprite_model_shader);

			if (shader == nullptr) {
				this->Init();

				return (-1);
			}

			this->SetShader(stage->GetShaderIndex(), shader);
			this->GetManager()->ReleaseResource(shader);
		}

		{// Layer1 Create
			auto layer = tml::make_unique<tml::graphic::SpriteModelLayer>(1U);

			if (layer->Create(this->GetManager()) < 0) {
				this->Init();

				return (-1);
			}

			layer->SetMeshIndex(0U);

			{// Mesh Create
				tml::shared_ptr<tml::graphic::Mesh> mesh;

				tml::graphic::MeshDesc desc;
				std::array<tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT, 4U> vb_element_ary = {
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.0f,  0.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  0.0f), 0U),
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 1.0f,  0.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  0.0f), 0U),
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.0f, -1.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  1.0f), 0U),
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 1.0f, -1.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  1.0f), 0U)
				};
				std::array<UINT, 4U> ib_element_ary = {0U, 1U, 2U, 3U};

				desc.manager = this->GetManager();
				desc.vertex_buffer_element_size = sizeof(tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT);
				desc.vertex_buffer_element_count = vb_element_ary.size();
				desc.vertex_buffer_element_array = reinterpret_cast<BYTE *>(vb_element_ary.data());
				desc.index_buffer_element_count = ib_element_ary.size();
				desc.index_buffer_element_array = ib_element_ary.data();
				desc.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

				this->GetManager()->GetResource<tml::graphic::Mesh>(mesh, desc);

				if (mesh == nullptr) {
					this->Init();

					return (-1);
				}

				this->SetMesh(layer->GetMeshIndex(), mesh);
				this->GetManager()->ReleaseResource(mesh);
			}

			stage->SetLayer(0U, layer);
		}

		this->SetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D, stage);
	}

	{// ShaderStructuredBuffer Create
		tml::graphic::ModelShaderStructuredBufferDesc desc;

		desc.manager = this->GetManager();
		desc.element_limit = 1U;
		desc.cpu_read_flag = true;

		this->GetManager()->GetResource<tml::graphic::ModelShaderStructuredBuffer>(this->ssb_, desc);

		if (this->ssb_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LayerShaderStructuredBuffer Create
		tml::graphic::ModelLayerShaderStructuredBufferDesc desc;

		desc.manager = this->GetManager();
		desc.element_limit = 1U;
		desc.cpu_read_flag = true;

		this->GetManager()->GetResource<tml::graphic::ModelLayerShaderStructuredBuffer>(this->layer_ssb_, desc);

		if (this->layer_ssb_ == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief DrawStageInit関数
 */
void tml::graphic::SpriteModel::DrawStageInit(void)
{
	XMMATRIX w_mat;

	this->GetManager()->GetWorldMatrix2D(w_mat, tml::XMFLOAT2EX(this->position->Get().x, this->position->Get().y), 0.0f, tml::XMFLOAT2EX(1.0f * 128.0f, 1.0f * 128.0f));

	this->ssb_->SetElement(0U, w_mat, this->GetManager()->GetDrawStageData()->view_matrix_2d, this->GetManager()->GetDrawStageData()->projection_matrix_2d);
	this->ssb_->UpdateBuffer();

	this->layer_ssb_->SetElement(0U);
	this->layer_ssb_->UpdateBuffer();

	return;
}


/**
 * @brief DrawStageForward2D関数
 */
void tml::graphic::SpriteModel::DrawStageForward2D(void)
{
	auto stage = this->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	std::array<tml::graphic::ShaderStructuredBuffer *, 2U> ssb_ary = {this->ssb_.get(), this->layer_ssb_.get()};

	this->GetManager()->SetDrawRasterizerState(this->GetRasterizerState(stage->GetRasterizerStateIndex()));
	this->GetManager()->SetDrawBlendState(this->GetBlendState(stage->GetBlendStateIndex()));
	this->GetManager()->SetDrawDepthState(this->GetDepthState(stage->GetDepthStateIndex()));
	this->GetManager()->SetDrawShader(this->GetShader(stage->GetShaderIndex()));
	this->GetManager()->SetDrawShaderStructuredBufferSR(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_INDEX::MODEL, ssb_ary.size(), ssb_ary.data());

	auto layer = stage->GetLayer(0U);

	this->GetManager()->SetDrawMesh(this->GetMesh(layer->GetMeshIndex()));

	this->GetManager()->Draw(1U);

	return;
}
