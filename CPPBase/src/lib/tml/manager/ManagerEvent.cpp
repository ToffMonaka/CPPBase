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
	event_main_index_(0U),
	event_sub_index_(0U)
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
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerEvent::Create(const tml::ManagerEventDesc &desc)
{
	if ((desc.GetManager() == nullptr)
	|| (this->event_main_index_ == 0U)
	|| (this->event_sub_index_ == 0U)) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}


/**
 * @brief SetEventMainIndex関数
 * @param mgr (manager)
 * @param event_main_index (event_main_index)
 */
void tml::ManagerEvent::SetEventMainIndex(tml::Manager *mgr, const UINT event_main_index)
{
	if (mgr->CheckFriendEvent(this)) {
		this->event_main_index_ = event_main_index;
	}

	return;
}


/**
 * @brief SetEventSubIndex関数
 * @param mgr (manager)
 * @param event_sub_index (event_sub_index)
 */
void tml::ManagerEvent::SetEventSubIndex(tml::Manager *mgr, const UINT event_sub_index)
{
	if (mgr->CheckFriendEvent(this)) {
		this->event_sub_index_ = event_sub_index;
	}

	return;
}
