/**
 * @file
 * @brief ManagerFactory�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../manager/ManagerResourceFactory.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerFactory�N���X
 */
class ManagerFactory
{
public: ManagerFactory(const tml::sound::ManagerFactory &) = delete;
public: tml::sound::ManagerFactory &operator =(const tml::sound::ManagerFactory &) = delete;

private:
	tml::sound::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(tml::sound::Manager *);

	tml::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
