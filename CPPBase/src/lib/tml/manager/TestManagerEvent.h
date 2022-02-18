/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../file/INIFile.h"


namespace tml {
namespace test {
class Manager;
}
}


namespace tml {
namespace test {
/**
 * @brief ManagerEventDescクラス
 */
class ManagerEventDesc
{
private:
	tml::test::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);

	tml::test::Manager *GetManager(void) const;
	void SetManager(tml::test::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::test::ManagerEventDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace test {
/**
 * @brief ManagerEventクラス
 *
 * インターフェースパターン
 */
class ManagerEvent
{
friend class tml::test::Manager;

public: ManagerEvent(const tml::test::ManagerEvent &) = delete;
public: tml::test::ManagerEvent &operator =(const tml::test::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::test::Manager *mgr_;
	UINT event_index_;

private:
	void Release(void);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::test::ManagerEventDesc &);

	tml::test::Manager *GetManager(void);
	UINT GetEventIndex(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::test::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventIndex関数
 * @return event_index (event_index)
 */
inline UINT tml::test::ManagerEvent::GetEventIndex(void) const
{
	return (this->event_index_);
}
