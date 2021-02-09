/**
 * @file
 * @brief ModelLayerShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "ModelLayerShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelLayerShaderStructuredBufferDesc::ModelLayerShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelLayerShaderStructuredBufferDesc::~ModelLayerShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelLayerShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelLayerShaderStructuredBuffer::ModelLayerShaderStructuredBuffer() :
	element_ary_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelLayerShaderStructuredBuffer::~ModelLayerShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::ModelLayerShaderStructuredBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_ary_);

	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelLayerShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ModelLayerShaderStructuredBuffer::Create(const tml::graphic::ModelLayerShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc, sizeof(tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ary_ = tml::MemoryUtil::Get<tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT>(desc.element_limit);

	return (0);
}
