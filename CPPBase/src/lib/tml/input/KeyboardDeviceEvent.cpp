/**
 * @file
 * @brief KeyboardDeviceEvent�R�[�h�t�@�C��
 */


#include "KeyboardDeviceEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardDeviceEventData::KeyboardDeviceEventData() :
	type_flag(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE::NONE),
	code(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardDeviceEventData::~KeyboardDeviceEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
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
 * @brief SetRawInput�֐�
 * @param rk (raw_keyboard)
 */
void tml::input::KeyboardDeviceEventData::SetRawInput(const RAWKEYBOARD &rk)
{
	this->type_flag = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE>((rk.Flags & 1) + 1);
	this->code = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE>(rk.VKey);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardDeviceEventDesc::KeyboardDeviceEventDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardDeviceEventDesc::~KeyboardDeviceEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::KeyboardDeviceEventDesc::Init(void)
{
	this->Release();

	tml::input::DeviceEventDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardDeviceEvent::KeyboardDeviceEvent()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardDeviceEvent::~KeyboardDeviceEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::KeyboardDeviceEvent::Init(void)
{
	this->Release();

	tml::input::DeviceEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
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
 * @brief OnRun�֐�
 * @param dat (data)
 */
void tml::input::KeyboardDeviceEvent::OnRun(const tml::ManagerEventData *dat)
{
	return;
}
