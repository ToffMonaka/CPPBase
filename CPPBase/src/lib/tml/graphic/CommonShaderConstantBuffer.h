/**
 * @file
 * @brief CommonShaderConstantBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief CommonShaderConstantBufferDesc�N���X
 */
class CommonShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

public:
	CommonShaderConstantBufferDesc();
	virtual ~CommonShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief CommonShaderConstantBuffer�N���X
 */
class CommonShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: CommonShaderConstantBuffer(const tml::graphic::CommonShaderConstantBuffer &) = delete;
public: tml::graphic::CommonShaderConstantBuffer &operator =(const tml::graphic::CommonShaderConstantBuffer &) = delete;
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
	tml::graphic::CommonShaderConstantBuffer::ELEMENT *element_;

private:
	void Release(void);

public:
	CommonShaderConstantBuffer();
	virtual ~CommonShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::CommonShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::CommonShaderConstantBuffer::ELEMENT *GetElement(void);
	//void SetElement(const UINT);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::CommonShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement�֐�
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::CommonShaderConstantBuffer::ELEMENT *tml::graphic::CommonShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
