/**
 * @file
 * @brief ConstantUtil_INPUTヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace INPUT {
	namespace CLASS_NAME {
	}
	namespace RESOURCE_NAME {
	}
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::INPUT::RESOURCE_TYPE::COUNT);
	enum class TASK_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT TASK_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::INPUT::TASK_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		NONE = 0U,
		BASE,
		MOUSE_DEVICE,
		KEYBOARD_DEVICE,
		USER,
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::COUNT);
	enum class MOUSE_DEVICE_EVENT_DATA_TYPE : UINT {
		NONE = 0U,
		LEFT_BUTTON_DOWN = RI_MOUSE_LEFT_BUTTON_DOWN,
		LEFT_BUTTON_UP = RI_MOUSE_LEFT_BUTTON_UP,
		RIGHT_BUTTON_DOWN = RI_MOUSE_RIGHT_BUTTON_DOWN,
		RIGHT_BUTTON_UP = RI_MOUSE_RIGHT_BUTTON_UP,
		MIDDLE_BUTTON_DOWN = RI_MOUSE_MIDDLE_BUTTON_DOWN,
		MIDDLE_BUTTON_UP = RI_MOUSE_MIDDLE_BUTTON_UP,
		SIDE1_BUTTON_DOWN = RI_MOUSE_BUTTON_4_DOWN,
		SIDE1_BUTTON_UP = RI_MOUSE_BUTTON_4_UP,
		SIDE2_BUTTON_DOWN = RI_MOUSE_BUTTON_5_DOWN,
		SIDE2_BUTTON_UP = RI_MOUSE_BUTTON_5_UP,
		MOVE = 0x00010000U,
		WHEEL = 0x00020000U
	};
	enum class KEYBOARD_DEVICE_EVENT_DATA_TYPE : UINT {
		NONE = 0U,
		BUTTON_DOWN = 0x00000001U,
		BUTTON_UP = 0x00000002U
	};
	enum class MOUSE_DEVICE_CODE : UINT {
		NONE = 0U,
		LEFT = VK_LBUTTON,
		RIGHT = VK_RBUTTON,
		MIDDLE = VK_MBUTTON,
		SIDE1 = VK_XBUTTON1,
		SIDE2 = VK_XBUTTON2,
		COUNT = 32U
	};
	const UINT MOUSE_DEVICE_CODE_COUNT = static_cast<UINT>(tml::ConstantUtil::INPUT::MOUSE_DEVICE_CODE::COUNT);
	enum class KEYBOARD_DEVICE_CODE : UINT {
		NONE = 0U,
		ESCAPE = VK_ESCAPE,
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,
		NUM0 = 0x30,
		NUM1 = 0x31,
		NUM2 = 0x32,
		NUM3 = 0x33,
		NUM4 = 0x34,
		NUM5 = 0x35,
		NUM6 = 0x36,
		NUM7 = 0x37,
		NUM8 = 0x38,
		NUM9 = 0x39,
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,
		BACK = VK_BACK,
		ENTER = VK_RETURN,
		TAB = VK_TAB,
		CAPS_LOCK = VK_CAPITAL,
		SPACE = VK_SPACE,
		SHIFT = VK_SHIFT,
		CONTROL = VK_CONTROL,
		ALT = VK_MENU,
		LEFT_WINDOWS = VK_LWIN,
		RIGHT_WINDOWS = VK_RWIN,
		KANA = VK_KANA,
		KANJI = VK_KANJI,
		CONVERT = VK_CONVERT,
		NONCONVERT = VK_NONCONVERT,
		PRINT_SCREEN = VK_SNAPSHOT,
		SCROLL_LOCK = VK_SCROLL,
		PAUSE = VK_PAUSE,
		INSERT_ = VK_INSERT,
		DELETE_ = VK_DELETE,
		HOME = VK_HOME,
		END = VK_END,
		PAGE_UP = VK_PRIOR,
		PAGE_DOWN = VK_NEXT,
		UP = VK_UP,
		DOWN = VK_DOWN,
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,
		NUMPAD_NUM0 = VK_NUMPAD0,
		NUMPAD_NUM1 = VK_NUMPAD1,
		NUMPAD_NUM2 = VK_NUMPAD2,
		NUMPAD_NUM3 = VK_NUMPAD3,
		NUMPAD_NUM4 = VK_NUMPAD4,
		NUMPAD_NUM5 = VK_NUMPAD5,
		NUMPAD_NUM6 = VK_NUMPAD6,
		NUMPAD_NUM7 = VK_NUMPAD7,
		NUMPAD_NUM8 = VK_NUMPAD8,
		NUMPAD_NUM9 = VK_NUMPAD9,
		NUMPAD_NUM_LOCK = VK_NUMLOCK,
		NUMPAD_PLUS = VK_ADD,
		NUMPAD_MINUS = VK_SUBTRACT,
		NUMPAD_MULTIPLY = VK_MULTIPLY,
		NUMPAD_DIVIDE = VK_DIVIDE,
		NUMPAD_ENTER = VK_SEPARATOR,
		NUMPAD_DOT = VK_DECIMAL,
		COUNT = 256U
	};
	const UINT KEYBOARD_DEVICE_CODE_COUNT = static_cast<UINT>(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_CODE::COUNT);
}
}
}


TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::INPUT::MOUSE_DEVICE_EVENT_DATA_TYPE, UINT)
TML_ENUM_CLASS_FLAG_OPERATOR(tml::ConstantUtil::INPUT::KEYBOARD_DEVICE_EVENT_DATA_TYPE, UINT)


namespace tml {
namespace input {
class Manager;
class DeviceEvent;
class DeviceEventDesc;
class MouseDeviceEvent;
class MouseDeviceEventDesc;
class KeyboardDeviceEvent;
class KeyboardDeviceEventDesc;
}
}
