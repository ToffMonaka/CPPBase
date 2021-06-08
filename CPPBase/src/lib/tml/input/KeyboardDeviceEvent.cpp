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

	this->data.Init();

	tml::input::DeviceEventDesc::Init();

	return;
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

	this->data.Init();

	tml::input::DeviceEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::KeyboardDeviceEvent::Create(const tml::input::KeyboardDeviceEventDesc &desc)
{
	this->Init();

	if (tml::input::DeviceEvent::Create(desc, tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::KEYBOARD) < 0) {
		this->Init();

		return (-1);
	}

	this->data = desc.data;

	return (0);
}
