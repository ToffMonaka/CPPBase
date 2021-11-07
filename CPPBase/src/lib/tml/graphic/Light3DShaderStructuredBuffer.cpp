/**
 * @file
 * @brief Light3DShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "Light3DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Light3D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Light3DShaderStructuredBufferDesc::Light3DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Light3DShaderStructuredBufferDesc::~Light3DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Light3DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Light3DShaderStructuredBuffer::Light3DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Light3DShaderStructuredBuffer::~Light3DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Light3DShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Light3DShaderStructuredBuffer::Create(const tml::graphic::Light3DShaderStructuredBufferDesc &desc)
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
void tml::graphic::Light3DShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Light3D *light)
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
void tml::graphic::Light3DShaderStructuredBuffer::SetElement(const UINT index, const UINT light_cnt, const tml::graphic::Light3D *const *light_ary)
{
	for (UINT light_i = 0U; light_i < light_cnt; ++light_i) {
		auto element = this->GetElement(index + light_i);

		if (element == nullptr) {
			break;
		}
	}

	return;
}
