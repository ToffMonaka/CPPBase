/**
 * @file
 * @brief GroundModel2Dコードファイル
 */


#include "GroundModel2D.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"
#include "Shader.h"
#include "GroundModel2DShaderStructuredBuffer.h"
#include "GroundModel2DLayerShaderStructuredBuffer.h"
#include "GroundModel2DBlockShaderStructuredBuffer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"
#include "Canvas2D.h"


const D3D11_INPUT_ELEMENT_DESC tml::graphic::GroundModel2D::INPUT_ELEMENT_DESC_ARRAY[tml::graphic::GroundModel2D::INPUT_ELEMENT_DESC_COUNT] = {
	{"POSITION", 0U, DXGI_FORMAT_R32G32B32A32_FLOAT, 0U, 0U, D3D11_INPUT_PER_VERTEX_DATA, 0U},
	{"TEXCOORD", 0U, DXGI_FORMAT_R32G32_FLOAT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U},
	{"LAYER_INDEX", 0U, DXGI_FORMAT_R32_UINT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U},
	{"BLOCK_INDEX", 0U, DXGI_FORMAT_R32_UINT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U},
	{"BLOCK_TILE_INDEX", 0U, DXGI_FORMAT_R32_UINT, 0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U}
};


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

	this->diffuse_texture.reset();
	this->diffuse_texture_desc.reset();
	this->map.reset();
	this->map_desc.reset();

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
	desc_(nullptr)
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

	this->map_.reset();
	this->ssb_.reset();
	this->layer_ssb_.reset();
	this->block_ssb_.reset();

	tml::graphic::Model2D::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2D::OnCreate(void)
{
	if (tml::graphic::Model2D::OnCreate() < 0) {
		return (-1);
	}

	// Map Create
	if (this->desc_->map != nullptr) {
		if (this->GetManager()->GetResource<tml::graphic::Map>(this->map_, this->desc_->map) == nullptr) {
			return (-1);
		}
	} else if (this->desc_->map_desc != nullptr) {
		if (this->GetManager()->GetResource<tml::graphic::Map>(this->map_, (*this->desc_->map_desc)) == nullptr) {
			return (-1);
		}
	} else {
		return (-1);
	}

	tml::XMFLOAT2EX size;

	{// Forward2DStage Create
		auto stage = tml::make_unique<tml::graphic::GroundModel2DStage>(1U);

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

			if (this->GetManager()->GetResource<tml::graphic::Shader>(shader, this->GetManager()->common.ground_model_2d_shader) == nullptr) {
				return (-1);
			}

			this->SetShader(stage->GetShaderIndex(), shader);
		}

		{// Layer0 Create
			auto layer = tml::make_unique<tml::graphic::GroundModel2DLayer>(1U);

			if (layer->Create(this->GetManager()) < 0) {
				return (-1);
			}

			layer->SetMeshIndex(0U);
			layer->SetDiffuseTextureIndex(0U);
			layer->SetDiffuseSamplerIndex(0U);

			{// Mesh Create
				tml::shared_ptr<tml::graphic::Mesh> mesh;
				tml::graphic::MeshDesc mesh_desc;
				std::vector<tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT> vb_element_cont;
				std::vector<UINT> ib_element_cont;
				std::array<tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT, 4U> base_vb_element_ary = {
					tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.0f,  0.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  0.0f), 0U, 0U, 0U),
					tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 1.0f,  0.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  0.0f), 0U, 0U, 0U),
					tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 0.0f, -1.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 0.0f,  1.0f), 0U, 0U, 0U),
					tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT(tml::XMFLOAT4EX( 1.0f, -1.0f,  0.0f,  1.0f), tml::XMFLOAT2EX( 1.0f,  1.0f), 0U, 0U, 0U)
				};
				std::array<UINT, 6U> base_ib_element_ary = {0U, 1U, 2U, 2U, 1U, 3U};
				UINT tile_index = 0U;
				FLOAT tile_pos_x = 0.0f;
				FLOAT tile_pos_y = 0.0f;
				UINT block_index = 0U;
				UINT block_tile_index = 0U;

				vb_element_cont.resize(base_vb_element_ary.size() * this->map_->GetTileCount().x * this->map_->GetTileCount().y);
				ib_element_cont.resize(base_ib_element_ary.size() * this->map_->GetTileCount().x * this->map_->GetTileCount().y);

				for (UINT tile_index_y = 0U; tile_index_y < this->map_->GetTileCount().y; ++tile_index_y) {
					for (UINT tile_index_x = 0U; tile_index_x < this->map_->GetTileCount().x; ++tile_index_x) {
						tile_index = (tile_index_y * this->map_->GetTileCount().x) + (tile_index_x);
						tile_pos_x = static_cast<FLOAT>(tile_index_x) - static_cast<FLOAT>(this->map_->GetTileCount().x) * 0.5f;
						tile_pos_y = -static_cast<FLOAT>(tile_index_y) + static_cast<FLOAT>(this->map_->GetTileCount().y) * 0.5f;
						block_index = (tile_index_y / 16U * this->map_->GetBlockCount().x) + (tile_index_x / 16U);
						block_tile_index = ((tile_index_y % 16U) * this->map_->GetBlockArray()[block_index].GetTileCount().x) + (tile_index_x % 16U);

						for (UINT base_vb_element_i = 0U; base_vb_element_i < base_vb_element_ary.size(); ++base_vb_element_i) {
							auto &vb_element = vb_element_cont[tile_index * base_vb_element_ary.size() + base_vb_element_i];

							vb_element = base_vb_element_ary[base_vb_element_i];
							vb_element.position.x += tile_pos_x;
							vb_element.position.y += tile_pos_y;
							vb_element.block_index = block_index;
							vb_element.block_tile_index = block_tile_index;
						}

						for (UINT base_ib_element_i = 0U; base_ib_element_i < base_ib_element_ary.size(); ++base_ib_element_i) {
							auto &ib_element = ib_element_cont[tile_index * base_ib_element_ary.size() + base_ib_element_i];

							ib_element = base_ib_element_ary[base_ib_element_i] + (tile_index * base_vb_element_ary.size());
						}
					}
				}

				mesh_desc.SetManager(this->GetManager());
				mesh_desc.SetVertexBufferDesc(sizeof(tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT), vb_element_cont.size(), reinterpret_cast<BYTE *>(vb_element_cont.data()));
				mesh_desc.SetIndexBufferDesc(sizeof(UINT), ib_element_cont.size(), reinterpret_cast<BYTE *>(ib_element_cont.data()), DXGI_FORMAT_R32_UINT);
				mesh_desc.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

				if (this->GetManager()->GetResource<tml::graphic::Mesh>(mesh, mesh_desc) == nullptr) {
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
				if (this->map_->GetTexture() != nullptr) {
					tml::shared_ptr<tml::graphic::Texture> tex;

					if (this->GetManager()->GetResource<tml::graphic::Texture>(tex, this->map_->GetTexture()) == nullptr) {
						return (-1);
					}

					this->SetTexture(layer->GetDiffuseTextureIndex(), tex);

					size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetRect().GetSize().x), static_cast<FLOAT>(tex->GetRect().GetSize().y));
				} else {
					this->SetTexture(layer->GetDiffuseTextureIndex(), tml::shared_ptr<tml::graphic::Texture>());
				}
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

	size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->map_->GetTilesetTileSize().x * this->map_->GetTileCount().x), static_cast<FLOAT>(this->map_->GetTilesetTileSize().y * this->map_->GetTileCount().y));

	if (this->desc_->size_auto_flag) {
		this->size = size;
	} else {
		this->size = this->desc_->size;
	}

	{// ShaderStructuredBuffer Create
		tml::graphic::GroundModel2DShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->GetManager());
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::GroundModel2DShaderStructuredBuffer>(this->ssb_, ssb_desc) == nullptr) {
			return (-1);
		}
	}

	{// LayerShaderStructuredBuffer Create
		tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->GetManager());
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::GroundModel2DLayerShaderStructuredBuffer>(this->layer_ssb_, ssb_desc) == nullptr) {
			return (-1);
		}
	}

	{// BlockShaderStructuredBuffer Create
		tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc ssb_desc;

		ssb_desc.SetManager(this->GetManager());
		ssb_desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT), this->map_->GetBlockCount().x * this->map_->GetBlockCount().y);

		if (this->GetManager()->GetResource<tml::graphic::GroundModel2DBlockShaderStructuredBuffer>(this->block_ssb_, ssb_desc) == nullptr) {
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
INT tml::graphic::GroundModel2D::OnCreateDeferred(void)
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
void tml::graphic::GroundModel2D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::GroundModel2DDesc *>(desc);

	tml::graphic::Model2D::OnSetDesc(this->desc_);

	return;
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
void tml::graphic::GroundModel2D::DrawStageInit(void)
{
	auto stage = this->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	auto layer = stage->GetLayer(0U);

	auto w_mat = DirectX::XMMatrixMultiply(
		DirectX::XMMatrixTransformation2D(DirectX::g_XMZero, 0.0f, DirectX::XMVectorSet(this->size.x / static_cast<FLOAT>(this->map_->GetTileCount().x) * this->transform.scale.x, this->size.y / static_cast<FLOAT>(this->map_->GetTileCount().y) * this->transform.scale.y, 0.0f, 0.0f), DirectX::g_XMZero, this->transform.angle, DirectX::XMVectorSet(this->transform.position.x, this->transform.position.y, 0.0f, 0.0f)),
		DirectX::XMMatrixTransformation2D(DirectX::g_XMZero, 0.0f, DirectX::XMVectorSet(this->draw_data->transform.scale.x, this->draw_data->transform.scale.y, 0.0f, 0.0f), DirectX::g_XMZero, this->draw_data->transform.angle, DirectX::XMVectorSet(this->draw_data->transform.position.x, this->draw_data->transform.position.y, 0.0f, 0.0f))
	);
	auto col = this->color * this->draw_data->color;

	this->ssb_->SetElement(0U, w_mat, this->draw_data->canvas->stage->view_matrix, this->draw_data->canvas->stage->projection_matrix, col, this->map_->GetTilesetTileCount());
	this->ssb_->UploadCPUBuffer();

	this->layer_ssb_->SetElement(0U, this->GetTexture(layer->GetDiffuseTextureIndex()).get());
	this->layer_ssb_->UploadCPUBuffer();

	this->block_ssb_->SetElement(0U, this->map_.get());
	this->block_ssb_->UploadCPUBuffer();

	return;
}


/**
 * @brief DrawStageForward2D関数
 */
void tml::graphic::GroundModel2D::DrawStageForward2D(void)
{
	auto stage = this->GetStage(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	auto layer = stage->GetLayer(0U);

	std::array<tml::graphic::ShaderStructuredBuffer *, 3U> ssb_ary = {this->ssb_.get(), this->layer_ssb_.get(), this->block_ssb_.get()};

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
