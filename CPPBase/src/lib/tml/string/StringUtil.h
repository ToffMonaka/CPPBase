/**
 * @file
 * @brief StringUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
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
	static std::string old_locale_name_;
	static bool old_locale_flg_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::StringUtilEngine> &);

	static bool CheckThreadFix(void);
	static std::vector<std::string> &Split(std::vector<std::string> &, const CHAR *, const CHAR *);
	static std::vector<std::wstring> &Split(std::vector<std::wstring> &, const WCHAR *, const WCHAR *);
	static std::list<std::string> &Split(std::list<std::string> &, const CHAR *, const CHAR *);
	static std::list<std::wstring> &Split(std::list<std::wstring> &, const WCHAR *, const WCHAR *);
	static std::string &Join(std::string &, const std::vector<std::string> &, const CHAR *);
	static std::wstring &Join(std::wstring &, const std::vector<std::wstring> &, const WCHAR *);
	static std::string &Join(std::string &, const std::list<std::string> &, const CHAR *);
	static std::wstring &Join(std::wstring &, const std::list<std::wstring> &, const WCHAR *);
	static INT GetValue(INT &, const CHAR *, const INT radix = 10);
	static INT GetValue(INT &, const WCHAR *, const INT radix = 10);
	static UINT GetValue(UINT &, const CHAR *, const INT radix = 10);
	static UINT GetValue(UINT &, const WCHAR *, const INT radix = 10);
	static LONGLONG GetValue(LONGLONG &, const CHAR *, const INT radix = 10);
	static LONGLONG GetValue(LONGLONG &, const WCHAR *, const INT radix = 10);
	static ULONGLONG GetValue(ULONGLONG &, const CHAR *, const INT radix = 10);
	static ULONGLONG GetValue(ULONGLONG &, const WCHAR *, const INT radix = 10);
	static FLOAT GetValue(FLOAT &, const CHAR *);
	static FLOAT GetValue(FLOAT &, const WCHAR *);
	static DOUBLE GetValue(DOUBLE &, const CHAR *);
	static DOUBLE GetValue(DOUBLE &, const WCHAR *);
	static std::string &GetString(std::string &, const WCHAR *);
	static std::wstring &GetString(std::wstring &, const CHAR *);
	static const CHAR *GetString(const std::string *);
	static const WCHAR *GetString(const std::wstring *);
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
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline INT tml::StringUtil::GetValue(INT &dst_val, const CHAR *str, const INT radix)
{
	dst_val = 0;

	if (str == nullptr) {
		return (dst_val);
	}

	CHAR *end_p = nullptr;
	auto val = static_cast<INT>(std::strtol(str, &end_p, radix));

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline INT tml::StringUtil::GetValue(INT &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = 0;

	if (str == nullptr) {
		return (dst_val);
	}

	WCHAR *end_p = nullptr;
	auto val = static_cast<INT>(std::wcstol(str, &end_p, radix));

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline UINT tml::StringUtil::GetValue(UINT &dst_val, const CHAR *str, const INT radix)
{
	dst_val = 0U;

	if (str == nullptr) {
		return (dst_val);
	}

	CHAR *end_p = nullptr;
	auto val = static_cast<UINT>(std::strtoul(str, &end_p, radix));

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline UINT tml::StringUtil::GetValue(UINT &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = 0U;

	if (str == nullptr) {
		return (dst_val);
	}

	WCHAR *end_p = nullptr;
	auto val = static_cast<UINT>(std::wcstoul(str, &end_p, radix));

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline LONGLONG tml::StringUtil::GetValue(LONGLONG &dst_val, const CHAR *str, const INT radix)
{
	dst_val = 0LL;

	if (str == nullptr) {
		return (dst_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtoll(str, &end_p, radix);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline LONGLONG tml::StringUtil::GetValue(LONGLONG &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = 0LL;

	if (str == nullptr) {
		return (dst_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstoll(str, &end_p, radix);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline ULONGLONG tml::StringUtil::GetValue(ULONGLONG &dst_val, const CHAR *str, const INT radix)
{
	dst_val = 0ULL;

	if (str == nullptr) {
		return (dst_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtoull(str, &end_p, radix);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline ULONGLONG tml::StringUtil::GetValue(ULONGLONG &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = 0ULL;

	if (str == nullptr) {
		return (dst_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstoull(str, &end_p, radix);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return val (value)
 */
inline FLOAT tml::StringUtil::GetValue(FLOAT &dst_val, const CHAR *str)
{
	dst_val = 0.0f;

	if (str == nullptr) {
		return (dst_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtof(str, &end_p);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return val (value)
 */
inline FLOAT tml::StringUtil::GetValue(FLOAT &dst_val, const WCHAR *str)
{
	dst_val = 0.0f;

	if (str == nullptr) {
		return (dst_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstof(str, &end_p);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return val (value)
 */
inline DOUBLE tml::StringUtil::GetValue(DOUBLE &dst_val, const CHAR *str)
{
	dst_val = 0.0;

	if (str == nullptr) {
		return (dst_val);
	}

	CHAR *end_p = nullptr;
	auto val = std::strtod(str, &end_p);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return val (value)
 */
inline DOUBLE tml::StringUtil::GetValue(DOUBLE &dst_val, const WCHAR *str)
{
	dst_val = 0.0;

	if (str == nullptr) {
		return (dst_val);
	}

	WCHAR *end_p = nullptr;
	auto val = std::wcstod(str, &end_p);

	if (end_p != str) {
		dst_val = val;
	}

	return (dst_val);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param str (string)
 * @return str (string)
 */
inline const CHAR *tml::StringUtil::GetString(const std::string *str)
{
	return ((str == nullptr) ? nullptr : str->c_str());
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param str (string)
 * @return str (string)
 */
inline const WCHAR *tml::StringUtil::GetString(const std::wstring *str)
{
	return ((str == nullptr) ? nullptr : str->c_str());
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
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
 * @param dst_str (dst_string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const DOUBLE val)
{
	dst_str = std::to_wstring(val);

	return (dst_str);
}
