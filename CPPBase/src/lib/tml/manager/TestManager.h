/**
 * @file
 * @brief Manager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "TestManagerFactory.h"


namespace tml {
namespace test {
/**
 * @brief ManagerDesc�N���X
 */
class ManagerDesc
{
public:
	HWND window_handle;
	HDC window_device_context_handle;
	tml::test::ManagerFactory *factory;

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
inline void tml::test::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
namespace test {
/**
 * @brief Manager�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Manager
{
public: Manager(const tml::test::Manager &) = delete;
public: tml::test::Manager &operator =(const tml::test::Manager &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;

public:
	tml::test::ManagerFactory *factory;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::test::ManagerDesc &);

	void Update(void);

	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
};
}
}


/**
 * @brief GetWindowHandle�֐�
 * @return wnd_handle (window_handle)
 */
inline HWND tml::test::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle�֐�
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::test::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}
