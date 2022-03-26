/**
 * @file
 * @brief ManagerResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerResourceDesc�N���X
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
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
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	tml::sound::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace sound {
/**
 * @brief ManagerResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::sound::ManagerResource &) = delete;
public: tml::sound::ManagerResource &operator =(const tml::sound::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	const tml::sound::ManagerResourceDesc *desc_;
	tml::sound::Manager *mgr_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);

	const tml::sound::ManagerResourceDesc *GetDesc(void) const;
	tml::sound::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::sound::ManagerResourceDesc *tml::sound::ManagerResource::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}
