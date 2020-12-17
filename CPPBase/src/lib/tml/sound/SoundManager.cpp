/**
 * @file
 * @brief SoundManagerコードファイル
 */


#include "SoundManager.h"


/**
 * @brief コンストラクタ
 */
tml::SoundManager::SoundManager()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::SoundManager::~SoundManager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::SoundManager::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::SoundManager::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::SoundManager::Create(void)
{
	this->Release();

	return (0);
}
