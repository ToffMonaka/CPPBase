/**
 * @file
 * @brief FogShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "FogShaderStructuredBuffer.h"
#include "Manager.h"
#include "Fog.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FogShaderStructuredBufferDesc::FogShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FogShaderStructuredBufferDesc::~FogShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::FogShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FogShaderStructuredBuffer::FogShaderStructuredBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FogShaderStructuredBuffer::~FogShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::FogShaderStructuredBuffer::Init(void)
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
INT tml::graphic::FogShaderStructuredBuffer::Create(const tml::graphic::FogShaderStructuredBufferDesc &desc)
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
void tml::graphic::FogShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Fog *fog)
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
void tml::graphic::FogShaderStructuredBuffer::SetElement(const UINT index, const UINT fog_cnt, const tml::graphic::Fog *const *fog_ary)
{
	for (UINT fog_i = 0U; fog_i < fog_cnt; ++fog_i) {
		auto element = this->GetElement(index + fog_i);

		if (element == nullptr) {
			break;
		}
	}

	return;
}
