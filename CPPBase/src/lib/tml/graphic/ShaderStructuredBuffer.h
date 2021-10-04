/**
 * @file
 * @brief ShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ShaderStructuredBufferDescクラス
 */
class ShaderStructuredBufferDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_BUFFER_DESC buffer_desc;
	UINT element_size;
	UINT element_limit;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ShaderStructuredBufferDesc();
	virtual ~ShaderStructuredBufferDesc();

	virtual void Init(void);

	void SetBufferDesc(const tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG, const UINT, const UINT, const bool dynamic_flg = true);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ShaderStructuredBufferクラス
 *
 * インターフェースパターン
 */
class ShaderStructuredBuffer : public tml::graphic::ManagerResource
{
public: ShaderStructuredBuffer(const tml::graphic::ShaderStructuredBuffer &) = delete;
public: tml::graphic::ShaderStructuredBuffer &operator =(const tml::graphic::ShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SHADER_STRUCTURED_BUFFER);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_TYPE::BASE);

private:
	ID3D11Buffer *buf_;
	CD3D11_BUFFER_DESC buf_desc_;
	UINT element_size_;
	UINT element_limit_;
	UINT element_cnt_;
	tml::DynamicBuffer cpu_buf_;
	D3D11_MAPPED_SUBRESOURCE msr_;
	ID3D11ShaderResourceView *sr_;
	ID3D11UnorderedAccessView *uasr_;

private:
	void Release(void);

protected:
	template <typename T>
	T *GetElementArray(void);
	template <typename T>
	T *GetElement(const UINT);
	template <typename T>
	T *GetElementFast(const UINT);

public:
	ShaderStructuredBuffer();
	virtual ~ShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ShaderStructuredBufferDesc &);

	ID3D11Buffer *GetBuffer(void);
	const CD3D11_BUFFER_DESC &GetBufferDesc(void) const;
	UINT GetElementSize(void) const;
	UINT GetElementLimit(void) const;
	UINT GetElementCount(void) const;
	void SetElementCount(const UINT);
	tml::DynamicBuffer &GetCPUBuffer(void);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
	const D3D11_MAPPED_SUBRESOURCE &GetMappedSubresource(void) const;
	ID3D11ShaderResourceView *GetSR(void);
	ID3D11UnorderedAccessView *GetUASR(void);
};
}
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::graphic::ShaderStructuredBuffer::GetBuffer(void)
{
	return (this->buf_);
}


/**
 * @brief GetBufferDesc関数
 * @return buf_desc (buffer_desc)
 */
inline const CD3D11_BUFFER_DESC &tml::graphic::ShaderStructuredBuffer::GetBufferDesc(void) const
{
	return (this->buf_desc_);
}


/**
 * @brief GetElementSize関数
 * @return element_size (element_size)
 */
inline UINT tml::graphic::ShaderStructuredBuffer::GetElementSize(void) const
{
	return (this->element_size_);
}


/**
 * @brief GetElementLimit関数
 * @return element_limit (element_limit)
 */
inline UINT tml::graphic::ShaderStructuredBuffer::GetElementLimit(void) const
{
	return (this->element_limit_);
}


/**
 * @brief GetElementCount関数
 * @return element_cnt (element_count)
 */
inline UINT tml::graphic::ShaderStructuredBuffer::GetElementCount(void) const
{
	return (this->element_cnt_);
}


/**
 * @brief SetElementCount関数
 * @param element_cnt (element_count)
 */
inline void tml::graphic::ShaderStructuredBuffer::SetElementCount(const UINT element_cnt)
{
	this->element_cnt_ = element_cnt;

	return;
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
template <typename T>
inline T *tml::graphic::ShaderStructuredBuffer::GetElementArray(void)
{
	return (reinterpret_cast<T *>(this->cpu_buf_.Get()));
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
template <typename T>
inline T *tml::graphic::ShaderStructuredBuffer::GetElement(const UINT index)
{
	if (index >= this->element_limit_) {
		return (nullptr);
	}

	if (index >= this->element_cnt_) {
		this->element_cnt_ = index + 1U;
	}

	return (&reinterpret_cast<T *>(this->cpu_buf_.Get())[index]);
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
template <typename T>
inline T *tml::graphic::ShaderStructuredBuffer::GetElementFast(const UINT index)
{
	if (index >= this->element_cnt_) {
		this->element_cnt_ = index + 1U;
	}

	return (&reinterpret_cast<T *>(this->cpu_buf_.Get())[index]);
}


/**
 * @brief GetCPUBuffer関数
 * @return cpu_buf (cpu_buffer)
 */
inline tml::DynamicBuffer &tml::graphic::ShaderStructuredBuffer::GetCPUBuffer(void)
{
	return (this->cpu_buf_);
}


/**
 * @brief GetMappedSubresource関数
 * @return msr (mapped_subresource)
 */
inline const D3D11_MAPPED_SUBRESOURCE &tml::graphic::ShaderStructuredBuffer::GetMappedSubresource(void) const
{
	return (this->msr_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::graphic::ShaderStructuredBuffer::GetSR(void)
{
	return (this->sr_);
}


/**
 * @brief GetUASR関数
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::graphic::ShaderStructuredBuffer::GetUASR(void)
{
	return (this->uasr_);
}
