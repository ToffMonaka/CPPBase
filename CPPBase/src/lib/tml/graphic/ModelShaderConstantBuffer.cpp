/**
 * @file
 * @brief ModelShaderConstantBufferコードファイル
 */


#include "ModelShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelShaderConstantBufferDesc::ModelShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelShaderConstantBufferDesc::~ModelShaderConstantBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelShaderConstantBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelShaderConstantBuffer::ModelShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelShaderConstantBuffer::~ModelShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ModelShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelShaderConstantBuffer::Init(void)
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
INT tml::graphic::ModelShaderConstantBuffer::Create(const tml::graphic::ModelShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::ModelShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::ModelShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief 要素セット関数
 * @param light_ssb_cnt …ライトシェーダー構造化バッファ数
 */
/*
void tml::graphic::ModelShaderConstantBuffer::SetElement(const UINT light_ssb_cnt)
{
	auto element = this->GetElement();

	element->light_ssb_cnt = light_ssb_cnt;

	return;
}
*/
