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

private:
	tml::sound::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::sound::Manager *);

	tml::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
