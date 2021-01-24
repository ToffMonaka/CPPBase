/**
 * @file
 * @brief LightShaderConstantBufferコードファイル
 */


#include "LightShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::LightShaderConstantBufferDesc::LightShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::LightShaderConstantBufferDesc::~LightShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::LightShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::LightShaderConstantBuffer::LightShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::LightShaderConstantBuffer::~LightShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::LightShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::LightShaderConstantBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBuffer::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::LightShaderConstantBuffer::Create(const tml::graphic::LightShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::LightShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::LightShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief 要素セット関数
 * @param light_ssb_cnt …ライトシェーダー構造化バッファ数
 */
/*
void tml::graphic::LightShaderConstantBuffer::SetElement(const UINT light_ssb_cnt)
{
	auto element = this->GetElement();

	element->light_ssb_cnt = light_ssb_cnt;

	return;
}
*/
