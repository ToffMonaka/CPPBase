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

public:

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::input::Manager *);
};
}
}
