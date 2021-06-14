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
	const CHAR *const STRING_ARRAY_MB[] = {"", "\r\n", "\r", "\n"};
	const WCHAR *const STRING_ARRAY_W[] = {L"", L"\r\n", L"\r", L"\n"};

	const CHAR *GetStringMB(const tml::ConstantUtil::NEWLINE_CODE::TYPE);
	const WCHAR *GetStringW(const tml::ConstantUtil::NEWLINE_CODE::TYPE);
}
}
}


/**
 * @brief GetStringMB関数
 * @param type (type)
 * @return str (string)
 */
inline const CHAR *tml::ConstantUtil::NEWLINE_CODE::GetStringMB(const tml::ConstantUtil::NEWLINE_CODE::TYPE type)
{
	return (tml::ConstantUtil::NEWLINE_CODE::STRING_ARRAY_MB[static_cast<size_t>(type)]);
}


/**
 * @brief GetStringW関数
 * @param type (type)
 * @return str (string)
 */
inline const WCHAR *tml::ConstantUtil::NEWLINE_CODE::GetStringW(const tml::ConstantUtil::NEWLINE_CODE::TYPE type)
{
	return (tml::ConstantUtil::NEWLINE_CODE::STRING_ARRAY_W[static_cast<size_t>(type)]);
}
