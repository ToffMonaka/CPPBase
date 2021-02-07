/**
 * @file
 * @brief ConfigShaderConstantBufferコードファイル
 */


#include "ConfigShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ConfigShaderConstantBufferDesc::ConfigShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ConfigShaderConstantBufferDesc::~ConfigShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ConfigShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ConfigShaderConstantBuffer::ConfigShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ConfigShaderConstantBuffer::~ConfigShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ConfigShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ConfigShaderConstantBuffer::Init(void)
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
INT tml::graphic::ConfigShaderConstantBuffer::Create(const tml::graphic::ConfigShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::ConfigShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::ConfigShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief SetElement関数
 * @param light_cnt (light_count)
 * @param fog_cnt (fog_count)
 */
void tml::graphic::ConfigShaderConstantBuffer::SetElement(const UINT light_cnt, const UINT fog_cnt)
{
	auto element = this->GetElement();

	element->light_count = light_cnt;
	element->fog_count = fog_cnt;

	return;
}
