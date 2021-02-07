/**
 * @file
 * @brief FogShaderStructuredBufferコードファイル
 */


#include "FogShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::FogShaderStructuredBufferDesc::FogShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FogShaderStructuredBufferDesc::~FogShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FogShaderStructuredBufferDesc::Init(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::FogShaderStructuredBuffer::FogShaderStructuredBuffer() :
	element_ary_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FogShaderStructuredBuffer::~FogShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::FogShaderStructuredBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_ary_);

	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FogShaderStructuredBuffer::Init(void)
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
INT tml::graphic::FogShaderStructuredBuffer::Create(const tml::graphic::FogShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc, sizeof(tml::graphic::FogShaderStructuredBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ary_ = tml::MemoryUtil::Get<tml::graphic::FogShaderStructuredBuffer::ELEMENT>(desc.element_limit);

	return (0);
}


/**
 * @brief SetElement関数
 * @param index (index)
 * @param fog (fog)
 */
void tml::graphic::FogShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Fog *fog)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	return;
}


/**
 * @brief SetElement関数
 * @param index (index)
 * @param fog_cnt (fog_count)
 * @param fog_ary (fog_array)
 */
void tml::graphic::FogShaderStructuredBuffer::SetElement(const UINT index, const UINT fog_cnt, const tml::graphic::Fog *const *fog_ary)
{
	for (UINT fog_i = 0U; fog_i < fog_cnt; ++fog_i) {
		auto element = this->GetElement(index + fog_i);

		if (element == nullptr) {
			break;
		}
	}

	return;
}
