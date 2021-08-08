/**
 * @file
 * @brief ManagerFactory�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../manager/ManagerResourceFactory.h"


namespace tml {
namespace input {
/**
 * @brief ManagerFactory�N���X
 */
class ManagerFactory
{
public: ManagerFactory(const tml::input::ManagerFactory &) = delete;
public: tml::input::ManagerFactory &operator =(const tml::input::ManagerFactory &) = delete;

private:
	tml::input::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(tml::input::Manager *);

	tml::input::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
