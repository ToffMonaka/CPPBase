/**
 * @file
 * @brief MouseDeviceEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "DeviceEvent.h"


namespace tml {
namespace input {
/**
 * @brief MouseDeviceEventDataクラス
 */
class MouseDeviceEventData : public tml::input::DeviceEventData
{
public:
	tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE type_flag;
	tml::XMINT2EX position;
	tml::XMINT2EX move_value;
	tml::XMFLOAT2EX wheel_value;

private:
	void Release(void);

public:
	MouseDeviceEventData();
	virtual ~MouseDeviceEventData();

	virtual void Init(void);

	void SetRawInput(const RAWMOUSE &, const tml::XMINT2EX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::MouseDeviceEventData::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief MouseDeviceEventDescクラス
 */
class MouseDeviceEventDesc : public tml::input::DeviceEventDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	MouseDeviceEventDesc();
	virtual ~MouseDeviceEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::MouseDeviceEventDesc::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief MouseDeviceEventクラス
 */
class MouseDeviceEvent : public tml::input::DeviceEvent
{
public: MouseDeviceEvent(const tml::input::MouseDeviceEvent &) = delete;
public: tml::input::MouseDeviceEvent &operator =(const tml::input::MouseDeviceEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT EVENT_TYPE = static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::MOUSE_DEVICE);

private:

private:
	void Release(void);

protected:
	virtual void OnRun(const tml::ManagerEventData *);

public:
	MouseDeviceEvent();
	virtual ~MouseDeviceEvent();

	virtual void Init(void);
	INT Create(const tml::input::MouseDeviceEventDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::MouseDeviceEvent::Release(void)
{
	return;
}
