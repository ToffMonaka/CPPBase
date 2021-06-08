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

	this->data.Init();

	tml::input::DeviceEventDesc::Init();

	return;
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

	this->data.Init();

	tml::input::DeviceEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
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
