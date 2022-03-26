/**
 * @file
 * @brief Manager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/input/Manager.h"
#include "ManagerCommon.h"


namespace cpp_base {
namespace input {
/**
 * @brief ManagerDesc�N���X
 */
class ManagerDesc : public tml::input::ManagerDesc
{
public:

private:
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
inline void cpp_base::input::ManagerDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace input {
/**
 * @brief Manager�N���X
 */
class Manager : public tml::input::Manager
{
public: Manager(const cpp_base::input::Manager &) = delete;
public: cpp_base::input::Manager &operator =(const cpp_base::input::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	cpp_base::input::ManagerCommon common2;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::input::ManagerDesc &);
};
}
}
