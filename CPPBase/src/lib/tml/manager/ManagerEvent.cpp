/**
 * @file
 * @brief ManagerEventコードファイル
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerEventDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
void tml::ManagerEventDesc::SetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
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
	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param event_index (event_index)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerEvent::Create(const tml::ManagerEventDesc &desc, const UINT event_index)
{
	if ((desc.GetManager() == nullptr)
	|| (!desc.GetManager()->CheckFriendEvent(this))) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_index_ = event_index;

	return (0);
}
