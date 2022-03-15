/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <list>
#include "TestManagerFactory.h"


namespace tml {
namespace test {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:
	HWND window_handle;
	HDC window_device_context_handle;
	tml::test::ManagerFactory *factory;
	UINT resource_count;
	UINT task_count;
	UINT event_count;

private:
	void Release(void);

protected:
	void InitResourceCount(void);
	void InitTaskCount(void);
	void InitEventCount(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::test::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
namespace test {
/**
 * @brief Managerクラス
 *
 * インターフェースパターン
 */
class Manager
{
public: Manager(const tml::test::Manager &) = delete;
public: tml::test::Manager &operator =(const tml::test::Manager &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	std::list<tml::shared_ptr<tml::test::ManagerResource>> res_cont_;
	std::list<tml::shared_ptr<tml::test::ManagerResource>>::iterator res_itr_;
	std::vector<std::list<tml::shared_ptr<tml::test::ManagerResource>>> res_cont_by_index_;
	std::unordered_map<std::wstring, tml::shared_ptr<tml::test::ManagerResource>> res_cont_by_name_;
	std::list<tml::shared_ptr<tml::test::ManagerResource>> deferred_create_res_cont_;
	std::list<tml::shared_ptr<tml::test::ManagerResource>> add_deferred_create_res_cont_;
	std::list<tml::shared_ptr<tml::test::ManagerTask>> task_cont_;
	std::list<tml::shared_ptr<tml::test::ManagerTask>>::iterator task_itr_;
	std::vector<std::list<tml::shared_ptr<tml::test::ManagerTask>>> task_cont_by_index_;
	std::unordered_map<std::wstring, tml::shared_ptr<tml::test::ManagerTask>> task_cont_by_name_;
	std::list<tml::shared_ptr<tml::test::ManagerTask>> run_task_cont_;
	std::list<tml::shared_ptr<tml::test::ManagerTask>> add_run_task_cont_;
	std::list<tml::shared_ptr<tml::test::ManagerEvent>> event_cont_;
	std::list<tml::shared_ptr<tml::test::ManagerEvent>>::iterator event_itr_;
	std::vector<std::list<tml::shared_ptr<tml::test::ManagerEvent>>> event_cont_by_index_;
	std::unordered_map<std::wstring, tml::shared_ptr<tml::test::ManagerEvent>> event_cont_by_name_;
	std::vector<std::list<tml::shared_ptr<tml::test::ManagerEvent>>> run_event_cont_;
	std::vector<std::list<tml::shared_ptr<tml::test::ManagerEvent>>> add_run_event_cont_;

public:
	tml::test::ManagerFactory *factory;

private:
	void Release(void);

	void InitResourcePart(tml::shared_ptr<tml::test::ManagerResource> &);
	void InitTaskPart(tml::shared_ptr<tml::test::ManagerTask> &);
	void InitEventPart(tml::shared_ptr<tml::test::ManagerEvent> &);

protected:
	INT CreateResourceContainer(const UINT);
	void DeleteResourceContainer(void);
	INT CreateTaskContainer(const UINT);
	void DeleteTaskContainer(void);
	INT CreateEventContainer(const UINT);
	void DeleteEventContainer(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::test::ManagerDesc &);

	void Update(void);

	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	const std::list<tml::shared_ptr<tml::test::ManagerResource>> *GetResourceContainer(const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const WCHAR *, INT *dst_result = nullptr);
	void SetResourceName(tml::test::ManagerResource *, const WCHAR *);
	const std::list<tml::shared_ptr<tml::test::ManagerTask>> *GetTaskContainer(const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetTask(tml::shared_ptr<T2> &, const D &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetTask(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetTask(tml::shared_ptr<T2> &, const WCHAR *, INT *dst_result = nullptr);
	void SetTaskName(tml::test::ManagerTask *, const WCHAR *);
	void SetTaskRunFlag(tml::test::ManagerTask *, const bool);
	void RunTask(void);
	const std::list<tml::shared_ptr<tml::test::ManagerEvent>> *GetEventContainer(const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetEvent(tml::shared_ptr<T2> &, const D &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetEvent(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetEvent(tml::shared_ptr<T2> &, const WCHAR *, INT *dst_result = nullptr);
	void SetEventName(tml::test::ManagerEvent *, const WCHAR *);
	void SetEventRunFlag(tml::test::ManagerEvent *, const bool);
	void RunEvent(const UINT);
};
}
}


/**
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::test::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::test::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetResourceContainer関数
 * @param res_index (resource_index)
 * @return res_cont (resource_container)<br>
 * nullptr=失敗
 */
inline const std::list<tml::shared_ptr<tml::test::ManagerResource>> *tml::test::Manager::GetResourceContainer(const UINT res_index)
{
	if (res_index >= this->res_cont_.size()) {
		return (nullptr);
	}

	return (&this->res_cont_by_index_[res_index]);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param desc (desc)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::test::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc, INT *dst_result)
{
	dst_res.reset();
	tml::SetResult(dst_result, 0);

	const std::wstring &tmp_res_name = desc.resource_name;

	if (!tmp_res_name.empty()) {
		auto res_itr = this->res_cont_by_name_.find(tmp_res_name);

		if (res_itr != this->res_cont_by_name_.end()) {
			dst_res = std::dynamic_pointer_cast<T2>(res_itr->second);
			tml::SetResult(dst_result, (dst_res != nullptr) ? 1 : -1);

			return (dst_res);
		}
	}

	if (desc.GetManager() != this) {
		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	tml::shared_ptr<tml::test::ManagerResource> res = tml::make_shared<T>(1U);

	reinterpret_cast<T *>(res.get())->SetManager(desc.GetManager());
	reinterpret_cast<T *>(res.get())->SetDesc(&desc);
	res->res_index_ = T::RESOURCE_INDEX;
	res->res_shared_p_ = res;
	res->res_name_ = desc.resource_name;

	dst_res = std::dynamic_pointer_cast<T2>(res);

	if ((dst_res == nullptr)
	|| (reinterpret_cast<T *>(res.get())->Create() < 0)) {
		this->InitResourcePart(res);

		dst_res.reset();
		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	res->deferred_create_flg_ = desc.deferred_create_flag_;

	if (res->deferred_create_flg_) {
		res->desc_unique_p_ = tml::make_unique<D>(1U);

		(*reinterpret_cast<D *>(res->desc_unique_p_.get())) = desc;

		reinterpret_cast<T *>(res.get())->SetDesc(reinterpret_cast<D *>(res->desc_unique_p_.get()));

		this->add_deferred_create_res_cont_.push_back(res);
	}

	this->res_cont_by_index_[res->res_index_].push_back(res);

	if (!res->res_name_.empty()) {
		this->res_cont_by_name_.emplace(res->res_name_, res->res_shared_p_);
	}

	this->res_cont_.push_back(res);

	return (dst_res);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param res (resource)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::test::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const tml::shared_ptr<T> &res, INT *dst_result)
{
	dst_res = std::dynamic_pointer_cast<T2>(res);
	tml::SetResult(dst_result, (dst_res != nullptr) ? 1 : -1);

	return (dst_res);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param res_name (resource_name)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::test::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const WCHAR *res_name, INT *dst_result)
{
	dst_res.reset();
	tml::SetResult(dst_result, 0);

	if ((res_name == nullptr)
	|| (res_name[0] == 0)) {
		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	const std::wstring tmp_res_name = res_name;

	if (!tmp_res_name.empty()) {
		auto res_itr = this->res_cont_by_name_.find(tmp_res_name);

		if (res_itr != this->res_cont_by_name_.end()) {
			dst_res = std::dynamic_pointer_cast<T2>(res_itr->second);
			tml::SetResult(dst_result, (dst_res != nullptr) ? 1 : -1);

			return (dst_res);
		}
	}

	if (dst_res == nullptr) {
		tml::SetResult(dst_result, -1);
	}

	return (dst_res);
}


/**
 * @brief GetTaskContainer関数
 * @param task_index (task_index)
 * @return task_cont (task_container)<br>
 * nullptr=失敗
 */
inline const std::list<tml::shared_ptr<tml::test::ManagerTask>> *tml::test::Manager::GetTaskContainer(const UINT task_index)
{
	if (task_index >= this->task_cont_.size()) {
		return (nullptr);
	}

	return (&this->task_cont_by_index_[task_index]);
}


/**
 * @brief GetTask関数
 * @param dst_task (dst_task)
 * @param desc (desc)
 * @param dst_result (dst_result)
 * @return dst_task (dst_task)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::test::Manager::GetTask(tml::shared_ptr<T2> &dst_task, const D &desc, INT *dst_result)
{
	dst_task.reset();
	tml::SetResult(dst_result, 0);

	const std::wstring &tmp_task_name = desc.task_name;

	if (!tmp_task_name.empty()) {
		auto task_itr = this->task_cont_by_name_.find(tmp_task_name);

		if (task_itr != this->task_cont_by_name_.end()) {
			dst_task = std::dynamic_pointer_cast<T2>(task_itr->second);
			tml::SetResult(dst_result, (dst_task != nullptr) ? 1 : -1);

			return (dst_task);
		}
	}

	if (desc.GetManager() != this) {
		tml::SetResult(dst_result, -1);

		return (dst_task);
	}

	tml::shared_ptr<tml::test::ManagerTask> task = tml::make_shared<T>(1U);

	reinterpret_cast<T *>(task.get())->SetManager(desc.GetManager());
	task->task_index_ = T::TASK_INDEX;
	task->task_shared_p_ = task;
	task->task_name_ = desc.task_name;

	dst_task = std::dynamic_pointer_cast<T2>(task);

	if ((dst_task == nullptr)
	|| (reinterpret_cast<T *>(task.get())->Create(desc) < 0)) {
		this->InitTaskPart(task);

		dst_task.reset();
		tml::SetResult(dst_result, -1);

		return (dst_task);
	}

	task->run_flg_ = desc.run_flag;

	if (task->run_flg_) {
		this->add_run_task_cont_.push_back(task);
	}

	this->task_cont_by_index_[task->task_index_].push_back(task);

	if (!task->task_name_.empty()) {
		this->task_cont_by_name_.emplace(task->task_name_, task->task_shared_p_);
	}

	this->task_cont_.push_back(task);

	return (dst_task);
}


/**
 * @brief GetTask関数
 * @param dst_task (dst_task)
 * @param task (task)
 * @param dst_result (dst_result)
 * @return dst_task (dst_task)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::test::Manager::GetTask(tml::shared_ptr<T2> &dst_task, const tml::shared_ptr<T> &task, INT *dst_result)
{
	dst_task = std::dynamic_pointer_cast<T2>(task);
	tml::SetResult(dst_result, (dst_task != nullptr) ? 1 : -1);

	return (dst_task);
}


/**
 * @brief GetTask関数
 * @param dst_task (dst_task)
 * @param task_name (task_name)
 * @param dst_result (dst_result)
 * @return dst_task (dst_task)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::test::Manager::GetTask(tml::shared_ptr<T2> &dst_task, const WCHAR *task_name, INT *dst_result)
{
	dst_task.reset();
	tml::SetResult(dst_result, 0);

	if ((task_name == nullptr)
	|| (task_name[0] == 0)) {
		tml::SetResult(dst_result, -1);

		return (dst_task);
	}

	const std::wstring tmp_task_name = task_name;

	if (!tmp_task_name.empty()) {
		auto task_itr = this->task_cont_by_name_.find(tmp_task_name);

		if (task_itr != this->task_cont_by_name_.end()) {
			dst_task = std::dynamic_pointer_cast<T2>(task_itr->second);
			tml::SetResult(dst_result, (dst_task != nullptr) ? 1 : -1);

			return (dst_task);
		}
	}

	if (dst_task == nullptr) {
		tml::SetResult(dst_result, -1);
	}

	return (dst_task);
}


/**
 * @brief GetEventContainer関数
 * @param event_index (event_index)
 * @return event_cont (event_container)<br>
 * nullptr=失敗
 */
inline const std::list<tml::shared_ptr<tml::test::ManagerEvent>> *tml::test::Manager::GetEventContainer(const UINT event_index)
{
	if (event_index >= this->event_cont_.size()) {
		return (nullptr);
	}

	return (&this->event_cont_by_index_[event_index]);
}


/**
 * @brief GetEvent関数
 * @param dst_event (dst_event)
 * @param desc (desc)
 * @param dst_result (dst_result)
 * @return dst_event (dst_event)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::test::Manager::GetEvent(tml::shared_ptr<T2> &dst_event, const D &desc, INT *dst_result)
{
	dst_event.reset();
	tml::SetResult(dst_result, 0);

	const std::wstring &tmp_event_name = desc.event_name;

	if (!tmp_event_name.empty()) {
		auto event_itr = this->event_cont_by_name_.find(tmp_event_name);

		if (event_itr != this->event_cont_by_name_.end()) {
			dst_event = std::dynamic_pointer_cast<T2>(event_itr->second);
			tml::SetResult(dst_result, (dst_event != nullptr) ? 1 : -1);

			return (dst_event);
		}
	}

	if (desc.GetManager() != this) {
		tml::SetResult(dst_result, -1);

		return (dst_event);
	}

	tml::shared_ptr<tml::test::ManagerEvent> event = tml::make_shared<T>(1U);

	reinterpret_cast<T *>(event.get())->SetManager(desc.GetManager());
	event->event_index_ = T::EVENT_INDEX;
	event->event_shared_p_ = event;
	event->event_name_ = desc.event_name;

	dst_event = std::dynamic_pointer_cast<T2>(event);

	if ((dst_event == nullptr)
	|| (reinterpret_cast<T *>(event.get())->Create(desc) < 0)) {
		this->InitEventPart(event);

		dst_event.reset();
		tml::SetResult(dst_result, -1);

		return (dst_event);
	}

	event->run_flg_ = desc.run_flag;

	if (event->run_flg_) {
		this->add_run_event_cont_[event->event_index_].push_back(event);
	}

	this->event_cont_by_index_[event->event_index_].push_back(event);

	if (!event->event_name_.empty()) {
		this->event_cont_by_name_.emplace(event->event_name_, event->event_shared_p_);
	}

	this->event_cont_.push_back(event);

	return (dst_event);
}


/**
 * @brief GetEvent関数
 * @param dst_event (dst_event)
 * @param event (event)
 * @param dst_result (dst_result)
 * @return dst_event (dst_event)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::test::Manager::GetEvent(tml::shared_ptr<T2> &dst_event, const tml::shared_ptr<T> &event, INT *dst_result)
{
	dst_event = std::dynamic_pointer_cast<T2>(event);
	tml::SetResult(dst_result, (dst_event != nullptr) ? 1 : -1);

	return (dst_event);
}


/**
 * @brief GetEvent関数
 * @param dst_event (dst_event)
 * @param event_name (event_name)
 * @param dst_result (dst_result)
 * @return dst_event (dst_event)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::test::Manager::GetEvent(tml::shared_ptr<T2> &dst_event, const WCHAR *event_name, INT *dst_result)
{
	dst_event.reset();
	tml::SetResult(dst_result, 0);

	if ((event_name == nullptr)
	|| (event_name[0] == 0)) {
		tml::SetResult(dst_result, -1);

		return (dst_event);
	}

	const std::wstring tmp_event_name = event_name;

	if (!tmp_event_name.empty()) {
		auto event_itr = this->event_cont_by_name_.find(tmp_event_name);

		if (event_itr != this->event_cont_by_name_.end()) {
			dst_event = std::dynamic_pointer_cast<T2>(event_itr->second);
			tml::SetResult(dst_result, (dst_event != nullptr) ? 1 : -1);

			return (dst_event);
		}
	}

	if (dst_event == nullptr) {
		tml::SetResult(dst_result, -1);
	}

	return (dst_event);
}
