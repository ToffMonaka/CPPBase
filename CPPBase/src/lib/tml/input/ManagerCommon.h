/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../memory/MemoryUtil.h"


namespace tml {
namespace input {
/**
 * @brief ManagerCommon�N���X
 */
class ManagerCommon
{
public: ManagerCommon(const tml::input::ManagerCommon &) = delete;
public: tml::input::ManagerCommon &operator =(const tml::input::ManagerCommon &) = delete;

private:
	tml::input::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::input::Manager *);

	tml::input::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
