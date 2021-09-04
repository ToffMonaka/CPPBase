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
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ManagerEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::ManagerEventDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Event Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"EVENT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
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
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerEvent::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::GRAPHIC::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ManagerEvent::Create(const tml::graphic::ManagerEventDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_type_ = static_cast<tml::ConstantUtil::GRAPHIC::EVENT_TYPE>(this->GetEventMainIndex());

	return (0);
}
