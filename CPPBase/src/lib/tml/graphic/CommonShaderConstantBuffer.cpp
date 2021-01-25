/**
 * @file
 * @brief CommonShaderConstantBufferコードファイル
 */


#include "CommonShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::CommonShaderConstantBufferDesc::CommonShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::CommonShaderConstantBufferDesc::~CommonShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::CommonShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::CommonShaderConstantBuffer::CommonShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::CommonShaderConstantBuffer::~CommonShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::CommonShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::CommonShaderConstantBuffer::Init(void)
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
INT tml::graphic::CommonShaderConstantBuffer::Create(const tml::graphic::CommonShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::CommonShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::CommonShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief 要素セット関数
 * @param common_ssb_cnt …ライトシェーダー構造化バッファ数
 */
/*
void tml::graphic::CommonShaderConstantBuffer::SetElement(const UINT common_ssb_cnt)
{
	auto element = this->GetElement();

	element->common_ssb_cnt = common_ssb_cnt;

	return;
}
*/
