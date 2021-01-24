/**
 * @file
 * @brief FogShaderConstantBufferコードファイル
 */


#include "FogShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::FogShaderConstantBufferDesc::FogShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FogShaderConstantBufferDesc::~FogShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::FogShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::FogShaderConstantBuffer::FogShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FogShaderConstantBuffer::~FogShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::FogShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::FogShaderConstantBuffer::Init(void)
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
INT tml::graphic::FogShaderConstantBuffer::Create(const tml::graphic::FogShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::FogShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::FogShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief 要素セット関数
 * @param light_ssb_cnt …ライトシェーダー構造化バッファ数
 */
/*
void tml::graphic::FogShaderConstantBuffer::SetElement(const UINT light_ssb_cnt)
{
	auto element = this->GetElement();

	element->light_ssb_cnt = light_ssb_cnt;

	return;
}
*/
