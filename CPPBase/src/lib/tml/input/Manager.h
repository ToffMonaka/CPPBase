/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathINT.h"
#include "../manager/Manager.h"
#include "ManagerFactory.h"
#include "ManagerCommon.h"


namespace tml {
namespace input {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::ManagerDesc
{
public:

private:
	void Release(void);

protected:
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
	tml::XMINT2EX mouse_device_pos_;
	std::array<bool, tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE_COUNT> mouse_device_code_stat_ary_;
	std::array<bool, tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE_COUNT> keyboard_device_code_stat_ary_;

public:
	tml::input::ManagerFactory factory;
	tml::input::ManagerCommon common;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::input::ManagerDesc &);

	void Update(void);

	const tml::XMINT2EX &GetMouseDevicePosition(void) const;
	const tml::XMINT2EX &GetMouseDevicePosition(const bool);
	void SetMouseDevicePosition(const tml::XMINT2EX &);
	void SetMouseDevicePosition(const tml::XMINT2EX &, const bool);
	bool GetMouseDeviceCodeState(const tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE) const;
	bool GetMouseDeviceCodeState(const tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE, const bool);
	void SetMouseDeviceCodeState(const tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE, const bool);
	void ClearMouseDeviceCodeState(void);
	INT AddMouseDeviceRawInput(const RAWMOUSE &, const tml::XMINT2EX &);
	bool GetKeyboardDeviceCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE) const;
	bool GetKeyboardDeviceCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE, const bool);
	void SetKeyboardDeviceCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE, const bool);
	void ClearKeyboardDeviceCodeState(void);
	INT AddKeyboardDeviceRawInput(const RAWKEYBOARD &);
};
}
}


/**
 * @brief GetMouseDevicePosition関数
 * @return mouse_device_pos (mouse_device_position)
 */
inline const tml::XMINT2EX &tml::input::Manager::GetMouseDevicePosition(void) const
{
	return (this->mouse_device_pos_);
}


/**
 * @brief GetMouseDevicePosition関数
 * @param sys_flg (system_flag)
 * @return mouse_device_pos (mouse_device_position)
 */
inline const tml::XMINT2EX &tml::input::Manager::GetMouseDevicePosition(const bool sys_flg)
{
	if (sys_flg) {
		POINT mouse_device_sys_pos;

		GetCursorPos(&mouse_device_sys_pos);
		ScreenToClient(this->GetWindowHandle(), &mouse_device_sys_pos);

		this->mouse_device_pos_ = tml::XMINT2EX(mouse_device_sys_pos.x, mouse_device_sys_pos.y);
	}

	return (this->mouse_device_pos_);
}


/**
 * @brief SetMouseDevicePosition関数
 * @param mouse_device_pos (mouse_device_position)
 */
inline void tml::input::Manager::SetMouseDevicePosition(const tml::XMINT2EX &mouse_device_pos)
{
	this->mouse_device_pos_ = mouse_device_pos;

	return;
}


/**
 * @brief SetMouseDevicePosition関数
 * @param mouse_device_pos (mouse_device_position)
 * @param sys_flg (system_flag)
 */
inline void tml::input::Manager::SetMouseDevicePosition(const tml::XMINT2EX &mouse_device_pos, const bool sys_flg)
{
	this->mouse_device_pos_ = mouse_device_pos;

	if (sys_flg) {
		POINT mouse_device_sys_pos = {this->mouse_device_pos_.x, this->mouse_device_pos_.y};

		ClientToScreen(this->GetWindowHandle(), &mouse_device_sys_pos);
		SetCursorPos(mouse_device_sys_pos.x, mouse_device_sys_pos.y);
	}

	return;
}


/**
 * @brief GetMouseDeviceCodeState関数
 * @param mouse_device_code (mouse_device_code)
 * @return mouse_device_code_stat (mouse_device_code_state)
 */
inline bool tml::input::Manager::GetMouseDeviceCodeState(const tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE mouse_device_code) const
{
	return (this->mouse_device_code_stat_ary_[static_cast<UINT>(mouse_device_code)]);
}


/**
 * @brief GetMouseDeviceCodeState関数
 * @param mouse_device_code (mouse_device_code)
 * @param sys_flg (system_flag)
 * @return mouse_device_code_stat (mouse_device_code_state)
 */
inline bool tml::input::Manager::GetMouseDeviceCodeState(const tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE mouse_device_code, const bool sys_flg)
{
	if (sys_flg) {
		this->mouse_device_code_stat_ary_[static_cast<UINT>(mouse_device_code)] = GetKeyState(static_cast<UINT>(mouse_device_code)) & 0x8000;
	}

	return (this->mouse_device_code_stat_ary_[static_cast<UINT>(mouse_device_code)]);
}


/**
 * @brief SetMouseDeviceCodeState関数
 * @param mouse_device_code (mouse_device_code)
 * @param mouse_device_code_stat (mouse_device_code_state)
 */
inline void tml::input::Manager::SetMouseDeviceCodeState(const tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE mouse_device_code, const bool mouse_device_code_stat)
{
	this->mouse_device_code_stat_ary_[static_cast<UINT>(mouse_device_code)] = mouse_device_code_stat;

	return;
}


/**
 * @brief ClearMouseDeviceCodeState関数
 */
inline void tml::input::Manager::ClearMouseDeviceCodeState(void)
{
	this->mouse_device_code_stat_ary_.fill(false);

	return;
}


/**
 * @brief GetKeyboardDeviceCodeState関数
 * @param keyboard_device_code (keyboard_device_code)
 * @return keyboard_device_code_stat (keyboard_device_code_state)
 */
inline bool tml::input::Manager::GetKeyboardDeviceCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE keyboard_device_code) const
{
	return (this->keyboard_device_code_stat_ary_[static_cast<UINT>(keyboard_device_code)]);
}


/**
 * @brief GetKeyboardDeviceCodeState関数
 * @param keyboard_device_code (keyboard_device_code)
 * @param sys_flg (system_flag)
 * @return keyboard_device_code_stat (keyboard_device_code_state)
 */
inline bool tml::input::Manager::GetKeyboardDeviceCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE keyboard_device_code, const bool sys_flg)
{
	if (sys_flg) {
		this->keyboard_device_code_stat_ary_[static_cast<UINT>(keyboard_device_code)] = GetKeyState(static_cast<UINT>(keyboard_device_code)) & 0x8000;
	}

	return (this->keyboard_device_code_stat_ary_[static_cast<UINT>(keyboard_device_code)]);
}


/**
 * @brief SetKeyboardDeviceCodeState関数
 * @param keyboard_device_code (keyboard_device_code)
 * @param keyboard_device_code_stat (keyboard_device_code_state)
 */
inline void tml::input::Manager::SetKeyboardDeviceCodeState(const tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE keyboard_device_code, const bool keyboard_device_code_stat)
{
	this->keyboard_device_code_stat_ary_[static_cast<UINT>(keyboard_device_code)] = keyboard_device_code_stat;

	return;
}


/**
 * @brief ClearKeyboardDeviceCodeState関数
 */
inline void tml::input::Manager::ClearKeyboardDeviceCodeState(void)
{
	this->keyboard_device_code_stat_ary_.fill(false);

	return;
}
