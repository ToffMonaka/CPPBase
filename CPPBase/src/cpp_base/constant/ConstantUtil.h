/**
 * @file
 * @brief ConstantUtilヘッダーファイル
 */
#pragma once


#include "../../lib/tml/constant/ConstantUtil.h"


namespace cpp_base {
}


namespace cpp_base {
namespace ConstantUtil {
namespace APPLICATION {
#if defined(DEBUG) || defined(_DEBUG)
	const bool DEBUG_FLAG = true;
#else
	const bool DEBUG_FLAG = false;
#endif
	const WCHAR NAME[] = L"CPP ベースプロジェクト";
	const WCHAR COMPANY_NAME[] = L"Toff Monaka Project";
	const WCHAR VERSION_NAME[] = L"1.0.0";
}
}
}
