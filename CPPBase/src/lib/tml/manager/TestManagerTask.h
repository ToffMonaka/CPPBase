/**
 * @file
 * @brief ManagerTaskヘッダーファイル
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
 * @brief ManagerTaskDescクラス
 */
class ManagerTaskDesc
{
private:
	tml::test::Manager *mgr_;

public:
	std::wstring task_name;
	bool run_flag;
	std::function<void(void)> function;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerTaskDesc();
	virtual ~ManagerTaskDesc();

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
inline void tml::test::ManagerTaskDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerTaskDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace test {
/**
 * @brief ManagerTaskクラス
 *
 * インターフェースパターン
 */
class ManagerTask
{
friend class tml::test::Manager;

public: ManagerTask(const tml::test::ManagerTask &) = delete;
public: tml::test::ManagerTask &operator =(const tml::test::ManagerTask &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::test::Manager *mgr_;
	UINT task_index_;
	tml::shared_ptr<tml::test::ManagerTask> task_shared_p_;
	std::wstring task_name_;
	bool run_flg_;
	bool run_added_flg_;
	std::function<void(void)> func_;

private:
	void Release(void);

protected:
	virtual void OnRun(void) = 0;

public:
	ManagerTask();
	virtual ~ManagerTask();

	virtual void Init(void);
	INT Create(const tml::test::ManagerTaskDesc &);

	void Run(void);

	tml::test::Manager *GetManager(void);
	UINT GetTaskIndex(void) const;
	const tml::shared_ptr<tml::test::ManagerTask> &GetTaskSharedPointer(void) const;
	const std::wstring &GetTaskName(void) const;
	bool GetRunFlag(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::test::ManagerTask::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerTask::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetTaskIndex関数
 * @return task_index (task_index)
 */
inline UINT tml::test::ManagerTask::GetTaskIndex(void) const
{
	return (this->task_index_);
}


/**
 * @brief GetTaskSharedPointer関数
 * @return task_shared_p (task_shared_pointer)
 */
inline const tml::shared_ptr<tml::test::ManagerTask> &tml::test::ManagerTask::GetTaskSharedPointer(void) const
{
	return (this->task_shared_p_);
}


/**
 * @brief GetTaskName関数
 * @return task_name (task_name)
 */
inline const std::wstring &tml::test::ManagerTask::GetTaskName(void) const
{
	return (this->task_name_);
}


/**
 * @brief GetRunFlag関数
 * @return run_flg (run_flag)
 */
inline bool tml::test::ManagerTask::GetRunFlag(void) const
{
	return (this->run_flg_);
}
