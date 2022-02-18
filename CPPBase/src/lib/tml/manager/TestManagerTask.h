/**
 * @file
 * @brief ManagerTask�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../file/INIFile.h"


namespace tml {
namespace test {
class Manager;
}
}


namespace tml {
namespace test {
/**
 * @brief ManagerTaskDesc�N���X
 */
class ManagerTaskDesc
{
private:
	tml::test::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerTaskDesc();
	virtual ~ManagerTaskDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);

	tml::test::Manager *GetManager(void) const;
	void SetManager(tml::test::Manager *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::test::ManagerTaskDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerTaskDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace test {
/**
 * @brief ManagerTask�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerTask
{
friend class tml::test::Manager;

public: ManagerTask(const tml::test::ManagerTask &) = delete;
public: tml::test::ManagerTask &operator =(const tml::test::ManagerTask &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::test::Manager *mgr_;
	UINT event_index_;

private:
	void Release(void);

public:
	ManagerTask();
	virtual ~ManagerTask();

	virtual void Init(void);
	INT Create(const tml::test::ManagerTaskDesc &);

	tml::test::Manager *GetManager(void);
	UINT GetEventIndex(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::test::ManagerTask::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::test::Manager *tml::test::ManagerTask::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventIndex�֐�
 * @return event_index (event_index)
 */
inline UINT tml::test::ManagerTask::GetEventIndex(void) const
{
	return (this->event_index_);
}
