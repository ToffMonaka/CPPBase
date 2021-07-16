/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace graphic {
/**
 * @brief ManagerCommonクラス
 */
class ManagerCommon
{
public: ManagerCommon(const cpp_base::graphic::ManagerCommon &) = delete;
public: cpp_base::graphic::ManagerCommon &operator =(const cpp_base::graphic::ManagerCommon &) = delete;

private:
	cpp_base::graphic::Manager *mgr_;

public:
	tml::shared_ptr<tml::graphic::Texture> bg_tex1;
	tml::shared_ptr<tml::graphic::Texture> empty_bg_tex1;

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(cpp_base::graphic::Manager *);

	cpp_base::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::graphic::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::graphic::Manager *cpp_base::graphic::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
