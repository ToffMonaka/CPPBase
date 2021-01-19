/**
 * @file
 * @brief ShaderConstantBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief ShaderConstantBufferDesc�N���X
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
 * @brief ShaderConstantBuffer�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
 * @brief GetBuffer�֐�
 * @return buf (buffer)
 */
inline ID3D11Buffer *tml::graphic::ShaderConstantBuffer::GetBuffer(void) const
{
	return (this->buf_);
}


/**
 * @brief GetElementSize�֐�
 * @return element_size (element_size)
 */
inline UINT tml::graphic::ShaderConstantBuffer::GetElementSize(void) const
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
inline T *tml::graphic::ShaderConstantBuffer::GetElement(T *element)
{
	return (element);
}


/**
 * @brief GetCPUReadFlag�֐�
 * @return cpu_read_flg (cpu_read_flag)
 */
inline bool tml::graphic::ShaderConstantBuffer::GetCPUReadFlag(void) const
{
	return (this->cpu_read_flg_);
}
