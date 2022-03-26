/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "DeviceEvent.h"
#include "MouseDeviceEvent.h"
#include "KeyboardDeviceEvent.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerDesc::ManagerDesc()
{
	this->resource_count = tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT;
	this->task_count = tml::ConstantUtil::INPUT::TASK_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerDesc::Init(void)
{
	this->Release();

	tml::ManagerDesc::Init();

	this->resource_count = tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT;
	this->task_count = tml::ConstantUtil::INPUT::TASK_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::Manager::Manager() :
	mouse_device_pos_(0),
	mouse_device_code_stat_ary_{},
	keyboard_device_code_stat_ary_{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::input::Manager::Release(void)
{
	this->common.Init();

	this->DeleteResourceContainer();
	this->DeleteTaskContainer();
	this->DeleteEventContainer();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::Manager::Init(void)
{
	this->Release();

	this->mouse_device_pos_ = 0;
	this->mouse_device_code_stat_ary_.fill(false);
	this->keyboard_device_code_stat_ary_.fill(false);

	tml::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::Manager::Create(const tml::input::ManagerDesc &desc)
{
	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	POINT mouse_device_sys_pos;

	GetCursorPos(&mouse_device_sys_pos);
	ScreenToClient(this->GetWindowHandle(), &mouse_device_sys_pos);

	this->mouse_device_pos_ = tml::XMINT2EX(mouse_device_sys_pos.x, mouse_device_sys_pos.y);

	{// ResourceFactory Set
	}

	{// EventFactory Set
	}

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::input::Manager::Update(void)
{
	tml::Manager::Update();

	return;
}


/**
 * @brief SetMouseDeviceRawInput関数
 * @param rm (raw_mouse)
 * @return result (result)<br>
 * 0未満=失敗
 */
void tml::input::Manager::SetMouseDeviceRawInput(const RAWMOUSE &rm)
{
	static tml::input::MouseDeviceEventData dat;

	dat.SetRawInput(rm, this->mouse_device_pos_);

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::LEFT, true);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::LEFT, false);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::RIGHT_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::RIGHT, true);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::RIGHT_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::RIGHT, false);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::MIDDLE_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::MIDDLE, true);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::MIDDLE_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::MIDDLE, false);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE1_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE1, true);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE1_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE1, false);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE2_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE2, true);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE2_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE2, false);
	}

	this->RunEvent(static_cast<INT>(tml::ConstantUtil::INPUT::EVENT_TYPE::MOUSE_DEVICE), &dat);

	return;
}


/**
 * @brief SetKeyboardDeviceRawInput関数
 * @param rk (raw_keyboard)
 * @return result (result)<br>
 * 0未満=失敗
 */
void tml::input::Manager::SetKeyboardDeviceRawInput(const RAWKEYBOARD &rk)
{
	static tml::input::KeyboardDeviceEventData dat;

	dat.SetRawInput(rk);

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::BUTTON_DOWN)) {
		this->SetKeyboardDeviceCodeState(dat.code, true);
	}

	if (static_cast<bool>(dat.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::BUTTON_UP)) {
		this->SetKeyboardDeviceCodeState(dat.code, false);
	}

	this->RunEvent(static_cast<INT>(tml::ConstantUtil::INPUT::EVENT_TYPE::KEYBOARD_DEVICE), &dat);

	return;
}
