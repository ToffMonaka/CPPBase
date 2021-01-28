/**
 * @file
 * @brief LightShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "LightShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::LightShaderStructuredBufferDesc::LightShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::LightShaderStructuredBufferDesc::~LightShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::LightShaderStructuredBufferDesc::Init(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::LightShaderStructuredBuffer::LightShaderStructuredBuffer() :
	element_ary_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::LightShaderStructuredBuffer::~LightShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::LightShaderStructuredBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_ary_);

	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::LightShaderStructuredBuffer::Init(void)
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
INT tml::graphic::LightShaderStructuredBuffer::Create(const tml::graphic::LightShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc, sizeof(tml::graphic::LightShaderStructuredBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ary_ = tml::MemoryUtil::Get<tml::graphic::LightShaderStructuredBuffer::ELEMENT>(desc.element_limit);

	return (0);
}


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param light (light)
 */
void tml::graphic::LightShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Light *light)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	return;
}
