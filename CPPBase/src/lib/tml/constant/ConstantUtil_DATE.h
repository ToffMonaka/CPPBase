/**
 * @file
 * @brief ConstantUtil_DATEヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace DATE {
	enum class WEEK_DAY : UCHAR {
		SUNDAY = 0,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY
	};
	const size_t STRING_LENGTH = 19U;
	const CHAR ZERO_STRING_MB[] = "0000-00-00 00:00:00";
	const WCHAR ZERO_STRING_W[] = L"0000-00-00 00:00:00";
}
}
}
