/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
class Manager;
}


namespace tml {
/**
 * @brief ManagerEventDescクラス
 */
class ManagerEventDesc
{
private:
	tml::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::Manager *GetManager(void) const;
	void SetManager(tml::Manager *);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerEventDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
/**
 * @brief ManagerEventクラス
 *
 * インターフェースパターン
 */
class ManagerEvent
{
public: ManagerEvent(const tml::ManagerEvent &) = delete;
public: tml::ManagerEvent &operator =(const tml::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::Manager *mgr_;
	UINT event_main_index_;
	UINT event_sub_index_;

protected:
	void Release(void);
	INT Create(const tml::ManagerEventDesc &);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);

	tml::Manager *GetManager(void);
	UINT GetEventMainIndex(void) const;
	void SetEventMainIndex(tml::Manager *, const UINT);
	UINT GetEventSubIndex(void) const;
	void SetEventSubIndex(tml::Manager *, const UINT);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventMainIndex関数
 * @return event_main_index (event_main_index)
 */
inline UINT tml::ManagerEvent::GetEventMainIndex(void) const
{
	return (this->event_main_index_);
}


/**
 * @brief GetEventSubIndex関数
 * @return event_sub_index (event_sub_index)
 */
inline UINT tml::ManagerEvent::GetEventSubIndex(void) const
{
	return (this->event_sub_index_);
}
