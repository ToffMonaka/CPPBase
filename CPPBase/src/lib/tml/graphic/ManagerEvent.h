/**
 * @file
 * @brief ManagerEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../manager/ManagerEvent.h"


namespace tml {
namespace graphic {
/**
 * @brief ManagerEventDesc�N���X
 */
class ManagerEventDesc : public tml::ManagerEventDesc
{
private:
	tml::graphic::Manager *mgr_;

public:

protected:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void) const;
	void SetManager(tml::graphic::Manager *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerEventDesc::Release(void)
{
	tml::ManagerEventDesc::Release();

	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerEvent�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerEvent : public tml::ManagerEvent
{
public: ManagerEvent(const tml::graphic::ManagerEvent &) = delete;
public: tml::graphic::ManagerEvent &operator =(const tml::graphic::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::graphic::Manager *mgr_;
	tml::ConstantUtil::GRAPHIC::EVENT_TYPE event_type_;

protected:
	void Release(void);
	INT Create(const tml::graphic::ManagerEventDesc &, const tml::ConstantUtil::GRAPHIC::EVENT_TYPE);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void) const;
	tml::ConstantUtil::GRAPHIC::EVENT_TYPE GetEventType(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerEvent::Release(void)
{
	tml::ManagerEvent::Release();

	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerEvent::GetManager(void) const
{
	return (this->mgr_);
}


/**
 * @brief GetEventType�֐�
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::GRAPHIC::EVENT_TYPE tml::graphic::ManagerEvent::GetEventType(void) const
{
	return (this->event_type_);
}
