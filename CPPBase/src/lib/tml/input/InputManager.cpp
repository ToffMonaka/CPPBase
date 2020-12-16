/**
 * @file
 * @brief InputManagerコードファイル
 */


#include "InputManager.h"


/**
 * @brief コンストラクタ
 */
tml::InputManager::InputManager()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::InputManager::~InputManager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::InputManager::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::InputManager::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::InputManager::Create(void)
{
	return (0);
}
