/**
 * @file
 * @brief ManagerTask�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../manager/ManagerTask.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerTaskDesc�N���X
 */
class ManagerTaskDesc : public tml::ManagerTaskDesc
{
private:
	tml::scene::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTaskDesc();
	virtual ~ManagerTaskDesc();

	virtual void Init(void);

	tml::scene::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerTaskDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerTaskDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace scene {
/**
 * @brief ManagerTask�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerTask : public tml::ManagerTask
{
public: ManagerTask(const tml::scene::ManagerTask &) = delete;
public: tml::scene::ManagerTask &operator =(const tml::scene::ManagerTask &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::scene::Manager *mgr_;

private:
	void Release(void);

protected:
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTask();
	virtual ~ManagerTask();

	virtual void Init(void);
	INT Create(const tml::scene::ManagerTaskDesc &);

	tml::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerTask::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerTask::GetManager(void)
{
	return (this->mgr_);
}
