/**
 * @file
 * @brief GroundModel2DBlockShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


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
	GroundModel2DBlockShaderStructuredBuffer();
	virtual ~GroundModel2DBlockShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc &);

	tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::GroundModel2DBlockShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT);
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
