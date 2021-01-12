/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"


namespace tml {
namespace sound {
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
namespace sound {
/**
 * @brief Managerクラス
 */
class Manager
{
public: Manager(const tml::sound::Manager &) = delete;
public: tml::sound::Manager &operator =(const tml::sound::Manager &) = delete;

private:

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(tml::sound::ManagerDesc &);
};
}
}
