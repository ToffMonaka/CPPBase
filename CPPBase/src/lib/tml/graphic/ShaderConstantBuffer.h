/**
 * @file
 * @brief ShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderConstantBufferDescクラス
 */
class ShaderConstantBufferDesc : public tml::GraphicResourceDesc
{
public:
	UINT element_size;
	bool cpu_flag;

public:
	ShaderConstantBufferDesc();
	virtual ~ShaderConstantBufferDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief ShaderConstantBufferクラス
 *
 * インターフェースパターン
 */
class ShaderConstantBuffer : public tml::GraphicResource
{
public: ShaderConstantBuffer(const tml::ShaderConstantBuffer &) = delete;
public: tml::ShaderConstantBuffer &operator =(const tml::ShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	ID3D11Buffer *buf_;
	UINT element_size_;
	bool cpu_flg_;

protected:
	void Release(void);
	INT Create(tml::ShaderConstantBufferDesc &);

	void UpdateBuffer(void *);
	template <typename T>
	T *GetElement(T *);

public:
	ShaderConstantBuffer();
	virtual ~ShaderConstantBuffer();

	virtual void Init(void);

	ID3D11Buffer *GetBuffer(void) const;
	UINT GetElementSize(void) const;
};
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::ShaderConstantBuffer::GetBuffer(void) const
{
	return (this->buf_);
}


/**
 * @brief GetElementSize関数
 * @return element_size (element_size)
 */
inline UINT tml::ShaderConstantBuffer::GetElementSize(void) const
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
inline T *tml::ShaderConstantBuffer::GetElement(T *element)
{
	return (element);
}
