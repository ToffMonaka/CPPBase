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
