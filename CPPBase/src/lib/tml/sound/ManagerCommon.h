/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace sound {
}
}


namespace tml {
namespace sound {
/**
 * @brief ManagerCommonクラス
 */
class ManagerCommon
{
public: ManagerCommon(const tml::sound::ManagerCommon &) = delete;
public: tml::sound::ManagerCommon &operator =(const tml::sound::ManagerCommon &) = delete;

public:

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::sound::Manager *);
};
}
}
