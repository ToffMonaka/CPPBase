/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathINT.h"
#include "ManagerCommon.h"
#include "Event.h"


namespace tml {
namespace input {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc
{
public:
	HWND window_handle;
	HDC window_device_context_handle;

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
 * @brief Release関数
 */
inline void tml::input::ManagerDesc::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief Managerクラス
 */
class Manager
{
public: Manager(const tml::input::Manager &) = delete;
public: tml::input::Manager &operator =(const tml::input::Manager &) = delete;

private:
	HWND wnd_handle_;
	HDC wnd_dc_handle_;
	tml::input::ManagerCommon common_;
	std::array<std::list<tml::shared_ptr<tml::input::Resource>>, tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT> res_cont_ary_;
	std::array<UINT, 2U> event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::input::Event>>, 2U> event_cont_ary_;
	UINT front_event_index_;
	UINT back_event_index_;
	std::array<UINT, tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT> stock_event_cnt_ary_;
	std::array<std::vector<tml::unique_ptr<tml::input::Event>>, tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT> stock_event_cont_ary_;

	tml::XMINT2EX mouse_pos_;
	std::array<bool, tml::ConstantUtil::INPUT::MOUSE_CODE_COUNT> mouse_code_stat_ary_;
	std::array<bool, tml::ConstantUtil::INPUT::KEYBOARD_CODE_COUNT> keyboard_code_stat_ary_;

private:
	void UpdateEvent(void);

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::input::ManagerDesc &);

	void Update(void);
	HWND GetWindowHandle(void) const;
	HDC GetWindowDeviceContextHandle(void) const;
	tml::input::ManagerCommon &GetCommon(void);
	template <typename T1, typename T2, typename D>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, const D &);
	template <typename T1, typename T2>
	tml::shared_ptr<T2> &GetResource(tml::shared_ptr<T2> &, tml::shared_ptr<T1> &);
	template <typename T>
	void ReleaseResource(tml::shared_ptr<T> &);
	UINT GetEventCount(void) const;
	const tml::unique_ptr<tml::input::Event> *GetEventArray(void) const;
	template <typename T, typename D>
	INT AddEvent(const D &);

	const tml::XMINT2EX &GetMousePosition(void) const;
	const tml::XMINT2EX &GetMousePosition(const bool);
	void SetMousePosition(const tml::XMINT2EX &);
	void SetMousePosition(const tml::XMINT2EX &, const bool);
	bool GetMouseCodeState(const tml::ConstantUtil::INPUT::MOUSE_CODE) const;
	bool GetMouseCodeState(const tml::ConstantUtil::INPUT::MOUSE_CODE, const bool);
	void SetMouseCodeState(const tml::ConstantUtil::INPUT::MOUSE_CODE, const bool);
	void SetMouseCodeState(const bool);
	bool GetKeyboardCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_CODE) const;
	bool GetKeyboardCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_CODE, const bool);
	void SetKeyboardCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_CODE, const bool);
	void SetKeyboardCodeState(const bool);
};
}
}


/**
 * @brief GetWindowHandle関数
 * @return wnd_handle (window_handle)
 */
inline HWND tml::input::Manager::GetWindowHandle(void) const
{
	return (this->wnd_handle_);
}


/**
 * @brief GetWindowDeviceContextHandle関数
 * @return wnd_dc_handle (window_device_context_handle)
 */
inline HDC tml::input::Manager::GetWindowDeviceContextHandle(void) const
{
	return (this->wnd_dc_handle_);
}


/**
 * @brief GetCommon関数
 * @return common (common)
 */
inline tml::input::ManagerCommon &tml::input::Manager::GetCommon(void)
{
	return (this->common_);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param desc (desc)
 * @return dst_res (dst_resource)
 */
template <typename T1, typename T2, typename D>
inline tml::shared_ptr<T2> &tml::input::Manager::GetResource(tml::shared_ptr<T2> &dst_res, const D &desc)
{
	this->ReleaseResource(dst_res);

	if (desc.manager != this) {
		return (dst_res);
	}

	auto res = tml::make_shared<T1>(1U);

	if (res->Create(desc) < 0) {
		return (dst_res);
	}

	auto res_index = static_cast<UINT>(res->GetResourceType());

	this->res_cont_ary_[res_index].push_back(res);

	dst_res = res;

	return (dst_res);
}


/**
 * @brief GetResource関数
 * @param dst_res (dst_resource)
 * @param res (resource)
 * @return dst_res (dst_resource)
 */
template <typename T1, typename T2>
inline tml::shared_ptr<T2> &tml::input::Manager::GetResource(tml::shared_ptr<T2> &dst_res, tml::shared_ptr<T1> &res)
{
	if (dst_res == res) {
		return (dst_res);
	}

	this->ReleaseResource(dst_res);

	dst_res = res;

	return (dst_res);
}


/**
 * @brief ReleaseResource関数
 * @param res (resource)
 */
template <typename T>
inline void tml::input::Manager::ReleaseResource(tml::shared_ptr<T> &res)
{
	if (res == nullptr) {
		return;
	}

	auto res_index = static_cast<UINT>(res->GetResourceType());

	if (res.use_count() <= 2L) {
		this->res_cont_ary_[res_index].remove(res);
	}

	res.reset();

	return;
}


/**
 * @brief GetEventCount関数
 * @return event_cnt (event_count)
 */
inline UINT tml::input::Manager::GetEventCount(void) const
{
	return (this->event_cnt_ary_[this->front_event_index_]);
}


/**
 * @brief GetEventArray関数
 * @return event_ary (event_array)
 */
inline const tml::unique_ptr<tml::input::Event> *tml::input::Manager::GetEventArray(void) const
{
	return (this->event_cont_ary_[this->front_event_index_].data());
}


/**
 * @brief AddEvent関数
 * @param dat (data)
 * @return res (result)<br>
 * 0未満=失敗
 */
template <typename T, typename D>
inline INT tml::input::Manager::AddEvent(const D &dat)
{
	tml::unique_ptr<tml::input::Event> event;

	auto event_index = static_cast<UINT>(T::EVENT_TYPE);
	auto &stock_event_cnt = this->stock_event_cnt_ary_[event_index];
	auto &stock_event_cont = this->stock_event_cont_ary_[event_index];

	if (stock_event_cnt > 0U) {
		--stock_event_cnt;

		event = std::move(stock_event_cont[stock_event_cnt]);
	} else {
		event = tml::make_unique<T>(1U);

		if (reinterpret_cast<T *>(event.get())->Create(this) < 0) {
			return (-1);
		}
	}

	reinterpret_cast<T *>(event.get())->SetData(dat);

	auto &back_event_cnt = this->event_cnt_ary_[this->back_event_index_];
	auto &back_event_cont = this->event_cont_ary_[this->back_event_index_];

	if (back_event_cnt >= back_event_cont.size()) {
		back_event_cont.resize(back_event_cnt + 128U);
	}

	back_event_cont[back_event_cnt] = std::move(event);

	++back_event_cnt;

	return (0);
}


/**
 * @brief GetMousePosition関数
 * @return mouse_pos (mouse_position)
 */
inline const tml::XMINT2EX &tml::input::Manager::GetMousePosition(void) const
{
	return (this->mouse_pos_);
}


/**
 * @brief GetMousePosition関数
 * @param sys_flg (system_flag)
 * @return mouse_pos (mouse_position)
 */
inline const tml::XMINT2EX &tml::input::Manager::GetMousePosition(const bool sys_flg)
{
	if (sys_flg) {
		POINT mouse_sys_pos;

		GetCursorPos(&mouse_sys_pos);
		ScreenToClient(this->wnd_handle_, &mouse_sys_pos);

		this->mouse_pos_ = tml::XMINT2EX(mouse_sys_pos.x, mouse_sys_pos.y);
	}

	return (this->mouse_pos_);
}


/**
 * @brief SetMousePosition関数
 * @param mouse_pos (mouse_position)
 */
inline void tml::input::Manager::SetMousePosition(const tml::XMINT2EX &mouse_pos)
{
	this->mouse_pos_ = mouse_pos;

	return;
}


/**
 * @brief SetMousePosition関数
 * @param mouse_pos (mouse_position)
 * @param sys_flg (system_flag)
 */
inline void tml::input::Manager::SetMousePosition(const tml::XMINT2EX &mouse_pos, const bool sys_flg)
{
	this->mouse_pos_ = mouse_pos;

	if (sys_flg) {
		POINT mouse_sys_pos = {this->mouse_pos_.x, this->mouse_pos_.y};

		ClientToScreen(this->wnd_handle_, &mouse_sys_pos);
		SetCursorPos(mouse_sys_pos.x, mouse_sys_pos.y);
	}

	return;
}


/**
 * @brief GetMouseCodeState関数
 * @param mouse_code (mouse_code)
 * @return mouse_code_stat (mouse_code_state)
 */
inline bool tml::input::Manager::GetMouseCodeState(const tml::ConstantUtil::INPUT::MOUSE_CODE mouse_code) const
{
	return (this->mouse_code_stat_ary_[static_cast<UINT>(mouse_code)]);
}


/**
 * @brief GetMouseCodeState関数
 * @param mouse_code (mouse_code)
 * @param sys_flg (system_flag)
 * @return mouse_code_stat (mouse_code_state)
 */
inline bool tml::input::Manager::GetMouseCodeState(const tml::ConstantUtil::INPUT::MOUSE_CODE mouse_code, const bool sys_flg)
{
	if (sys_flg) {
		this->mouse_code_stat_ary_[static_cast<UINT>(mouse_code)] = GetKeyState(static_cast<UINT>(mouse_code)) & 0x8000;
	}

	return (this->mouse_code_stat_ary_[static_cast<UINT>(mouse_code)]);
}


/**
 * @brief SetMouseCodeState関数
 * @param mouse_code (mouse_code)
 * @param mouse_code_stat (mouse_code_state)
 */
inline void tml::input::Manager::SetMouseCodeState(const tml::ConstantUtil::INPUT::MOUSE_CODE mouse_code, const bool mouse_code_stat)
{
	this->mouse_code_stat_ary_[static_cast<UINT>(mouse_code)] = mouse_code_stat;

	return;
}


/**
 * @brief SetMouseCodeState関数
 * @param mouse_code_stat (mouse_code_state)
 */
inline void tml::input::Manager::SetMouseCodeState(const bool mouse_code_stat)
{
	this->mouse_code_stat_ary_.fill(mouse_code_stat);

	return;
}


/**
 * @brief GetKeyboardCodeState関数
 * @param keyboard_code (keyboard_code)
 * @return keyboard_code_stat (keyboard_code_state)
 */
inline bool tml::input::Manager::GetKeyboardCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_CODE keyboard_code) const
{
	return (this->keyboard_code_stat_ary_[static_cast<UINT>(keyboard_code)]);
}


/**
 * @brief GetKeyboardCodeState関数
 * @param keyboard_code (keyboard_code)
 * @param sys_flg (system_flag)
 * @return keyboard_code_stat (keyboard_code_state)
 */
inline bool tml::input::Manager::GetKeyboardCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_CODE keyboard_code, const bool sys_flg)
{
	if (sys_flg) {
		this->keyboard_code_stat_ary_[static_cast<UINT>(keyboard_code)] = GetKeyState(static_cast<UINT>(keyboard_code)) & 0x8000;
	}

	return (this->keyboard_code_stat_ary_[static_cast<UINT>(keyboard_code)]);
}


/**
 * @brief SetKeyboardCodeState関数
 * @param keyboard_code (keyboard_code)
 * @param keyboard_code_stat (keyboard_code_state)
 */
inline void tml::input::Manager::SetKeyboardCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_CODE keyboard_code, const bool keyboard_code_stat)
{
	this->keyboard_code_stat_ary_[static_cast<UINT>(keyboard_code)] = keyboard_code_stat;

	return;
}


/**
 * @brief SetKeyboardCodeState関数
 * @param keyboard_code_stat (keyboard_code_state)
 */
inline void tml::input::Manager::SetKeyboardCodeState(const bool keyboard_code_stat)
{
	this->keyboard_code_stat_ary_.fill(keyboard_code_stat);

	return;
}
