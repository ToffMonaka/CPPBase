/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathINT.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"


namespace tml {
namespace input {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::ManagerDesc
{
public:

protected:
	void Release(void);

	void InitResourceCount(void);
	void InitEventCount(void);

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
	tml::ManagerDesc::Release();

	return;
}


namespace tml {
namespace input {
/**
 * @brief Managerクラス
 */
class Manager : public tml::Manager
{
public: Manager(const tml::input::Manager &) = delete;
public: tml::input::Manager &operator =(const tml::input::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::input::ManagerCommon common_;

	tml::XMINT2EX mouse_pos_;
	std::array<bool, tml::ConstantUtil::INPUT::MOUSE_CODE_COUNT> mouse_code_stat_ary_;
	std::array<bool, tml::ConstantUtil::INPUT::KEYBOARD_CODE_COUNT> keyboard_code_stat_ary_;

protected:
	void Release(void);

	INT CreateCommon(void);
	void DeleteCommon(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::input::ManagerDesc &);

	void Update(void);
	tml::input::ManagerCommon &GetCommon(void);

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
 * @brief GetCommon関数
 * @return common (common)
 */
inline tml::input::ManagerCommon &tml::input::Manager::GetCommon(void)
{
	return (this->common_);
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
		ScreenToClient(this->GetWindowHandle(), &mouse_sys_pos);

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

		ClientToScreen(this->GetWindowHandle(), &mouse_sys_pos);
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
