/**
 * @file
 * @brief Model2DShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Model2DShaderStructuredBufferDesc�N���X
 */
class Model2DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	Model2DShaderStructuredBufferDesc();
	virtual ~Model2DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Model2DShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model2DShaderStructuredBuffer�N���X
 */
class Model2DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Model2DShaderStructuredBuffer(const tml::graphic::Model2DShaderStructuredBuffer &) = delete;
public: tml::graphic::Model2DShaderStructuredBuffer &operator =(const tml::graphic::Model2DShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		tml::XMFLOAT4X4EX world_view_projection_matrix;
		tml::XMFLOAT4EX color;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			world_view_projection_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			color(1.0f)
		{
			return;
		};
	} ELEMENT;

protected:
	void Release(void);

public:
	Model2DShaderStructuredBuffer();
	virtual ~Model2DShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Model2DShaderStructuredBufferDesc &);

	tml::graphic::Model2DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Model2DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const tml::XMFLOAT4EX &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Model2DShaderStructuredBuffer::Release(void)
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
inline tml::graphic::Model2DShaderStructuredBuffer::ELEMENT *tml::graphic::Model2DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Model2DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::Model2DShaderStructuredBuffer::ELEMENT *tml::graphic::Model2DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Model2DShaderStructuredBuffer::ELEMENT>(index));
}
