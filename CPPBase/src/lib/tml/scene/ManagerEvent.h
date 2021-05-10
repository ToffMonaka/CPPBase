/**
 * @file
 * @brief ManagerEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../manager/ManagerEvent.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerEventDesc�N���X
 */
class ManagerEventDesc : public tml::ManagerEventDesc
{
public:
	tml::scene::Manager *manager;

protected:
	void Release(void);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerEventDesc::Release(void)
{
	tml::ManagerEventDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief ManagerEvent�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerEvent : public tml::ManagerEvent
{
public: ManagerEvent(const tml::scene::ManagerEvent &) = delete;
public: tml::scene::ManagerEvent &operator =(const tml::scene::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::scene::Manager *mgr_;
	tml::ConstantUtil::SCENE::EVENT_TYPE event_type_;

protected:
	void Release(void);
	INT Create(const tml::scene::ManagerEventDesc &, const tml::ConstantUtil::SCENE::EVENT_TYPE);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);

	tml::scene::Manager *GetManager(void);
	tml::ConstantUtil::SCENE::EVENT_TYPE GetEventType(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerEvent::Release(void)
{
	tml::ManagerEvent::Release();

	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetEventType�֐�
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::SCENE::EVENT_TYPE tml::scene::ManagerEvent::GetEventType(void) const
{
	return (this->event_type_);
}
