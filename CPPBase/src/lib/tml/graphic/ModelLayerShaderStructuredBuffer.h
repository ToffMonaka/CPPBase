/**
 * @file
 * @brief ModelLayerShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelLayerShaderStructuredBufferDesc�N���X
 */
class ModelLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	ModelLayerShaderStructuredBufferDesc();
	virtual ~ModelLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ModelLayerShaderStructuredBuffer�N���X
 */
class ModelLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: ModelLayerShaderStructuredBuffer(const tml::graphic::ModelLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::ModelLayerShaderStructuredBuffer &operator =(const tml::graphic::ModelLayerShaderStructuredBuffer &) = delete;
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
	tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	ModelLayerShaderStructuredBuffer();
	virtual ~ModelLayerShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ModelLayerShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	//void SetElement(const UINT, tml::graphic::ModelLayer *, const bool, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::ModelLayerShaderStructuredBuffer::UpdateBuffer(void)
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
inline tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::ModelLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
