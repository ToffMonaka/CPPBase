/**
 * @file
 * @brief Processコードファイル
 */


#include "Process.h"
#include "ProcessUtil.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::Process::Process() :
	instance_handle_(NULLP),
	wnd_handle_(NULLP),
	wnd_show_type_(0)
{
	tml::MemoryUtil::Clear(&this->wnd_class_, 1U);
	this->wnd_class_atom_ = 0;

	return;
}


/**
 * @brief デストラクタ
 */
tml::Process::~Process()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::Process::Release(void)
{
	this->DeleteWindow_();

	return;
}


/**
 * @brief Init関数
 */
void tml::Process::Init(void)
{
	this->th_id_ = std::thread::id();
	this->instance_handle_ = NULLP;
	this->wnd_name_.clear();
	this->wnd_show_type_ = 0;

	return;
}


/**
 * @brief Create関数
 * @param instance_handle (instance_handle)
 * @param wnd_name (window_name)
 * @param wnd_show_type (window_show_type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Process::Create(const HINSTANCE instance_handle, const WCHAR *wnd_name, const INT wnd_show_type)
{
	this->th_id_ = std::this_thread::get_id();
	this->instance_handle_ = instance_handle;
	this->wnd_name_ = wnd_name;
	this->wnd_show_type_ = wnd_show_type;

	return (0);
}


/**
 * @brief CreateWindow_関数
 * @param wnd_class (window_class)
 * @return res (result)<br>
 * 0未満=失敗,-2=多重起動
 */
INT tml::Process::CreateWindow_(const WNDCLASSEX &wnd_class)
{
	if (this->wnd_handle_ != NULLP) {
		return (-1);
	}

	if (FindWindow(wnd_class.lpszClassName, this->wnd_name_.c_str()) != NULLP) {
		return(-2);
	}

	tml::MemoryUtil::Copy(&this->wnd_class_, &wnd_class, 1U);
	this->wnd_class_atom_ = RegisterClassEx(&this->wnd_class_);

	if (!this->wnd_class_atom_) {
		this->DeleteWindow_();

		return (-1);
	}

	this->wnd_handle_ = CreateWindow(
		this->wnd_class_.lpszClassName, this->wnd_name_.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULLP, NULLP, this->instance_handle_,
		NULLP
	);

	if (this->wnd_handle_ == NULLP) {
		this->DeleteWindow_();

		return (-1);
	}

	ShowWindow(this->wnd_handle_, this->wnd_show_type_);
	UpdateWindow(this->wnd_handle_);

	return (0);
}


/**
 * @brief DeleteWindow_関数
 */
void tml::Process::DeleteWindow_(void)
{
	if (this->wnd_handle_ != NULLP) {
		DestroyWindow(this->wnd_handle_);

		this->wnd_handle_ = NULLP;
	}

	if (this->wnd_class_atom_) {
		UnregisterClass(this->wnd_class_.lpszClassName, this->instance_handle_);

		tml::MemoryUtil::Clear(&this->wnd_class_, 1U);
		this->wnd_class_atom_ = 0;
	}

	return;
}
