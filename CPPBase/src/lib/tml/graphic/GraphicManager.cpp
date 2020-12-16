/**
 * @file
 * @brief GraphicManagerコードファイル
 */


#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::GraphicManager::GraphicManager()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::GraphicManager::~GraphicManager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::GraphicManager::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::GraphicManager::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::GraphicManager::Create(void)
{
	return (0);
}
