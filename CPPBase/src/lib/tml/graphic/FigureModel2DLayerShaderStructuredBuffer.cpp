/**
 * @file
 * @brief FigureModel2DLayerShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "FigureModel2DLayerShaderStructuredBuffer.h"
#include "Manager.h"
#include "Texture.h"
#include "Sampler.h"
#include "FigureModel2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc::FigureModel2DLayerShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc::~FigureModel2DLayerShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FigureModel2DLayerShaderStructuredBuffer::FigureModel2DLayerShaderStructuredBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FigureModel2DLayerShaderStructuredBuffer::~FigureModel2DLayerShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::FigureModel2DLayerShaderStructuredBuffer::Init(void)
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
INT tml::graphic::FigureModel2DLayerShaderStructuredBuffer::OnCreate(void)
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
INT tml::graphic::FigureModel2DLayerShaderStructuredBuffer::OnCreateDeferred(void)
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
void tml::graphic::FigureModel2DLayerShaderStructuredBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc *>(desc);

	tml::graphic::ShaderStructuredBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param diffuse_tex (diffuse_texture)
 */
void tml::graphic::FigureModel2DLayerShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Texture *diffuse_tex)
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
