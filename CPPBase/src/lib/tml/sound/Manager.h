/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "ManagerCommon.h"


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
