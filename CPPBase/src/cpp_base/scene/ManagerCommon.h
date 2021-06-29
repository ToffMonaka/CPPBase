/**
 * @file
 * @brief ManagerCommon�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/memory/MemoryUtil.h"


namespace cpp_base {
namespace scene {
/**
 * @brief ManagerCommon�N���X
 */
class ManagerCommon
{
public: ManagerCommon(const cpp_base::scene::ManagerCommon &) = delete;
public: cpp_base::scene::ManagerCommon &operator =(const cpp_base::scene::ManagerCommon &) = delete;

private:
	cpp_base::scene::Manager *mgr_;

public:
	tml::shared_ptr<cpp_base::scene::DebugNode> debug_node;

protected:
	void Release(void);

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(cpp_base::scene::Manager *);

	cpp_base::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::ManagerCommon::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::ManagerCommon::GetManager(void)
{
	return (this->mgr_);
}
