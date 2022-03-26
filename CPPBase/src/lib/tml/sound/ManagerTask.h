/**
 * @file
 * @brief ManagerTask�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../manager/ManagerTask.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerTaskDesc�N���X
 */
class ManagerTaskDesc : public tml::ManagerTaskDesc
{
private:
	tml::sound::Manager *mgr_;

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

	tml::sound::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerTaskDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerTaskDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace sound {
/**
 * @brief ManagerTask�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerTask : public tml::ManagerTask
{
public: ManagerTask(const tml::sound::ManagerTask &) = delete;
public: tml::sound::ManagerTask &operator =(const tml::sound::ManagerTask &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::sound::Manager *mgr_;

private:
	void Release(void);

protected:
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTask();
	virtual ~ManagerTask();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerTaskDesc &);

	tml::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerTask::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerTask::GetManager(void)
{
	return (this->mgr_);
}
