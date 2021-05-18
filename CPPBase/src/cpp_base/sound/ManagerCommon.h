/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace sound {
/**
 * @brief ManagerCommon�N���X
 */
class ManagerCommon
{
public: ManagerCommon(const cpp_base::sound::ManagerCommon &) = delete;
public: cpp_base::sound::ManagerCommon &operator =(const cpp_base::sound::ManagerCommon &) = delete;

private:
	cpp_base::sound::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(cpp_base::sound::Manager *);

	cpp_base::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::sound::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::sound::Manager *cpp_base::sound::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
