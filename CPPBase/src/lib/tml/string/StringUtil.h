/**
 * @file
 * @brief StringUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <list>
#include "../util/Util.h"
#include "StringUtilEngine.h"


namespace tml {
/**
 * @brief StringUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
 */
class StringUtil
{
public: StringUtil() = delete;
public: StringUtil(const tml::StringUtil &) = delete;
public: tml::StringUtil &operator =(const tml::StringUtil &) = delete;

private:
	static std::unique_ptr<tml::StringUtilEngine> engine_;
	static std::string old_locale_name_;
	static bool locale_created_flg_;

private:
	static INT CreateLocale(const CHAR *);
	static void DeleteLocale(void);

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::StringUtilEngine> &);

	static bool CheckFixedThread(void);
	static std::vector<std::string> &Split(std::vector<std::string> &, const CHAR *, const CHAR *);
	static std::vector<std::wstring> &Split(std::vector<std::wstring> &, const WCHAR *, const WCHAR *);
	static std::list<std::string> &Split(std::list<std::string> &, const CHAR *, const CHAR *);
	static std::list<std::wstring> &Split(std::list<std::wstring> &, const WCHAR *, const WCHAR *);
	static std::string &Join(std::string &, const std::vector<std::string> &, const CHAR *);
	static std::wstring &Join(std::wstring &, const std::vector<std::wstring> &, const WCHAR *);
	static std::string &Join(std::string &, const std::list<std::string> &, const CHAR *);
	static std::wstring &Join(std::wstring &, const std::list<std::wstring> &, const WCHAR *);
	static INT GetINT(const CHAR *, const INT radix = 10);
	static INT GetINT(const WCHAR *, const INT radix = 10);
	static UINT GetUINT(const CHAR *, const INT radix = 10);
	static UINT GetUINT(const WCHAR *, const INT radix = 10);
	static LONGLONG GetLONGLONG(const CHAR *, const INT radix = 10);
	static LONGLONG GetLONGLONG(const WCHAR *, const INT radix = 10);
	static ULONGLONG GetULONGLONG(const CHAR *, const INT radix = 10);
	static ULONGLONG GetULONGLONG(const WCHAR *, const INT radix = 10);
	static FLOAT GetFLOAT(const CHAR *);
	static FLOAT GetFLOAT(const WCHAR *);
	static DOUBLE GetDOUBLE(const CHAR *);
	static DOUBLE GetDOUBLE(const WCHAR *);
	static bool GetBool(const CHAR *);
	static bool GetBool(const WCHAR *);
	static INT &GetValue(INT &, const CHAR *, const INT radix = 10);
	static INT &GetValue(INT &, const WCHAR *, const INT radix = 10);
	static UINT &GetValue(UINT &, const CHAR *, const INT radix = 10);
	static UINT &GetValue(UINT &, const WCHAR *, const INT radix = 10);
	static LONGLONG &GetValue(LONGLONG &, const CHAR *, const INT radix = 10);
	static LONGLONG &GetValue(LONGLONG &, const WCHAR *, const INT radix = 10);
	static ULONGLONG &GetValue(ULONGLONG &, const CHAR *, const INT radix = 10);
	static ULONGLONG &GetValue(ULONGLONG &, const WCHAR *, const INT radix = 10);
	static FLOAT &GetValue(FLOAT &, const CHAR *);
	static FLOAT &GetValue(FLOAT &, const WCHAR *);
	static DOUBLE &GetValue(DOUBLE &, const CHAR *);
	static DOUBLE &GetValue(DOUBLE &, const WCHAR *);
	static bool &GetValue(bool &, const CHAR *);
	static bool &GetValue(bool &, const WCHAR *);
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
	static std::string &GetString(std::string &, const bool);
	static std::wstring &GetString(std::wstring &, const bool);
	static std::string &GetString(std::string &, const WCHAR *);
	static std::wstring &GetString(std::wstring &, const CHAR *);
};
}


/**
 * @brief CheckFixedThread�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::StringUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}


/**
 * @brief GetINT�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline INT tml::StringUtil::GetINT(const CHAR *str, const INT radix)
{
	INT val = 0;

	if (str == nullptr) {
		return (val);
	}

	CHAR *end_p = nullptr;

	val = static_cast<INT>(std::strtol(str, &end_p, radix));

	return ((end_p == str) ? 0 : val);
}


/**
 * @brief GetINT�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline INT tml::StringUtil::GetINT(const WCHAR *str, const INT radix)
{
	INT val = 0;

	if (str == nullptr) {
		return (val);
	}

	WCHAR *end_p = nullptr;

	val = static_cast<INT>(std::wcstol(str, &end_p, radix));

	return ((end_p == str) ? 0 : val);
}


/**
 * @brief GetUINT�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline UINT tml::StringUtil::GetUINT(const CHAR *str, const INT radix)
{
	UINT val = 0U;

	if (str == nullptr) {
		return (val);
	}

	CHAR *end_p = nullptr;

	val = static_cast<UINT>(std::strtoul(str, &end_p, radix));

	return ((end_p == str) ? 0U : val);
}


/**
 * @brief GetUINT�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline UINT tml::StringUtil::GetUINT(const WCHAR *str, const INT radix)
{
	UINT val = 0U;

	if (str == nullptr) {
		return (val);
	}

	WCHAR *end_p = nullptr;

	val = static_cast<UINT>(std::wcstoul(str, &end_p, radix));

	return ((end_p == str) ? 0U : val);
}


/**
 * @brief GetLONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline LONGLONG tml::StringUtil::GetLONGLONG(const CHAR *str, const INT radix)
{
	LONGLONG val = 0LL;

	if (str == nullptr) {
		return (val);
	}

	CHAR *end_p = nullptr;

	val = std::strtoll(str, &end_p, radix);

	return ((end_p == str) ? 0LL : val);
}


/**
 * @brief GetLONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline LONGLONG tml::StringUtil::GetLONGLONG(const WCHAR *str, const INT radix)
{
	LONGLONG val = 0LL;

	if (str == nullptr) {
		return (val);
	}

	WCHAR *end_p = nullptr;

	val = std::wcstoll(str, &end_p, radix);

	return ((end_p == str) ? 0LL : val);
}


/**
 * @brief GetULONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline ULONGLONG tml::StringUtil::GetULONGLONG(const CHAR *str, const INT radix)
{
	ULONGLONG val = 0ULL;

	if (str == nullptr) {
		return (val);
	}

	CHAR *end_p = nullptr;

	val = std::strtoull(str, &end_p, radix);

	return ((end_p == str) ? 0ULL : val);
}


/**
 * @brief GetULONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @param radix (radix)
 * @return val (value)
 */
inline ULONGLONG tml::StringUtil::GetULONGLONG(const WCHAR *str, const INT radix)
{
	ULONGLONG val = 0ULL;

	if (str == nullptr) {
		return (val);
	}

	WCHAR *end_p = nullptr;

	val = std::wcstoull(str, &end_p, radix);

	return ((end_p == str) ? 0ULL : val);
}


/**
 * @brief GetFLOAT�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return val (value)
 */
inline FLOAT tml::StringUtil::GetFLOAT(const CHAR *str)
{
	FLOAT val = 0.0f;

	if (str == nullptr) {
		return (val);
	}

	CHAR *end_p = nullptr;

	val = std::strtof(str, &end_p);

	return ((end_p == str) ? 0.0f : val);
}


/**
 * @brief GetFLOAT�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return val (value)
 */
inline FLOAT tml::StringUtil::GetFLOAT(const WCHAR *str)
{
	FLOAT val = 0.0f;

	if (str == nullptr) {
		return (val);
	}

	WCHAR *end_p = nullptr;

	val = std::wcstof(str, &end_p);

	return ((end_p == str) ? 0.0f : val);
}


/**
 * @brief GetDOUBLE�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return val (value)
 */
inline DOUBLE tml::StringUtil::GetDOUBLE(const CHAR *str)
{
	DOUBLE val = 0.0;

	if (str == nullptr) {
		return (val);
	}

	CHAR *end_p = nullptr;

	val = std::strtod(str, &end_p);

	return ((end_p == str) ? 0.0 : val);
}


/**
 * @brief GetDOUBLE�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return val (value)
 */
inline DOUBLE tml::StringUtil::GetDOUBLE(const WCHAR *str)
{
	DOUBLE val = 0.0;

	if (str == nullptr) {
		return (val);
	}

	WCHAR *end_p = nullptr;

	val = std::wcstod(str, &end_p);

	return ((end_p == str) ? 0.0 : val);
}


/**
 * @brief GetBool�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return val (value)
 */
inline bool tml::StringUtil::GetBool(const CHAR *str)
{
	return (tml::StringUtil::GetINT(str));
}


/**
 * @brief GetBool�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return val (value)
 */
inline bool tml::StringUtil::GetBool(const WCHAR *str)
{
	return (tml::StringUtil::GetINT(str));
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline INT &tml::StringUtil::GetValue(INT &dst_val, const CHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetINT(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline INT &tml::StringUtil::GetValue(INT &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetINT(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline UINT &tml::StringUtil::GetValue(UINT &dst_val, const CHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetUINT(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline UINT &tml::StringUtil::GetValue(UINT &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetUINT(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::StringUtil::GetValue(LONGLONG &dst_val, const CHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetLONGLONG(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::StringUtil::GetValue(LONGLONG &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetLONGLONG(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::StringUtil::GetValue(ULONGLONG &dst_val, const CHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetULONGLONG(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @param radix (radix)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::StringUtil::GetValue(ULONGLONG &dst_val, const WCHAR *str, const INT radix)
{
	dst_val = tml::StringUtil::GetULONGLONG(str, radix);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::StringUtil::GetValue(FLOAT &dst_val, const CHAR *str)
{
	dst_val = tml::StringUtil::GetFLOAT(str);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::StringUtil::GetValue(FLOAT &dst_val, const WCHAR *str)
{
	dst_val = tml::StringUtil::GetFLOAT(str);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::StringUtil::GetValue(DOUBLE &dst_val, const CHAR *str)
{
	dst_val = tml::StringUtil::GetDOUBLE(str);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::StringUtil::GetValue(DOUBLE &dst_val, const WCHAR *str)
{
	dst_val = tml::StringUtil::GetDOUBLE(str);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return dst_val (dst_value)
 */
inline bool &tml::StringUtil::GetValue(bool &dst_val, const CHAR *str)
{
	dst_val = tml::StringUtil::GetBool(str);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param str (string)
 * @return dst_val (dst_value)
 */
inline bool &tml::StringUtil::GetValue(bool &dst_val, const WCHAR *str)
{
	dst_val = tml::StringUtil::GetBool(str);

	return (dst_val);
}


/**
 * @brief GetString�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return str (string)
 */
inline const CHAR *tml::StringUtil::GetString(const std::string *str)
{
	return ((str == nullptr) ? nullptr : str->c_str());
}


/**
 * @brief GetString�֐�
 *
 * Create�֐��s�v
 *
 * @param str (string)
 * @return str (string)
 */
inline const WCHAR *tml::StringUtil::GetString(const std::wstring *str)
{
	return ((str == nullptr) ? nullptr : str->c_str());
}


/**
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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
 * @brief GetString�֐�
 *
 * Create�֐��s�v
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


/**
 * @brief GetString�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_str (dst_string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::string &tml::StringUtil::GetString(std::string &dst_str, const bool val)
{
	return (tml::StringUtil::GetString(dst_str, static_cast<INT>(val)));
}


/**
 * @brief GetString�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_str (dst_string)
 * @param val (value)
 * @return dst_str (dst_string)
 */
inline std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const bool val)
{
	return (tml::StringUtil::GetString(dst_str, static_cast<INT>(val)));
}
