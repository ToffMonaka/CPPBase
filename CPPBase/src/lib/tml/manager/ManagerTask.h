/**
 * @file
 * @brief ManagerTaskヘッダーファイル
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
 * @brief ManagerTaskDescクラス
 */
class ManagerTaskDesc
{
private:
	tml::Manager *mgr_;

public:
	std::wstring task_name;
	bool run_flag;
	std::function<void(void)> function;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTaskDesc();
	virtual ~ManagerTaskDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);

	tml::Manager *GetManager(void) const;
	void SetManager(tml::Manager *);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerTaskDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerTaskDesc::GetManager(void) const
{
	return (this->mgr_);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::ManagerTaskDesc::SetManager(tml::Manager *mgr)
{
	this->OnSetManager(mgr);

	return;
}


namespace tml {
/**
 * @brief ManagerTaskクラス
 *
 * インターフェースパターン
 */
class ManagerTask
{
friend class tml::Manager;

public: ManagerTask(const tml::ManagerTask &) = delete;
public: tml::ManagerTask &operator =(const tml::ManagerTask &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::Manager *mgr_;
	UINT task_type_;
	tml::shared_ptr<tml::ManagerTask> task_shared_p_;
	std::wstring task_name_;
	bool run_flg_;
	bool run_added_flg_;
	std::function<void(void)> func_;

private:
	void Release(void);

protected:
	virtual void OnRun(void) = 0;

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTask();
	virtual ~ManagerTask();

	virtual void Init(void);
	INT Create(const tml::ManagerTaskDesc &);

	void Run(void);

	tml::Manager *GetManager(void);
	void SetManager(tml::Manager *);
	UINT GetTaskType(void) const;
	const tml::shared_ptr<tml::ManagerTask> &GetTaskSharedPointer(void) const;
	const std::wstring &GetTaskName(void) const;
	bool GetRunFlag(void) const;
	void SetRunFlag(const bool);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerTask::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerTask::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
inline void tml::ManagerTask::SetManager(tml::Manager *mgr)
{
	this->OnSetManager(mgr);

	return;
}


/**
 * @brief GetTaskType関数
 * @return task_type (task_type)
 */
inline UINT tml::ManagerTask::GetTaskType(void) const
{
	return (this->task_type_);
}


/**
 * @brief GetTaskSharedPointer関数
 * @return task_shared_p (task_shared_pointer)
 */
inline const tml::shared_ptr<tml::ManagerTask> &tml::ManagerTask::GetTaskSharedPointer(void) const
{
	return (this->task_shared_p_);
}


/**
 * @brief GetTaskName関数
 * @return task_name (task_name)
 */
inline const std::wstring &tml::ManagerTask::GetTaskName(void) const
{
	return (this->task_name_);
}


/**
 * @brief GetRunFlag関数
 * @return run_flg (run_flag)
 */
inline bool tml::ManagerTask::GetRunFlag(void) const
{
	return (this->run_flg_);
}
