/**
 * @file
 * @brief StringUtilコードファイル
 */


#include "StringUtil.h"
#include <locale>
#include "../memory/MemoryUtil.h"


tml::ThreadFix tml::StringUtil::th_fix_;
std::unique_ptr<tml::StringUtilEngine> tml::StringUtil::engine_;
std::string tml::StringUtil::old_local_name_;
bool tml::StringUtil::old_local_flg_ = false;


/**
 * @brief Init関数
 */
void tml::StringUtil::Init(void)
{
	if (!tml::StringUtil::th_fix_.Check()) {
		return;
	}

	if (tml::StringUtil::old_local_flg_) {
		try {
			std::locale::global(std::locale(tml::StringUtil::old_local_name_));
		} catch (std::runtime_error &e) {
			std::cout << e.what() << std::endl;
		}

		tml::StringUtil::old_local_name_.clear();
		tml::StringUtil::old_local_flg_ = false;
	}

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
	if (!tml::StringUtil::th_fix_.Check()) {
		tml::StringUtil::Init();

		return (-1);
	}

	tml::StringUtil::Init();

	tml::StringUtil::engine_ = std::move(engine);

	try {
		std::locale old_local = std::locale::global(std::locale(tml::StringUtil::engine_->GetLocaleName()));

		tml::StringUtil::old_local_name_ = old_local.name();
		tml::StringUtil::old_local_flg_ = true;
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;

		tml::StringUtil::Init();

		return (-1);
	}

	return (0);
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

	if (sep_str == nullptr) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	auto sep_str_len = strlen(sep_str);

	if (sep_str_len <= 0U) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	std::string tmp_str = str;
	size_t tmp_str_index = 0U;

	if (tmp_str.length() <= 0U) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

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

	if (sep_str == nullptr) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	auto sep_str_len = wcslen(sep_str);

	if (sep_str_len <= 0U) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

	std::wstring tmp_str = str;
	size_t tmp_str_index = 0U;

	if (tmp_str.length() <= 0U) {
		dst_str_cont.push_back(str);

		return (dst_str_cont);
	}

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

	CHAR *tmp_str = nullptr;
	size_t tmp_str_size = (wcslen(str) << 1) + 1U;

	tmp_str = tml::MemoryUtil::Get<CHAR>(tmp_str_size);

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

	WCHAR *tmp_str = nullptr;
	size_t tmp_str_size = strlen(str) + 1U;

	tmp_str = tml::MemoryUtil::Get<WCHAR>(tmp_str_size);

	if (mbstowcs_s(nullptr, tmp_str, tmp_str_size, str, _TRUNCATE) == 0) {
		dst_str = tmp_str;
	}

	tml::MemoryUtil::Release(&tmp_str);
	tmp_str_size = 0U;

	return (dst_str);
}
