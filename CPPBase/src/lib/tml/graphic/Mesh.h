/**
 * @file
 * @brief Meshヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief MeshDescクラス
 */
class MeshDesc : public tml::GraphicResourceDesc
{
public:
	UINT vertex_buffer_element_size;
	UINT vertex_buffer_element_count;
	BYTE *vertex_buffer_element_array;
	UINT index_buffer_element_count;
	UINT *index_buffer_element_array;
	D3D11_PRIMITIVE_TOPOLOGY primitive_topology;
	bool cpu_data_flag;
	bool gpu_data_flag;

public:
	MeshDesc();
	virtual ~MeshDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Meshクラス
 */
class Mesh : public tml::GraphicResource
{
public: Mesh(const tml::Mesh &) = delete;
public: tml::Mesh &operator =(const tml::Mesh &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11Buffer *vb_;
	UINT vb_element_size_;
	UINT vb_element_cnt_;
	BYTE *vb_element_ary_;
	ID3D11Buffer *ib_;
	UINT ib_element_size_;
	UINT ib_element_cnt_;
	UINT *ib_element_ary_;
	DXGI_FORMAT ib_format_;
	D3D11_PRIMITIVE_TOPOLOGY pt_;
	bool cpu_dat_flg_;
	bool gpu_dat_flg_;

private:
	void Release(void);

public:
	Mesh();
	virtual ~Mesh();

	virtual void Init(void);
	INT Create(tml::MeshDesc &);

	ID3D11Buffer *GetVertexBuffer(void) const;
	UINT GetVertexBufferElementSize(void) const;
	UINT GetVertexBufferElementCount(void) const;
	BYTE *GetVertexBufferElementArray(void) const;
	ID3D11Buffer *GetIndexBuffer(void) const;
	UINT GetIndexBufferElementSize(void) const;
	UINT GetIndexBufferElementCount(void) const;
	UINT *GetIndexBufferElementArray(void) const;
	DXGI_FORMAT GetIndexBufferFormat(void) const;
	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology(void) const;
};
}


/**
 * @brief GetVertexBuffer関数
 * @return vb (vertex_buffer)
 */
inline ID3D11Buffer *tml::Mesh::GetVertexBuffer(void) const
{
	return (this->vb_);
}


/**
 * @brief GetVertexBufferElementSize関数
 * @return vb_element_size (vertex_buffer_element_size)
 */
inline UINT tml::Mesh::GetVertexBufferElementSize(void) const
{
	return (this->vb_element_size_);
}


/**
 * @brief GetVertexBufferElementCount関数
 * @return vb_element_cnt (vertex_buffer_element_count)
 */
inline UINT tml::Mesh::GetVertexBufferElementCount(void) const
{
	return (this->vb_element_cnt_);
}


/**
 * @brief GetVertexBufferElementArray関数
 * @return vb_element_ary (vertex_buffer_element_array)
 */
inline BYTE *tml::Mesh::GetVertexBufferElementArray(void) const
{
	return (this->vb_element_ary_);
}


/**
 * @brief GetIndexBuffer関数
 * @return ib (index_buffer)
 */
inline ID3D11Buffer *tml::Mesh::GetIndexBuffer(void) const
{
	return (this->ib_);
}


/**
 * @brief GetIndexBufferElementSize関数
 * @return ib_element_size (index_buffer_element_size)
 */
inline UINT tml::Mesh::GetIndexBufferElementSize(void) const
{
	return (this->ib_element_size_);
}


/**
 * @brief GetIndexBufferElementCount関数
 * @return ib_element_cnt (index_buffer_element_count)
 */
inline UINT tml::Mesh::GetIndexBufferElementCount(void) const
{
	return (this->ib_element_cnt_);
}


/**
 * @brief GetIndexBufferElementArray関数
 * @return ib_element_ary (index_buffer_element_array)
 */
inline UINT *tml::Mesh::GetIndexBufferElementArray(void) const
{
	return (this->ib_element_ary_);
}


/**
 * @brief GetIndexBufferFormat関数
 * @return ib_format (index_buffer_format)
 */
inline DXGI_FORMAT tml::Mesh::GetIndexBufferFormat(void) const
{
	return (this->ib_format_);
}


/**
 * @brief GetPrimitiveTopology関数
 * @return pt (primitive_topology)
 */
inline D3D11_PRIMITIVE_TOPOLOGY tml::Mesh::GetPrimitiveTopology(void) const
{
	return (this->pt_);
}
