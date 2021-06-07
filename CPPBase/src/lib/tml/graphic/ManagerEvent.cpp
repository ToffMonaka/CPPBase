/**
 * @file
 * @brief ManagerEventコードファイル
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerEventDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::ManagerEventDesc::Init();

	return;
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
void tml::graphic::ManagerEventDesc::SetManager(tml::graphic::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerEventDesc::SetManager(mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_type_(tml::ConstantUtil::GRAPHIC::EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerEvent::~ManagerEvent()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerEvent::Init(void)
{
	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::GRAPHIC::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param event_type (event_type)
 * @param event_sub_index (event_sub_index)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ManagerEvent::Create(const tml::graphic::ManagerEventDesc &desc, const tml::ConstantUtil::GRAPHIC::EVENT_TYPE event_type, const UINT event_sub_index)
{
	if ((desc.GetManager() == nullptr)
	|| (event_type == tml::ConstantUtil::GRAPHIC::EVENT_TYPE::NONE)) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc, static_cast<UINT>(event_type), event_sub_index) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_type_ = event_type;

	return (0);
}
