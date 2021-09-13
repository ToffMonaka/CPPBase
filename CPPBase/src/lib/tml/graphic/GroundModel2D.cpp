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
#include "GroundModel2DShaderStructuredBuffer.h"
#include "GroundModel2DLayerShaderStructuredBuffer.h"
#include "GroundModel2DBlockShaderStructuredBuffer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sampler.h"


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
tml::graphic::GroundModel2DBlock::GroundModel2DBlock() :
	tile_count(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DBlock::~GroundModel2DBlock()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DBlock::Init(void)
{
	this->Release();

	this->tile_count = 0U;
	this->tile_type_container.clear();

	return;
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

	this->image_file_read_desc.Init();
	this->map_file_read_desc.Init();
	this->map_directory_path.clear();

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
	tile_cnt_(0U),
	block_cnt_(0U),
	tileset_tile_size_(0U),
	tileset_tile_cnt_(0U)
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

	this->tile_cnt_ = 0U;
	this->block_cnt_ = 0U;
	this->block_cont_.clear();
	this->tileset_tile_size_ = 0U;
	this->tileset_tile_cnt_ = 0U;
	this->ssb_.reset();
	this->layer_ssb_.reset();
	this->block_ssb_.reset();

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

	auto img_file_read_desc_dat = desc.image_file_read_desc.GetDataByParent();

	auto map_file_read_desc_dat = desc.map_file_read_desc.GetDataByParent();

	tml::XMLFile map_file;

	map_file.read_desc.parent_data = map_file_read_desc_dat;

	if (map_file.Read() < 0) {
		this->Init();

		return (-1);
	}

	auto &map_file_root_node = map_file.data.GetRootNode();

	if (map_file_root_node->GetChildNodeContainer().empty()) {
		this->Init();

		return (-1);
	}

	auto &map_file_map_node = map_file_root_node->GetChildNode(L"map");

	if (map_file_map_node == nullptr) {
		this->Init();

		return (-1);
	}

	auto &map_file_tileset_node = map_file_root_node->GetChildNode(L"tileset");

	if (map_file_tileset_node == nullptr) {
		this->Init();

		return (-1);
	}

	auto &map_file_img_node = map_file_root_node->GetChildNode(L"image");

	if (map_file_img_node == nullptr) {
		this->Init();

		return (-1);
	}

	auto &map_file_dat_node = map_file_root_node->GetChildNode(L"data");

	if (map_file_dat_node == nullptr) {
		this->Init();

		return (-1);
	}

	const std::wstring *val = nullptr;

	val = map_file_map_node->GetValue(L"width");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tile_cnt_.x, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	val = map_file_map_node->GetValue(L"height");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tile_cnt_.y, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	std::vector<UINT> tile_type_cont;
	std::vector<std::wstring> tile_type_str_cont;

	tml::StringUtil::Split(tile_type_str_cont, map_file_dat_node->string.c_str(), L",");

	tile_type_cont.resize(tile_type_str_cont.size());

	for (size_t val_i = 0U; val_i < tile_type_str_cont.size(); ++val_i) {
		tml::StringUtil::GetValue(tile_type_cont[val_i], tile_type_str_cont[val_i].c_str());
	}

	this->block_cnt_.x = static_cast<UINT>(std::ceil(static_cast<FLOAT>(this->tile_cnt_.x) / 16.0f));
	this->block_cnt_.y = static_cast<UINT>(std::ceil(static_cast<FLOAT>(this->tile_cnt_.y) / 16.0f));
	this->block_cont_.resize(this->block_cnt_.x * this->block_cnt_.y);

	for (UINT block_index_y = 0U; block_index_y < this->block_cnt_.y; ++block_index_y) {
		for (UINT block_index_x = 0U; block_index_x < this->block_cnt_.x; ++block_index_x) {
			auto &block = this->block_cont_[block_index_y * this->block_cnt_.x + block_index_x];

			block.tile_count.x = (block_index_x == (this->block_cnt_.x - 1U)) ? this->tile_cnt_.x - (block_index_x * 16U) : 16U;
			block.tile_count.y = (block_index_y == (this->block_cnt_.y - 1U)) ? this->tile_cnt_.y - (block_index_y * 16U) : 16U;
			block.tile_type_container.resize(block.tile_count.x * block.tile_count.y);

			for (UINT block_tile_index_y = 0U; block_tile_index_y < block.tile_count.y; ++block_tile_index_y) {
				for (UINT block_tile_index_x = 0U; block_tile_index_x < block.tile_count.x; ++block_tile_index_x) {
					auto &block_tile_type = block.tile_type_container[block_tile_index_y * block.tile_count.x + block_tile_index_x];

					block_tile_type = tile_type_cont[((block_index_y * 16U + block_tile_index_y) * this->tile_cnt_.x) + (block_index_x * 16U + block_tile_index_x)];
				}
			}
		}
	}

	val = map_file_tileset_node->GetValue(L"tilewidth");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_size_.x, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	val = map_file_tileset_node->GetValue(L"tileheight");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_size_.y, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	val = map_file_tileset_node->GetValue(L"columns");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_cnt_.x, val->c_str());
	} else {
		this->Init();

		return (-1);
	}

	val = map_file_tileset_node->GetValue(L"tilecount");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_cnt_.y, val->c_str());

		this->tileset_tile_cnt_.y /= this->tileset_tile_cnt_.x;
	} else {
		this->Init();

		return (-1);
	}

	tml::BinaryFileReadDescData tile_img_file_read_desc_dat;

	if (img_file_read_desc_dat->IsEmpty()) {
		val = map_file_img_node->GetValue(L"source");

		if (val != nullptr) {
			tile_img_file_read_desc_dat.file_path = desc.map_directory_path;
			tile_img_file_read_desc_dat.file_path += L"/";
			tile_img_file_read_desc_dat.file_path += (*val);
		} else {
			this->Init();

			return (-1);
		}

		img_file_read_desc_dat = &tile_img_file_read_desc_dat;
	}

	tml::XMFLOAT2EX size;

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

			if (this->GetManager()->GetResource<tml::graphic::Shader>(shader, this->GetManager()->common.ground_model_2d_shader) == nullptr) {
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
			layer->SetDiffuseTextureIndex(0U);
			layer->SetDiffuseSamplerIndex(0U);

			{// Mesh Create
				tml::shared_ptr<tml::graphic::Mesh> mesh;

				tml::graphic::MeshDesc desc;
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

				vb_element_cont.resize(base_vb_element_ary.size() * this->tile_cnt_.x * this->tile_cnt_.y);
				ib_element_cont.resize(base_ib_element_ary.size() * this->tile_cnt_.x * this->tile_cnt_.y);

				for (UINT tile_index_y = 0U; tile_index_y < this->tile_cnt_.y; ++tile_index_y) {
					for (UINT tile_index_x = 0U; tile_index_x < this->tile_cnt_.x; ++tile_index_x) {
						tile_index = (tile_index_y * this->tile_cnt_.x) + (tile_index_x);
						tile_pos_x = static_cast<FLOAT>(tile_index_x) - static_cast<FLOAT>(this->tile_cnt_.x) * 0.5f;
						tile_pos_y = -static_cast<FLOAT>(tile_index_y) + static_cast<FLOAT>(this->tile_cnt_.y) * 0.5f;
						block_index = (tile_index_y / 16U * this->block_cnt_.x) + (tile_index_x / 16U);
						block_tile_index = ((tile_index_y % 16U) * this->block_cont_[block_index].tile_count.x) + (tile_index_x % 16U);

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

				desc.SetManager(this->GetManager());
				desc.SetVertexBufferDesc(sizeof(tml::graphic::GroundModel2D::VERTEX_BUFFER_ELEMENT), vb_element_cont.size(), reinterpret_cast<BYTE *>(vb_element_cont.data()));
				desc.SetIndexBufferDesc(sizeof(UINT), ib_element_cont.size(), reinterpret_cast<BYTE *>(ib_element_cont.data()), DXGI_FORMAT_R32_UINT);
				desc.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

				if (this->GetManager()->GetResource<tml::graphic::Mesh>(mesh, desc) == nullptr) {
					this->Init();

					return (-1);
				}

				this->SetMesh(layer->GetMeshIndex(), mesh);
			}

			// DiffuseTexture Create
			if (!img_file_read_desc_dat->IsEmpty()) {
				tml::shared_ptr<tml::graphic::Texture> tex;

				tml::graphic::TextureDesc desc;

				desc.SetManager(this->GetManager());
				desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
				desc.image_file_read_desc_container[0].parent_data = img_file_read_desc_dat;

				if (this->GetManager()->GetResource<tml::graphic::Texture>(tex, desc) == nullptr) {
					this->Init();

					return (-1);
				}

				this->SetTexture(layer->GetDiffuseTextureIndex(), tex);

				size = tml::XMFLOAT2EX(static_cast<FLOAT>(tex->GetSizeFast(0U)->x), static_cast<FLOAT>(tex->GetSizeFast(0U)->y));
			} else {
				this->SetTexture(layer->GetDiffuseTextureIndex(), tml::shared_ptr<tml::graphic::Texture>());
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

	size = tml::XMFLOAT2EX(static_cast<FLOAT>(this->tileset_tile_size_.x * this->tile_cnt_.x), static_cast<FLOAT>(this->tileset_tile_size_.y * this->tile_cnt_.y));

	if (desc.size_flag) {
		this->size = desc.size;
	} else {
		this->size = size;
	}

	{// ShaderStructuredBuffer Create
		tml::graphic::GroundModel2DShaderStructuredBufferDesc desc;

		desc.SetManager(this->GetManager());
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::GroundModel2DShaderStructuredBuffer>(this->ssb_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// LayerShaderStructuredBuffer Create
		tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc desc;

		desc.SetManager(this->GetManager());
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT), 1U);

		if (this->GetManager()->GetResource<tml::graphic::GroundModel2DLayerShaderStructuredBuffer>(this->layer_ssb_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BlockShaderStructuredBuffer Create
		tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc desc;

		desc.SetManager(this->GetManager());
		desc.SetBufferDesc(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR, sizeof(tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT), this->block_cont_.size());

		if (this->GetManager()->GetResource<tml::graphic::GroundModel2DBlockShaderStructuredBuffer>(this->block_ssb_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief GetWorldMatrix関数
 * @param dst_mat (dst_matrix)
 * @return dst_mat (dst_matrix)
 */
DirectX::XMMATRIX &tml::graphic::GroundModel2D::GetWorldMatrix(DirectX::XMMATRIX &dst_mat)
{
	auto scale_x = this->size.x / static_cast<FLOAT>(this->tile_cnt_.x) * this->scale.x;
	auto scale_y = this->size.y / static_cast<FLOAT>(this->tile_cnt_.y) * this->scale.y;

	dst_mat = DirectX::XMMatrixTransformation2D(DirectX::g_XMZero, 0.0f, DirectX::XMVectorSet(scale_x, scale_y, 0.0f, 0.0f), DirectX::g_XMZero, this->position.GetAngle(), DirectX::XMVectorSet(this->position.GetX(), this->position.GetY(), 0.0f, 0.0f));

	return (dst_mat);
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

	this->GetWorldMatrix(w_mat);

	this->ssb_->SetElement(0U, w_mat, this->GetManager()->GetDrawStageData()->view_matrix, this->GetManager()->GetDrawStageData()->projection_matrix, this->color, this->tileset_tile_cnt_);
	this->ssb_->UploadCPUBuffer();

	this->layer_ssb_->SetElement(0U, this->GetTexture(layer->GetDiffuseTextureIndex()).get());
	this->layer_ssb_->UploadCPUBuffer();

	this->block_ssb_->SetElement(0U, this->block_cont_);
	this->block_ssb_->UploadCPUBuffer();

	return;
}


/**
 * @brief DrawStageForward2D関数
 */
void tml::graphic::GroundModel2D::DrawStageForward2D(void)
{
	auto stage = this->GetStageFast(tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE::FORWARD_2D);
	auto layer = stage->GetLayerFast(0U);

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
