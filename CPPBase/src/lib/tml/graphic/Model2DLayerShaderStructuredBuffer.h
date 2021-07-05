/**
 * @file
 * @brief Model2DLayerShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Model2DLayerShaderStructuredBufferDesc�N���X
 */
class Model2DLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	Model2DLayerShaderStructuredBufferDesc();
	virtual ~Model2DLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Model2DLayerShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model2DLayerShaderStructuredBuffer�N���X
 */
class Model2DLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Model2DLayerShaderStructuredBuffer(const tml::graphic::Model2DLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::Model2DLayerShaderStructuredBuffer &operator =(const tml::graphic::Model2DLayerShaderStructuredBuffer &) = delete;
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
	Model2DLayerShaderStructuredBuffer();
	virtual ~Model2DLayerShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Model2DLayerShaderStructuredBufferDesc &);

	tml::graphic::Model2DLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Model2DLayerShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const bool);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Model2DLayerShaderStructuredBuffer::Release(void)
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
inline tml::graphic::Model2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::Model2DLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Model2DLayerShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::Model2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::Model2DLayerShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Model2DLayerShaderStructuredBuffer::ELEMENT>(index));
}
