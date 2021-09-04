/**
 * @file
 * @brief ManagerEventコードファイル
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::ManagerEventDesc::Init(void)
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
INT tml::scene::ManagerEventDesc::ReadValue(const tml::INIFile &conf_file)
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
void tml::scene::ManagerEventDesc::SetManager(tml::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerEventDesc::SetManager(mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_type_(tml::ConstantUtil::SCENE::EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::ManagerEvent::~ManagerEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::ManagerEvent::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::SCENE::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::ManagerEvent::Create(const tml::scene::ManagerEventDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_type_ = static_cast<tml::ConstantUtil::SCENE::EVENT_TYPE>(this->GetEventMainIndex());

	return (0);
}
