/**
 * @file
 * @brief ConstantUtil_INPUTヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace INPUT {
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::INPUT::RESOURCE_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		NONE = 0U,
		MOUSE,
		KEYBOARD,
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::COUNT);
	enum class MOUSE_EVENT_DATA_TYPE : UINT {
		NONE = 0U,
		LEFT_BUTTON_DOWN,
		LEFT_BUTTON_UP,
		RIGHT_BUTTON_DOWN,
		RIGHT_BUTTON_UP,
		MIDDLE_BUTTON_DOWN,
		MIDDLE_BUTTON_UP
	};
}
}
}
