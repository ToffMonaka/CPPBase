/**
 * @file
 * @brief Object2DModelLayerShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelLayerShaderStructuredBufferDesc�N���X
 */
class Object2DModelLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	Object2DModelLayerShaderStructuredBufferDesc();
	virtual ~Object2DModelLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Object2DModelLayerShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelLayerShaderStructuredBuffer�N���X
 */
class Object2DModelLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Object2DModelLayerShaderStructuredBuffer(const tml::graphic::Object2DModelLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::Object2DModelLayerShaderStructuredBuffer &operator =(const tml::graphic::Object2DModelLayerShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		UINT diffuse_texture_flag;
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			diffuse_texture_flag(0U),
			dummy1(0U),
			dummy2(0U),
			dummy3(0U)
		{
			return;
		};
	} ELEMENT;

protected:
	void Release(void);

public:
	Object2DModelLayerShaderStructuredBuffer();
	virtual ~Object2DModelLayerShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Object2DModelLayerShaderStructuredBufferDesc &);

	tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const bool);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Object2DModelLayerShaderStructuredBuffer::Release(void)
{
	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::Object2DModelLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::Object2DModelLayerShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT>(index));
}
