/**
 * @file
 * @brief ManagerResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../manager/ManagerResource.h"


namespace tml {
namespace input {
/**
 * @brief ManagerResourceDesc�N���X
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
{
private:
	tml::input::Manager *mgr_;

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

	tml::input::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::ManagerResourceDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerResourceDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace input {
/**
 * @brief ManagerResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::input::ManagerResource &) = delete;
public: tml::input::ManagerResource &operator =(const tml::input::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	const tml::input::ManagerResourceDesc *desc_;
	tml::input::Manager *mgr_;

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

	const tml::input::ManagerResourceDesc *GetDesc(void) const;
	tml::input::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::input::ManagerResourceDesc *tml::input::ManagerResource::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}
