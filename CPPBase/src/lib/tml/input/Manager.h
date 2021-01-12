/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"


namespace tml {
namespace input {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace input {
/**
 * @brief Managerクラス
 */
class Manager
{
public: Manager(const tml::input::Manager &) = delete;
public: tml::input::Manager &operator =(const tml::input::Manager &) = delete;

private:

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(tml::input::ManagerDesc &);
};
}
}
