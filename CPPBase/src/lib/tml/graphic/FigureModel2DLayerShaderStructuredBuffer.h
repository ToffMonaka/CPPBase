/**
 * @file
 * @brief FigureModel2DLayerShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathUINT.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
class FigureModel2DLayer;
}
}


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2DLayerShaderStructuredBufferDesc�N���X
 */
class FigureModel2DLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	FigureModel2DLayerShaderStructuredBufferDesc();
	virtual ~FigureModel2DLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2DLayerShaderStructuredBuffer�N���X
 */
class FigureModel2DLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: FigureModel2DLayerShaderStructuredBuffer(const tml::graphic::FigureModel2DLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::FigureModel2DLayerShaderStructuredBuffer &operator =(const tml::graphic::FigureModel2DLayerShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		UINT diffuse_texture_flag;
		tml::XMUINT2EX diffuse_texture_rect_position;
		tml::XMUINT2EX diffuse_texture_rect_size;
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			diffuse_texture_flag(0U),
			diffuse_texture_rect_position(0U),
			diffuse_texture_rect_size(0U),
			dummy1(0U),
			dummy2(0U),
			dummy3(0U)
		{
			return;
		};
	} ELEMENT;

private:
	void Release(void);

public:
	FigureModel2DLayerShaderStructuredBuffer();
	virtual ~FigureModel2DLayerShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc &);

	tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const bool);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FigureModel2DLayerShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetElementArray�֐�
 * @return element_ary (element_array)
 */
inline tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::FigureModel2DLayerShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::FigureModel2DLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::FigureModel2DLayerShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT>(index));
}
