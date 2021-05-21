/**
 * @file
 * @brief ManagerResourceFactoryヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <functional>
#include <unordered_map>
#include "../file/INIFile.h"


namespace tml {
/**
 * @brief ManagerResourceFactoryクラス
 */
template <typename T>
class ManagerResourceFactory
{
public: ManagerResourceFactory(const tml::ManagerResourceFactory<T> &) = delete;
public: tml::ManagerResourceFactory<T> &operator =(const tml::ManagerResourceFactory<T> &) = delete;

private:
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<T>(const tml::INIFileReadDesc &)>> func_cont_;

protected:
	void Release(void);

public:
	ManagerResourceFactory();
	virtual ~ManagerResourceFactory();

	virtual void Init(void);

	template <typename T_T>
	tml::shared_ptr<T_T> &Get(tml::shared_ptr<T_T> &, const WCHAR *, const tml::INIFileReadDesc &);
	INT AddFunction(const WCHAR *, std::function<tml::shared_ptr<T>(const tml::INIFileReadDesc &)>);
	void RemoveFunction(const WCHAR *);
};
}


/**
 * @brief コンストラクタ
 */
template <typename T>
inline tml::ManagerResourceFactory<T>::ManagerResourceFactory()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <typename T>
inline tml::ManagerResourceFactory<T>::~ManagerResourceFactory()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <typename T>
inline void tml::ManagerResourceFactory<T>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <typename T>
inline void tml::ManagerResourceFactory<T>::Init(void)
{
	this->Release();

	this->func_cont_.clear();

	return;
}


/**
 * @brief Get関数
 * @param dst_res (dst_resource)
 * @param class_name (class_name)
 * @param desc_read_desc (desc_read_desc)
 * @return dst_res (dst_resource)
 */
template <typename T>
template <typename T_T>
inline tml::shared_ptr<T_T> &tml::ManagerResourceFactory<T>::Get(tml::shared_ptr<T_T> &dst_res, const WCHAR *class_name, const tml::INIFileReadDesc &desc_read_desc)
{
	dst_res.reset();

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (dst_res);
	}

	tml::shared_ptr<T> res;

	auto func_itr = this->func_cont_.find(class_name);

	if (func_itr == this->func_cont_.end()) {
		return (dst_res);
	}

	res = func_itr->second(desc_read_desc);

	dst_res = std::dynamic_pointer_cast<T_T>(res);

	return (dst_res);
}


/**
 * @brief AddFunction関数
 * @param class_name (class_name)
 * @param func (function)
 * @return res (result)<br>
 * 0未満=失敗
 */
template <typename T>
inline INT tml::ManagerResourceFactory<T>::AddFunction(const WCHAR *class_name, std::function<tml::shared_ptr<T>(const tml::INIFileReadDesc &)> func)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (-1);
	}

	this->func_cont_[class_name] = func;

	return (0);
}


/**
 * @brief RemoveFunction関数
 * @param class_name (class_name)
 */
template <typename T>
inline void tml::ManagerResourceFactory<T>::RemoveFunction(const WCHAR *class_name)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return;
	}

	this->func_cont_.erase(class_name);

	return;
}
