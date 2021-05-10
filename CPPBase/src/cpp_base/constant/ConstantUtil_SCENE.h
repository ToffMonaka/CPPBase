/**
 * @file
 * @brief ConstantUtil_SCENEヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
#include "../../lib/tml/constant/ConstantUtil_SCENE.h"


namespace cpp_base {
namespace ConstantUtil {
namespace SCENE {
	enum class SCENE_TYPE : UINT {
		INIT = static_cast<UINT>(tml::ConstantUtil::SCENE::SCENE_TYPE::USER),
		TITLE,
		COUNT
	};
	const UINT SCENE_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::SCENE::SCENE_TYPE::COUNT);
}
}
}


namespace cpp_base {
namespace scene {
class Manager;
}
}
