/**
 * @file
 * @brief ConstantUtil_INPUT�w�b�_�[�t�@�C��
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
}
}
}
