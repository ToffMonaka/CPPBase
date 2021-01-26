/**
 * @file
 * @brief SystemShaderConstantBufferコードファイル
 */


#include "SystemShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::SystemShaderConstantBufferDesc::SystemShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SystemShaderConstantBufferDesc::~SystemShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::SystemShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SystemShaderConstantBuffer::SystemShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SystemShaderConstantBuffer::~SystemShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::SystemShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::SystemShaderConstantBuffer::Init(void)
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
INT tml::graphic::SystemShaderConstantBuffer::Create(const tml::graphic::SystemShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::SystemShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::SystemShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief 要素セット関数
 * @param common_ssb_cnt …ライトシェーダー構造化バッファ数
 */
/*
void tml::graphic::SystemShaderConstantBuffer::SetElement(const UINT common_ssb_cnt)
{
	auto element = this->GetElement();

	element->common_ssb_cnt = common_ssb_cnt;

	return;
}
*/
