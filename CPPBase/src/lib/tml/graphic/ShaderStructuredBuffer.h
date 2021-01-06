/**
 * @file
 * @brief ShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderStructuredBufferDesc�N���X
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
 * @brief ShaderStructuredBuffer�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
	INT Create(tml::ShaderStructuredBufferDesc &);

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
	UINT GetElementSize(void) const;
	UINT GetElementLimit(void) const;
	UINT GetElementCount(void) const;
	void SetElementCount(const UINT);
};
}


/**
 * @brief Get�֐�
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::ShaderStructuredBuffer::Get(void) const
{
	return (this->buf_);
}


/**
 * @brief GetSR�֐�
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::ShaderStructuredBuffer::GetSR(void) const
{
	return (this->sr_);
}


/**
 * @brief GetUASR�֐�
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::ShaderStructuredBuffer::GetUASR(void) const
{
	return (this->uasr_);
}


/**
 * @brief GetElementSize�֐�
 * @return element_size (element_size)
 */
inline UINT tml::ShaderStructuredBuffer::GetElementSize(void) const
{
	return (this->element_size_);
}


/**
 * @brief GetElementLimit�֐�
 * @return element_limit (element_limit)
 */
inline UINT tml::ShaderStructuredBuffer::GetElementLimit(void) const
{
	return (this->element_limit_);
}


/**
 * @brief GetElementCount�֐�
 * @return element_cnt (element_count)
 */
inline UINT tml::ShaderStructuredBuffer::GetElementCount(void) const
{
	return (this->element_cnt_);
}


/**
 * @brief SetElementCount�֐�
 * @param element_cnt (element_count)
 */
inline void tml::ShaderStructuredBuffer::SetElementCount(const UINT element_cnt)
{
	this->element_cnt_ = element_cnt;

	return;
}


/**
 * @brief GetElement�֐�
 * @param element_ary (element_array)
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
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
