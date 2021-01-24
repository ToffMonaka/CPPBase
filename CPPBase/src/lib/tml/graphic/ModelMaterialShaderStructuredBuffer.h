/**
 * @file
 * @brief ModelMaterialShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelMaterialShaderStructuredBufferDesc�N���X
 */
class ModelMaterialShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	ModelMaterialShaderStructuredBufferDesc();
	virtual ~ModelMaterialShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ModelMaterialShaderStructuredBuffer�N���X
 */
class ModelMaterialShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: ModelMaterialShaderStructuredBuffer(const tml::graphic::ModelMaterialShaderStructuredBuffer &) = delete;
public: tml::graphic::ModelMaterialShaderStructuredBuffer &operator =(const tml::graphic::ModelMaterialShaderStructuredBuffer &) = delete;
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
	tml::graphic::ModelMaterialShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	ModelMaterialShaderStructuredBuffer();
	virtual ~ModelMaterialShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ModelMaterialShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ModelMaterialShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	//void SetElement(const UINT, tml::graphic::ModelMaterial *, const bool, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::ModelMaterialShaderStructuredBuffer::UpdateBuffer(void)
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
inline tml::graphic::ModelMaterialShaderStructuredBuffer::ELEMENT *tml::graphic::ModelMaterialShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
