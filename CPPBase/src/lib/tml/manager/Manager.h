/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <list>
#include "ManagerFactory.h"


namespace tml {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:
	HWND window_handle;
	HDC window_device_context_handle;
	tml::ManagerFactory *factory;
	UINT resource_count;
	UINT task_count;
	UINT event_count;

private:
	void Release(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief Managerクラス
 *
 * インターフェースパターン
 */
class Manager
{
public: Manager(const tml::Manager &) = delete;
public: tml::Manager &operator =(const tml::Manager &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	std::list<tml::shared_ptr<tml::ManagerResource>> res_cont_;
	std::list<tml::shared_ptr<tml::ManagerResource>>::iterator res_itr_;
	std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>> res_cont_by_type_;
	std::unordered_map<std::wstring, tml::shared_ptr<tml::ManagerResource>> res_cont_by_name_;
	std::list<tml::shared_ptr<tml::ManagerResource>> deferred_create_res_cont_;
	std::list<tml::shared_ptr<tml::ManagerResource>> add_deferred_create_res_cont_;
	std::list<tml::shared_ptr<tml::ManagerTask>> task_cont_;
	std::list<tml::shared_ptr<tml::ManagerTask>>::iterator task_itr_;
	std::vector<std::list<tml::shared_ptr<tml::ManagerTask>>> task_cont_by_type_;
	std::unordered_map<std::wstring, tml::shared_ptr<tml::ManagerTask>> task_cont_by_name_;
	std::list<tml::shared_ptr<tml::ManagerTask>> run_task_cont_;
	std::list<tml::shared_ptr<tml::ManagerTask>> add_run_task_cont_;
	std::list<tml::shared_ptr<tml::ManagerEvent>> event_cont_;
	std::list<tml::shared_ptr<tml::ManagerEvent>>::iterator event_itr_;
	std::vector<std::list<tml::shared_ptr<tml::ManagerEvent>>> event_cont_by_type_;
	std::unordered_map<std::wstring, tml::shared_ptr<tml::ManagerEvent>> event_cont_by_name_;
	std::vector<std::list<tml::shared_ptr<tml::ManagerEvent>>> run_event_cont_;
	std::list<tml::shared_ptr<tml::ManagerEvent>> add_run_event_cont_;

public:
	tml::ManagerFactory *factory;

private:
	void Release(void);

	void InitResourcePart(tml::shared_ptr<tml::ManagerResource> &);
	void InitTaskPart(tml::shared_ptr<tml::ManagerTask> &);
	void InitEventPart(tml::shared_ptr<tml::ManagerEvent> &);

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
	INT Create(const tml::ManagerDesc &);

	void Update(void);

	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	const std::list<tml::shared_ptr<tml::ManagerResource>> *GetResourceContainer(const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const WCHAR *, INT *dst_result = nullptr);
	void SetResourceName(tml::ManagerResource *, const WCHAR *);
	const std::list<tml::shared_ptr<tml::ManagerTask>> *GetTaskContainer(const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetTask(tml::shared_ptr<T2> &, const D &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetTask(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetTask(tml::shared_ptr<T2> &, const WCHAR *, INT *dst_result = nullptr);
	void SetTaskName(tml::ManagerTask *, const WCHAR *);
	void SetTaskRunFlag(tml::ManagerTask *, const bool);
	void RunTask(void);
	const std::list<tml::shared_ptr<tml::ManagerEvent>> *GetEventContainer(const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetEvent(tml::shared_ptr<T2> &, const D &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetEvent(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetEvent(tml::shared_ptr<T2> &, const WCHAR *, INT *dst_result = nullptr);
	void SetEventName(tml::ManagerEvent *, const WCHAR *);
	void SetEventRunFlag(tml::ManagerEvent *, const bool);
	void RunEvent(const UINT, const tml::ManagerEventData *);
};
}


/**
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetResourceContainer関数
 * @param res_type (resource_type)
 * @return res_cont (resource_container)<br>
 * nullptr=失敗
 */
inline const std::list<tml::shared_ptr<tml::ManagerResource>> *tml::Manager::GetResourceContainer(const UINT res_type)
{
	if (res_type >= this->res_cont_.size()) {
		return (nullptr);
	}

	return (&this->res_cont_by_type_[res_type]);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param desc (desc)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc, INT *dst_result)
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

	tml::shared_ptr<tml::ManagerResource> res = tml::make_shared<T>(1U);

	res->SetDesc(&desc);
	res->SetManager(desc.GetManager());
	res->res_type_ = T::RESOURCE_TYPE;
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

	res->deferred_create_flg_ = desc.deferred_create_flag;

	if (res->deferred_create_flg_) {
		tml::unique_ptr<tml::ManagerResourceDesc> desc_unique_p = tml::make_unique<D>(1U);

		(*reinterpret_cast<D *>(desc_unique_p.get())) = desc;

		res->desc_unique_p_ = std::move(desc_unique_p);
		res->SetDesc(reinterpret_cast<D *>(res->desc_unique_p_.get()));

		this->add_deferred_create_res_cont_.push_back(res);
	}

	this->res_cont_by_type_[res->res_type_].push_back(res);

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
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const tml::shared_ptr<T> &res, INT *dst_result)
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
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const WCHAR *res_name, INT *dst_result)
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
 * @param task_type (task_type)
 * @return task_cont (task_container)<br>
 * nullptr=失敗
 */
inline const std::list<tml::shared_ptr<tml::ManagerTask>> *tml::Manager::GetTaskContainer(const UINT task_type)
{
	if (task_type >= this->task_cont_.size()) {
		return (nullptr);
	}

	return (&this->task_cont_by_type_[task_type]);
}


/**
 * @brief GetTask関数
 * @param dst_task (dst_task)
 * @param desc (desc)
 * @param dst_result (dst_result)
 * @return dst_task (dst_task)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::Manager::GetTask(tml::shared_ptr<T2> &dst_task, const D &desc, INT *dst_result)
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

	tml::shared_ptr<tml::ManagerTask> task = tml::make_shared<T>(1U);

	task->SetManager(desc.GetManager());
	task->task_type_ = T::TASK_TYPE;
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

	this->task_cont_by_type_[task->task_type_].push_back(task);

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
inline tml::shared_ptr<T2> &tml::Manager::GetTask(tml::shared_ptr<T2> &dst_task, const tml::shared_ptr<T> &task, INT *dst_result)
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
inline tml::shared_ptr<T2> &tml::Manager::GetTask(tml::shared_ptr<T2> &dst_task, const WCHAR *task_name, INT *dst_result)
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
 * @param event_type (event_type)
 * @return event_cont (event_container)<br>
 * nullptr=失敗
 */
inline const std::list<tml::shared_ptr<tml::ManagerEvent>> *tml::Manager::GetEventContainer(const UINT event_type)
{
	if (event_type >= this->event_cont_.size()) {
		return (nullptr);
	}

	return (&this->event_cont_by_type_[event_type]);
}


/**
 * @brief GetEvent関数
 * @param dst_event (dst_event)
 * @param desc (desc)
 * @param dst_result (dst_result)
 * @return dst_event (dst_event)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::Manager::GetEvent(tml::shared_ptr<T2> &dst_event, const D &desc, INT *dst_result)
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

	tml::shared_ptr<tml::ManagerEvent> event = tml::make_shared<T>(1U);

	event->SetManager(desc.GetManager());
	event->event_type_ = T::EVENT_TYPE;
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
		this->add_run_event_cont_[event->event_type_].push_back(event);
	}

	this->event_cont_by_type_[event->event_type_].push_back(event);

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
inline tml::shared_ptr<T2> &tml::Manager::GetEvent(tml::shared_ptr<T2> &dst_event, const tml::shared_ptr<T> &event, INT *dst_result)
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
inline tml::shared_ptr<T2> &tml::Manager::GetEvent(tml::shared_ptr<T2> &dst_event, const WCHAR *event_name, INT *dst_result)
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


#if 0
#include "../constant/ConstantUtil.h"
#include <vector>
#include <list>
#include "ManagerFactory.h"


namespace tml {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:
	HWND window_handle;
	HDC window_device_context_handle;
	tml::ManagerFactory *factory;
	std::vector<UINT> resource_count_container;
	std::vector<UINT> event_count_container;

private:
	void Release(void);

protected:
	void InitResourceCount(void);
	void InitEventCount(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief Managerクラス
 *
 * インターフェースパターン
 */
class Manager
{
public: Manager(const tml::Manager &) = delete;
public: tml::Manager &operator =(const tml::Manager &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	std::vector<std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>>> res_cont_;
	std::unordered_map<std::wstring, tml::shared_ptr<tml::ManagerResource>> res_cont_by_name_;
	std::list<tml::shared_ptr<tml::ManagerResource>> check_res_cont_;
	std::list<tml::shared_ptr<tml::ManagerResource>>::iterator check_res_itr_;
	std::list<tml::shared_ptr<tml::ManagerResource>> deferred_create_res_cont_;
	tml::ManagerResource *friend_res_;
	std::array<std::vector<UINT>, 2U> event_cnt_cont_ary_;
	std::array<std::vector<std::vector<tml::unique_ptr<tml::ManagerEvent>>>, 2U> event_cont_ary_;
	UINT front_event_index_;
	UINT back_event_index_;
	std::vector<std::vector<UINT>> stock_event_cnt_cont_cont_;
	std::vector<std::vector<std::vector<tml::unique_ptr<tml::ManagerEvent>>>> stock_event_cont_cont_;
	tml::ManagerEvent *friend_event_;

public:
	tml::ManagerFactory *factory;

private:
	void GetResourceInitPart(tml::shared_ptr<tml::ManagerResource> &);
	void AddEventInitPart(tml::unique_ptr<tml::ManagerEvent> &);

private:
	void Release(void);

protected:
	INT CreateResourceContainer(const std::vector<UINT> &);
	void DeleteResourceContainer(void);
	INT CreateEventContainer(const std::vector<UINT> &);
	void DeleteEventContainer(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::ManagerDesc &);

	void Update(void);
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	const std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>> *GetResourceContainer(const UINT);
	const std::list<tml::shared_ptr<tml::ManagerResource>> *GetResourceContainer(const UINT, const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &, INT *dst_result = nullptr);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const WCHAR *, INT *dst_result = nullptr);
	void SetResourceName(tml::ManagerResource *, const WCHAR *);
	bool CheckFriendResource(const tml::ManagerResource *) const;
	UINT GetEventCount(const UINT) const;
	tml::ManagerEvent *GetEvent(const UINT, const UINT);
	tml::ManagerEvent *GetEventFast(const UINT, const UINT);
	template <typename T, typename D>
	INT AddEvent(const D &);
	bool CheckFriendEvent(const tml::ManagerEvent *) const;
};
}


/**
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetResourceContainer関数
 * @param res_main_index (resource_main_index)
 * @return res_cont (resource_container)<br>
 * nullptr=失敗
 */
inline const std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>> *tml::Manager::GetResourceContainer(const UINT res_main_index)
{
	if (res_main_index >= this->res_cont_.size()) {
		return (nullptr);
	}

	return (&this->res_cont_[res_main_index]);
}


/**
 * @brief GetResourceContainer関数
 * @param res_main_index (resource_main_index)
 * @param res_sub_index (resource_sub_index)
 * @return res_cont (resource_container)<br>
 * nullptr=失敗
 */
inline const std::list<tml::shared_ptr<tml::ManagerResource>> *tml::Manager::GetResourceContainer(const UINT res_main_index, const UINT res_sub_index)
{
	if ((res_main_index >= this->res_cont_.size())
	|| (res_sub_index >= this->res_cont_[res_main_index].size())) {
		return (nullptr);
	}

	return (&this->res_cont_[res_main_index][res_sub_index]);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param desc (desc)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc, INT *dst_result)
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

	tml::shared_ptr<tml::ManagerResource> res = tml::make_shared<T>(1U);
	UINT res_main_index = T::RESOURCE_MAIN_INDEX;
	UINT res_sub_index = T::RESOURCE_SUB_INDEX;

	this->friend_res_ = res.get();
	this->friend_res_->SetResourceMainIndex(this, res_main_index);
	this->friend_res_->SetResourceSubIndex(this, res_sub_index);
	this->friend_res_->SetResourceSharedPointer(this, res);
	this->friend_res_->SetResourceName(this, desc.resource_name.c_str());
	this->friend_res_ = nullptr;

	if (reinterpret_cast<T *>(res.get())->Create(desc) < 0) {
		this->GetResourceInitPart(res);

		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	if (desc.deferred_create_flag) {
		tml::unique_ptr<tml::ManagerResourceDesc> tmp_desc = tml::make_unique<D>(1U);

		(*reinterpret_cast<D *>(tmp_desc.get())) = desc;

		res->SetDeferredCreateDesc(tmp_desc);

		this->deferred_create_res_cont_.push_back(res);
	} else {
		res->SetDeferredCreateDesc(&desc);

		if ((res->CreateDeferred() < 0)
		|| (res->IsDeferredCreating())) {
			this->GetResourceInitPart(res);

			tml::SetResult(dst_result, -1);

			return (dst_res);
		}
	}

	this->res_cont_[res->GetResourceMainIndex()][res->GetResourceSubIndex()].push_back(res);

	if (!res->GetResourceName().empty()) {
		this->res_cont_by_name_.insert(std::make_pair(res->GetResourceName(), res));
	}

	this->check_res_cont_.push_back(res);

	dst_res = std::dynamic_pointer_cast<T2>(res);

	if (dst_res == nullptr) {
		tml::SetResult(dst_result, -1);
	}

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
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const tml::shared_ptr<T> &res, INT *dst_result)
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
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const WCHAR *res_name, INT *dst_result)
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
 * @brief GetEventCount関数
 * @return event_main_index (event_main_index)
 */
inline UINT tml::Manager::GetEventCount(const UINT event_main_index) const
{
	return (this->event_cnt_cont_ary_[this->front_event_index_][event_main_index]);
}


/**
 * @brief GetEvent関数
 * @param event_main_index (event_main_index)
 * @param index (index)
 * @return event (event)<br>
 * nullptr=失敗
 */
inline tml::ManagerEvent *tml::Manager::GetEvent(const UINT event_main_index, const UINT index)
{
	if (index >= this->event_cont_ary_[this->front_event_index_][event_main_index].size()) {
		return (nullptr);
	}

	return (this->event_cont_ary_[this->front_event_index_][event_main_index][index].get());
}


/**
 * @brief GetEventFast関数
 * @param event_main_index (event_main_index)
 * @param index (index)
 * @return event (event)<br>
 * nullptr=失敗
 */
inline tml::ManagerEvent *tml::Manager::GetEventFast(const UINT event_main_index, const UINT index)
{
	return (this->event_cont_ary_[this->front_event_index_][event_main_index][index].get());
}


/**
 * @brief AddEvent関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
template <typename T, typename D>
inline INT tml::Manager::AddEvent(const D &desc)
{
	tml::unique_ptr<tml::ManagerEvent> event;
	UINT event_main_index = T::EVENT_MAIN_INDEX;
	UINT event_sub_index = T::EVENT_SUB_INDEX;

	auto &stock_event_cnt = this->stock_event_cnt_cont_cont_[event_main_index][event_sub_index];
	auto &stock_event_cont = this->stock_event_cont_cont_[event_main_index][event_sub_index];

	if (stock_event_cnt > 0U) {
		--stock_event_cnt;

		event = std::move(stock_event_cont[stock_event_cnt]);

		reinterpret_cast<T *>(event.get())->data = desc.data;
	} else {
		if (desc.GetManager() != this) {
			return (-1);
		}

		event = tml::make_unique<T>(1U);

		this->friend_event_ = event.get();
		this->friend_event_->SetEventMainIndex(this, event_main_index);
		this->friend_event_->SetEventSubIndex(this, event_sub_index);
		this->friend_event_ = nullptr;

		if (reinterpret_cast<T *>(event.get())->Create(desc) < 0) {
			this->AddEventInitPart(event);

			return (-1);
		}
	}

	auto &event_cnt_cont = this->event_cnt_cont_ary_[this->back_event_index_];
	auto &event_cont_cont = this->event_cont_ary_[this->back_event_index_];

	auto &event_cnt = event_cnt_cont[event->GetEventMainIndex()];
	auto &event_cont = event_cont_cont[event->GetEventMainIndex()];

	if (event_cnt >= event_cont.size()) {
		event_cont.resize(event_cnt + 128U);
	}

	event_cont[event_cnt] = std::move(event);

	++event_cnt;

	return (0);
}
#endif
