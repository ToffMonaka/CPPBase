/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerCommon::ManagerCommon()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ManagerCommon::~ManagerCommon()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::sound::ManagerCommon::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::ManagerCommon::Create(tml::sound::Manager *mgr)
{
	this->Init();

	return (0);
}
