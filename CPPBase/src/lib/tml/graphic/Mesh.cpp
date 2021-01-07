/**
 * @file
 * @brief Meshコードファイル
 */


#include "Mesh.h"
#include "../memory/MemoryUtil.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::MeshDesc::MeshDesc() :
	vertex_buffer_element_size(0U),
	vertex_buffer_element_count(0U),
	vertex_buffer_element_array(nullptr),
	index_buffer_element_count(0U),
	index_buffer_element_array(nullptr),
	primitive_topology(D3D_PRIMITIVE_TOPOLOGY_UNDEFINED),
	cpu_data_flag(false),
	gpu_data_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MeshDesc::~MeshDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::MeshDesc::Init(void)
{
	this->vertex_buffer_element_size = 0U;
	this->vertex_buffer_element_count = 0U;
	this->vertex_buffer_element_array = nullptr;
	this->index_buffer_element_count = 0U;
	this->index_buffer_element_array = nullptr;
	this->primitive_topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
	this->cpu_data_flag = false;
	this->gpu_data_flag = false;

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Mesh::Mesh() :
	vb_(nullptr),
	vb_element_size_(0U),
	vb_element_cnt_(0U),
	vb_element_ary_(nullptr),
	ib_(nullptr),
	ib_element_size_(0U),
	ib_element_cnt_(0U),
	ib_element_ary_(nullptr),
	ib_format_(DXGI_FORMAT_UNKNOWN),
	pt_(D3D_PRIMITIVE_TOPOLOGY_UNDEFINED),
	cpu_dat_flg_(false),
	gpu_dat_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Mesh::~Mesh()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Mesh::Release(void)
{
	if (this->ib_ != nullptr) {
		this->ib_->Release();

		this->ib_ = nullptr;
	}

	tml::MemoryUtil::Release(&this->ib_element_ary_);

	if (this->vb_ != nullptr) {
		this->vb_->Release();

		this->vb_ = nullptr;
	}

	tml::MemoryUtil::Release(&this->vb_element_ary_);

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Mesh::Init(void)
{
	this->Release();

	this->vb_element_size_ = 0U;
	this->vb_element_cnt_ = 0U;
	this->ib_element_size_ = 0U;
	this->ib_element_cnt_ = 0U;
	this->ib_format_ = DXGI_FORMAT_UNKNOWN;
	this->pt_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
	this->cpu_dat_flg_ = false;
	this->gpu_dat_flg_ = false;

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Mesh::Create(tml::MeshDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->cpu_dat_flg_ = desc.cpu_data_flag;
	this->gpu_dat_flg_ = desc.gpu_data_flag;

	this->vb_element_size_ = desc.vertex_buffer_element_size;
	this->vb_element_cnt_ = desc.vertex_buffer_element_count;

	UINT vb_size = this->vb_element_size_ * this->vb_element_cnt_;

	if (vb_size > 0U) {
		if (this->cpu_dat_flg_) {
			this->vb_element_ary_ = tml::MemoryUtil::Get<BYTE>(vb_size);
			tml::MemoryUtil::Copy(this->vb_element_ary_, desc.vertex_buffer_element_array, vb_size);
		}

		if (this->gpu_dat_flg_) {
			CD3D11_BUFFER_DESC vb_desc = CD3D11_BUFFER_DESC(vb_size, D3D11_BIND_VERTEX_BUFFER);
			D3D11_SUBRESOURCE_DATA vb_srd = {};

			vb_srd.pSysMem = this->vb_element_ary_;

			if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&vb_desc, &vb_srd, &this->vb_))) {
				this->Init();

				return (-1);
			}
		}
	}

	this->ib_element_size_ = sizeof(UINT);
	this->ib_element_cnt_ = desc.index_buffer_element_count;

	UINT ib_size = this->ib_element_size_ * this->ib_element_cnt_;

	if (ib_size > 0U) {
		if (this->cpu_dat_flg_) {
			this->ib_element_ary_ = tml::MemoryUtil::Get<UINT>(this->ib_element_cnt_);
			tml::MemoryUtil::Copy(this->ib_element_ary_, desc.index_buffer_element_array, this->ib_element_cnt_);
		}

		if (this->gpu_dat_flg_) {
			CD3D11_BUFFER_DESC ib_desc = CD3D11_BUFFER_DESC(ib_size, D3D11_BIND_INDEX_BUFFER);
			D3D11_SUBRESOURCE_DATA ib_srd = {};

			ib_srd.pSysMem = this->ib_element_ary_;

			if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&ib_desc, &ib_srd, &this->ib_))) {
				this->Init();

				return (-1);
			}
		}
	}

	this->ib_format_ = DXGI_FORMAT_R32_UINT;

	this->pt_ = desc.primitive_topology;

	return (0);
}
