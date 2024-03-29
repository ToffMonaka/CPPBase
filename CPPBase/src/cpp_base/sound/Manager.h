/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/sound/Manager.h"
#include "ManagerCommon.h"


namespace cpp_base {
namespace sound {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::sound::ManagerDesc
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
inline void cpp_base::sound::ManagerDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace sound {
/**
 * @brief Managerクラス
 */
class Manager : public tml::sound::Manager
{
public: Manager(const cpp_base::sound::Manager &) = delete;
public: cpp_base::sound::Manager &operator =(const cpp_base::sound::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	cpp_base::sound::ManagerCommon common2;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::sound::ManagerDesc &);
};
}
}
