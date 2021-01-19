/**
 * @file
 * @brief ShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief ShaderConstantBufferDescクラス
 */
class ShaderConstantBufferDesc : public tml::graphic::ResourceDesc
{
public:
	UINT element_size;
	bool cpu_read_flag;

public:
	ShaderConstantBufferDesc();
	virtual ~ShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ShaderConstantBufferクラス
 *
 * インターフェースパターン
 */
class ShaderConstantBuffer : public tml::graphic::Resource
{
public: ShaderConstantBuffer(const tml::graphic::ShaderConstantBuffer &) = delete;
public: tml::graphic::ShaderConstantBuffer &operator =(const tml::graphic::ShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	ID3D11Buffer *buf_;
	UINT element_size_;
	bool cpu_read_flg_;

protected:
	void Release(void);
	INT Create(tml::graphic::ShaderConstantBufferDesc &);

	void UpdateBuffer(void *);
	template <typename T>
	T *GetElement(T *);

public:
	ShaderConstantBuffer();
	virtual ~ShaderConstantBuffer();

	virtual void Init(void);

	ID3D11Buffer *GetBuffer(void) const;
	UINT GetElementSize(void) const;
	bool GetCPUReadFlag(void) const;
};
}
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::graphic::ShaderConstantBuffer::GetBuffer(void) const
{
	return (this->buf_);
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
 * @param element (element)
 * @return element (element)<br>
 * nullptr=失敗
 */
template <typename T>
inline T *tml::graphic::ShaderConstantBuffer::GetElement(T *element)
{
	return (element);
}


/**
 * @brief GetCPUReadFlag関数
 * @return cpu_read_flg (cpu_read_flag)
 */
inline bool tml::graphic::ShaderConstantBuffer::GetCPUReadFlag(void) const
{
	return (this->cpu_read_flg_);
}
