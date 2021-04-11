/**
 * @file
 * @brief ManagerEventコードファイル
 */


#include "ManagerEvent.h"


/**
 * @brief コンストラクタ
 */
tml::ManagerEvent::ManagerEvent() :
	event_index_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerEvent::~ManagerEvent()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerEvent::Init(void)
{
	this->event_index_ = 0U;

	return;
}


/**
 * @brief Create関数
 * @param event_index (event_index)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerEvent::Create(const UINT event_index)
{
	this->event_index_ = event_index;

	return (0);
}
