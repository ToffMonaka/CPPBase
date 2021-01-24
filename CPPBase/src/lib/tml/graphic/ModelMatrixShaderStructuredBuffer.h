/**
 * @file
 * @brief ModelMatrixShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelMatrixShaderStructuredBufferDesc�N���X
 */
class ModelMatrixShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	ModelMatrixShaderStructuredBufferDesc();
	virtual ~ModelMatrixShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ModelMatrixShaderStructuredBuffer�N���X
 */
class ModelMatrixShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: ModelMatrixShaderStructuredBuffer(const tml::graphic::ModelMatrixShaderStructuredBuffer &) = delete;
public: tml::graphic::ModelMatrixShaderStructuredBuffer &operator =(const tml::graphic::ModelMatrixShaderStructuredBuffer &) = delete;
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
		}
	} ELEMENT;

private:
	tml::graphic::ModelMatrixShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	ModelMatrixShaderStructuredBuffer();
	virtual ~ModelMatrixShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ModelMatrixShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ModelMatrixShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	//void SetElement(const UINT, tml::graphic::ModelMatrix *, const bool, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::ModelMatrixShaderStructuredBuffer::UpdateBuffer(void)
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
inline tml::graphic::ModelMatrixShaderStructuredBuffer::ELEMENT *tml::graphic::ModelMatrixShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
