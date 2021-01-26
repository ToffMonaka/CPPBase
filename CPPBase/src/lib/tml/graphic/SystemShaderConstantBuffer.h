/**
 * @file
 * @brief SystemShaderConstantBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief SystemShaderConstantBufferDesc�N���X
 */
class SystemShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

public:
	SystemShaderConstantBufferDesc();
	virtual ~SystemShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief SystemShaderConstantBuffer�N���X
 */
class SystemShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: SystemShaderConstantBuffer(const tml::graphic::SystemShaderConstantBuffer &) = delete;
public: tml::graphic::SystemShaderConstantBuffer &operator =(const tml::graphic::SystemShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;
		UINT dummy4;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			dummy1(0U),
			dummy2(0U),
			dummy3(0U),
			dummy4(0U)
		{
			return;
		}
	} ELEMENT;

private:
	tml::graphic::SystemShaderConstantBuffer::ELEMENT *element_;

private:
	void Release(void);

public:
	SystemShaderConstantBuffer();
	virtual ~SystemShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::SystemShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::SystemShaderConstantBuffer::ELEMENT *GetElement(void);
	//void SetElement(const UINT);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::SystemShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement�֐�
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::SystemShaderConstantBuffer::ELEMENT *tml::graphic::SystemShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
