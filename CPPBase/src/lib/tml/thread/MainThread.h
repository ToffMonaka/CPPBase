/**
 * @file
 * @brief MainThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "Thread.h"


namespace tml {
/**
 * @brief MainThreadクラス
 *
 * インターフェースパターン
 */
class MainThread : public tml::Thread
{
public: MainThread(const tml::MainThread &) = delete;
public: tml::MainThread &operator =(const tml::MainThread &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	bool com_created_flg_;
	HINSTANCE instance_handle_;
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	std::wstring wnd_name_;
	INT wnd_show_type_;
	WNDCLASSEX wnd_class_;
	ATOM wnd_class_atom_;

private:
	void Release(void);

protected:
	virtual INT OnStart(void) = 0;
	virtual void OnEnd(void) = 0;
	virtual void OnUpdate(void) = 0;

	INT CreateCOM(void);
	void DeleteCOM(void);
	INT CreateWindow_(const WNDCLASSEX &, const tml::XMUINT2EX &, const tml::XMUINT2EX &);
	void DeleteWindow_(void);

public:
	MainThread();
	virtual ~MainThread();

	virtual void Init(void);
	INT Create(const HINSTANCE, const WCHAR *, const INT);

	HINSTANCE GetInstanceHandle(void) const;
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	const std::wstring &GetWindowName(void) const;
	INT GetWindowShowType(void) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::MainThread::Release(void)
{
	return;
}


/**
 * @brief GetInstanceHandle関数
 * @return instance_handle (instance_handle)
 */
inline HINSTANCE tml::MainThread::GetInstanceHandle(void) const
{
	return (this->instance_handle_);
}


/**
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::MainThread::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::MainThread::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetWindowName関数
 * @return wnd_name (window_name)
 */
inline const std::wstring &tml::MainThread::GetWindowName(void) const
{
	return (this->wnd_name_);
}


/**
 * @brief GetWindowShowType関数
 * @return wnd_show_type (window_show_type)
 */
inline INT tml::MainThread::GetWindowShowType(void) const
{
	return (this->wnd_show_type_);
}
