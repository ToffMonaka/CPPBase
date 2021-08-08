/**
 * @file
 * @brief ManagerFactory�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace input {
/**
 * @brief ManagerFactory�N���X
 */
class ManagerFactory
{
public: ManagerFactory(const cpp_base::input::ManagerFactory &) = delete;
public: cpp_base::input::ManagerFactory &operator =(const cpp_base::input::ManagerFactory &) = delete;

private:
	cpp_base::input::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(cpp_base::input::Manager *);

	cpp_base::input::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::input::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::input::Manager *cpp_base::input::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
