/**
 * @file
 * @brief Process�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <thread>


namespace tml {
/**
 * @brief Process�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Process
{
public: Process(const Process &) = delete;
public: Process &operator =(const Process &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	std::thread::id th_id_;
	HINSTANCE instance_handle_;
	HWND wnd_handle_;
	std::wstring wnd_name_;
	INT wnd_show_type_;
	WNDCLASSEX wnd_class_;
	ATOM wnd_class_atom_;

protected:
	void Release(void);
	INT Create(const HINSTANCE, const WCHAR *, const INT);

	INT CreateWindow_(const WNDCLASSEX &);
	void DeleteWindow_(void);

public:
	Process();
	virtual ~Process();

	virtual void Init(void);

	virtual INT Start(void) = 0;
	virtual void End(void) = 0;
	virtual void Update(void) = 0;
	const std::thread::id &GetThreadID(void) const;
	HINSTANCE GetInstanceHandle(void) const;
	HWND GetWindowHandle(void) const;
	const std::wstring &GetWindowName(void) const;
	INT GetWindowShowType(void) const;
};
}


/**
 * @brief GetThreadID�֐�
 * @return th_id (thread_id)
 */
inline const std::thread::id &tml::Process::GetThreadID(void) const
{
	return (this->th_id_);
}


/**
 * @brief GetInstanceHandle�֐�
 * @return instance_handle (instance_handle)
 */
inline HINSTANCE tml::Process::GetInstanceHandle(void) const
{
	return (this->instance_handle_);
}


/**
 * @brief GetWindowHandle�֐�
 * @return wnd_handle (window_handle)
 */
inline HWND tml::Process::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowName�֐�
 * @return wnd_name (window_name)
 */
inline const std::wstring &tml::Process::GetWindowName(void) const
{
	return (this->wnd_name_);
}


/**
 * @brief GetWindowShowType�֐�
 * @return wnd_show_type (window_show_type)
 */
inline INT tml::Process::GetWindowShowType(void) const
{
	return (this->wnd_show_type_);
}
