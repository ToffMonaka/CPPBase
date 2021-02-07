/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerCommon.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:

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
	std::array<std::list<tml::shared_ptr<tml::sound::Resource>>, tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT> res_cont_ary_;

public:
	tml::sound::ManagerCommon common;

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerDesc &);

	void Update(void);
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

	UINT res_type = static_cast<UINT>(res->GetResourceType());

	if (res_type >= tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT) {
		return (dst_res);
	}

	this->res_cont_ary_[res_type].push_back(res);

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

	UINT res_type = static_cast<UINT>(res->GetResourceType());

	if (res_type >= tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT) {
		return;
	}

	if (res.use_count() <= 2L) {
		this->res_cont_ary_[res_type].remove(res);
	}

	res.reset();

	return;
}
