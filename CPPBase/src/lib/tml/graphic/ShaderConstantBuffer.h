/**
 * @file
 * @brief ShaderConstantBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderConstantBufferDesc�N���X
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
 * @brief ShaderConstantBuffer�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
 * @brief GetBuffer�֐�
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::ShaderConstantBuffer::GetBuffer(void) const
{
	return (this->buf_);
}


/**
 * @brief GetElementSize�֐�
 * @return element_size (element_size)
 */
inline UINT tml::ShaderConstantBuffer::GetElementSize(void) const
{
	return (this->element_size_);
}


/**
 * @brief GetElement�֐�
 * @param element (element)
 * @return element (element)<br>
 * nullptr=���s
 */
template <typename T>
inline T *tml::ShaderConstantBuffer::GetElement(T *element)
{
	return (element);
}
