#if 0
/**
 * @file
 * @brief Eventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"


namespace tml {
namespace input {
class Manager;
}
}


namespace tml {
namespace input {
/**
 * @brief Eventクラス
 *
 * インターフェースパターン
 */
class Event
{
public: Event(const tml::input::Event &) = delete;
public: tml::input::Event &operator =(const tml::input::Event &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::INPUT::EVENT_TYPE event_type_;
	tml::input::Manager *mgr_;

protected:
	void Release(void);
	INT Create(const tml::ConstantUtil::INPUT::EVENT_TYPE, tml::input::Manager *);

public:
	Event();
	virtual ~Event();

	virtual void Init(void);

	tml::ConstantUtil::INPUT::EVENT_TYPE GetEventType(void) const;
	tml::input::Manager *GetManager(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::Event::Release(void)
{
	return;
}


/**
 * @brief GetEventType関数
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::INPUT::EVENT_TYPE tml::input::Event::GetEventType(void) const
{
	return (this->event_type_);
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::Event::GetManager(void)
{
	return (this->mgr_);
}
#endif
