/**
 * @file
 * @brief Fog2DShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "Fog2DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Fog2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Fog2DShaderStructuredBufferDesc::Fog2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Fog2DShaderStructuredBufferDesc::~Fog2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Fog2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Fog2DShaderStructuredBuffer::Fog2DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Fog2DShaderStructuredBuffer::~Fog2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Fog2DShaderStructuredBuffer::Init(void)
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
INT tml::graphic::Fog2DShaderStructuredBuffer::Create(const tml::graphic::Fog2DShaderStructuredBufferDesc &desc)
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
void tml::graphic::Fog2DShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Fog2D *fog)
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
void tml::graphic::Fog2DShaderStructuredBuffer::SetElement(const UINT index, const UINT fog_cnt, const tml::graphic::Fog2D *const *fog_ary)
{
	for (UINT fog_i = 0U; fog_i < fog_cnt; ++fog_i) {
		auto element = this->GetElement(index + fog_i);

		if (element == nullptr) {
			break;
		}
	}

	return;
}
