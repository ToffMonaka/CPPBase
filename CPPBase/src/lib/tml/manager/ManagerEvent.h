/**
 * @file
 * @brief ManagerEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
class Manager;
}


namespace tml {
/**
 * @brief ManagerEventDesc�N���X
 */
class ManagerEventDesc
{
private:
	tml::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::Manager *GetManager(void) const;
	void SetManager(tml::Manager *);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::ManagerEventDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
/**
 * @brief ManagerEvent�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerEvent
{
public: ManagerEvent(const tml::ManagerEvent &) = delete;
public: tml::ManagerEvent &operator =(const tml::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::Manager *mgr_;
	UINT event_index_;

protected:
	void Release(void);
	INT Create(const tml::ManagerEventDesc &, const UINT);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);

	tml::Manager *GetManager(void);
	UINT GetEventIndex(void) const;
};
}


/**
 * @brief Release�֐�
 */
inline void tml::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::Manager *tml::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventIndex�֐�
 * @return event_index (event_index)
 */
inline UINT tml::ManagerEvent::GetEventIndex(void) const
{
	return (this->event_index_);
}
