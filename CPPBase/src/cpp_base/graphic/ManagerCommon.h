/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace graphic {
/**
 * @brief ManagerCommon�N���X
 */
class ManagerCommon
{
public: ManagerCommon(const cpp_base::graphic::ManagerCommon &) = delete;
public: cpp_base::graphic::ManagerCommon &operator =(const cpp_base::graphic::ManagerCommon &) = delete;

private:
	cpp_base::graphic::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(cpp_base::graphic::Manager *);

	cpp_base::graphic::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::graphic::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::graphic::Manager *cpp_base::graphic::ManagerCommon::GetManager(void) const
{
	return (this->mgr_);
}
