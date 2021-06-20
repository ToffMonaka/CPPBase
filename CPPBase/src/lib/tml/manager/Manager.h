/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <list>
#include <unordered_map>
#include "ManagerResource.h"
#include "ManagerResourceFactory.h"
#include "ManagerEvent.h"


namespace tml {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:
	HWND window_handle;
	HDC window_device_context_handle;
	std::vector<UINT> resource_count_container;
	std::vector<UINT> event_count_container;

protected:
	void Release(void);

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
	tml::ManagerResource *friend_res_;
	std::array<std::vector<UINT>, 2U> event_cnt_cont_ary_;
	std::array<std::vector<std::vector<tml::unique_ptr<tml::ManagerEvent>>>, 2U> event_cont_ary_;
	UINT front_event_index_;
	UINT back_event_index_;
	std::vector<std::vector<UINT>> stock_event_cnt_cont_cont_;
	std::vector<std::vector<std::vector<tml::unique_ptr<tml::ManagerEvent>>>> stock_event_cont_cont_;
	tml::ManagerEvent *friend_event_;

protected:
	void Release(void);
	INT Create(const tml::ManagerDesc &);

	INT CreateResourceContainer(const std::vector<UINT> &);
	void DeleteResourceContainer(void);
	INT CreateEventContainer(const std::vector<UINT> &);
	void DeleteEventContainer(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);

	void Update(void);
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	const std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>> *GetResourceContainer(const UINT);
	const std::list<tml::shared_ptr<tml::ManagerResource>> *GetResourceContainer(const UINT, const UINT);
	template <typename T, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const tml::shared_ptr<T> &);
	template <typename T, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const WCHAR *);
	void SetResourceSharedPointer(tml::ManagerResource *, const tml::shared_ptr<tml::ManagerResource> &);
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
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc)
{
	dst_res.reset();

	const std::wstring &tmp_res_name = desc.resource_name;

	if (!tmp_res_name.empty()) {
		auto res_itr = this->res_cont_by_name_.find(tmp_res_name);

		if (res_itr != this->res_cont_by_name_.end()) {
			dst_res = std::dynamic_pointer_cast<T2>(res_itr->second);

			return (dst_res);
		}
	}

	if (desc.GetManager() != this) {
		return (dst_res);
	}

	tml::shared_ptr<tml::ManagerResource> res = tml::make_shared<T>(1U);

	if (reinterpret_cast<T *>(res.get())->Create(desc) < 0) {
		return (dst_res);
	}

	if ((res->GetResourceMainIndex() >= this->res_cont_.size())
	|| (res->GetResourceSubIndex() >= this->res_cont_[res->GetResourceMainIndex()].size())) {
		return (dst_res);
	}

	this->friend_res_ = res.get();
	this->friend_res_->SetResourceSharedPointer(res);
	this->friend_res_->SetResourceName(desc.resource_name.c_str());
	this->friend_res_ = nullptr;

	this->res_cont_[res->GetResourceMainIndex()][res->GetResourceSubIndex()].push_back(res);

	if (!res->GetResourceName().empty()) {
		this->res_cont_by_name_.insert(std::make_pair(res->GetResourceName(), res));
	}

	this->check_res_cont_.push_back(res);

	dst_res = std::dynamic_pointer_cast<T2>(res);

	return (dst_res);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param res (resource)
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const tml::shared_ptr<T> &res)
{
	if (std::is_same<T, T2>::value) {
		dst_res = res;
	} else {
		dst_res = std::dynamic_pointer_cast<T2>(res);
	}

	return (dst_res);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param res_name (resource_name)
 * @return dst_res (dst_resource)
 */
template <typename T, typename T2>
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const WCHAR *res_name)
{
	dst_res.reset();

	if ((res_name == nullptr)
	|| (res_name[0] == 0)) {
		return (dst_res);
	}

	std::wstring tmp_res_name = res_name;

	if (!tmp_res_name.empty()) {
		auto res_itr = this->res_cont_by_name_.find(tmp_res_name);

		if (res_itr != this->res_cont_by_name_.end()) {
			dst_res = std::dynamic_pointer_cast<T2>(res_itr->second);

			return (dst_res);
		}
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
 * @return res (result)<br>
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

		if (reinterpret_cast<T *>(event.get())->Create(desc) < 0) {
			return (-1);
		}
	}

	auto &event_cnt_cont = this->event_cnt_cont_ary_[this->back_event_index_];
	auto &event_cont_cont = this->event_cont_ary_[this->back_event_index_];

	auto &event_cnt = event_cnt_cont[event_main_index];
	auto &event_cont = event_cont_cont[event_main_index];

	if (event_cnt >= event_cont.size()) {
		event_cont.resize(event_cnt + 128U);
	}

	event_cont[event_cnt] = std::move(event);

	++event_cnt;

	return (0);
}
