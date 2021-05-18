/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace input {
/**
 * @brief ManagerCommon�N���X
 */
class ManagerCommon
{
public: ManagerCommon(const cpp_base::input::ManagerCommon &) = delete;
public: cpp_base::input::ManagerCommon &operator =(const cpp_base::input::ManagerCommon &) = delete;

private:
	cpp_base::input::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(cpp_base::input::Manager *);

	cpp_base::input::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::input::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::input::Manager *cpp_base::input::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
