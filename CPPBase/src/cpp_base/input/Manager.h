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
inline void cpp_base::input::ManagerDesc::Release(void)
{
	tml::input::ManagerDesc::Release();

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
	cpp_base::input::ManagerCommon common2_;

protected:
	void Release(void);

	INT CreateCommon2(void);
	void DeleteCommon2(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::input::ManagerDesc &);

	cpp_base::input::ManagerCommon &GetCommon2(void);
};
}
}


/**
 * @brief GetCommon2�֐�
 * @return common2 (common2)
 */
inline cpp_base::input::ManagerCommon &cpp_base::input::Manager::GetCommon2(void)
{
	return (this->common2_);
}
