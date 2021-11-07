/**
 * @file
 * @brief Light2DShaderStructuredBufferコードファイル
 */


#include "Light2DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Light2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Light2DShaderStructuredBufferDesc::Light2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Light2DShaderStructuredBufferDesc::~Light2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Light2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Light2DShaderStructuredBuffer::Light2DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Light2DShaderStructuredBuffer::~Light2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Light2DShaderStructuredBuffer::Init(void)
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
INT tml::graphic::Light2DShaderStructuredBuffer::Create(const tml::graphic::Light2DShaderStructuredBufferDesc &desc)
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
 * @param light (light)
 */
void tml::graphic::Light2DShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Light2D *light)
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
 * @param light_cnt (light_count)
 * @param light_ary (light_array)
 */
void tml::graphic::Light2DShaderStructuredBuffer::SetElement(const UINT index, const UINT light_cnt, const tml::graphic::Light2D *const *light_ary)
{
	for (UINT light_i = 0U; light_i < light_cnt; ++light_i) {
		auto element = this->GetElement(index + light_i);

		if (element == nullptr) {
			break;
		}
	}

	return;
}
