/**
 * @file
 * @brief Manager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/sound/Manager.h"
#include "ManagerFactory.h"
#include "ManagerCommon.h"


namespace cpp_base {
namespace sound {
/**
 * @brief ManagerDesc�N���X
 */
class ManagerDesc : public tml::sound::ManagerDesc
{
public:

private:
	void InitResourceCount(void);
	void InitEventCount(void);

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
inline void cpp_base::sound::ManagerDesc::Release(void)
{
	tml::sound::ManagerDesc::Release();

	return;
}


namespace cpp_base {
namespace sound {
/**
 * @brief Manager�N���X
 */
class Manager : public tml::sound::Manager
{
public: Manager(const cpp_base::sound::Manager &) = delete;
public: cpp_base::sound::Manager &operator =(const cpp_base::sound::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	cpp_base::sound::ManagerFactory factory2;
	cpp_base::sound::ManagerCommon common2;

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::sound::ManagerDesc &);
};
}
}
