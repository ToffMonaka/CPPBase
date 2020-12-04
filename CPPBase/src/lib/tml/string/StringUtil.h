/**
 * @file
 * @brief StringUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
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
public: StringUtil(const tml::StringUtil &) = delete;
public: tml::StringUtil &operator =(const tml::StringUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::StringUtilEngine> engine_;
	static std::string old_local_name_;
	static bool old_local_flg_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::StringUtilEngine> &);

	static bool CheckThreadFix(void);
	static std::list<std::string> &Split(std::list<std::string> &, const CHAR *, const CHAR *);
	static std::list<std::wstring> &Split(std::list<std::wstring> &, const WCHAR *, const WCHAR *);
	static std::string &Join(std::string &, const std::list<std::string> &, const CHAR *);
	static std::wstring &Join(std::wstring &, const std::list<std::wstring> &, const WCHAR *);
	static INT GetINT(const CHAR *, const INT default_val = 0, const INT radix = 10);
	static INT GetINT(const WCHAR *, const INT default_val = 0, const INT radix = 10);
	static UINT GetUINT(const CHAR *, const UINT default_val = 0U, const INT radix = 10);
	static UINT GetUINT(const WCHAR *, const UINT default_val = 0U, const INT radix = 10);
	static LONGLONG GetLONGLONG(const CHAR *, const LONGLONG default_val = 0LL, const INT radix = 10);
	static LONGLONG GetLONGLONG(const WCHAR *, const LONGLONG default_val = 0LL, const INT radix = 10);
	static ULONGLONG GetULONGLONG(const CHAR *, const ULONGLONG default_val = 0ULL, const INT radix = 10);
	static ULONGLONG GetULONGLONG(const WCHAR *, const ULONGLONG default_val = 0ULL, const INT radix = 10);
	static FLOAT GetFLOAT(const CHAR *, const FLOAT default_val = 0.0f);
	static FLOAT GetFLOAT(const WCHAR *, const FLOAT default_val = 0.0f);
	static DOUBLE GetDOUBLE(const CHAR *, const DOUBLE default_val = 0.0);
	static DOUBLE GetDOUBLE(const WCHAR *, const DOUBLE default_val = 0.0);
	static std::string &GetString(std::string &, const INT);
	static std::wstring &GetString(std::wstring &, const INT);
	static std::string &GetString(std::string &, const UINT);
	static std::wstring &GetString(std::wstring &, const UINT);
	static std::string &GetString(std::string &, const LONGLONG);
	static std::wstring &GetString(std::wstring &, const LONGLONG);
	static std::string &GetString(std::string &, const ULONGLONG);
	static std::wstring &GetString(std::wstring &, const ULONGLONG);
	static std::string &GetString(std::string &, const FLOAT);
	static std::wstring &GetString(std::wstring &, const FLOAT);
	static std::string &GetString(std::string &, const DOUBLE);
	static std::wstring &GetString(std::wstring &, const DOUBLE);
	static std::string &GetString(std::string &, const WCHAR *);
	static std::wstring &GetString(std::wstring &, const CHAR *);
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::StringUtil::CheckThreadFix(void)
{
	return (tml::StringUtil::th_fix_.Check());
}


/**
 * @brief GetINT関数
 *
 * Create関数不要
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
 * Create関数不要
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
 * @brief GetUINT関数
 *
 * Create関数不要
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
 * Create関数不要
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
 * @brief GetLONGLONG関数
 *
 * Create関数不要
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
 * Create関数不要
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
 * @brief GetULONGLONG関数
 *
 * Create関数不要
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
 * Create関数不要
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
 * Create関数不要
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
 * Create関数不要
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
 * Create関数不要
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
 * Create関数不要
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


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::string &tml::StringUtil::GetString(std::string &dst_str, const INT val)
{
	dst_str = std::to_string(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const INT val)
{
	dst_str = std::to_wstring(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::string &tml::StringUtil::GetString(std::string &dst_str, const UINT val)
{
	dst_str = std::to_string(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const UINT val)
{
	dst_str = std::to_wstring(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::string &tml::StringUtil::GetString(std::string &dst_str, const LONGLONG val)
{
	dst_str = std::to_string(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const LONGLONG val)
{
	dst_str = std::to_wstring(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::string &tml::StringUtil::GetString(std::string &dst_str, const ULONGLONG val)
{
	dst_str = std::to_string(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const ULONGLONG val)
{
	dst_str = std::to_wstring(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::string &tml::StringUtil::GetString(std::string &dst_str, const FLOAT val)
{
	dst_str = std::to_string(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const FLOAT val)
{
	dst_str = std::to_wstring(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::string &tml::StringUtil::GetString(std::string &dst_str, const DOUBLE val)
{
	dst_str = std::to_string(val);

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const DOUBLE val)
{
	dst_str = std::to_wstring(val);

	return (dst_str);
}
