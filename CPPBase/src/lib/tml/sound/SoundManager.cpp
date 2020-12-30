/**
 * @file
 * @brief SoundManagerコードファイル
 */


#include "SoundManager.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::SoundManagerDesc::SoundManagerDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::SoundManagerDesc::~SoundManagerDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::SoundManagerDesc::Init(void)
{
	return;
}


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
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::SoundManager::Create(const tml::SoundManagerDesc &desc)
{
	this->Init();

	return (0);
}
