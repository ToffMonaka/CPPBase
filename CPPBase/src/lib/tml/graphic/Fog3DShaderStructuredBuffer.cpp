/**
 * @file
 * @brief Fog3DShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "Fog3DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Fog3D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Fog3DShaderStructuredBufferDesc::Fog3DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Fog3DShaderStructuredBufferDesc::~Fog3DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Fog3DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Fog3DShaderStructuredBuffer::Fog3DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Fog3DShaderStructuredBuffer::~Fog3DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Fog3DShaderStructuredBuffer::Init(void)
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
INT tml::graphic::Fog3DShaderStructuredBuffer::Create(const tml::graphic::Fog3DShaderStructuredBufferDesc &desc)
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
 * @param fog (fog)
 */
void tml::graphic::Fog3DShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Fog3D *fog)
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
 * @param fog_cnt (fog_count)
 * @param fog_ary (fog_array)
 */
void tml::graphic::Fog3DShaderStructuredBuffer::SetElement(const UINT index, const UINT fog_cnt, const tml::graphic::Fog3D *const *fog_ary)
{
	for (UINT fog_i = 0U; fog_i < fog_cnt; ++fog_i) {
		auto element = this->GetElement(index + fog_i);

		if (element == nullptr) {
			break;
		}
	}

	return;
}
