/**
 * @file
 * @brief ManagerFactoryヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/manager/ManagerFactory.h"


namespace cpp_base {
/**
 * @brief ManagerFactoryDescクラス
 */
class ManagerFactoryDesc : public tml::ManagerFactoryDesc
{
public:

private:
	void Release(void);

public:
	ManagerFactoryDesc();
	virtual ~ManagerFactoryDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void cpp_base::ManagerFactoryDesc::Release(void)
{
	return;
}


namespace cpp_base {
/**
 * @brief ManagerFactoryクラス
 */
class ManagerFactory : public tml::ManagerFactory
{
public: ManagerFactory(const cpp_base::ManagerFactory &) = delete;
public: cpp_base::ManagerFactory &operator =(const cpp_base::ManagerFactory &) = delete;

private:

private:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(const cpp_base::ManagerFactoryDesc &);
};
}


/**
 * @brief Release関数
 */
inline void cpp_base::ManagerFactory::Release(void)
{
	return;
}
