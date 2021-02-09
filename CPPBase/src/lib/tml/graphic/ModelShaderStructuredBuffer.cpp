/**
 * @file
 * @brief ModelShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "ModelShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelShaderStructuredBufferDesc::ModelShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelShaderStructuredBufferDesc::~ModelShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelShaderStructuredBuffer::ModelShaderStructuredBuffer() :
	element_ary_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelShaderStructuredBuffer::~ModelShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::ModelShaderStructuredBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_ary_);

	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelShaderStructuredBuffer::Init(void)
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
INT tml::graphic::ModelShaderStructuredBuffer::Create(const tml::graphic::ModelShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc, sizeof(tml::graphic::ModelShaderStructuredBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ary_ = tml::MemoryUtil::Get<tml::graphic::ModelShaderStructuredBuffer::ELEMENT>(desc.element_limit);

	return (0);
}
