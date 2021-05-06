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
		SCENE,
		NODE,
		USER,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::COUNT);
	enum class SCENE_TYPE : UINT {
		NONE = 0U,
		ETC,
		USER,
		COUNT
	};
	const UINT SCENE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::SCENE_TYPE::COUNT);
	enum class NODE_TYPE : UINT {
		NONE = 0U,
		ETC,
		OBJECT_2D,
		USER,
		COUNT
	};
	const UINT NODE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::NODE_TYPE::COUNT);
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
