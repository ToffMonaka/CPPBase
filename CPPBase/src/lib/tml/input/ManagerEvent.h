/**
 * @file
 * @brief ManagerEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../manager/ManagerEvent.h"


namespace tml {
namespace input {
/**
 * @brief ManagerEventDesc�N���X
 */
class ManagerEventDesc : public tml::ManagerEventDesc
{
private:
	tml::input::Manager *mgr_;

public:

private:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::input::Manager *GetManager(void) const;
	void SetManager(tml::input::Manager *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::ManagerEventDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace input {
/**
 * @brief ManagerEvent�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerEvent : public tml::ManagerEvent
{
public: ManagerEvent(const tml::input::ManagerEvent &) = delete;
public: tml::input::ManagerEvent &operator =(const tml::input::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::input::Manager *mgr_;
	tml::ConstantUtil::INPUT::EVENT_TYPE event_type_;

private:
	void Release(void);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::input::ManagerEventDesc &);

	tml::input::Manager *GetManager(void);
	tml::ConstantUtil::INPUT::EVENT_TYPE GetEventType(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventType�֐�
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::INPUT::EVENT_TYPE tml::input::ManagerEvent::GetEventType(void) const
{
	return (this->event_type_);
}
