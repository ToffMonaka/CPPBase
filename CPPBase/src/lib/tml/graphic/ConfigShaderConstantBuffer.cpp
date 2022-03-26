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
tml::graphic::ConfigShaderConstantBuffer::ConfigShaderConstantBuffer() :
	desc_(nullptr)
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
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::ConfigShaderConstantBuffer::OnCreate(void)
{
	if (tml::graphic::ShaderConstantBuffer::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::ConfigShaderConstantBuffer::OnCreateDeferred(void)
{
	if (tml::graphic::ShaderConstantBuffer::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::graphic::ConfigShaderConstantBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::ConfigShaderConstantBufferDesc *>(desc);

	tml::graphic::ShaderConstantBuffer::OnSetDesc(this->desc_);

	return;
}
