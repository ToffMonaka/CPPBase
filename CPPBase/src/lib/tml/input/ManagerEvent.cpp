/**
 * @file
 * @brief ManagerEventコードファイル
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerEventData::ManagerEventData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerEventData::~ManagerEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerEventData::Init(void)
{
	this->Release();

	tml::ManagerEventData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
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
INT tml::input::ManagerEventDesc::ReadValue(const tml::INIFile &conf_file)
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
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::input::ManagerEventDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::input::Manager *>(mgr);

	tml::ManagerEventDesc::OnSetManager(this->mgr_);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::ManagerEvent::ManagerEvent() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerEvent::~ManagerEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerEvent::Init(void)
{
	this->Release();

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::ManagerEvent::Create(const tml::input::ManagerEventDesc &desc)
{
	if (tml::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::input::ManagerEvent::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::input::Manager *>(mgr);

	tml::ManagerEvent::OnSetManager(this->mgr_);

	return;
}
