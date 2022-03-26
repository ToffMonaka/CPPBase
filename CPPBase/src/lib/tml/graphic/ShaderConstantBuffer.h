/**
 * @file
 * @brief ShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ShaderConstantBufferDescクラス
 */
class ShaderConstantBufferDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_BUFFER_DESC buffer_desc;
	UINT element_size;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ShaderConstantBufferDesc();
	virtual ~ShaderConstantBufferDesc();

	virtual void Init(void);

	void SetBufferDesc(const tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG, const UINT, const bool dynamic_flg = true);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ShaderConstantBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ShaderConstantBufferクラス
 *
 * インターフェースパターン
 */
class ShaderConstantBuffer : public tml::graphic::ManagerResource
{
public: ShaderConstantBuffer(const tml::graphic::ShaderConstantBuffer &) = delete;
public: tml::graphic::ShaderConstantBuffer &operator =(const tml::graphic::ShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SHADER_CONSTANT_BUFFER);

private:
	const tml::graphic::ShaderConstantBufferDesc *desc_;
	ID3D11Buffer *buf_;
	CD3D11_BUFFER_DESC buf_desc_;
	UINT element_size_;
	tml::DynamicBuffer cpu_buf_;
	D3D11_MAPPED_SUBRESOURCE msr_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);
	template <typename T>
	T *GetElement(void);

public:
	ShaderConstantBuffer();
	virtual ~ShaderConstantBuffer();

	virtual void Init(void);

	const tml::graphic::ShaderConstantBufferDesc *GetDesc(void) const;
	ID3D11Buffer *GetBuffer(void);
	const CD3D11_BUFFER_DESC &GetBufferDesc(void) const;
	UINT GetElementSize(void) const;
	tml::DynamicBuffer &GetCPUBuffer(void);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
	const D3D11_MAPPED_SUBRESOURCE &GetMappedSubresource(void) const;
	ID3D11Buffer *GetSR(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::ShaderConstantBufferDesc *tml::graphic::ShaderConstantBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::graphic::ShaderConstantBuffer::GetBuffer(void)
{
	return (this->buf_);
}


/**
 * @brief GetBufferDesc関数
 * @return buf_desc (buffer_desc)
 */
inline const CD3D11_BUFFER_DESC &tml::graphic::ShaderConstantBuffer::GetBufferDesc(void) const
{
	return (this->buf_desc_);
}


/**
 * @brief GetElementSize関数
 * @return element_size (element_size)
 */
inline UINT tml::graphic::ShaderConstantBuffer::GetElementSize(void) const
{
	return (this->element_size_);
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
template <typename T>
inline T *tml::graphic::ShaderConstantBuffer::GetElement(void)
{
	return (reinterpret_cast<T *>(this->cpu_buf_.Get()));
}


/**
 * @brief GetCPUBuffer関数
 * @return cpu_buf (cpu_buffer)
 */
inline tml::DynamicBuffer &tml::graphic::ShaderConstantBuffer::GetCPUBuffer(void)
{
	return (this->cpu_buf_);
}


/**
 * @brief GetMappedSubresource関数
 * @return msr (mapped_subresource)
 */
inline const D3D11_MAPPED_SUBRESOURCE &tml::graphic::ShaderConstantBuffer::GetMappedSubresource(void) const
{
	return (this->msr_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11Buffer *tml::graphic::ShaderConstantBuffer::GetSR(void)
{
	return (this->buf_);
}
