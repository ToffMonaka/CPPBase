/**
 * @file
 * @brief ManagerResourceFactoryヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <functional>
#include <map>
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

public:
	std::map<std::wstring, std::wstring> value_container;

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
	const std::wstring *GetValue(const WCHAR *) const;
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
 * @param conf_file_read_desc (config_file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_res (dst_resource)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::ManagerResourceFactory::Get(tml::shared_ptr<T> &dst_res, const WCHAR *class_name, const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result)
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

	tml::shared_ptr<tml::ManagerResource> res = func_itr->second(conf_file_read_desc, dst_result);

	dst_res = std::dynamic_pointer_cast<T>(res);

	if (dst_res == nullptr) {
		tml::SetResult(dst_result, -1);
	}

	return (dst_res);
}


/**
 * @brief GetValue関数
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline const std::wstring *tml::ManagerResourceFactory::GetValue(const WCHAR *val_name) const
{
	auto res_factory_val_itr = this->value_container.find(val_name);

	if (res_factory_val_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&res_factory_val_itr->second);
}
