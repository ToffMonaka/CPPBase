#if 0
/**
 * @file
 * @brief Eventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"


namespace tml {
namespace sound {
class Manager;
}
}


namespace tml {
namespace sound {
/**
 * @brief Eventクラス
 *
 * インターフェースパターン
 */
class Event
{
public: Event(const tml::sound::Event &) = delete;
public: tml::sound::Event &operator =(const tml::sound::Event &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::SOUND::EVENT_TYPE event_type_;
	tml::sound::Manager *mgr_;

protected:
	void Release(void);
	INT Create(const tml::ConstantUtil::SOUND::EVENT_TYPE, tml::sound::Manager *);

public:
	Event();
	virtual ~Event();

	virtual void Init(void);

	tml::ConstantUtil::SOUND::EVENT_TYPE GetEventType(void) const;
	tml::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::Event::Release(void)
{
	return;
}


/**
 * @brief GetEventType関数
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::SOUND::EVENT_TYPE tml::sound::Event::GetEventType(void) const
{
	return (this->event_type_);
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::Event::GetManager(void)
{
	return (this->mgr_);
}
#endif
