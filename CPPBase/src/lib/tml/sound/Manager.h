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

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}
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

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(tml::sound::ManagerDesc &);

	void Update(void);
	template <typename T, typename D>
	tml::shared_ptr<T> GetResource(D &);
	template <typename T>
	tml::shared_ptr<T> &GetResource(tml::shared_ptr<T> &);
	template <typename T>
	void ReleaseResource(tml::shared_ptr<T> &);
};
}
}


/**
 * @brief GetResource関数
 * @param desc (desc)
 * @return res (resource)
 */
template <typename T, typename D>
inline tml::shared_ptr<T> tml::sound::Manager::GetResource(D &desc)
{
	desc.manager = this;

	auto res = tml::make_shared<T>(1U);

	if (res->Create(desc) < 0) {
		res.reset();

		return (res);
	}

	UINT res_type = static_cast<UINT>(res->GetResourceType());

	if (res_type >= tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT) {
		res.reset();

		return (res);
	}

	this->res_cont_ary_[res_type].push_back(res);

	return (res);
}


/**
 * @brief GetResource関数
 * @param res (resource)
 * @return res (resource)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::sound::Manager::GetResource(tml::shared_ptr<T> &res)
{
	return (res);
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
