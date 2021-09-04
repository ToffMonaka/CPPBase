/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../manager/ManagerEvent.h"


namespace tml {
namespace graphic {
/**
 * @brief ManagerEventDescクラス
 */
class ManagerEventDesc : public tml::ManagerEventDesc
{
private:
	tml::graphic::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void) const;
	void SetManager(tml::graphic::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ManagerEventDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerEventクラス
 *
 * インターフェースパターン
 */
class ManagerEvent : public tml::ManagerEvent
{
public: ManagerEvent(const tml::graphic::ManagerEvent &) = delete;
public: tml::graphic::ManagerEvent &operator =(const tml::graphic::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::graphic::Manager *mgr_;
	tml::ConstantUtil::GRAPHIC::EVENT_TYPE event_type_;

private:
	void Release(void);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::graphic::ManagerEventDesc &);

	tml::graphic::Manager *GetManager(void);
	tml::ConstantUtil::GRAPHIC::EVENT_TYPE GetEventType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventType関数
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::GRAPHIC::EVENT_TYPE tml::graphic::ManagerEvent::GetEventType(void) const
{
	return (this->event_type_);
}
