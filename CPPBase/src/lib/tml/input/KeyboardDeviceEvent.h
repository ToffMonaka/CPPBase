/**
 * @file
 * @brief KeyboardDeviceEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "DeviceEvent.h"


namespace tml {
namespace input {
/**
 * @brief KeyboardDeviceEventData�N���X
 */
class KeyboardDeviceEventData
{
public:
	tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE type_flag;
	tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE code;

private:
	void Release(void);

public:
	KeyboardDeviceEventData();
	virtual ~KeyboardDeviceEventData();

	virtual void Init(void);

	void SetRawInput(const RAWKEYBOARD &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::KeyboardDeviceEventData::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief KeyboardDeviceEventDesc�N���X
 */
class KeyboardDeviceEventDesc : public tml::input::DeviceEventDesc
{
public:
	tml::input::KeyboardDeviceEventData data;

private:
	void Release(void);

public:
	KeyboardDeviceEventDesc();
	virtual ~KeyboardDeviceEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::KeyboardDeviceEventDesc::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief KeyboardDeviceEvent�N���X
 */
class KeyboardDeviceEvent : public tml::input::DeviceEvent
{
public: KeyboardDeviceEvent(const tml::input::KeyboardDeviceEvent &) = delete;
public: tml::input::KeyboardDeviceEvent &operator =(const tml::input::KeyboardDeviceEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT EVENT_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::KEYBOARD);

private:

public:
	tml::input::KeyboardDeviceEventData data;

private:
	void Release(void);

public:
	KeyboardDeviceEvent();
	virtual ~KeyboardDeviceEvent();

	virtual void Init(void);
	INT Create(const tml::input::KeyboardDeviceEventDesc &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::KeyboardDeviceEvent::Release(void)
{
	return;
}
