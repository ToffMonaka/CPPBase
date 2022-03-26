/**
 * @file
 * @brief ManagerEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../manager/ManagerEvent.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerEventDesc�N���X
 */
class ManagerEventDesc : public tml::ManagerEventDesc
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
	ManagerEventDesc();
	virtual ~ManagerEventDesc();

	virtual void Init(void);

	tml::sound::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerEventDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerEventDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace sound {
/**
 * @brief ManagerEvent�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerEvent : public tml::ManagerEvent
{
public: ManagerEvent(const tml::sound::ManagerEvent &) = delete;
public: tml::sound::ManagerEvent &operator =(const tml::sound::ManagerEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::sound::Manager *mgr_;

private:
	void Release(void);

protected:
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerEvent();
	virtual ~ManagerEvent();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerEventDesc &);

	tml::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerEvent::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerEvent::GetManager(void)
{
	return (this->mgr_);
}
