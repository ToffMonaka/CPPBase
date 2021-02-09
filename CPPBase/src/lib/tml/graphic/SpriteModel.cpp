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

	auto forward_2d_stage = tml::make_unique<tml::graphic::SpriteModelStage>(1U);

	{// Forward2DStage Create
		auto &stage = forward_2d_stage;

		if (stage->Create(this->GetManager()) < 0) {
			this->Init();

			return (-1);
		}

		stage->SetRasterizerStateIndex(0U);
		stage->SetBlendStateIndex(0U);
		stage->SetDepthStateIndex(0U);
		stage->SetShaderIndex(0U);

		tml::shared_ptr<tml::graphic::RasterizerState> rs;

		{// RasterizerState Create
			this->GetManager()->GetResource(rs, this->GetManager()->common.back_culling_rasterizer_state);

			if (rs == nullptr) {
				this->Init();

				return (-1);
			}
		}

		this->SetRasterizerState(stage->GetRasterizerStateIndex(), rs);
		this->GetManager()->ReleaseResource(rs);

		tml::shared_ptr<tml::graphic::BlendState> bs;

		{// BlendState Create
			this->GetManager()->GetResource(bs, this->GetManager()->common.alignment_blend_state_array[1]);

			if (bs == nullptr) {
				this->Init();

				return (-1);
			}
		}

		this->SetBlendState(stage->GetBlendStateIndex(), bs);
		this->GetManager()->ReleaseResource(bs);

		tml::shared_ptr<tml::graphic::DepthState> ds;

		{// DepthState Create
			this->GetManager()->GetResource(ds, this->GetManager()->common.reference_depth_state);

			if (ds == nullptr) {
				this->Init();

				return (-1);
			}
		}

		this->SetDepthState(stage->GetDepthStateIndex(), ds);
		this->GetManager()->ReleaseResource(ds);

		tml::shared_ptr<tml::graphic::Shader> shader;

		{// Shader Create
			this->GetManager()->GetResource(shader, this->GetManager()->common.sprite_model_shader);

			if (shader == nullptr) {
				this->Init();

				return (-1);
			}
		}

		this->SetShader(stage->GetShaderIndex(), shader);
		this->GetManager()->ReleaseResource(shader);

		auto layer0 = tml::make_unique<tml::graphic::SpriteModelLayer>(1U);

		{// Layer0 Create
			auto &layer = layer0;

			if (layer->Create(this->GetManager()) < 0) {
				this->Init();

				return (-1);
			}

			layer->SetMeshIndex(0U);

			tml::shared_ptr<tml::graphic::Mesh> mesh;

			{// Mesh Create
				std::array<tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT, 4U> vb_element_ary = {
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.0f,  0.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  0.0f), 0U),
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 1.0f,  0.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  0.0f), 0U),
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.0f, -1.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  1.0f), 0U),
					tml::graphic::SpriteModel::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 1.0f, -1.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  1.0f), 0U)
				};
				std::array<UINT, 4U> ib_element_ary = {0U, 1U, 2U, 3U};

				tml::graphic::MeshDesc desc;

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
			}

			this->SetMesh(layer->GetMeshIndex(), mesh);
			this->GetManager()->ReleaseResource(mesh);
		}

		stage->SetLayer(0U, layer0);
	}

	this->SetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D, forward_2d_stage);

	return (0);
}
