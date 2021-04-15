/**
 * @file
 * @brief ManagerEventコードファイル
 */


#include "ManagerEvent.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerEventDesc::ManagerEventDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerEventDesc::Init(void)
{
	this->Release();

	this->manager = nullptr;

	tml::ManagerEventDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_type_(tml::ConstantUtil::INPUT::EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerEvent::~ManagerEvent()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerEvent::Init(void)
{
	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::INPUT::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param event_type (event_type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::ManagerEvent::Create(const tml::input::ManagerEventDesc &desc, const tml::ConstantUtil::INPUT::EVENT_TYPE event_type)
{
	if ((desc.manager == nullptr)
	|| (event_type == tml::ConstantUtil::INPUT::EVENT_TYPE::NONE)) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc, static_cast<UINT>(event_type)) < 0) {
		return (-1);
	}

	this->mgr_ = desc.manager;
	this->event_type_ = event_type;

	return (0);
}
