/**
 * @file
 * @brief ManagerResourceFactoryヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <functional>
#include <unordered_map>
#include "../file/INIFile.h"
#include "../file/XMLFile.h"


namespace tml {
/**
 * @brief ManagerResourceFactoryクラス
 */
template <typename T, typename D>
class ManagerResourceFactory
{
public: ManagerResourceFactory(const tml::ManagerResourceFactory<T, D> &) = delete;
public: tml::ManagerResourceFactory<T, D> &operator =(const tml::ManagerResourceFactory<T, D> &) = delete;

private:
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<T>(const D &)>> func_cont_;

protected:
	void Release(void);

public:
	ManagerResourceFactory();
	virtual ~ManagerResourceFactory();

	virtual void Init(void);

	template <typename T2>
	tml::shared_ptr<T2> &Get(tml::shared_ptr<T2> &, const WCHAR *, const D &);
	INT AddFunction(const WCHAR *, std::function<tml::shared_ptr<T>(const D &)>);
	void RemoveFunction(const WCHAR *);
};
}


/**
 * @brief コンストラクタ
 */
template <typename T, typename D>
inline tml::ManagerResourceFactory<T, D>::ManagerResourceFactory()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <typename T, typename D>
inline tml::ManagerResourceFactory<T, D>::~ManagerResourceFactory()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <typename T, typename D>
inline void tml::ManagerResourceFactory<T, D>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <typename T, typename D>
inline void tml::ManagerResourceFactory<T, D>::Init(void)
{
	this->Release();

	this->func_cont_.clear();

	return;
}


/**
 * @brief Get関数
 * @param dst_res (dst_resource)
 * @param class_name (class_name)
 * @param read_desc (read_desc)
 * @return dst_res (dst_resource)
 */
template <typename T, typename D>
template <typename T2>
inline tml::shared_ptr<T2> &tml::ManagerResourceFactory<T, D>::Get(tml::shared_ptr<T2> &dst_res, const WCHAR *class_name, const D &read_desc)
{
	dst_res.reset();

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (dst_res);
	}

	auto func_itr = this->func_cont_.find(class_name);

	if (func_itr == this->func_cont_.end()) {
		return (dst_res);
	}

	tml::shared_ptr<T> res = func_itr->second(read_desc);

	if (std::is_same<T, T2>::value) {
		dst_res = res;
	} else {
		dst_res = std::dynamic_pointer_cast<T2>(res);
	}

	return (dst_res);
}


/**
 * @brief AddFunction関数
 * @param class_name (class_name)
 * @param func (function)
 * @return res (result)<br>
 * 0未満=失敗
 */
template <typename T, typename D>
inline INT tml::ManagerResourceFactory<T, D>::AddFunction(const WCHAR *class_name, std::function<tml::shared_ptr<T>(const D &)> func)
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
template <typename T, typename D>
inline void tml::ManagerResourceFactory<T, D>::RemoveFunction(const WCHAR *class_name)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return;
	}

	this->func_cont_.erase(class_name);

	return;
}
