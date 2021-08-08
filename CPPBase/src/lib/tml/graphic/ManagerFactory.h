/**
 * @file
 * @brief ManagerFactory�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../manager/ManagerResourceFactory.h"


namespace tml {
namespace graphic {
/**
 * @brief ManagerFactory�N���X
 */
class ManagerFactory
{
public: ManagerFactory(const tml::graphic::ManagerFactory &) = delete;
public: tml::graphic::ManagerFactory &operator =(const tml::graphic::ManagerFactory &) = delete;

private:
	tml::graphic::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
