/**
 * @file
 * @brief Fogコードファイル
 */


#include "Fog.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::FogDesc::FogDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FogDesc::~FogDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::FogDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Fog::Fog()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Fog::~Fog()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Fog::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Fog::Init(void)
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
INT tml::Fog::Create(const tml::FogDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
