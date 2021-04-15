/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../manager/ManagerEvent.h"


namespace tml {
namespace sound {
class Manager;
}
}


namespace tml {
namespace sound {
/**
 * @brief ManagerEventDescクラス
 */
class ManagerEventDesc : public tml::ManagerEventDesc
{
public:
	tml::sound::Manager *manager;

protected:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::ManagerEventDesc::Release(void)
{
	tml::ManagerEventDesc::Release();

	return;
}


namespace tml {
namespace sound {
/**
 * @brief ManagerEventクラス
 *
 * インターフェースパターン
 */
class ManagerEvent : public tml::ManagerEvent
{
public: ManagerEvent(const tml::sound::ManagerEvent &) = delete;
public: tml::sound::ManagerEvent &operator =(const tml::sound::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::sound::Manager *mgr_;
	tml::ConstantUtil::SOUND::EVENT_TYPE event_type_;

protected:
	void Release(void);
	INT Create(const tml::sound::ManagerEventDesc &, const tml::ConstantUtil::SOUND::EVENT_TYPE);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);

	tml::sound::Manager *GetManager(void);
	tml::ConstantUtil::SOUND::EVENT_TYPE GetEventType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::ManagerEvent::Release(void)
{
	tml::ManagerEvent::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventType関数
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::SOUND::EVENT_TYPE tml::sound::ManagerEvent::GetEventType(void) const
{
	return (this->event_type_);
}
