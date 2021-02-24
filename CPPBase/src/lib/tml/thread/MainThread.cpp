/**
 * @file
 * @brief MainThreadコードファイル
 */


#include "MainThread.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::MainThread::MainThread() :
	instance_handle_(nullptr),
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	wnd_show_type_(0),
	wnd_class_{},
	wnd_class_atom_(0)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MainThread::~MainThread()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::MainThread::Release(void)
{
	this->DeleteWindow_();

	tml::Thread::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::MainThread::Init(void)
{
	this->instance_handle_ = nullptr;
	this->wnd_name_.clear();
	this->wnd_show_type_ = 0;

	tml::Thread::Init();

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
INT tml::MainThread::Create(const HINSTANCE instance_handle, const WCHAR *wnd_name, const INT wnd_show_type)
{
	if (tml::Thread::Create(tml::ConstantUtil::THREAD::TYPE::MAIN) < 0) {
		return (-1);
	}

	this->instance_handle_ = instance_handle;
	this->wnd_name_ = wnd_name;
	this->wnd_show_type_ = wnd_show_type;

	return (0);
}


/**
 * @brief CreateWindow_関数
 * @param wnd_class (window_class)
 * @param pos (position)
 * @param size (size)
 * @return res (result)<br>
 * 0未満=失敗,-2=多重起動
 */
INT tml::MainThread::CreateWindow_(const WNDCLASSEX &wnd_class, const tml::XMUINT2EX &pos, const tml::XMUINT2EX &size)
{
	if (this->wnd_handle_ != nullptr) {
		return (-1);
	}

	if (FindWindow(wnd_class.lpszClassName, this->wnd_name_.c_str()) != nullptr) {
		return(-2);
	}

	tml::MemoryUtil::Copy(&this->wnd_class_, &wnd_class, 1U);
	this->wnd_class_atom_ = RegisterClassEx(&this->wnd_class_);

	if (!this->wnd_class_atom_) {
		this->DeleteWindow_();

		return (-1);
	}

	RECT wnd_rect = {0L, 0L, static_cast<LONG>(size.x), static_cast<LONG>(size.y)};

	AdjustWindowRect(&wnd_rect, WS_OVERLAPPEDWINDOW, false);

	this->wnd_handle_ = CreateWindow(
		this->wnd_class_.lpszClassName, this->wnd_name_.c_str(),
		WS_OVERLAPPEDWINDOW,
		pos.x, pos.y, wnd_rect.right - wnd_rect.left, wnd_rect.bottom - wnd_rect.top,
		nullptr, nullptr, this->instance_handle_,
		nullptr
	);

	if (this->wnd_handle_ == nullptr) {
		this->DeleteWindow_();

		return (-1);
	}

	this->wnd_dc_handle_ = GetDC(this->wnd_handle_);

	if (this->wnd_dc_handle_ == nullptr) {
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
void tml::MainThread::DeleteWindow_(void)
{
	if (this->wnd_dc_handle_ != nullptr) {
		ReleaseDC(this->wnd_handle_, this->wnd_dc_handle_);

		this->wnd_dc_handle_ = nullptr;
	}

	if (this->wnd_handle_ != nullptr) {
		DestroyWindow(this->wnd_handle_);

		this->wnd_handle_ = nullptr;
	}

	if (this->wnd_class_atom_) {
		UnregisterClass(this->wnd_class_.lpszClassName, this->instance_handle_);

		tml::MemoryUtil::Clear(&this->wnd_class_, 1U);
		this->wnd_class_atom_ = 0;
	}

	return;
}
