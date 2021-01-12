/**
 * @file
 * @brief ShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief ShaderStructuredBufferDescクラス
 */
class ShaderStructuredBufferDesc : public tml::graphic::ResourceDesc
{
public:
	UINT element_size;
	UINT element_limit;
	bool cpu_flag;
	bool uasr_flag;

public:
	ShaderStructuredBufferDesc();
	virtual ~ShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ShaderStructuredBufferクラス
 *
 * インターフェースパターン
 */
class ShaderStructuredBuffer : public tml::graphic::Resource
{
public: ShaderStructuredBuffer(const tml::graphic::ShaderStructuredBuffer &) = delete;
public: tml::graphic::ShaderStructuredBuffer &operator =(const tml::graphic::ShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	ID3D11Buffer *buf_;
	ID3D11ShaderResourceView *sr_;
	ID3D11UnorderedAccessView *uasr_;
	UINT element_size_;
	UINT element_limit_;
	UINT element_cnt_;
	bool cpu_flg_;
	bool uasr_flg_;

protected:
	void Release(void);
	INT Create(tml::graphic::ShaderStructuredBufferDesc &);

	void UpdateBuffer(void *);
	template <typename T>
	T *GetElement(T *, const UINT);

public:
	ShaderStructuredBuffer();
	virtual ~ShaderStructuredBuffer();

	virtual void Init(void);

	ID3D11Buffer *GetBuffer(void) const;
	ID3D11ShaderResourceView *GetSR(void) const;
	ID3D11UnorderedAccessView *GetUASR(void) const;
	UINT GetElementSize(void) const;
	UINT GetElementLimit(void) const;
	UINT GetElementCount(void) const;
	void SetElementCount(const UINT);
};
}
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::graphic::ShaderStructuredBuffer::GetBuffer(void) const
{
	return (this->buf_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::graphic::ShaderStructuredBuffer::GetSR(void) const
{
	return (this->sr_);
}


/**
 * @brief GetUASR関数
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::graphic::ShaderStructuredBuffer::GetUASR(void) const
{
	return (this->uasr_);
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
 * @brief GetElement関数
 * @param element_ary (element_array)
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
template <typename T>
inline T *tml::graphic::ShaderStructuredBuffer::GetElement(T *element_ary, const UINT index)
{
	if (index >= this->element_limit_) {
		return (nullptr);
	}

	if (index >= this->element_cnt_) {
		this->element_cnt_ = index + 1U;
	}

	return (&element_ary[index]);
}
