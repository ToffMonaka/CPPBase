/**
 * @file
 * @brief ManagerResourceFactoryヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <functional>
#include <unordered_map>
#include "ManagerResource.h"


namespace tml {
/**
 * @brief ManagerResourceFactoryクラス
 */
class ManagerResourceFactory
{
public: ManagerResourceFactory(const tml::ManagerResourceFactory &) = delete;
public: tml::ManagerResourceFactory &operator =(const tml::ManagerResourceFactory &) = delete;

private:
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<tml::ManagerResource>(const tml::INIFileReadDesc &, INT *)>> func_cont_;

private:
	void Release(void);

public:
	ManagerResourceFactory();
	virtual ~ManagerResourceFactory();

	virtual void Init(void);

	template <typename T>
	tml::shared_ptr<T> &Get(tml::shared_ptr<T> &, const WCHAR *, const tml::INIFileReadDesc &, INT *dst_result = nullptr);
	INT AddFunction(const WCHAR *, std::function<tml::shared_ptr<tml::ManagerResource>(const tml::INIFileReadDesc &, INT *)>);
	void RemoveFunction(const WCHAR *);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerResourceFactory::Release(void)
{
	return;
}


/**
 * @brief Get関数
 * @param dst_res (dst_resource)
 * @param class_name (class_name)
 * @param file_read_desc (file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::ManagerResourceFactory::Get(tml::shared_ptr<T> &dst_res, const WCHAR *class_name, const tml::INIFileReadDesc &file_read_desc, INT *dst_result)
{
	dst_res.reset();
	tml::SetResult(dst_result, 0);

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	auto func_itr = this->func_cont_.find(class_name);

	if (func_itr == this->func_cont_.end()) {
		tml::SetResult(dst_result, -1);

		return (dst_res);
	}

	tml::shared_ptr<tml::ManagerResource> res = func_itr->second(file_read_desc, dst_result);

	dst_res = std::dynamic_pointer_cast<T>(res);

	if (dst_res == nullptr) {
		tml::SetResult(dst_result, -1);
	}

	return (dst_res);
}
