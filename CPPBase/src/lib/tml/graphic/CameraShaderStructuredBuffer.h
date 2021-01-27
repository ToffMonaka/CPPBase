/**
 * @file
 * @brief CameraShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"
#include "Camera.h"


namespace tml {
namespace graphic {
/**
 * @brief CameraShaderStructuredBufferDesc�N���X
 */
class CameraShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	CameraShaderStructuredBufferDesc();
	virtual ~CameraShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
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
		XMFLOAT4X4EX view_matrix;
		XMFLOAT4X4EX inverse_view_matrix;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			view_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			inverse_view_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE)
		{
			return;
		};
	} ELEMENT;

private:
	tml::graphic::CameraShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	CameraShaderStructuredBuffer();
	virtual ~CameraShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::CameraShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::CameraShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	void SetElement(const UINT, const tml::graphic::Camera *, const XMMATRIX &, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::CameraShaderStructuredBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderStructuredBuffer::UpdateBuffer(this->element_ary_);

	return;
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::CameraShaderStructuredBuffer::ELEMENT *tml::graphic::CameraShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
