/**
 * @file
 * @brief Meshコードファイル
 */


#include "Mesh.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::MeshDesc::MeshDesc() :
	vertex_buffer_desc(0U, D3D11_BIND_VERTEX_BUFFER),
	vertex_buffer_subresource_data{},
	vertex_buffer_element_size(0U),
	vertex_buffer_element_count(0U),
	vertex_buffer_cpu_buffer_flag(false),
	index_buffer_desc(0U, D3D11_BIND_INDEX_BUFFER),
	index_buffer_subresource_data{},
	index_buffer_element_size(0U),
	index_buffer_element_count(0U),
	index_buffer_format(DXGI_FORMAT_UNKNOWN),
	index_buffer_cpu_buffer_flag(false),
	primitive_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::MeshDesc::~MeshDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::MeshDesc::Init(void)
{
	this->Release();

	this->vertex_buffer_desc = CD3D11_BUFFER_DESC(0U, D3D11_BIND_VERTEX_BUFFER);
	tml::Clear(&this->vertex_buffer_subresource_data, 1U);
	this->vertex_buffer_element_size = 0U;
	this->vertex_buffer_element_count = 0U;
	this->vertex_buffer_cpu_buffer_flag = false;
	this->index_buffer_desc = CD3D11_BUFFER_DESC(0U, D3D11_BIND_INDEX_BUFFER);
	tml::Clear(&this->index_buffer_subresource_data, 1U);
	this->index_buffer_element_size = 0U;
	this->index_buffer_element_count = 0U;
	this->index_buffer_format = DXGI_FORMAT_UNKNOWN;
	this->index_buffer_cpu_buffer_flag = false;
	this->primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::MeshDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Mesh Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MESH");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetVertexBufferDesc関数
 * @param element_size (element_size)
 * @param element_cnt (element_count)
 * @param element_ary (element_array)
 * @param dynamic_flg (dynamic_flag)
 */
void tml::graphic::MeshDesc::SetVertexBufferDesc(const UINT element_size, const UINT element_cnt, const BYTE *element_ary, const bool dynamic_flg)
{
	this->vertex_buffer_desc = CD3D11_BUFFER_DESC(element_size * element_cnt, D3D11_BIND_VERTEX_BUFFER);

	if (dynamic_flg) {
		this->vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		this->vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	tml::Clear(&this->vertex_buffer_subresource_data, 1U);
	this->vertex_buffer_subresource_data.pSysMem = element_ary;
	this->vertex_buffer_element_size = element_size;
	this->vertex_buffer_element_count = element_cnt;

	return;
}


/**
 * @brief SetIndexBufferDesc関数
 * @param element_size (element_size)
 * @param element_cnt (element_count)
 * @param element_ary (element_array)
 * @param format (format)
 * @param dynamic_flg (dynamic_flag)
 */
void tml::graphic::MeshDesc::SetIndexBufferDesc(const UINT element_size, const UINT element_cnt, const BYTE *element_ary, const DXGI_FORMAT format, const bool dynamic_flg)
{
	this->index_buffer_desc = CD3D11_BUFFER_DESC(element_size * element_cnt, D3D11_BIND_INDEX_BUFFER);

	if (dynamic_flg) {
		this->index_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		this->index_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	tml::Clear(&this->index_buffer_subresource_data, 1U);
	this->index_buffer_subresource_data.pSysMem = element_ary;
	this->index_buffer_element_size = element_size;
	this->index_buffer_element_count = element_cnt;
	this->index_buffer_format = format;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Mesh::Mesh() :
	desc_(nullptr),
	vb_(nullptr),
	vb_desc_(0U, D3D11_BIND_VERTEX_BUFFER),
	vb_element_size_(0U),
	vb_element_cnt_(0U),
	vb_msr_{},
	ib_(nullptr),
	ib_desc_(0U, D3D11_BIND_INDEX_BUFFER),
	ib_element_size_(0U),
	ib_element_cnt_(0U),
	ib_format_(DXGI_FORMAT_UNKNOWN),
	ib_msr_{},
	pt_(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Mesh::~Mesh()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Mesh::Release(void)
{
	if (this->ib_ != nullptr) {
		this->ib_->Release();

		this->ib_ = nullptr;
	}

	if (this->vb_ != nullptr) {
		this->vb_->Release();

		this->vb_ = nullptr;
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Mesh::Init(void)
{
	this->Release();

	this->vb_desc_ = CD3D11_BUFFER_DESC(0U, D3D11_BIND_VERTEX_BUFFER);
	this->vb_element_size_ = 0U;
	this->vb_element_cnt_ = 0U;
	this->vb_cpu_buf_.Init();
	tml::Clear(&this->vb_msr_, 1U);
	this->ib_desc_ = CD3D11_BUFFER_DESC(0U, D3D11_BIND_INDEX_BUFFER);
	this->ib_element_size_ = 0U;
	this->ib_element_cnt_ = 0U;
	this->ib_format_ = DXGI_FORMAT_UNKNOWN;
	this->ib_cpu_buf_.Init();
	tml::Clear(&this->ib_msr_, 1U);
	this->pt_ = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Mesh::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	if ((this->desc_->vertex_buffer_element_size * this->desc_->vertex_buffer_element_count) > 0U) {
		if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&this->desc_->vertex_buffer_desc, &this->desc_->vertex_buffer_subresource_data, &this->vb_))) {
			return (-1);
		}

		this->vb_->GetDesc(&this->vb_desc_);
		this->vb_element_size_ = this->desc_->vertex_buffer_element_size;
		this->vb_element_cnt_ = this->desc_->vertex_buffer_element_count;

		if (this->desc_->vertex_buffer_cpu_buffer_flag) {
			INT result = 0;

			this->GetManager()->GetCPUBuffer(this->vb_cpu_buf_, this->vb_msr_, this->vb_, &result);

			if (result < 0) {
				return (-1);
			}
		}
	}

	if ((this->desc_->index_buffer_element_size * this->desc_->index_buffer_element_count) > 0U) {
		if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&this->desc_->index_buffer_desc, &this->desc_->index_buffer_subresource_data, &this->ib_))) {
			return (-1);
		}

		this->ib_->GetDesc(&this->ib_desc_);
		this->ib_element_size_ = this->desc_->index_buffer_element_size;
		this->ib_element_cnt_ = this->desc_->index_buffer_element_count;
		this->ib_format_ = this->desc_->index_buffer_format;

		if (this->desc_->index_buffer_cpu_buffer_flag) {
			INT result = 0;

			this->GetManager()->GetCPUBuffer(this->ib_cpu_buf_, this->ib_msr_, this->ib_, &result);

			if (result < 0) {
				return (-1);
			}
		}
	}

	this->pt_ = this->desc_->primitive_topology;

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Mesh::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Mesh::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::MeshDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief UploadVertexBufferCPUBuffer関数
 */
void tml::graphic::Mesh::UploadVertexBufferCPUBuffer(void)
{
	if (this->vb_cpu_buf_.GetLength() <= 0U) {
		return;
	}

	if (this->vb_desc_.Usage == D3D11_USAGE_DYNAMIC) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->vb_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
			if (msr.DepthPitch >= (this->vb_element_size_ * this->vb_element_cnt_)) {
				memcpy(msr.pData, this->vb_cpu_buf_.Get(), this->vb_element_size_ * this->vb_element_cnt_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(this->vb_, 0U);
		}
	} else {
		this->GetManager()->GetDeviceContext()->UpdateSubresource(this->vb_, 0U, nullptr, this->vb_cpu_buf_.Get(), 0U, 0U);
	}

	return;
}


/**
 * @brief DownloadVertexBufferCPUBuffer関数
 */
void tml::graphic::Mesh::DownloadVertexBufferCPUBuffer(void)
{
	if (this->vb_cpu_buf_.GetLength() <= 0U) {
		return;
	}

	ID3D11Buffer *tmp_buf = nullptr;
	CD3D11_BUFFER_DESC tmp_buf_desc = this->vb_desc_;

	tmp_buf_desc.BindFlags = 0U;
	tmp_buf_desc.Usage = D3D11_USAGE_STAGING;
	tmp_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	tmp_buf_desc.MiscFlags = 0U;

	if (SUCCEEDED(this->GetManager()->GetDevice()->CreateBuffer(&tmp_buf_desc, nullptr, &tmp_buf))) {
		this->GetManager()->GetDeviceContext()->CopyResource(tmp_buf, this->vb_);

		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(tmp_buf, 0U, D3D11_MAP_READ, 0U, &msr))) {
			if (msr.DepthPitch >= (this->vb_element_size_ * this->vb_element_cnt_)) {
				memcpy(this->vb_cpu_buf_.Get(), msr.pData, this->vb_element_size_ * this->vb_element_cnt_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(tmp_buf, 0U);
		}

		tmp_buf->Release();
	}

	return;
}


/**
 * @brief UploadIndexBufferCPUBuffer関数
 */
void tml::graphic::Mesh::UploadIndexBufferCPUBuffer(void)
{
	if (this->ib_cpu_buf_.GetLength() <= 0U) {
		return;
	}

	if (this->ib_desc_.Usage == D3D11_USAGE_DYNAMIC) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->ib_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
			if (msr.DepthPitch >= (this->ib_element_size_ * this->ib_element_cnt_)) {
				memcpy(msr.pData, this->ib_cpu_buf_.Get(), this->ib_element_size_ * this->ib_element_cnt_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(this->ib_, 0U);
		}
	} else {
		this->GetManager()->GetDeviceContext()->UpdateSubresource(this->ib_, 0U, nullptr, this->ib_cpu_buf_.Get(), 0U, 0U);
	}

	return;
}


/**
 * @brief DownloadIndexBufferCPUBuffer関数
 */
void tml::graphic::Mesh::DownloadIndexBufferCPUBuffer(void)
{
	if (this->ib_cpu_buf_.GetLength() <= 0U) {
		return;
	}

	ID3D11Buffer *tmp_buf = nullptr;
	CD3D11_BUFFER_DESC tmp_buf_desc = this->ib_desc_;

	tmp_buf_desc.BindFlags = 0U;
	tmp_buf_desc.Usage = D3D11_USAGE_STAGING;
	tmp_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	tmp_buf_desc.MiscFlags = 0U;

	if (SUCCEEDED(this->GetManager()->GetDevice()->CreateBuffer(&tmp_buf_desc, nullptr, &tmp_buf))) {
		this->GetManager()->GetDeviceContext()->CopyResource(tmp_buf, this->ib_);

		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(tmp_buf, 0U, D3D11_MAP_READ, 0U, &msr))) {
			if (msr.DepthPitch >= (this->ib_element_size_ * this->ib_element_cnt_)) {
				memcpy(this->ib_cpu_buf_.Get(), msr.pData, this->ib_element_size_ * this->ib_element_cnt_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(tmp_buf, 0U);
		}

		tmp_buf->Release();
	}

	return;
}
