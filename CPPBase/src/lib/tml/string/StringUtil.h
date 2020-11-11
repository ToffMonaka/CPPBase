/**
 * @file
 * @brief StringUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "StringUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief StringUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class StringUtil
{
public: StringUtil() = delete;
public: StringUtil(const StringUtil &) = delete;
public: StringUtil &operator =(const StringUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::StringUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::StringUtilEngine> &);

	static INT GetINT(const CHAR *, const INT default_val = 0, const INT radix = 10);
	static INT GetINT(const WCHAR *, const INT default_val = 0, const INT radix = 10);
	static LONGLONG GetLONGLONG(const CHAR *, const LONGLONG default_val = 0LL, const INT radix = 10);
	static LONGLONG GetLONGLONG(const WCHAR *, const LONGLONG default_val = 0LL, const INT radix = 10);
	static UINT GetUINT(const CHAR *, const UINT default_val = 0U, const INT radix = 10);
	static UINT GetUINT(const WCHAR *, const UINT default_val = 0U, const INT radix = 10);
	static ULONGLONG GetULONGLONG(const CHAR *, const ULONGLONG default_val = 0ULL, const INT radix = 10);
	static ULONGLONG GetULONGLONG(const WCHAR *, const ULONGLONG default_val = 0ULL, const INT radix = 10);
	static FLOAT GetFLOAT(const CHAR *, const FLOAT default_val = 0.0f);
	static FLOAT GetFLOAT(const WCHAR *, const FLOAT default_val = 0.0f);
	static DOUBLE GetDOUBLE(const CHAR *, const DOUBLE default_val = 0.0);
	static DOUBLE GetDOUBLE(const WCHAR *, const DOUBLE default_val = 0.0);
};
}


/**
 * @brief GetINT関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline INT tml::StringUtil::GetINT(const CHAR *str, const INT default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	CHAR *end_p = nullptr;
	auto val = static_cast<INT>(std::strtol(str, &end_p, radix));

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetINT関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline INT tml::StringUtil::GetINT(const WCHAR *str, const INT default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	WCHAR *end_p = nullptr;
	auto val = static_cast<INT>(std::wcstol(str, &end_p, radix));

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetLONGLONG関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline LONGLONG tml::StringUtil::GetLONGLONG(const CHAR *str, const LONGLONG default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtoll(str, &end_p, radix);

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetLONGLONG関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline LONGLONG tml::StringUtil::GetLONGLONG(const WCHAR *str, const LONGLONG default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstoll(str, &end_p, radix);

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetUINT関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline UINT tml::StringUtil::GetUINT(const CHAR *str, const UINT default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	CHAR *end_p = nullptr;
	auto val = static_cast<UINT>(std::strtoul(str, &end_p, radix));

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetUINT関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline UINT tml::StringUtil::GetUINT(const WCHAR *str, const UINT default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	WCHAR *end_p = nullptr;
	auto val = static_cast<UINT>(std::wcstoul(str, &end_p, radix));

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetULONGLONG関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline ULONGLONG tml::StringUtil::GetULONGLONG(const CHAR *str, const ULONGLONG default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtoull(str, &end_p, radix);

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetULONGLONG関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @param radix (radix)
 * @return val (value)
 */
inline ULONGLONG tml::StringUtil::GetULONGLONG(const WCHAR *str, const ULONGLONG default_val, const INT radix)
{
	if (str == nullptr) {
		return (default_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstoull(str, &end_p, radix);

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetFLOAT関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @return val (value)
 */
inline FLOAT tml::StringUtil::GetFLOAT(const CHAR *str, const FLOAT default_val)
{
	if (str == nullptr) {
		return (default_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtof(str, &end_p);

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetFLOAT関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @return val (value)
 */
inline FLOAT tml::StringUtil::GetFLOAT(const WCHAR *str, const FLOAT default_val)
{
	if (str == nullptr) {
		return (default_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstof(str, &end_p);

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetDOUBLE関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @return val (value)
 */
inline DOUBLE tml::StringUtil::GetDOUBLE(const CHAR *str, const DOUBLE default_val)
{
	if (str == nullptr) {
		return (default_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtod(str, &end_p);

	return ((end_p == str) ? default_val : val);
}


/**
 * @brief GetDOUBLE関数
 *
 * エンジン不要
 *
 * @param str (string)
 * @param default_val (default_value)
 * @return val (value)
 */
inline DOUBLE tml::StringUtil::GetDOUBLE(const WCHAR *str, const DOUBLE default_val)
{
	if (str == nullptr) {
		return (default_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstod(str, &end_p);

	return ((end_p == str) ? default_val : val);
}
