/**
 * @file
 * @brief Meshヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief MeshDescクラス
 */
class MeshDesc : public tml::graphic::ResourceDesc
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
 * @brief Release関数
 */
inline void tml::graphic::MeshDesc::Release(void)
{
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Meshクラス
 */
class Mesh : public tml::graphic::Resource
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
	tml::DynamicBuffer &GetVertexBufferCPUBuffer(void);
	void UploadVertexBufferCPUBuffer(void);
	void DownloadVertexBufferCPUBuffer(void);
	const D3D11_MAPPED_SUBRESOURCE &GetVertexBufferMappedSubresource(void) const;
	ID3D11Buffer *GetIndexBuffer(void);
	const CD3D11_BUFFER_DESC &GetIndexBufferDesc(void) const;
	UINT GetIndexBufferElementSize(void) const;
	UINT GetIndexBufferElementCount(void) const;
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
 * @brief GetVertexBuffer関数
 * @return vb (vertex_buffer)
 */
inline ID3D11Buffer *tml::graphic::Mesh::GetVertexBuffer(void)
{
	return (this->vb_);
}


/**
 * @brief GetVertexBufferDesc関数
 * @return vb_desc (vertex_buffer_desc)
 */
inline const CD3D11_BUFFER_DESC &tml::graphic::Mesh::GetVertexBufferDesc(void) const
{
	return (this->vb_desc_);
}


/**
 * @brief GetVertexBufferElementSize関数
 * @return vb_element_size (vertex_buffer_element_size)
 */
inline UINT tml::graphic::Mesh::GetVertexBufferElementSize(void) const
{
	return (this->vb_element_size_);
}


/**
 * @brief GetVertexBufferElementCount関数
 * @return vb_element_cnt (vertex_buffer_element_count)
 */
inline UINT tml::graphic::Mesh::GetVertexBufferElementCount(void) const
{
	return (this->vb_element_cnt_);
}


/**
 * @brief GetVertexBufferCPUBuffer関数
 * @return vb_cpu_buf (vertex_buffer_cpu_buffer)
 */
inline tml::DynamicBuffer &tml::graphic::Mesh::GetVertexBufferCPUBuffer(void)
{
	return (this->vb_cpu_buf_);
}


/**
 * @brief GetVertexBufferMappedSubresource関数
 * @return vb_msr (vertex_buffer_mapped_subresource)
 */
inline const D3D11_MAPPED_SUBRESOURCE &tml::graphic::Mesh::GetVertexBufferMappedSubresource(void) const
{
	return (this->vb_msr_);
}


/**
 * @brief GetIndexBuffer関数
 * @return ib (index_buffer)
 */
inline ID3D11Buffer *tml::graphic::Mesh::GetIndexBuffer(void)
{
	return (this->ib_);
}


/**
 * @brief GetIndexBufferDesc関数
 * @return ib_desc (index_buffer_desc)
 */
inline const CD3D11_BUFFER_DESC &tml::graphic::Mesh::GetIndexBufferDesc(void) const
{
	return (this->ib_desc_);
}


/**
 * @brief GetIndexBufferElementSize関数
 * @return ib_element_size (index_buffer_element_size)
 */
inline UINT tml::graphic::Mesh::GetIndexBufferElementSize(void) const
{
	return (this->ib_element_size_);
}


/**
 * @brief GetIndexBufferElementCount関数
 * @return ib_element_cnt (index_buffer_element_count)
 */
inline UINT tml::graphic::Mesh::GetIndexBufferElementCount(void) const
{
	return (this->ib_element_cnt_);
}


/**
 * @brief GetIndexBufferFormat関数
 * @return ib_format (index_buffer_format)
 */
inline DXGI_FORMAT tml::graphic::Mesh::GetIndexBufferFormat(void) const
{
	return (this->ib_format_);
}


/**
 * @brief GetIndexBufferCPUBuffer関数
 * @return ib_cpu_buf (index_buffer_cpu_buffer)
 */
inline tml::DynamicBuffer &tml::graphic::Mesh::GetIndexBufferCPUBuffer(void)
{
	return (this->ib_cpu_buf_);
}


/**
 * @brief GetIndexBufferMappedSubresource関数
 * @return ib_msr (index_buffer_mapped_subresource)
 */
inline const D3D11_MAPPED_SUBRESOURCE &tml::graphic::Mesh::GetIndexBufferMappedSubresource(void) const
{
	return (this->ib_msr_);
}


/**
 * @brief GetPrimitiveTopology関数
 * @return pt (primitive_topology)
 */
inline D3D11_PRIMITIVE_TOPOLOGY tml::graphic::Mesh::GetPrimitiveTopology(void) const
{
	return (this->pt_);
}
