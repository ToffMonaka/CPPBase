/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "MouseDeviceEvent.h"
#include "KeyboardDeviceEvent.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerDesc::ManagerDesc()
{
	this->InitResourceCount();
	this->InitEventCount();

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

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void tml::input::ManagerDesc::InitResourceCount(void)
{
	tml::ManagerDesc::InitResourceCount();

	this->resource_count_container.resize(tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT);

	return;
}


/**
 * @brief InitEventCount関数
 */
void tml::input::ManagerDesc::InitEventCount(void)
{
	tml::ManagerDesc::InitEventCount();

	this->event_count_container.resize(tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT);
	this->event_count_container[static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE)] = tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE_COUNT;

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
	this->factory.Init();
	this->common.Init();

	this->DeleteResourceContainer();

	tml::Manager::Release();

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
 * @return res (result)<br>
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

	if (this->factory.Create(this) < 0) {
		this->Init();

		return (-1);
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
 * @brief AddMouseDeviceRawInput関数
 * @param rm (raw_mouse)
 * @param pos (position)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::Manager::AddMouseDeviceRawInput(const RAWMOUSE &rm, const tml::XMINT2EX &pos)
{
	tml::input::MouseDeviceEventDesc event_desc;

	event_desc.SetManager(this);
	event_desc.data.SetRawInput(rm, pos);

	this->AddEvent<tml::input::MouseDeviceEvent>(event_desc);

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::LEFT, true);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::LEFT_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::LEFT, false);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::RIGHT_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::RIGHT, true);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::RIGHT_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::RIGHT, false);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::MIDDLE_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::MIDDLE, true);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::MIDDLE_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::MIDDLE, false);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE1_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE1, true);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE1_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE1, false);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE2_BUTTON_DOWN)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE2, true);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE::SIDE2_BUTTON_UP)) {
		this->SetMouseDeviceCodeState(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::SIDE2, false);
	}

	return (0);
}


/**
 * @brief AddKeyboardDeviceRawInput関数
 * @param rk (raw_keyboard)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::Manager::AddKeyboardDeviceRawInput(const RAWKEYBOARD &rk)
{
	tml::input::KeyboardDeviceEventDesc event_desc;

	event_desc.SetManager(this);
	event_desc.data.SetRawInput(rk);

	this->AddEvent<tml::input::KeyboardDeviceEvent>(event_desc);

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::BUTTON_DOWN)) {
		this->SetKeyboardDeviceCodeState(event_desc.data.code, true);
	}

	if (static_cast<bool>(event_desc.data.type_flag & tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::BUTTON_UP)) {
		this->SetKeyboardDeviceCodeState(event_desc.data.code, false);
	}

	return (0);
}
