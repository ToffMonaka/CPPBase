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
	std::vector<UINT> resource_count_container;
	std::vector<UINT> task_count_container;
	std::vector<UINT> event_count_container;

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

public:
	tml::test::ManagerFactory *factory;

private:
	void Release(void);

	void GetResourceInitPart(tml::shared_ptr<tml::test::ManagerResource> &);

protected:
	INT CreateResourceContainer(const std::vector<UINT> &);
	void DeleteResourceContainer(void);

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
	UINT res_index = T::RESOURCE_INDEX;

	res->res_index_ = res_index;
	res->res_shared_p_ = res;
	res->res_name_ = desc.resource_name;

	if (reinterpret_cast<T *>(res.get())->Create(desc) < 0) {
		this->GetResourceInitPart(res);

		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	if (desc.deferred_create_flag) {
		tml::unique_ptr<tml::test::ManagerResourceDesc> deferred_create_desc = tml::make_unique<D>(1U);

		(*reinterpret_cast<D *>(deferred_create_desc.get())) = desc;

		res->deferred_create_desc_unique_p_ = std::move(deferred_create_desc);
		res->deferred_create_desc_ = res->deferred_create_desc_unique_p_.get();

		this->deferred_create_res_cont_.push_back(res);
	} else {
		res->deferred_create_desc_unique_p_.reset();
		res->deferred_create_desc_ = &desc;

		if ((res->CreateDeferred() < 0)
		|| (res->IsDeferredCreating())) {
			this->GetResourceInitPart(res);

			tml::SetResult(dst_result, -1);

			return (dst_res);
		}
	}

	this->res_cont_by_index_[res->res_index_].push_back(res);

	if (!res->res_name_.empty()) {
		this->res_cont_by_name_.emplace(res->res_name_, res->res_shared_p_);
	}

	this->res_cont_.push_back(res);

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
