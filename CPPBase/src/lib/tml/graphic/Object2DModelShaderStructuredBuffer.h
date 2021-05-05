/**
 * @file
 * @brief Object2DModelShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelShaderStructuredBufferDesc�N���X
 */
class Object2DModelShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	Object2DModelShaderStructuredBufferDesc();
	virtual ~Object2DModelShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Object2DModelShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelShaderStructuredBuffer�N���X
 */
class Object2DModelShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Object2DModelShaderStructuredBuffer(const tml::graphic::Object2DModelShaderStructuredBuffer &) = delete;
public: tml::graphic::Object2DModelShaderStructuredBuffer &operator =(const tml::graphic::Object2DModelShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		tml::XMFLOAT4X4EX world_projection_matrix;
		tml::XMFLOAT4EX color;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			world_projection_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			color(1.0f)
		{
			return;
		};
	} ELEMENT;

protected:
	void Release(void);

public:
	Object2DModelShaderStructuredBuffer();
	virtual ~Object2DModelShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Object2DModelShaderStructuredBufferDesc &);

	tml::graphic::Object2DModelShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Object2DModelShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const tml::XMFLOAT4EX &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Object2DModelShaderStructuredBuffer::Release(void)
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
inline tml::graphic::Object2DModelShaderStructuredBuffer::ELEMENT *tml::graphic::Object2DModelShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Object2DModelShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::Object2DModelShaderStructuredBuffer::ELEMENT *tml::graphic::Object2DModelShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Object2DModelShaderStructuredBuffer::ELEMENT>(index));
}
