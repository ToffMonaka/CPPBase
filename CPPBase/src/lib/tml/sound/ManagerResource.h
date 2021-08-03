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

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	tml::sound::Manager *GetManager(void) const;
	void SetManager(tml::sound::Manager *);
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
	tml::sound::Manager *mgr_;
	tml::ConstantUtil::SOUND::RESOURCE_TYPE res_type_;

private:
	void Release(void);
	void ReleaseDeferred(void);

protected:
	virtual INT OnCreateDeferred(void);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerResourceDesc &);
	virtual void InitDeferred(void);

	tml::sound::Manager *GetManager(void);
	tml::ConstantUtil::SOUND::RESOURCE_TYPE GetResourceType(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::ManagerResource::Release(void)
{
	this->ReleaseDeferred();

	return;
}


/**
 * @brief ReleaseDeferred�֐�
 */
inline void tml::sound::ManagerResource::ReleaseDeferred(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceType�֐�
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::SOUND::RESOURCE_TYPE tml::sound::ManagerResource::GetResourceType(void) const
{
	return (this->res_type_);
}
