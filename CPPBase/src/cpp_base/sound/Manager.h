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
	void InitResourceCount(void);
	void InitEventCount(void);

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
inline void cpp_base::sound::ManagerDesc::Release(void)
{
	tml::sound::ManagerDesc::Release();

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
	cpp_base::sound::ManagerCommon common2_;

protected:
	void Release(void);

	INT CreateCommon2(void);
	void DeleteCommon2(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::sound::ManagerDesc &);

	cpp_base::sound::ManagerCommon &GetCommon2(void);
};
}
}


/**
 * @brief GetCommon2関数
 * @return common2 (common2)
 */
inline cpp_base::sound::ManagerCommon &cpp_base::sound::Manager::GetCommon2(void)
{
	return (this->common2_);
}
