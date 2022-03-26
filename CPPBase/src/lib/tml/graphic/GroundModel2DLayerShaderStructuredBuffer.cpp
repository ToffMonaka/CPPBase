/**
 * @file
 * @brief GroundModel2DLayerShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "GroundModel2DLayerShaderStructuredBuffer.h"
#include "Manager.h"
#include "Texture.h"
#include "Sampler.h"
#include "GroundModel2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc::GroundModel2DLayerShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc::~GroundModel2DLayerShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::GroundModel2DLayerShaderStructuredBuffer::GroundModel2DLayerShaderStructuredBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::GroundModel2DLayerShaderStructuredBuffer::~GroundModel2DLayerShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::GroundModel2DLayerShaderStructuredBuffer::Init(void)
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
INT tml::graphic::GroundModel2DLayerShaderStructuredBuffer::OnCreate(void)
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
INT tml::graphic::GroundModel2DLayerShaderStructuredBuffer::OnCreateDeferred(void)
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
void tml::graphic::GroundModel2DLayerShaderStructuredBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc *>(desc);

	tml::graphic::ShaderStructuredBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param diffuse_tex (diffuse_texture)
 */
void tml::graphic::GroundModel2DLayerShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Texture *diffuse_tex)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	element->texture_flag = 0U;

	if (diffuse_tex != nullptr) {
		element->texture_flag |= 1U;
		element->diffuse_texture_rect_position = diffuse_tex->GetRect().GetPosition();
		element->diffuse_texture_rect_size = diffuse_tex->GetRect().GetSize();
	}

	return;
}
