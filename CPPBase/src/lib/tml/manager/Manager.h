/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <list>
#include "ManagerResource.h"
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
	UINT event_count;

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
	std::vector<std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>>> res_cont_cont_;
	std::list<tml::shared_ptr<tml::ManagerResource>> check_res_cont_;
	std::list<tml::shared_ptr<tml::ManagerResource>>::iterator check_res_itr_;
	std::array<UINT, 2U> event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::ManagerEvent>>, 2U> event_cont_ary_;
	UINT front_event_index_;
	UINT back_event_index_;
	std::vector<UINT> stock_event_cnt_cont_;
	std::vector<std::vector<tml::unique_ptr<tml::ManagerEvent>>> stock_event_cont_cont_;

protected:
	void Release(void);
	INT Create(const tml::ManagerDesc &);

	INT CreateResourceContainer(const std::vector<UINT> &);
	void DeleteResourceContainer(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);

	void Update(void);
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	template <typename T1, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &);
	const std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>> *GetResourceContainer(const UINT);
	const std::list<tml::shared_ptr<tml::ManagerResource>> *GetResourceContainer(const UINT, const UINT);
	UINT GetEventCount(void) const;
	const tml::ManagerEvent *GetEvent(const UINT) const;
	const tml::ManagerEvent *GetEventFast(const UINT) const;
	template <typename T, typename D>
	INT AddEvent(const D &);
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
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param desc (desc)
 * @return dst_res (dst_resource)
 */
template <typename T1, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc)
{
	dst_res.reset();

	tml::shared_ptr<tml::ManagerResource> res = tml::make_shared<T1>(1U);

	if (reinterpret_cast<T1 *>(res.get())->Create(desc) < 0) {
		return (dst_res);
	}

	UINT res_main_index = res->GetResourceMainIndex();
	UINT res_sub_index = res->GetResourceSubIndex();

	if ((res_main_index >= this->res_cont_cont_.size())
	|| (res_sub_index >= this->res_cont_cont_[res_main_index].size())) {
		return (dst_res);
	}

	this->res_cont_cont_[res_main_index][res_sub_index].push_back(res);

	this->check_res_cont_.push_back(res);

	dst_res = std::dynamic_pointer_cast<T2>(res);

	return (dst_res);
}


/**
 * @brief GetResourceContainer関数
 * @param res_main_index (resource_main_index)
 * @return res_cont (resource_container)<br>
 * nullptr=失敗
 */
inline const std::vector<std::list<tml::shared_ptr<tml::ManagerResource>>> *tml::Manager::GetResourceContainer(const UINT res_main_index)
{
	if (res_main_index >= this->res_cont_cont_.size()) {
		return (nullptr);
	}

	return (&this->res_cont_cont_[res_main_index]);
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
	if ((res_main_index >= this->res_cont_cont_.size())
	|| (res_sub_index >= this->res_cont_cont_[res_main_index].size())) {
		return (nullptr);
	}

	return (&this->res_cont_cont_[res_main_index][res_sub_index]);
}


/**
 * @brief GetEventCount関数
 * @return event_cnt (event_count)
 */
inline UINT tml::Manager::GetEventCount(void) const
{
	return (this->event_cnt_ary_[this->front_event_index_]);
}


/**
 * @brief GetEvent関数
 * @param index (index)
 * @return event (event)<br>
 * nullptr=失敗
 */
inline const tml::ManagerEvent *tml::Manager::GetEvent(const UINT index) const
{
	if (index >= this->event_cont_ary_[this->front_event_index_].size()) {
		return (nullptr);
	}

	return (this->event_cont_ary_[this->front_event_index_][index].get());
}


/**
 * @brief GetEventFast関数
 * @param index (index)
 * @return event (event)<br>
 * nullptr=失敗
 */
inline const tml::ManagerEvent *tml::Manager::GetEventFast(const UINT index) const
{
	return (this->event_cont_ary_[this->front_event_index_][index].get());
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
	UINT event_index = static_cast<UINT>(T::EVENT_TYPE);

	auto &stock_event_cnt = this->stock_event_cnt_cont_[event_index];
	auto &stock_event_cont = this->stock_event_cont_cont_[event_index];

	if (stock_event_cnt > 0U) {
		--stock_event_cnt;

		event = std::move(stock_event_cont[stock_event_cnt]);

		reinterpret_cast<T *>(event.get())->SetData(desc.data);
	} else {
		event = tml::make_unique<T>(1U);

		if (reinterpret_cast<T *>(event.get())->Create(desc) < 0) {
			return (-1);
		}
	}

	auto &back_event_cnt = this->event_cnt_ary_[this->back_event_index_];
	auto &back_event_cont = this->event_cont_ary_[this->back_event_index_];

	if (back_event_cnt >= back_event_cont.size()) {
		back_event_cont.resize(back_event_cnt + 128U);
	}

	back_event_cont[back_event_cnt] = std::move(event);

	++back_event_cnt;

	return (0);
}
