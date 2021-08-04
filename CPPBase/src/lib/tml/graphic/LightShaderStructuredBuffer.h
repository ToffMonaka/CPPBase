/**
 * @file
 * @brief LightShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief LightShaderStructuredBufferDesc�N���X
 */
class LightShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	LightShaderStructuredBufferDesc();
	virtual ~LightShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::LightShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief LightShaderStructuredBuffer�N���X
 */
class LightShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: LightShaderStructuredBuffer(const tml::graphic::LightShaderStructuredBuffer &) = delete;
public: tml::graphic::LightShaderStructuredBuffer &operator =(const tml::graphic::LightShaderStructuredBuffer &) = delete;
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
		};
	} ELEMENT;

private:
	void Release(void);

public:
	LightShaderStructuredBuffer();
	virtual ~LightShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::LightShaderStructuredBufferDesc &);

	tml::graphic::LightShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::LightShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Light *);
	void SetElement(const UINT, const UINT, const tml::graphic::Light *const *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::LightShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::LightShaderStructuredBuffer::ELEMENT *tml::graphic::LightShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::LightShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::LightShaderStructuredBuffer::ELEMENT *tml::graphic::LightShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::LightShaderStructuredBuffer::ELEMENT>(index));
}
