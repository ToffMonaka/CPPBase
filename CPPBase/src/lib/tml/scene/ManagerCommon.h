/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../memory/MemoryUtil.h"


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

	tml::scene::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerCommon::GetManager(void) const
{
	return (this->mgr_);
}
