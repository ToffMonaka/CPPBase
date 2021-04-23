/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerCommon�N���X
 */
class ManagerCommon
{
public: ManagerCommon(const tml::scene::ManagerCommon &) = delete;
public: tml::scene::ManagerCommon &operator =(const tml::scene::ManagerCommon &) = delete;

private:
	tml::scene::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::scene::Manager *);

	tml::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
