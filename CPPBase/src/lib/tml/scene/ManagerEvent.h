/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../manager/ManagerEvent.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerEventDescクラス
 */
class ManagerEventDesc : public tml::ManagerEventDesc
{
private:
	tml::scene::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::scene::Manager *GetManager(void) const;
	void SetManager(tml::scene::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::ManagerEventDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace scene {
/**
 * @brief ManagerEventクラス
 *
 * インターフェースパターン
 */
class ManagerEvent : public tml::ManagerEvent
{
public: ManagerEvent(const tml::scene::ManagerEvent &) = delete;
public: tml::scene::ManagerEvent &operator =(const tml::scene::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::scene::Manager *mgr_;
	tml::ConstantUtil::SCENE::EVENT_TYPE event_type_;

private:
	void Release(void);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::scene::ManagerEventDesc &);

	tml::scene::Manager *GetManager(void);
	tml::ConstantUtil::SCENE::EVENT_TYPE GetEventType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventType関数
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::SCENE::EVENT_TYPE tml::scene::ManagerEvent::GetEventType(void) const
{
	return (this->event_type_);
}
