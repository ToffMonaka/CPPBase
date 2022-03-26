/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/graphic/Manager.h"
#include "ManagerCommon.h"


namespace cpp_base {
namespace graphic {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::graphic::ManagerDesc
{
public:

private:
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
inline void cpp_base::graphic::ManagerDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace graphic {
/**
 * @brief Managerクラス
 */
class Manager : public tml::graphic::Manager
{
public: Manager(const cpp_base::graphic::Manager &) = delete;
public: cpp_base::graphic::Manager &operator =(const cpp_base::graphic::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	cpp_base::graphic::ManagerCommon common2;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::graphic::ManagerDesc &);
};
}
}
