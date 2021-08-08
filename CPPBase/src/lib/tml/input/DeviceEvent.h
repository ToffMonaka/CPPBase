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
 * @brief DeviceEventDescクラス
 */
class DeviceEventDesc : public tml::input::ManagerEventDesc
{
public:

private:
	void Release(void);

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

public:
	static const UINT EVENT_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE);

private:
	tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE type_;

private:
	void Release(void);

public:
	DeviceEvent();
	virtual ~DeviceEvent();

	virtual void Init(void);
	INT Create(const tml::input::DeviceEventDesc &);

	tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE GetType(void) const;
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


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE tml::input::DeviceEvent::GetType(void) const
{
	return (this->type_);
}
