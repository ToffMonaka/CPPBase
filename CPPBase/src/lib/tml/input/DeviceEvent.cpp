/**
 * @file
 * @brief DeviceEventコードファイル
 */


#include "DeviceEvent.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::DeviceEventDesc::DeviceEventDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::DeviceEventDesc::~DeviceEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::DeviceEventDesc::Init(void)
{
	this->Release();

	tml::input::ManagerEventDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::DeviceEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::input::ManagerEventDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// DeviceEvent Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"DEVICE_EVENT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::input::DeviceEvent::DeviceEvent() :
	type_(tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::DeviceEvent::~DeviceEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::DeviceEvent::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::NONE;

	tml::input::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::DeviceEvent::Create(const tml::input::DeviceEventDesc &desc)
{
	if (tml::input::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE>(this->GetEventSubIndex());

	return (0);
}
