/**
 * @file
 * @brief Event�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"


namespace tml {
namespace graphic {
class Manager;
}
}


namespace tml {
namespace graphic {
/**
 * @brief Event�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Event
{
public: Event(const tml::graphic::Event &) = delete;
public: tml::graphic::Event &operator =(const tml::graphic::Event &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::GRAPHIC::EVENT_TYPE event_type_;
	tml::graphic::Manager *mgr_;

protected:
	void Release(void);
	INT Create(const tml::ConstantUtil::GRAPHIC::EVENT_TYPE, tml::graphic::Manager *);

public:
	Event();
	virtual ~Event();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::EVENT_TYPE GetEventType(void) const;
	tml::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Event::Release(void)
{
	return;
}


/**
 * @brief GetEventType�֐�
 * @return event_type (event_type)
 */
inline tml::ConstantUtil::GRAPHIC::EVENT_TYPE tml::graphic::Event::GetEventType(void) const
{
	return (this->event_type_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::Event::GetManager(void)
{
	return (this->mgr_);
}
