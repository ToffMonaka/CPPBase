/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerDesc::ManagerDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ManagerDesc::~ManagerDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ManagerDesc::Init(void)
{
	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::sound::Manager::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::Manager::Init(void)
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
INT tml::sound::Manager::Create(tml::sound::ManagerDesc &desc)
{
	this->Init();

	return (0);
}
