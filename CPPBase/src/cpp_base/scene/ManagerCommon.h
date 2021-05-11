/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace scene {
/**
 * @brief ManagerCommonクラス
 */
class ManagerCommon
{
public: ManagerCommon(const cpp_base::scene::ManagerCommon &) = delete;
public: cpp_base::scene::ManagerCommon &operator =(const cpp_base::scene::ManagerCommon &) = delete;

private:
	cpp_base::scene::Manager *mgr_;

public:
	tml::TIME_REAL log_update_time;
	tml::shared_ptr<tml::graphic::Object2DModel> log_model;
	tml::shared_ptr<tml::graphic::Font> log_font;

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(cpp_base::scene::Manager *);

	cpp_base::scene::Manager *GetManager(void);

	void UpdateLog(const tml::TIME_REAL &);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
