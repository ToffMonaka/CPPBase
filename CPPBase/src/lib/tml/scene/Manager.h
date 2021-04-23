/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::ManagerDesc
{
public:

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
inline void tml::scene::ManagerDesc::Release(void)
{
	tml::ManagerDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief Managerクラス
 */
class Manager : public tml::Manager
{
public: Manager(const tml::scene::Manager &) = delete;
public: tml::scene::Manager &operator =(const tml::scene::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::scene::ManagerCommon common_;

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::scene::ManagerDesc &);

	void Update(void);
	tml::scene::ManagerCommon &GetCommon(void);
};
}
}


/**
 * @brief GetCommon関数
 * @return common (common)
 */
inline tml::scene::ManagerCommon &tml::scene::Manager::GetCommon(void)
{
	return (this->common_);
}
