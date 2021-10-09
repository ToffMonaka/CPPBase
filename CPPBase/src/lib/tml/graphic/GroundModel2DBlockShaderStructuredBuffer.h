/**
 * @file
 * @brief GroundModel2DBlockShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathUINT.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
class GroundModel2DBlock;
}
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DBlockShaderStructuredBufferDesc�N���X
 */
class GroundModel2DBlockShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	GroundModel2DBlockShaderStructuredBufferDesc();
	virtual ~GroundModel2DBlockShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DBlockShaderStructuredBuffer�N���X
 */
class GroundModel2DBlockShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: GroundModel2DBlockShaderStructuredBuffer(const tml::graphic::GroundModel2DBlockShaderStructuredBuffer &) = delete;
public: tml::graphic::GroundModel2DBlockShaderStructuredBuffer &operator =(const tml::graphic::GroundModel2DBlockShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		tml::XMUINT2EX tile_count;
		UINT dummy1;
		UINT dummy2;
		UINT tile_type_array[256];

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			tile_count(0U),
			dummy1(0U),
			dummy2(0U),
			tile_type_array{}
		{
			return;
		};
	} ELEMENT;

private:
	void Release(void);

public:
	GroundModel2DBlockShaderStructuredBuffer();
	virtual ~GroundModel2DBlockShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc &);

	tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Map *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::GroundModel2DBlockShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetElementArray�֐�
 * @return element_ary (element_array)
 */
inline tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DBlockShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DBlockShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DBlockShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT>(index));
}
