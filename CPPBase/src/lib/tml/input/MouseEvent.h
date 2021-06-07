/**
 * @file
 * @brief MouseEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathINT.h"
#include "../math/XNAMathFLOAT.h"
#include "ManagerEvent.h"


namespace tml {
namespace input {
/**
 * @brief MouseEventDataクラス
 */
class MouseEventData
{
public:
	tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE type_flag;
	tml::XMINT2EX position;
	tml::XMINT2EX move_value;
	tml::XMFLOAT2EX wheel_value;

protected:
	void Release(void);

public:
	MouseEventData();
	virtual ~MouseEventData();

	virtual void Init(void);

	void SetRawInput(const RAWMOUSE &, const tml::XMINT2EX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::MouseEventData::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief MouseEventDescクラス
 */
class MouseEventDesc : public tml::input::ManagerEventDesc
{
public:
	tml::input::MouseEventData data;

protected:
	void Release(void);

public:
	MouseEventDesc();
	virtual ~MouseEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::MouseEventDesc::Release(void)
{
	tml::input::ManagerEventDesc::Release();

	return;
}


namespace tml {
namespace input {
/**
 * @brief MouseEventクラス
 */
class MouseEvent : public tml::input::ManagerEvent
{
public: MouseEvent(const tml::input::MouseEvent &) = delete;
public: tml::input::MouseEvent &operator =(const tml::input::MouseEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT EVENT_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE);
	static const UINT EVENT_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::MOUSE);

private:
	tml::input::MouseEventData dat_;

protected:
	void Release(void);

public:
	MouseEvent();
	virtual ~MouseEvent();

	virtual void Init(void);
	INT Create(const tml::input::MouseEventDesc &);

	tml::input::MouseEventData &GetData(void);
	void SetData(const tml::input::MouseEventData &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::MouseEvent::Release(void)
{
	tml::input::ManagerEvent::Release();

	return;
}


/**
 * @brief GetData関数
 * @return dat (data)
 */
inline tml::input::MouseEventData &tml::input::MouseEvent::GetData(void)
{
	return (this->dat_);
}


/**
 * @brief SetData関数
 * @param dat (data)
 */
inline void tml::input::MouseEvent::SetData(const tml::input::MouseEventData &dat)
{
	this->dat_ = dat;

	return;
}
