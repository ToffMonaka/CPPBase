/**
 * @file
 * @brief ConstantUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "ConstantInclude_ConstantUtilBase.h"


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
	const WCHAR NAME[] = L"CPP �x�[�X�v���W�F�N�g";
	const WCHAR COMPANY_NAME[] = L"Toff Monaka Project";
	const WCHAR VERSION_NAME[] = L"1.0.0";
}
}
}
