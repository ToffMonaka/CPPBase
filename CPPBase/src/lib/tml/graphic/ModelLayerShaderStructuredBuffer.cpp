/**
 * @file
 * @brief ModelLayerShaderStructuredBufferコードファイル
 */


#include "ModelLayerShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBufferDesc::ModelLayerShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBufferDesc::~ModelLayerShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelLayerShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBuffer::ModelLayerShaderStructuredBuffer() :
	element_ary_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBuffer::~ModelLayerShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ModelLayerShaderStructuredBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_ary_);

	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelLayerShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ModelLayerShaderStructuredBuffer::Create(const tml::graphic::ModelLayerShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc, sizeof(tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ary_ = tml::MemoryUtil::Get<tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT>(desc.element_limit);

	return (0);
}


/**
 * @brief SetElement関数
 * @param index (index)
 * @param diffuse_tex_flg (diffuse_texture_flag)
 */
void tml::graphic::ModelLayerShaderStructuredBuffer::SetElement(const UINT index, const bool diffuse_tex_flg)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	element->diffuse_texture_flag = diffuse_tex_flg;

	return;
}
