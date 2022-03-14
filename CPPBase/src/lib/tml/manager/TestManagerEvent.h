/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <functional>
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
	std::wstring event_name;
	bool run_flag;
	std::function<void(void)> function;

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
	tml::shared_ptr<tml::test::ManagerEvent> event_shared_p_;
	std::wstring event_name_;
	bool run_flg_;
	bool run_added_flg_;
	std::function<void(void)> func_;

private:
	void Release(void);

protected:
	virtual void OnRun(void) = 0;

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::test::ManagerEventDesc &);

	void Run(void);

	tml::test::Manager *GetManager(void);
	UINT GetEventIndex(void) const;
	const tml::shared_ptr<tml::test::ManagerEvent> &GetEventSharedPointer(void) const;
	const std::wstring &GetEventName(void) const;
	bool GetRunFlag(void) const;
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


/**
 * @brief GetEventSharedPointer関数
 * @return event_shared_p (event_shared_pointer)
 */
inline const tml::shared_ptr<tml::test::ManagerEvent> &tml::test::ManagerEvent::GetEventSharedPointer(void) const
{
	return (this->event_shared_p_);
}


/**
 * @brief GetEventName関数
 * @return event_name (event_name)
 */
inline const std::wstring &tml::test::ManagerEvent::GetEventName(void) const
{
	return (this->event_name_);
}


/**
 * @brief GetRunFlag関数
 * @return run_flg (run_flag)
 */
inline bool tml::test::ManagerEvent::GetRunFlag(void) const
{
	return (this->run_flg_);
}
