/**
 * @file
 * @brief ManagerTask�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../manager/ManagerTask.h"


namespace tml {
namespace graphic {
/**
 * @brief ManagerTaskDesc�N���X
 */
class ManagerTaskDesc : public tml::ManagerTaskDesc
{
private:
	tml::graphic::Manager *mgr_;

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

	tml::graphic::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerTaskDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerTaskDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerTask�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerTask : public tml::ManagerTask
{
public: ManagerTask(const tml::graphic::ManagerTask &) = delete;
public: tml::graphic::ManagerTask &operator =(const tml::graphic::ManagerTask &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::graphic::Manager *mgr_;

private:
	void Release(void);

protected:
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTask();
	virtual ~ManagerTask();

	virtual void Init(void);
	INT Create(const tml::graphic::ManagerTaskDesc &);

	tml::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerTask::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerTask::GetManager(void)
{
	return (this->mgr_);
}
