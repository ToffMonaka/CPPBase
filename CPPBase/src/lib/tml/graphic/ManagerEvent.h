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

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerEventDesc::Release(void)
{
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

private:
	void Release(void);

protected:
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::graphic::ManagerEventDesc &);

	tml::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}
