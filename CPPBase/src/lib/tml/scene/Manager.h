/**
 * @file
 * @brief Manager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerDesc�N���X
 */
class ManagerDesc : public tml::ManagerDesc
{
public:

protected:
	void Release(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerDesc::Release(void)
{
	tml::ManagerDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief Manager�N���X
 */
class Manager : public tml::Manager
{
public: Manager(const tml::scene::Manager &) = delete;
public: tml::scene::Manager &operator =(const tml::scene::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::scene::ManagerCommon common_;

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::scene::ManagerDesc &);

	void Update(void);
	tml::scene::ManagerCommon &GetCommon(void);
};
}
}


/**
 * @brief GetCommon�֐�
 * @return common (common)
 */
inline tml::scene::ManagerCommon &tml::scene::Manager::GetCommon(void)
{
	return (this->common_);
}
