/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace input {
}
}


namespace tml {
namespace input {
/**
 * @brief ManagerCommonクラス
 */
class ManagerCommon
{
public: ManagerCommon(const tml::input::ManagerCommon &) = delete;
public: tml::input::ManagerCommon &operator =(const tml::input::ManagerCommon &) = delete;

private:
	tml::input::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::input::Manager *);

	tml::input::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
