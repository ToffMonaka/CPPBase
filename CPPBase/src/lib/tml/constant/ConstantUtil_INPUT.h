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
}
}
}
