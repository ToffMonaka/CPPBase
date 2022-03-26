/**
 * @file
 * @brief Light2DShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "Light2DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Light2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Light2DShaderStructuredBufferDesc::Light2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Light2DShaderStructuredBufferDesc::~Light2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Light2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Light2DShaderStructuredBuffer::Light2DShaderStructuredBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Light2DShaderStructuredBuffer::~Light2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Light2DShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Light2DShaderStructuredBuffer::OnCreate(void)
{
	if (tml::graphic::ShaderStructuredBuffer::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Light2DShaderStructuredBuffer::OnCreateDeferred(void)
{
	if (tml::graphic::ShaderStructuredBuffer::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::graphic::Light2DShaderStructuredBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Light2DShaderStructuredBufferDesc *>(desc);

	tml::graphic::ShaderStructuredBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param light (light)
 */
void tml::graphic::Light2DShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Light2D *light)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	return;
}
