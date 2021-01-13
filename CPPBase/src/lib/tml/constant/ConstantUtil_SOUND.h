/**
 * @file
 * @brief ConstantUtil_SOUNDヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace SOUND {
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::COUNT);
}
}
}
