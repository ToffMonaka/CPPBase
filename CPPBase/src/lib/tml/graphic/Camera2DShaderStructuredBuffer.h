/**
 * @file
 * @brief Camera2DShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "../math/XNAMathMatrix.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Camera2DShaderStructuredBufferDesc�N���X
 */
class Camera2DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	Camera2DShaderStructuredBufferDesc();
	virtual ~Camera2DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Camera2DShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Camera2DShaderStructuredBuffer�N���X
 */
class Camera2DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Camera2DShaderStructuredBuffer(const tml::graphic::Camera2DShaderStructuredBuffer &) = delete;
public: tml::graphic::Camera2DShaderStructuredBuffer &operator =(const tml::graphic::Camera2DShaderStructuredBuffer &) = delete;
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
	const tml::graphic::Camera2DShaderStructuredBufferDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Camera2DShaderStructuredBuffer();
	virtual ~Camera2DShaderStructuredBuffer();

	virtual void Init(void);

	const tml::graphic::Camera2DShaderStructuredBufferDesc *GetDesc(void) const;
	tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Camera2DShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::graphic::Camera2DShaderStructuredBufferDesc *tml::graphic::Camera2DShaderStructuredBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElementArray�֐�
 * @return element_ary (element_array)
 */
inline tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT *tml::graphic::Camera2DShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT *tml::graphic::Camera2DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT *tml::graphic::Camera2DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Camera2DShaderStructuredBuffer::ELEMENT>(index));
}
