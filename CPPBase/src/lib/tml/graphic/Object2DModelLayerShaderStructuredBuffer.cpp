/**
 * @file
 * @brief Object2DModelLayerShaderStructuredBufferコードファイル
 */


#include "Object2DModelLayerShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Object2DModelLayerShaderStructuredBufferDesc::Object2DModelLayerShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Object2DModelLayerShaderStructuredBufferDesc::~Object2DModelLayerShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Object2DModelLayerShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Object2DModelLayerShaderStructuredBuffer::Object2DModelLayerShaderStructuredBuffer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Object2DModelLayerShaderStructuredBuffer::~Object2DModelLayerShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Object2DModelLayerShaderStructuredBuffer::Init(void)
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
INT tml::graphic::Object2DModelLayerShaderStructuredBuffer::Create(const tml::graphic::Object2DModelLayerShaderStructuredBufferDesc &desc)
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
 * @param diffuse_tex_flg (diffuse_texture_flag)
 */
void tml::graphic::Object2DModelLayerShaderStructuredBuffer::SetElement(const UINT index, const bool diffuse_tex_flg)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	element->diffuse_texture_flag = diffuse_tex_flg;

	return;
}
