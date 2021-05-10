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
inline void cpp_base::graphic::ManagerDesc::Release(void)
{
	tml::graphic::ManagerDesc::Release();

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
	cpp_base::graphic::ManagerCommon common2_;

protected:
	void Release(void);

	INT CreateCommon2(void);
	void DeleteCommon2(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::graphic::ManagerDesc &);

	cpp_base::graphic::ManagerCommon &GetCommon2(void);
};
}
}


/**
 * @brief GetCommon2関数
 * @return common2 (common2)
 */
inline cpp_base::graphic::ManagerCommon &cpp_base::graphic::Manager::GetCommon2(void)
{
	return (this->common2_);
}
