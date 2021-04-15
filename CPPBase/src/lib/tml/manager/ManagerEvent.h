/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief ManagerEventDescクラス
 */
class ManagerEventDesc
{
public:

protected:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerEventDesc::Release(void)
{
	return;
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
	UINT event_index_;

protected:
	void Release(void);
	INT Create(const tml::ManagerEventDesc &, const UINT);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);

	UINT GetEventIndex(void) const;
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
 * @brief GetEventIndex関数
 * @return event_index (event_index)
 */
inline UINT tml::ManagerEvent::GetEventIndex(void) const
{
	return (this->event_index_);
}
