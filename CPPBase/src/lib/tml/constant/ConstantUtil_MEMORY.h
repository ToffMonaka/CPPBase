/**
 * @file
 * @brief ConstantUtil_MEMORYヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace MEMORY {
	enum class ALLOCATOR_TYPE : UINT {
		NONE = 0U,
		NEW,
		DLMALLOC
	};
}
}
}
