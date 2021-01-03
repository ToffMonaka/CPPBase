/**
 * @file
 * @brief Lightコードファイル
 */


#include "Light.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::LightDesc::LightDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::LightDesc::~LightDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::LightDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Light::Light()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Light::~Light()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Light::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Light::Init(void)
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
INT tml::Light::Create(const tml::LightDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
