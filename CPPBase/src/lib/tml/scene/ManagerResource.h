/**
 * @file
 * @brief ManagerResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerResourceDesc�N���X
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
{
private:
	tml::scene::Manager *mgr_;

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

	tml::scene::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace scene {
/**
 * @brief ManagerResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::scene::ManagerResource &) = delete;
public: tml::scene::ManagerResource &operator =(const tml::scene::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	const tml::scene::ManagerResourceDesc *desc_;
	tml::scene::Manager *mgr_;

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

	const tml::scene::ManagerResourceDesc *GetDesc(void) const;
	tml::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::scene::ManagerResourceDesc *tml::scene::ManagerResource::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}
