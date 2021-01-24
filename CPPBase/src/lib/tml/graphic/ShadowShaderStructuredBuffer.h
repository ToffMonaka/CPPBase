/**
 * @file
 * @brief ShadowShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ShadowShaderStructuredBufferDesc�N���X
 */
class ShadowShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	ShadowShaderStructuredBufferDesc();
	virtual ~ShadowShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ShadowShaderStructuredBuffer�N���X
 */
class ShadowShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: ShadowShaderStructuredBuffer(const tml::graphic::ShadowShaderStructuredBuffer &) = delete;
public: tml::graphic::ShadowShaderStructuredBuffer &operator =(const tml::graphic::ShadowShaderStructuredBuffer &) = delete;
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
	tml::graphic::ShadowShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	ShadowShaderStructuredBuffer();
	virtual ~ShadowShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ShadowShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ShadowShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	//void SetElement(const UINT, tml::graphic::Shadow *, const bool, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::ShadowShaderStructuredBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderStructuredBuffer::UpdateBuffer(this->element_ary_);

	return;
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::ShadowShaderStructuredBuffer::ELEMENT *tml::graphic::ShadowShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
