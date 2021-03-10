/**
 * @file
 * @brief MouseEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "Event.h"


namespace tml {
namespace input {
/**
 * @brief MouseEventDataクラス
 */
class MouseEventData
{
public:
	UINT type_flag;
	tml::XMUINT2EX position;

protected:
	void Release(void);

public:
	MouseEventData();
	virtual ~MouseEventData();

	virtual void Init(void);
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
 * @brief MouseEventクラス
 */
class MouseEvent : public tml::input::Event
{
public: MouseEvent(const tml::input::MouseEvent &) = delete;
public: tml::input::MouseEvent &operator =(const tml::input::MouseEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const tml::ConstantUtil::INPUT::EVENT_TYPE EVENT_TYPE = tml::ConstantUtil::INPUT::EVENT_TYPE::MOUSE;

private:
	tml::input::MouseEventData dat_;

protected:
	void Release(void);

public:
	MouseEvent();
	virtual ~MouseEvent();

	virtual void Init(void);
	INT Create(tml::input::Manager *);

	const tml::input::MouseEventData &GetData(void) const;
	void SetData(const tml::input::MouseEventData &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::MouseEvent::Release(void)
{
	tml::input::Event::Release();

	return;
}


/**
 * @brief GetData関数
 * @return dat (data)
 */
inline const tml::input::MouseEventData &tml::input::MouseEvent::GetData(void) const
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
