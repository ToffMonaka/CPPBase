/**
 * @file
 * @brief DeviceEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerEvent.h"


namespace tml {
namespace input {
/**
 * @brief DeviceEventDataクラス
 */
class DeviceEventData : public tml::input::ManagerEventData
{
public:

private:
	void Release(void);

public:
	DeviceEventData();
	virtual ~DeviceEventData();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::DeviceEventData::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief DeviceEventDescクラス
 */
class DeviceEventDesc : public tml::input::ManagerEventDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	DeviceEventDesc();
	virtual ~DeviceEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::DeviceEventDesc::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief DeviceEventクラス
 *
 * インターフェースパターン
 */
class DeviceEvent : public tml::input::ManagerEvent
{
public: DeviceEvent(const tml::input::DeviceEvent &) = delete;
public: tml::input::DeviceEvent &operator =(const tml::input::DeviceEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	DeviceEvent();
	virtual ~DeviceEvent();

	virtual void Init(void);
	INT Create(const tml::input::DeviceEventDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::DeviceEvent::Release(void)
{
	return;
}
