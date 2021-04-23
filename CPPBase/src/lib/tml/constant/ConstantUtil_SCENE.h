/**
 * @file
 * @brief ConstantUtil_SCENEヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace SCENE {
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::EVENT_TYPE::COUNT);
}
}
}
