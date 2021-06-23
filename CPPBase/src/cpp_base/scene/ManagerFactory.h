/**
 * @file
 * @brief ManagerFactoryヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace scene {
/**
 * @brief ManagerFactoryクラス
 */
class ManagerFactory
{
public: ManagerFactory(const cpp_base::scene::ManagerFactory &) = delete;
public: cpp_base::scene::ManagerFactory &operator =(const cpp_base::scene::ManagerFactory &) = delete;

private:
	cpp_base::scene::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(cpp_base::scene::Manager *);

	cpp_base::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
