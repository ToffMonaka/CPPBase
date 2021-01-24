/**
 * @file
 * @brief ShadowCameraShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ShadowCameraShaderStructuredBufferDesc�N���X
 */
class ShadowCameraShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	ShadowCameraShaderStructuredBufferDesc();
	virtual ~ShadowCameraShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ShadowCameraShaderStructuredBuffer�N���X
 */
class ShadowCameraShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: ShadowCameraShaderStructuredBuffer(const tml::graphic::ShadowCameraShaderStructuredBuffer &) = delete;
public: tml::graphic::ShadowCameraShaderStructuredBuffer &operator =(const tml::graphic::ShadowCameraShaderStructuredBuffer &) = delete;
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
	tml::graphic::ShadowCameraShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	ShadowCameraShaderStructuredBuffer();
	virtual ~ShadowCameraShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ShadowCameraShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ShadowCameraShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	//void SetElement(const UINT, tml::graphic::ShadowCamera *, const bool, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::ShadowCameraShaderStructuredBuffer::UpdateBuffer(void)
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
inline tml::graphic::ShadowCameraShaderStructuredBuffer::ELEMENT *tml::graphic::ShadowCameraShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
