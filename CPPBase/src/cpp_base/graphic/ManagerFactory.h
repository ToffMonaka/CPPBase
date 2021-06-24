/**
 * @file
 * @brief ManagerFactory�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace graphic {
/**
 * @brief ManagerFactory�N���X
 */
class ManagerFactory
{
public: ManagerFactory(const cpp_base::graphic::ManagerFactory &) = delete;
public: cpp_base::graphic::ManagerFactory &operator =(const cpp_base::graphic::ManagerFactory &) = delete;

private:
	cpp_base::graphic::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(cpp_base::graphic::Manager *);

	cpp_base::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::graphic::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::graphic::Manager *cpp_base::graphic::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
