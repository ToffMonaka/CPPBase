/**
 * @file
 * @brief ShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/DynamicBuffer.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderStructuredBufferDescクラス
 */
class ShaderStructuredBufferDesc : public tml::GraphicResourceDesc
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


namespace tml {
/**
 * @brief ShaderStructuredBufferクラス
 *
 * インターフェースパターン
 */
class ShaderStructuredBuffer : public tml::GraphicResource
{
public: ShaderStructuredBuffer(const tml::ShaderStructuredBuffer &) = delete;
public: tml::ShaderStructuredBuffer &operator =(const tml::ShaderStructuredBuffer &) = delete;
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
	INT Create(const tml::ShaderStructuredBufferDesc &);

	void Update(void *);
	template <typename T>
	T *GetElement(T *, const UINT);

public:
	ShaderStructuredBuffer();
	virtual ~ShaderStructuredBuffer();

	virtual void Init(void);

	ID3D11Buffer *Get(void) const;
	ID3D11ShaderResourceView *GetSR(void) const;
	ID3D11UnorderedAccessView *GetUASR(void) const;
};
}


/**
 * @brief Get関数
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::ShaderStructuredBuffer::Get(void) const
{
	return (this->buf_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::ShaderStructuredBuffer::GetSR(void) const
{
	return (this->sr_);
}


/**
 * @brief GetUASR関数
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::ShaderStructuredBuffer::GetUASR(void) const
{
	return (this->uasr_);
}


/**
 * @brief GetElement関数
 * @param element_ary (element_array)
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
template <typename T>
inline T *tml::ShaderStructuredBuffer::GetElement(T *element_ary, const UINT index)
{
	if (index >= this->element_limit_) {
		return (nullptr);
	}

	if (index >= this->element_cnt_) {
		this->element_cnt_ = index + 1U;
	}

	return (&element_ary[index]);
}
