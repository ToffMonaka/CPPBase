/**
 * @file
 * @brief ManagerFactory�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace sound {
/**
 * @brief ManagerFactory�N���X
 */
class ManagerFactory
{
public: ManagerFactory(const cpp_base::sound::ManagerFactory &) = delete;
public: cpp_base::sound::ManagerFactory &operator =(const cpp_base::sound::ManagerFactory &) = delete;

private:
	cpp_base::sound::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(cpp_base::sound::Manager *);

	cpp_base::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::sound::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::sound::Manager *cpp_base::sound::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
