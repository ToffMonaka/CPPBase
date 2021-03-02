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
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ConfigShaderConstantBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ConfigShaderConstantBuffer::ConfigShaderConstantBuffer()
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

	if (tml::graphic::ShaderConstantBuffer::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
