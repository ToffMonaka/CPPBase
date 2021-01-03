/**
 * @file
 * @brief Shaderコードファイル
 */


#include "Shader.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::ShaderDesc::ShaderDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ShaderDesc::~ShaderDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ShaderDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Shader::Shader()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Shader::~Shader()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Shader::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Shader::Init(void)
{
	this->Release();

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Shader::Create(const tml::ShaderDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
