/**
 * @file
 * @brief MeshÉwÉbÉ_Å[ÉtÉ@ÉCÉã
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief MeshDescÉNÉâÉX
 */
class MeshDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_SUBRESOURCE_DATA vertex_buffer_subresource_data;
	UINT vertex_buffer_element_size;
	UINT vertex_buffer_element_count;
	bool vertex_buffer_cpu_buffer_flag;
	CD3D11_BUFFER_DESC index_buffer_desc;
	D3D11_SUBRESOURCE_DATA index_buffer_subresource_data;
	UINT index_buffer_element_size;
	UINT index_buffer_element_count;
	DXGI_FORMAT index_buffer_format;
	bool index_buffer_cpu_buffer_flag;
	D3D11_PRIMITIVE_TOPOLOGY primitive_topology;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	MeshDesc();
	virtual ~MeshDesc();

	virtual void Init(void);

	void SetVertexBufferDesc(const UINT, const UINT, const BYTE *, const bool dynamic_flg = false);
	void SetIndexBufferDesc(const UINT, const UINT, const BYTE *, const DXGI_FORMAT, const bool dynamic_flg = false);
};
}
}


/**
 * @brief Releaseä÷êî
 */
inline void tml::graphic::MeshDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief MeshÉNÉâÉX
 */
class Mesh : public tml::graphic::ManagerResource
{
public: Mesh(const tml::graphic::Mesh &) = delete;
public: tml::graphic::Mesh &operator =(const tml::graphic::Mesh &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11Buffer *vb_;
	CD3D11_BUFFER_DESC vb_desc_;
	UINT vb_element_size_;
	UINT vb_element_cnt_;
	tml::DynamicBuffer vb_cpu_buf_;
	D3D11_MAPPED_SUBRESOURCE vb_msr_;
	ID3D11Buffer *ib_;
	CD3D11_BUFFER_DESC ib_desc_;
	UINT ib_element_size_;
	UINT ib_element_cnt_;
	DXGI_FORMAT ib_format_;
	tml::DynamicBuffer ib_cpu_buf_;
	D3D11_MAPPED_SUBRESOURCE ib_msr_;
	D3D11_PRIMITIVE_TOPOLOGY pt_;

protected:
	void Release(void);

public:
	Mesh();
	virtual ~Mesh();

	virtual void Init(void);
	INT Create(const tml::graphic::MeshDesc &);

	ID3D11Buffer *GetVertexBuffer(void);
	const CD3D11_BUFFER_DESC &GetVertexBufferDesc(void) const;
	UINT GetVertexBufferElementSize(void) const;
	UINT GetVertexBufferElementCount(void) const;
	template <typename T>
	T *GetVertexBufferElement(const UINT);
	template <typename T>
	T *GetVertexBufferElementFast(const UINT);
	tml::DynamicBuffer &GetVertexBufferCPUBuffer(void);
	void UploadVertexBufferCPUBuffer(void);
	void DownloadVertexBufferCPUBuffer(void);
	const D3D11_MAPPED_SUBRESOURCE &GetVertexBufferMappedSubresource(void) const;
	ID3D11Buffer *GetIndexBuffer(void);
	const CD3D11_BUFFER_DESC &GetIndexBufferDesc(void) const;
	UINT GetIndexBufferElementSize(void) const;
	UINT GetIndexBufferElementCount(void) const;
	template <typename T>
	T *GetIndexBufferElement(const UINT);
	template <typename T>
	T *GetIndexBufferElementFast(const UINT);
	DXGI_FORMAT GetIndexBufferFormat(void) const;
	tml::DynamicBuffer &GetIndexBufferCPUBuffer(void);
	void UploadIndexBufferCPUBuffer(void);
	void DownloadIndexBufferCPUBuffer(void);
	const D3D11_MAPPED_SUBRESOURCE &GetIndexBufferMappedSubresource(void) const;
	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology(void) const;
};
}
}


/**
 * @brief GetVertexBufferä÷êî
 * @return vb (vertex_buffer)
 */
inline ID3D11Buffer *tml::graphic::Mesh::GetVertexBuffer(void)
{
	return (this->vb_);
}


/**
 * @brief GetVertexBufferDescä÷êî
 * @return vb_desc (vertex_buffer_desc)
 */
inline const CD3D11_BUFFER_DESC &tml::graphic::Mesh::GetVertexBufferDesc(void) const
{
	return (this->vb_desc_);
}


/**
 * @brief GetVertexBufferElementSizeä÷êî
 * @return vb_element_size (vertex_buffer_element_size)
 */
inline UINT tml::graphic::Mesh::GetVertexBufferElementSize(void) const
{
	return (this->vb_element_size_);
}


/**
 * @brief GetVertexBufferElementCountä÷êî
 * @return vb_element_cnt (vertex_buffer_element_count)
 */
inline UINT tml::graphic::Mesh::GetVertexBufferElementCount(void) const
{
	return (this->vb_element_cnt_);
}


/**
 * @brief GetVertexBufferElementä÷êî
 * @param index (index)
 * @return vb_element (vertex_buffer_element)<br>
 * nullptr=é∏îs
 */
template <typename T>
inline T *tml::graphic::Mesh::GetVertexBufferElement(const UINT index)
{
	if (index >= this->vb_element_cnt_) {
		return (nullptr);
	}

	return (&reinterpret_cast<T *>(this->vb_cpu_buf_.Get())[index]);
}


/**
 * @brief GetVertexBufferElementFastä÷êî
 * @param index (index)
 * @return vb_element (vertex_buffer_element)<br>
 * nullptr=é∏îs
 */
template <typename T>
inline T *tml::graphic::Mesh::GetVertexBufferElementFast(const UINT index)
{
	return (&reinterpret_cast<T *>(this->vb_cpu_buf_.Get())[index]);
}


/**
 * @brief GetVertexBufferCPUBufferä÷êî
 * @return vb_cpu_buf (vertex_buffer_cpu_buffer)
 */
inline tml::DynamicBuffer &tml::graphic::Mesh::GetVertexBufferCPUBuffer(void)
{
	return (this->vb_cpu_buf_);
}


/**
 * @brief GetVertexBufferMappedSubresourceä÷êî
 * @return vb_msr (vertex_buffer_mapped_subresource)
 */
inline const D3D11_MAPPED_SUBRESOURCE &tml::graphic::Mesh::GetVertexBufferMappedSubresource(void) const
{
	return (this->vb_msr_);
}


/**
 * @brief GetIndexBufferä÷êî
 * @return ib (index_buffer)
 */
inline ID3D11Buffer *tml::graphic::Mesh::GetIndexBuffer(void)
{
	return (this->ib_);
}


/**
 * @brief GetIndexBufferDescä÷êî
 * @return ib_desc (index_buffer_desc)
 */
inline const CD3D11_BUFFER_DESC &tml::graphic::Mesh::GetIndexBufferDesc(void) const
{
	return (this->ib_desc_);
}


/**
 * @brief GetIndexBufferElementSizeä÷êî
 * @return ib_element_size (index_buffer_element_size)
 */
inline UINT tml::graphic::Mesh::GetIndexBufferElementSize(void) const
{
	return (this->ib_element_size_);
}


/**
 * @brief GetIndexBufferElementCountä÷êî
 * @return ib_element_cnt (index_buffer_element_count)
 */
inline UINT tml::graphic::Mesh::GetIndexBufferElementCount(void) const
{
	return (this->ib_element_cnt_);
}


/**
 * @brief GetIndexBufferElementä÷êî
 * @param index (index)
 * @return ib_element (index_buffer_element)<br>
 * nullptr=é∏îs
 */
template <typename T>
inline T *tml::graphic::Mesh::GetIndexBufferElement(const UINT index)
{
	if (index >= this->ib_element_cnt_) {
		return (nullptr);
	}

	return (&reinterpret_cast<T *>(this->ib_cpu_buf_.Get())[index]);
}


/**
 * @brief GetIndexBufferElementFastä÷êî
 * @param index (index)
 * @return ib_element (index_buffer_element)<br>
 * nullptr=é∏îs
 */
template <typename T>
inline T *tml::graphic::Mesh::GetIndexBufferElementFast(const UINT index)
{
	return (&reinterpret_cast<T *>(this->ib_cpu_buf_.Get())[index]);
}


/**
 * @brief GetIndexBufferFormatä÷êî
 * @return ib_format (index_buffer_format)
 */
inline DXGI_FORMAT tml::graphic::Mesh::GetIndexBufferFormat(void) const
{
	return (this->ib_format_);
}


/**
 * @brief GetIndexBufferCPUBufferä÷êî
 * @return ib_cpu_buf (index_buffer_cpu_buffer)
 */
inline tml::DynamicBuffer &tml::graphic::Mesh::GetIndexBufferCPUBuffer(void)
{
	return (this->ib_cpu_buf_);
}


/**
 * @brief GetIndexBufferMappedSubresourceä÷êî
 * @return ib_msr (index_buffer_mapped_subresource)
 */
inline const D3D11_MAPPED_SUBRESOURCE &tml::graphic::Mesh::GetIndexBufferMappedSubresource(void) const
{
	return (this->ib_msr_);
}


/**
 * @brief GetPrimitiveTopologyä÷êî
 * @return pt (primitive_topology)
 */
inline D3D11_PRIMITIVE_TOPOLOGY tml::graphic::Mesh::GetPrimitiveTopology(void) const
{
	return (this->pt_);
}
