/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerCommon::ManagerCommon()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerCommon::~ManagerCommon()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::input::ManagerCommon::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::ManagerCommon::Create(tml::input::Manager *mgr)
{
	this->Init();

	return (0);
}
