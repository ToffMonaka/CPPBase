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
 * @param event_main_index (event_main_index)
 * @param event_sub_index (event_sub_index)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerEvent::Create(const tml::ManagerEventDesc &desc, const UINT event_main_index, const UINT event_sub_index)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_main_index_ = event_main_index;
	this->event_sub_index_ = event_sub_index;

	return (0);
}
