/**
 * @file
 * @brief ConstantUtil_NEWLINE_CODEヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace NEWLINE_CODE {
	enum class TYPE : UINT {
		NONE = 0U,
		CRLF,
		CR,
		LF
	};
	const WCHAR *const STRING_ARRAY[] = {L"", L"\r\n", L"\r", L"\n"};

	const WCHAR *GetString(const tml::ConstantUtil::NEWLINE_CODE::TYPE);
}
}
}


/**
 * @brief GetNewlineCodeString関数
 * @param type (type)
 * @return newline_code_str (newline_code_string)
 */
inline const WCHAR *tml::ConstantUtil::NEWLINE_CODE::GetString(const tml::ConstantUtil::NEWLINE_CODE::TYPE type)
{
	return (tml::ConstantUtil::NEWLINE_CODE::STRING_ARRAY[static_cast<size_t>(type)]);
}
