/**
 * @file
 * @brief ManagerResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ManagerResourceDesc�N���X
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
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
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::graphic::ManagerResource &) = delete;
public: tml::graphic::ManagerResource &operator =(const tml::graphic::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	const tml::graphic::ManagerResourceDesc *desc_;
	tml::graphic::Manager *mgr_;

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

	const tml::graphic::ManagerResourceDesc *GetDesc(void) const;
	tml::graphic::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::graphic::ManagerResourceDesc *tml::graphic::ManagerResource::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}
