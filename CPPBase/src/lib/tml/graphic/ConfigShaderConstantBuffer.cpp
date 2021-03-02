/**
 * @file
 * @brief ConfigShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "ConfigShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ConfigShaderConstantBufferDesc::ConfigShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ConfigShaderConstantBufferDesc::~ConfigShaderConstantBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ConfigShaderConstantBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ConfigShaderConstantBuffer::ConfigShaderConstantBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ConfigShaderConstantBuffer::~ConfigShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ConfigShaderConstantBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBuffer::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ConfigShaderConstantBuffer::Create(const tml::graphic::ConfigShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
