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
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::LightShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::LightShaderStructuredBuffer::LightShaderStructuredBuffer()
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
 * @brief Init�֐�
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

	if (tml::graphic::ShaderStructuredBuffer::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

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


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param light_cnt (light_count)
 * @param light_ary (light_array)
 */
void tml::graphic::LightShaderStructuredBuffer::SetElement(const UINT index, const UINT light_cnt, const tml::graphic::Light *const *light_ary)
{
	for (UINT light_i = 0U; light_i < light_cnt; ++light_i) {
		auto element = this->GetElement(index + light_i);

		if (element == nullptr) {
			break;
		}
	}

	return;
}
