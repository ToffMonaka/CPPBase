/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "ManagerCommon.h"
#include "Event.h"


namespace tml {
namespace input {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:
	HWND window_handle;
	HDC window_device_context_handle;

protected:
	void Release(void);

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
inline void tml::input::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief Managerクラス
 */
class Manager
{
public: Manager(const tml::input::Manager &) = delete;
public: tml::input::Manager &operator =(const tml::input::Manager &) = delete;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	tml::input::ManagerCommon common_;
	std::array<std::list<tml::shared_ptr<tml::input::Resource>>, tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT> res_cont_ary_;
	UINT event_index_;
	std::array<UINT, 2U> event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::input::Event>>, 2U> event_cont_ary_;
	std::array<UINT, tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT> stock_event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::input::Event>>, tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT> stock_event_cont_ary_;

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::input::ManagerDesc &);

	void Update(void);
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	tml::input::ManagerCommon &GetCommon(void);
	template <typename T1, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &);
	template <typename T1, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, tml::shared_ptr<T1> &);
	template <typename T>
	void ReleaseResource(tml::shared_ptr<T> &);
	template <typename T, typename D>
	INT AddEvent(const D &);
};
}
}


/**
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::input::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::input::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetCommon関数
 * @return common (common)
 */
inline tml::input::ManagerCommon &tml::input::Manager::GetCommon(void)
{
	return (this->common_);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param desc (desc)
 * @return dst_res (dst_resource)
 */
template <typename T1, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::input::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc)
{
	this->ReleaseResource(dst_res);

	if (desc.manager != this) {
		return (dst_res);
	}

	tml::shared_ptr<T1> res = tml::make_shared<T1>(1U);

	if (res->Create(desc) < 0) {
		return (dst_res);
	}

	auto res_index = static_cast<UINT>(res->GetResourceType());

	this->res_cont_ary_[res_index].push_back(res);

	dst_res = res;

	return (dst_res);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param res (resource)
 * @return dst_res (dst_resource)
 */
template <typename T1, typename T2>
inline tml::shared_ptr<T2> &tml::input::Manager::GetResource(tml::shared_ptr<T2> &dst_res, tml::shared_ptr<T1> &res)
{
	if (dst_res == res) {
		return (dst_res);
	}

	this->ReleaseResource(dst_res);

	dst_res = res;

	return (dst_res);
}


/**
 * @brief ReleaseResource関数
 * @param res (resource)
 */
template <typename T>
inline void tml::input::Manager::ReleaseResource(tml::shared_ptr<T> &res)
{
	if (res == nullptr) {
		return;
	}

	auto res_index = static_cast<UINT>(res->GetResourceType());

	if (res.use_count() <= 2L) {
		this->res_cont_ary_[res_index].remove(res);
	}

	res.reset();

	return;
}


/**
 * @brief AddEvent関数
 * @param dat (data)
 * @return res (result)<br>
 * 0未満=失敗
 */
template <typename T, typename D>
inline INT tml::input::Manager::AddEvent(const D &dat)
{
	tml::unique_ptr<tml::input::Event> event;

	auto event_index = static_cast<UINT>(T::EVENT_TYPE);

	if (this->stock_event_cnt_ary_[event_index] > 0U) {
		--this->stock_event_cnt_ary_[event_index];

		auto &stock_event_cont = this->stock_event_cont_ary_[event_index];

		event = std::move(stock_event_cont[this->stock_event_cnt_ary_[event_index]]);
	} else {
		event = tml::make_unique<T>(1U);
	}

	reinterpret_cast<T *>(event.get())->SetData(dat);

	auto &event_cont = this->event_cont_ary_[this->event_index_];

	if (this->event_cnt_ary_[this->event_index_] >= event_cont.size()) {
		event_cont.resize(this->event_cnt_ary_[this->event_index_] + 128U);
	}

	event_cont[this->event_cnt_ary_[this->event_index_]] = std::move(event);

	++this->event_cnt_ary_[this->event_index_];

	return (0);
}
