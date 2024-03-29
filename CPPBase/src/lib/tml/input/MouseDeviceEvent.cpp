/**
 * @file
 * @brief MouseDeviceEventコードファイル
 */


#include "MouseDeviceEvent.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::MouseDeviceEventData::MouseDeviceEventData() :
	type_flag(tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::NONE),
	position(0),
	move_value(0),
	wheel_value(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::MouseDeviceEventData::~MouseDeviceEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::MouseDeviceEventData::Init(void)
{
	this->Release();

	this->type_flag = tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::NONE;
	this->position = 0;
	this->move_value = 0;
	this->wheel_value = 0.0f;

	tml::input::DeviceEventData::Init();

	return;
}


/**
 * @brief SetRawInput関数
 * @param rm (raw_mouse)
 * @param pos (position)
 */
void tml::input::MouseDeviceEventData::SetRawInput(const RAWMOUSE &rm, const tml::XMINT2EX &pos)
{
	this->type_flag = static_cast<tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE>(rm.usButtonFlags);
	this->position = pos;

	if ((rm.lLastX != 0L) || (rm.lLastY != 0L)) {
		this->type_flag |= tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::MOVE;
		this->move_value.x = rm.lLastX;
		this->move_value.y = rm.lLastY;
	} else {
		this->move_value = 0;
	}

	if (rm.usButtonFlags & (RI_MOUSE_HWHEEL | RI_MOUSE_WHEEL)) {
		this->type_flag |= tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::WHEEL;
		this->wheel_value.x = (rm.usButtonFlags & RI_MOUSE_HWHEEL) ? static_cast<FLOAT>(static_cast<SHORT>(rm.usButtonData)) / WHEEL_DELTA : 0.0f;
		this->wheel_value.y = (rm.usButtonFlags & RI_MOUSE_WHEEL) ? static_cast<FLOAT>(static_cast<SHORT>(rm.usButtonData)) / WHEEL_DELTA : 0.0f;
	} else {
		this->wheel_value = 0.0f;
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::MouseDeviceEventDesc::MouseDeviceEventDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::MouseDeviceEventDesc::~MouseDeviceEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::MouseDeviceEventDesc::Init(void)
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
INT tml::input::MouseDeviceEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::input::DeviceEventDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// MouseDeviceEvent Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MOUSE_DEVICE_EVENT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::input::MouseDeviceEvent::MouseDeviceEvent()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::MouseDeviceEvent::~MouseDeviceEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::MouseDeviceEvent::Init(void)
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
INT tml::input::MouseDeviceEvent::Create(const tml::input::MouseDeviceEventDesc &desc)
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
void tml::input::MouseDeviceEvent::OnRun(const tml::ManagerEventData *dat)
{
	return;
}
