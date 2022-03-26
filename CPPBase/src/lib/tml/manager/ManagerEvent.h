/**
 * @file
 * @brief ManagerEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <functional>
#include "../file/INIFile.h"


namespace tml {
class Manager;
}


namespace tml {
/**
 * @brief ManagerEventDataクラス
 */
class ManagerEventData
{
public:

private:
	void Release(void);

public:
	ManagerEventData();
	virtual ~ManagerEventData();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerEventData::Release(void)
{
	return;
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
	std::wstring event_name;
	bool run_flag;
	std::function<void(const tml::ManagerEventData *)> function;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);

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


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::ManagerEventDesc::SetManager(tml::Manager *mgr)
{
	this->OnSetManager(mgr);

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
friend class tml::Manager;

public: ManagerEvent(const tml::ManagerEvent &) = delete;
public: tml::ManagerEvent &operator =(const tml::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::Manager *mgr_;
	UINT event_type_;
	tml::shared_ptr<tml::ManagerEvent> event_shared_p_;
	std::wstring event_name_;
	bool run_flg_;
	bool run_added_flg_;
	std::function<void(const tml::ManagerEventData *)> func_;

private:
	void Release(void);

protected:
	virtual void OnRun(const tml::ManagerEventData *) = 0;

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::ManagerEventDesc &);

	void Run(const tml::ManagerEventData *);

	tml::Manager *GetManager(void);
	void SetManager(tml::Manager *);
	UINT GetEventType(void) const;
	const tml::shared_ptr<tml::ManagerEvent> &GetEventSharedPointer(void) const;
	const std::wstring &GetEventName(void) const;
	bool GetRunFlag(void) const;
	void SetRunFlag(const bool);
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
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::ManagerEvent::SetManager(tml::Manager *mgr)
{
	this->OnSetManager(mgr);

	return;
}


/**
 * @brief GetEventType関数
 * @return event_type (event_type)
 */
inline UINT tml::ManagerEvent::GetEventType(void) const
{
	return (this->event_type_);
}


/**
 * @brief GetEventSharedPointer関数
 * @return event_shared_p (event_shared_pointer)
 */
inline const tml::shared_ptr<tml::ManagerEvent> &tml::ManagerEvent::GetEventSharedPointer(void) const
{
	return (this->event_shared_p_);
}


/**
 * @brief GetEventName関数
 * @return event_name (event_name)
 */
inline const std::wstring &tml::ManagerEvent::GetEventName(void) const
{
	return (this->event_name_);
}


/**
 * @brief GetRunFlag関数
 * @return run_flg (run_flag)
 */
inline bool tml::ManagerEvent::GetRunFlag(void) const
{
	return (this->run_flg_);
}
