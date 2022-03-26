/**
 * @file
 * @brief GroundModel2DLayerShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
class GroundModel2DLayer;
}
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DLayerShaderStructuredBufferDesc�N���X
 */
class GroundModel2DLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	GroundModel2DLayerShaderStructuredBufferDesc();
	virtual ~GroundModel2DLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DLayerShaderStructuredBuffer�N���X
 */
class GroundModel2DLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: GroundModel2DLayerShaderStructuredBuffer(const tml::graphic::GroundModel2DLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::GroundModel2DLayerShaderStructuredBuffer &operator =(const tml::graphic::GroundModel2DLayerShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		UINT texture_flag;
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;
		tml::XMUINT2EX diffuse_texture_rect_position;
		tml::XMUINT2EX diffuse_texture_rect_size;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			texture_flag(0U),
			dummy1(0U),
			dummy2(0U),
			dummy3(0U),
			diffuse_texture_rect_position(0U),
			diffuse_texture_rect_size(0U)
		{
			return;
		};
	} ELEMENT;

private:
	const tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	GroundModel2DLayerShaderStructuredBuffer();
	virtual ~GroundModel2DLayerShaderStructuredBuffer();

	virtual void Init(void);

	const tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc *GetDesc(void) const;
	tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Texture *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::GroundModel2DLayerShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc *tml::graphic::GroundModel2DLayerShaderStructuredBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementArray�֐�
 * @return element_ary (element_array)
 */
inline tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DLayerShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DLayerShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::GroundModel2DLayerShaderStructuredBuffer::ELEMENT>(index));
}
