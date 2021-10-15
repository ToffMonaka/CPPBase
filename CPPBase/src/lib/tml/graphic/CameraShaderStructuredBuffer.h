/**
 * @file
 * @brief CameraShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "../math/XNAMathMatrix.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief CameraShaderStructuredBufferDesc�N���X
 */
class CameraShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	CameraShaderStructuredBufferDesc();
	virtual ~CameraShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::CameraShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief CameraShaderStructuredBuffer�N���X
 */
class CameraShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: CameraShaderStructuredBuffer(const tml::graphic::CameraShaderStructuredBuffer &) = delete;
public: tml::graphic::CameraShaderStructuredBuffer &operator =(const tml::graphic::CameraShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		tml::XMFLOAT4X4EX view_matrix;
		tml::XMFLOAT4X4EX inverse_view_matrix;
		tml::XMFLOAT4X4EX projection_matrix;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			view_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			inverse_view_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			projection_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE)
		{
			return;
		};
	} ELEMENT;

private:
	void Release(void);

public:
	CameraShaderStructuredBuffer();
	virtual ~CameraShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::CameraShaderStructuredBufferDesc &);

	tml::graphic::CameraShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::CameraShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::CameraShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::CameraShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetElementArray�֐�
 * @return element_ary (element_array)
 */
inline tml::graphic::CameraShaderStructuredBuffer::ELEMENT *tml::graphic::CameraShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::CameraShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::CameraShaderStructuredBuffer::ELEMENT *tml::graphic::CameraShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::CameraShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::CameraShaderStructuredBuffer::ELEMENT *tml::graphic::CameraShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::CameraShaderStructuredBuffer::ELEMENT>(index));
}
