/**
 * @file
 * @brief GroundModel2DLayerShaderStructuredBufferコードファイル
 */


#include "GroundModel2DLayerShaderStructuredBuffer.h"
#include "Manager.h"
#include "Texture.h"
#include "Sampler.h"
#include "GroundModel2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc::GroundModel2DLayerShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc::~GroundModel2DLayerShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DLayerShaderStructuredBuffer::GroundModel2DLayerShaderStructuredBuffer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DLayerShaderStructuredBuffer::~GroundModel2DLayerShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DLayerShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2DLayerShaderStructuredBuffer::Create(const tml::graphic::GroundModel2DLayerShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief SetElement関数
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
