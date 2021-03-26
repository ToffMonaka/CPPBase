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
namespace sound {
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
inline void tml::sound::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
namespace sound {
/**
 * @brief Managerクラス
 */
class Manager
{
public: Manager(const tml::sound::Manager &) = delete;
public: tml::sound::Manager &operator =(const tml::sound::Manager &) = delete;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	tml::sound::ManagerCommon common_;
	std::array<std::list<tml::shared_ptr<tml::sound::Resource>>, tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT> res_cont_ary_;
	std::array<UINT, 2U> event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::sound::Event>>, 2U> event_cont_ary_;
	UINT front_event_index_;
	UINT back_event_index_;
	std::array<UINT, tml::ConstantUtil::SOUND::EVENT_TYPE_COUNT> stock_event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::sound::Event>>, tml::ConstantUtil::SOUND::EVENT_TYPE_COUNT> stock_event_cont_ary_;

	ALCdevice *device_;
	ALCcontext *device_context_;

private:
	void UpdateEvent(void);

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerDesc &);

	void Update(void);
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	tml::sound::ManagerCommon &GetCommon(void);
	template <typename T1, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &);
	template <typename T1, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, tml::shared_ptr<T1> &);
	template <typename T>
	void ReleaseResource(tml::shared_ptr<T> &);
	UINT GetEventCount(void) const;
	const tml::unique_ptr<tml::sound::Event> *GetEventArray(void) const;
	template <typename T, typename D>
	INT AddEvent(const D &);

	ALCdevice *GetDevice(void);
	ALCcontext *GetDeviceContext(void);
};
}
}


/**
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::sound::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::sound::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetCommon関数
 * @return common (common)
 */
inline tml::sound::ManagerCommon &tml::sound::Manager::GetCommon(void)
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
inline tml::shared_ptr<T2> &tml::sound::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc)
{
	this->ReleaseResource(dst_res);

	if (desc.manager != this) {
		return (dst_res);
	}

	auto res = tml::make_shared<T1>(1U);

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
inline tml::shared_ptr<T2> &tml::sound::Manager::GetResource(tml::shared_ptr<T2> &dst_res, tml::shared_ptr<T1> &res)
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
inline void tml::sound::Manager::ReleaseResource(tml::shared_ptr<T> &res)
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
 * @brief GetEventCount関数
 * @return event_cnt (event_count)
 */
inline UINT tml::sound::Manager::GetEventCount(void) const
{
	return (this->event_cnt_ary_[this->front_event_index_]);
}


/**
 * @brief GetEventArray関数
 * @return event_ary (event_array)
 */
inline const tml::unique_ptr<tml::sound::Event> *tml::sound::Manager::GetEventArray(void) const
{
	return (this->event_cont_ary_[this->front_event_index_].data());
}


/**
 * @brief AddEvent関数
 * @param dat (data)
 * @return res (result)<br>
 * 0未満=失敗
 */
template <typename T, typename D>
inline INT tml::sound::Manager::AddEvent(const D &dat)
{
	tml::unique_ptr<tml::sound::Event> event;

	auto event_index = static_cast<UINT>(T::EVENT_TYPE);
	auto &stock_event_cnt = this->stock_event_cnt_ary_[event_index];
	auto &stock_event_cont = this->stock_event_cont_ary_[event_index];

	if (stock_event_cnt > 0U) {
		--stock_event_cnt;

		event = std::move(stock_event_cont[stock_event_cnt]);
	} else {
		event = tml::make_unique<T>(1U);

		if (reinterpret_cast<T *>(event.get())->Create(this) < 0) {
			return (-1);
		}
	}

	reinterpret_cast<T *>(event.get())->SetData(dat);

	auto &back_event_cnt = this->event_cnt_ary_[this->back_event_index_];
	auto &back_event_cont = this->event_cont_ary_[this->back_event_index_];

	if (back_event_cnt >= back_event_cont.size()) {
		back_event_cont.resize(back_event_cnt + 128U);
	}

	back_event_cont[back_event_cnt] = std::move(event);

	++back_event_cnt;

	return (0);
}


/**
 * @brief GetDevice関数
 * @return device (device)
 */
inline ALCdevice *tml::sound::Manager::GetDevice(void)
{
	return (this->device_);
}


/**
 * @brief GetDeviceContext関数
 * @return device_context (device_context)
 */
inline ALCcontext *tml::sound::Manager::GetDeviceContext(void)
{
	return (this->device_context_);
}
