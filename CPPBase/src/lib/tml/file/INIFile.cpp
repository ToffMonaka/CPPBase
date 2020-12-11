/**
 * @file
 * @brief INIFileコードファイル
 */


#include "INIFile.h"
#include <regex>
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::INIFileData::INIFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileData::~INIFileData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileData::Init(void)
{
	this->value_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFileReadPlan::INIFileReadPlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileReadPlan::~INIFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileReadPlan::Init(void)
{
	tml::TextFileReadPlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFileWritePlan::INIFileWritePlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileWritePlan::~INIFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileWritePlan::Init(void)
{
	tml::TextFileWritePlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFile::INIFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFile::~INIFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::INIFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::INIFile::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_plan.Init();
	this->write_plan.Init();

	return;
}


/**
 * @brief Read関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::INIFile::Read(void)
{
	tml::TextFile txt_file;

	if (this->read_plan.file_path.empty()) {
		txt_file.read_plan.file_path = this->read_plan.file_path;
		txt_file.read_plan.file_buffer = std::move(this->read_plan.file_buffer);
		txt_file.read_plan.one_buffer_size = this->read_plan.one_buffer_size;
		txt_file.read_plan.newline_code_type = this->read_plan.newline_code_type;

		if (txt_file.Read()) {
			this->read_plan.file_buffer = std::move(txt_file.read_plan.file_buffer);

			return (-1);
		}

		this->read_plan.file_buffer = std::move(txt_file.read_plan.file_buffer);
	} else {
		txt_file.read_plan.file_path = this->read_plan.file_path;
		txt_file.read_plan.one_buffer_size = this->read_plan.one_buffer_size;
		txt_file.read_plan.newline_code_type = this->read_plan.newline_code_type;

		if (txt_file.Read()) {
			return (-1);
		}
	}

	this->data.Init();

	if (txt_file.data.string_container.empty()) {
		return (0);
	}

	std::wstring empty_str = L"";
	std::wregex needless_pattern(L"^[\\s|　]+|[\\s|　]+$");
	std::wstring comment_str = L";";
	size_t comment_str_index = 0U;
	std::wstring section_start_str = L"[";
	size_t section_start_str_index = 0U;
	std::wstring section_end_str = L"]";
	size_t section_end_str_index = 0U;
	std::wstring equal_str = L"=";
	size_t equal_str_index = 0U;
	std::wstring section_name;
	std::wstring tmp_section_name;
	std::wstring val_name;
	std::wstring val;

	for (auto txt_str : txt_file.data.string_container) {
		if (txt_str.empty()) {
			continue;
		}

		{// コメントを削除
			comment_str_index = txt_str.find(comment_str);

			if (comment_str_index != std::wstring::npos) {
				txt_str.erase(comment_str_index);
			}
		}

		if (txt_str.empty()) {
			continue;
		}

		{// ｢=｣を確認
			equal_str_index = txt_str.find(equal_str);

			if (equal_str_index == std::wstring::npos) {
				section_start_str_index = txt_str.find(section_start_str);

				if (section_start_str_index == std::wstring::npos) {
					continue;
				}

				section_end_str_index = txt_str.find(section_end_str, section_start_str_index + section_start_str.length());

				if (section_end_str_index == std::wstring::npos) {
					continue;
				}

				tmp_section_name = txt_str.substr(section_start_str_index + section_start_str.length(), section_end_str_index - (section_start_str_index + section_start_str.length()));

				if (!tmp_section_name.empty()) {
					section_name = tmp_section_name;

					auto val_name_itr = this->data.value_container.find(section_name);

					if (val_name_itr == this->data.value_container.end()) {
						std::map<std::wstring, std::wstring> val_name_cont;

						this->data.value_container.insert(std::make_pair(section_name, val_name_cont));
					}
				}

				continue;
			}
		}

		auto val_name_itr = this->data.value_container.find(section_name);

		if (val_name_itr == this->data.value_container.end()) {
			continue;
		}

		val_name = txt_str.substr(0U, equal_str_index);
		val_name = std::regex_replace(val_name.c_str(), needless_pattern, empty_str);

		if (val_name.empty()) {
			continue;
		}

		val = txt_str.substr(equal_str_index + equal_str.length());
		val = std::regex_replace(val.c_str(), needless_pattern, empty_str);

		val_name_itr->second.insert(std::make_pair(val_name, val));
	}

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::INIFile::Write(void)
{
	if (this->write_plan.file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	std::wstring empty_str = L"";
	std::wstring section_start_str = L"[";
	std::wstring section_end_str = L"]";
	std::wstring equal_str = L"=";
	std::wstring str;

	for (auto &val_name_cont : this->data.value_container) {
		str = section_start_str + val_name_cont.first + section_end_str;

		txt_file.data.string_container.push_back(str);

		for (auto &val : val_name_cont.second) {
			str = val.first + equal_str + val.second;

			txt_file.data.string_container.push_back(str);
		}

		txt_file.data.string_container.push_back(empty_str);
	}

	if (txt_file.data.string_container.empty()) {
		txt_file.data.string_container.push_back(empty_str);
	}

	txt_file.write_plan.file_path = this->write_plan.file_path;
	txt_file.write_plan.one_buffer_size = this->write_plan.one_buffer_size;
	txt_file.write_plan.add_flag = this->write_plan.add_flag;
	txt_file.write_plan.add_newline_code_count = this->write_plan.add_newline_code_count;
	txt_file.write_plan.newline_code_type = this->write_plan.newline_code_type;

	if (txt_file.Write()) {
		return (-1);
	}

	return (0);
}
