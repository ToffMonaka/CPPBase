/**
 * @file
 * @brief KeyboardDeviceEventコードファイル
 */


#include "KeyboardDeviceEvent.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::KeyboardDeviceEventData::KeyboardDeviceEventData() :
	type_flag(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::NONE),
	code(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::KeyboardDeviceEventData::~KeyboardDeviceEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::KeyboardDeviceEventData::Init(void)
{
	this->Release();

	this->type_flag = tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::NONE;
	this->code = tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::NONE;

	tml::input::DeviceEventData::Init();

	return;
}


/**
 * @brief SetRawInput関数
 * @param rk (raw_keyboard)
 */
void tml::input::KeyboardDeviceEventData::SetRawInput(const RAWKEYBOARD &rk)
{
	this->type_flag = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE>((rk.Flags & 1) + 1);
	this->code = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE>(rk.VKey);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::KeyboardDeviceEventDesc::KeyboardDeviceEventDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::KeyboardDeviceEventDesc::~KeyboardDeviceEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::KeyboardDeviceEventDesc::Init(void)
{
	this->Release();

	tml::input::DeviceEventDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::KeyboardDeviceEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::input::DeviceEventDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// KeyboardDeviceEvent Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"KEYBOARD_DEVICE_EVENT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::input::KeyboardDeviceEvent::KeyboardDeviceEvent()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::KeyboardDeviceEvent::~KeyboardDeviceEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::KeyboardDeviceEvent::Init(void)
{
	this->Release();

	tml::input::DeviceEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::KeyboardDeviceEvent::Create(const tml::input::KeyboardDeviceEventDesc &desc)
{
	this->Init();

	if (tml::input::DeviceEvent::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief OnRun関数
 * @param dat (data)
 */
void tml::input::KeyboardDeviceEvent::OnRun(const tml::ManagerEventData *dat)
{
	return;
}
