/**
 * @file
 * @brief ManagerFactoryヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <map>
#include <unordered_map>
#include <functional>
#include "ManagerResource.h"
#include "ManagerTask.h"
#include "ManagerEvent.h"


namespace tml {
/**
 * @brief ManagerFactoryDescクラス
 */
class ManagerFactoryDesc
{
public:

private:
	void Release(void);

public:
	ManagerFactoryDesc();
	virtual ~ManagerFactoryDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerFactoryDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief ManagerFactoryクラス
 */
class ManagerFactory
{
public: ManagerFactory(const tml::ManagerFactory &) = delete;
public: tml::ManagerFactory &operator =(const tml::ManagerFactory &) = delete;

private:
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<tml::ManagerResource>(const tml::INIFileReadDesc &, INT *)>> res_func_cont_;
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<tml::ManagerTask>(const tml::INIFileReadDesc &, INT *)>> task_func_cont_;
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<tml::ManagerEvent>(const tml::INIFileReadDesc &, INT *)>> event_func_cont_;

public:
	std::map<std::wstring, std::wstring> value_container;

private:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(const tml::ManagerFactoryDesc &);

	template <typename T>
	tml::shared_ptr<T> &GetResource(tml::shared_ptr<T> &, const WCHAR *, const tml::INIFileReadDesc &, INT *dst_result = nullptr);
	INT AddResourceFunction(const WCHAR *, std::function<tml::shared_ptr<tml::ManagerResource>(const tml::INIFileReadDesc &, INT *)>);
	void RemoveResourceFunction(const WCHAR *);

	template <typename T>
	tml::shared_ptr<T> &GetTask(tml::shared_ptr<T> &, const WCHAR *, const tml::INIFileReadDesc &, INT *dst_result = nullptr);
	INT AddTaskFunction(const WCHAR *, std::function<tml::shared_ptr<tml::ManagerTask>(const tml::INIFileReadDesc &, INT *)>);
	void RemoveTaskFunction(const WCHAR *);

	template <typename T>
	tml::shared_ptr<T> &GetEvent(tml::shared_ptr<T> &, const WCHAR *, const tml::INIFileReadDesc &, INT *dst_result = nullptr);
	INT AddEventFunction(const WCHAR *, std::function<tml::shared_ptr<tml::ManagerEvent>(const tml::INIFileReadDesc &, INT *)>);
	void RemoveEventFunction(const WCHAR *);

	const std::wstring *GetValue(const WCHAR *) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param class_name (class_name)
 * @param conf_file_read_desc (config_file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::ManagerFactory::GetResource(tml::shared_ptr<T> &dst_res, const WCHAR *class_name, const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result)
{
	dst_res.reset();
	tml::SetResult(dst_result, 0);

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	auto res_func_itr = this->res_func_cont_.find(class_name);

	if (res_func_itr != this->res_func_cont_.end()) {
		auto res_func = res_func_itr->second;

		if (res_func != nullptr) {
			auto res = res_func(conf_file_read_desc, dst_result);

			dst_res = std::dynamic_pointer_cast<T>(res);

			if (dst_res != nullptr) {
				return (dst_res);
			}
		}
	}

	tml::SetResult(dst_result, -1);

	return (dst_res);
}


/**
 * @brief GetTask関数
 * @param dst_task (dst_task)
 * @param class_name (class_name)
 * @param conf_file_read_desc (config_file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_task (dst_task)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::ManagerFactory::GetTask(tml::shared_ptr<T> &dst_task, const WCHAR *class_name, const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result)
{
	dst_task.reset();
	tml::SetResult(dst_result, 0);

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		tml::SetResult(dst_result, -1);

		return (dst_task);
	}

	auto task_func_itr = this->task_func_cont_.find(class_name);

	if (task_func_itr != this->task_func_cont_.end()) {
		auto task_func = task_func_itr->second;

		if (task_func != nullptr) {
			auto task = task_func(conf_file_read_desc, dst_result);

			dst_task = std::dynamic_pointer_cast<T>(task);

			if (dst_task != nullptr) {
				return (dst_task);
			}
		}
	}

	tml::SetResult(dst_result, -1);

	return (dst_task);
}


/**
 * @brief GetEvent関数
 * @param dst_event (dst_event)
 * @param class_name (class_name)
 * @param conf_file_read_desc (config_file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_event (dst_event)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::ManagerFactory::GetEvent(tml::shared_ptr<T> &dst_event, const WCHAR *class_name, const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result)
{
	dst_event.reset();
	tml::SetResult(dst_result, 0);

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		tml::SetResult(dst_result, -1);

		return (dst_event);
	}

	auto event_func_itr = this->event_func_cont_.find(class_name);

	if (event_func_itr != this->event_func_cont_.end()) {
		auto event_func = event_func_itr->second;

		if (event_func != nullptr) {
			auto event = event_func(conf_file_read_desc, dst_result);

			dst_event = std::dynamic_pointer_cast<T>(event);

			if (dst_event != nullptr) {
				return (dst_event);
			}
		}
	}

	tml::SetResult(dst_result, -1);

	return (dst_event);
}


/**
 * @brief GetValue関数
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline const std::wstring *tml::ManagerFactory::GetValue(const WCHAR *val_name) const
{
	auto val_itr = this->value_container.find(val_name);

	if (val_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}
