/**
 * @file
 * @brief ConstantUtil_APPLICATIONヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace cpp_base {
namespace ConstantUtil {
namespace APPLICATION {
#ifdef _DEBUG
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
