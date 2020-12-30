/**
 * @file
 * @brief InputManagerコードファイル
 */


#include "InputManager.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::InputManagerDesc::InputManagerDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::InputManagerDesc::~InputManagerDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::InputManagerDesc::Init(void)
{
	return;
}


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
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::InputManager::Create(const tml::InputManagerDesc &desc)
{
	this->Init();

	return (0);
}
