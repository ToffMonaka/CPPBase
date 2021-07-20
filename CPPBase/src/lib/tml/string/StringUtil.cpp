/**
 * @file
 * @brief StringUtilコードファイル
 */


#include "StringUtil.h"
#include <locale>
#include "../memory/MemoryUtil.h"


std::unique_ptr<tml::StringUtilEngine> tml::StringUtil::engine_;
std::string tml::StringUtil::old_locale_name_;
bool tml::StringUtil::locale_created_flg_ = false;


/**
 * @brief Init関数
 */
void tml::StringUtil::Init(void)
{
	if (!tml::StringUtil::CheckFixedThread()) {
		return;
	}

	tml::StringUtil::DeleteLocale();

	tml::StringUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::StringUtil::Create(std::unique_ptr<tml::StringUtilEngine> &engine)
{
	if (!tml::StringUtil::CheckFixedThread()) {
		tml::StringUtil::Init();

		return (-1);
	}

	tml::StringUtil::Init();

	tml::StringUtil::engine_ = std::move(engine);

	if (tml::StringUtil::CreateLocale(tml::StringUtil::engine_->GetLocaleName().c_str()) < 0) {
		tml::StringUtil::Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief CreateLocale関数
 * @param locale_name (locale_name)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::StringUtil::CreateLocale(const CHAR *locale_name)
{
	tml::StringUtil::DeleteLocale();

	try {
		std::locale old_locale = std::locale::global(std::locale(locale_name));

		tml::StringUtil::old_locale_name_ = old_locale.name();
	} catch (std::runtime_error &err) {
		if (tml::ConstantUtil::LIBRARY::DEBUG_FLAG) {
			OutputDebugString(L"Error: Locale Set\n");

			std::cout << err.what() << std::endl;
		}

		return (-1);
	}

	tml::StringUtil::locale_created_flg_ = true;

	return (0);
}


/**
 * @brief DeleteLocale関数
 */
void tml::StringUtil::DeleteLocale(void)
{
	if (!tml::StringUtil::locale_created_flg_) {
		return;
	}

	try {
		std::locale::global(std::locale(tml::StringUtil::old_locale_name_));

		tml::StringUtil::old_locale_name_.clear();
	} catch (std::runtime_error &err) {
		std::cout << err.what() << std::endl;
	}

	tml::StringUtil::locale_created_flg_ = false;

	return;
}


/**
 * @brief Split関数
 *
 * Create関数不要
 *
 * @param dst_str_cont (dst_string_container)
 * @param str (string)
 * @param sep_str (separator_string)
 * @return dst_str_cont (dst_string_container)
 */
std::vector<std::string> &tml::StringUtil::Split(std::vector<std::string> &dst_str_cont, const CHAR *str, const CHAR *sep_str)
{
	dst_str_cont.clear();

	if (str == nullptr) {
		return (dst_str_cont);
	}

	if ((str[0] == 0)
	|| (sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	auto sep_str_len = strlen(sep_str);
	std::string tmp_str = str;
	size_t tmp_str_index = 0U;

	while (1) {
		auto sep_str_index = tmp_str.find(sep_str, tmp_str_index);

		if (sep_str_index == std::string::npos) {
			dst_str_cont.push_back(tmp_str.substr(tmp_str_index));

			break;
		}

		dst_str_cont.push_back(tmp_str.substr(tmp_str_index, sep_str_index - tmp_str_index));

		tmp_str_index = sep_str_index + sep_str_len;
	}

	return (dst_str_cont);
}


/**
 * @brief Split関数
 *
 * Create関数不要
 *
 * @param dst_str_cont (dst_string_container)
 * @param str (string)
 * @param sep_str (separator_string)
 * @return dst_str_cont (dst_string_container)
 */
std::vector<std::wstring> &tml::StringUtil::Split(std::vector<std::wstring> &dst_str_cont, const WCHAR *str, const WCHAR *sep_str)
{
	dst_str_cont.clear();

	if (str == nullptr) {
		return (dst_str_cont);
	}

	if ((str[0] == 0)
	|| (sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	auto sep_str_len = wcslen(sep_str);
	std::wstring tmp_str = str;
	size_t tmp_str_index = 0U;

	while (1) {
		auto sep_str_index = tmp_str.find(sep_str, tmp_str_index);

		if (sep_str_index == std::wstring::npos) {
			dst_str_cont.push_back(tmp_str.substr(tmp_str_index));

			break;
		}

		dst_str_cont.push_back(tmp_str.substr(tmp_str_index, sep_str_index - tmp_str_index));

		tmp_str_index = sep_str_index + sep_str_len;
	}

	return (dst_str_cont);
}


/**
 * @brief Split関数
 *
 * Create関数不要
 *
 * @param dst_str_cont (dst_string_container)
 * @param str (string)
 * @param sep_str (separator_string)
 * @return dst_str_cont (dst_string_container)
 */
std::list<std::string> &tml::StringUtil::Split(std::list<std::string> &dst_str_cont, const CHAR *str, const CHAR *sep_str)
{
	dst_str_cont.clear();

	if (str == nullptr) {
		return (dst_str_cont);
	}

	if ((str[0] == 0)
	|| (sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	auto sep_str_len = strlen(sep_str);
	std::string tmp_str = str;
	size_t tmp_str_index = 0U;

	while (1) {
		auto sep_str_index = tmp_str.find(sep_str, tmp_str_index);

		if (sep_str_index == std::string::npos) {
			dst_str_cont.push_back(tmp_str.substr(tmp_str_index));

			break;
		}

		dst_str_cont.push_back(tmp_str.substr(tmp_str_index, sep_str_index - tmp_str_index));

		tmp_str_index = sep_str_index + sep_str_len;
	}

	return (dst_str_cont);
}


/**
 * @brief Split関数
 *
 * Create関数不要
 *
 * @param dst_str_cont (dst_string_container)
 * @param str (string)
 * @param sep_str (separator_string)
 * @return dst_str_cont (dst_string_container)
 */
std::list<std::wstring> &tml::StringUtil::Split(std::list<std::wstring> &dst_str_cont, const WCHAR *str, const WCHAR *sep_str)
{
	dst_str_cont.clear();

	if (str == nullptr) {
		return (dst_str_cont);
	}

	if ((str[0] == 0)
	|| (sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	auto sep_str_len = wcslen(sep_str);
	std::wstring tmp_str = str;
	size_t tmp_str_index = 0U;

	while (1) {
		auto sep_str_index = tmp_str.find(sep_str, tmp_str_index);

		if (sep_str_index == std::wstring::npos) {
			dst_str_cont.push_back(tmp_str.substr(tmp_str_index));

			break;
		}

		dst_str_cont.push_back(tmp_str.substr(tmp_str_index, sep_str_index - tmp_str_index));

		tmp_str_index = sep_str_index + sep_str_len;
	}

	return (dst_str_cont);
}


/**
 * @brief Join関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param str_cont (string_container)
 * @param sep_str (separator_string)
 * @return dst_str (dst_string)
 */
std::string &tml::StringUtil::Join(std::string &dst_str, const std::vector<std::string> &str_cont, const CHAR *sep_str)
{
	dst_str.clear();

	if ((sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		for (auto &str : str_cont) {
			dst_str += str;
		}

		return (dst_str);
	}

	size_t str_i = 0U;

	for (auto &str : str_cont) {
		if (str_i > 0U) {
			dst_str += sep_str;
		}

		dst_str += str;

		++str_i;
	}

	return (dst_str);
}


/**
 * @brief Join関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param str_cont (string_container)
 * @param sep_str (separator_string)
 * @return dst_str (dst_string)
 */
std::wstring &tml::StringUtil::Join(std::wstring &dst_str, const std::vector<std::wstring> &str_cont, const WCHAR *sep_str)
{
	dst_str.clear();

	if ((sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		for (auto &str : str_cont) {
			dst_str += str;
		}

		return (dst_str);
	}

	size_t str_i = 0U;

	for (auto &str : str_cont) {
		if (str_i > 0U) {
			dst_str += sep_str;
		}

		dst_str += str;

		++str_i;
	}

	return (dst_str);
}


/**
 * @brief Join関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param str_cont (string_container)
 * @param sep_str (separator_string)
 * @return dst_str (dst_string)
 */
std::string &tml::StringUtil::Join(std::string &dst_str, const std::list<std::string> &str_cont, const CHAR *sep_str)
{
	dst_str.clear();

	if ((sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		for (auto &str : str_cont) {
			dst_str += str;
		}

		return (dst_str);
	}

	size_t str_i = 0U;

	for (auto &str : str_cont) {
		if (str_i > 0U) {
			dst_str += sep_str;
		}

		dst_str += str;

		++str_i;
	}

	return (dst_str);
}


/**
 * @brief Join関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param str_cont (string_container)
 * @param sep_str (separator_string)
 * @return dst_str (dst_string)
 */
std::wstring &tml::StringUtil::Join(std::wstring &dst_str, const std::list<std::wstring> &str_cont, const WCHAR *sep_str)
{
	dst_str.clear();

	if ((sep_str == nullptr)
	|| (sep_str[0] == 0)) {
		for (auto &str : str_cont) {
			dst_str += str;
		}

		return (dst_str);
	}

	size_t str_i = 0U;

	for (auto &str : str_cont) {
		if (str_i > 0U) {
			dst_str += sep_str;
		}

		dst_str += str;

		++str_i;
	}

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param str (string)
 * @return dst_str (dst_string)
 */
std::string &tml::StringUtil::GetString(std::string &dst_str, const WCHAR *str)
{
	dst_str.clear();

	if ((str == nullptr)
	|| (str[0] == 0)) {
		return (dst_str);
	}

	size_t tmp_str_size = (wcslen(str) << 1) + 1U;
	CHAR *tmp_str = tml::MemoryUtil::Get<CHAR>(tmp_str_size);

	if (wcstombs_s(nullptr, tmp_str, tmp_str_size, str, _TRUNCATE) == 0) {
		dst_str = tmp_str;
	}

	tml::MemoryUtil::Release(&tmp_str);
	tmp_str_size = 0U;

	return (dst_str);
}


/**
 * @brief GetString関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param str (string)
 * @return dst_str (dst_string)
 */
std::wstring &tml::StringUtil::GetString(std::wstring &dst_str, const CHAR *str)
{
	dst_str.clear();

	if ((str == nullptr)
	|| (str[0] == 0)) {
		return (dst_str);
	}

	size_t tmp_str_size = strlen(str) + 1U;
	WCHAR *tmp_str = tml::MemoryUtil::Get<WCHAR>(tmp_str_size);

	if (mbstowcs_s(nullptr, tmp_str, tmp_str_size, str, _TRUNCATE) == 0) {
		dst_str = tmp_str;
	}

	tml::MemoryUtil::Release(&tmp_str);
	tmp_str_size = 0U;

	return (dst_str);
}
