/**
 * @file
 * @brief INIFileコードファイル
 */


#include "INIFile.h"
#include <regex>
#include "TextFile.h"
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
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::INIFileData::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileData::Init(void)
{
	this->Release();

	this->value_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFileReadPlan::INIFileReadPlan() :
	one_buffer_size(1024U),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
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
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFileWritePlan::INIFileWritePlan() :
	one_buffer_size(1024U),
	add_flag(false),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
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
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->add_flag = false;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

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

	txt_file.read_plan.file_path = this->read_plan.file_path;
	txt_file.read_plan.one_buffer_size = this->read_plan.one_buffer_size;
	txt_file.read_plan.newline_code_type = this->read_plan.newline_code_type;

	if (txt_file.Read()) {
		return (-1);
	}

	this->data.value_container.clear();

	if (txt_file.data.string_container.empty()) {
		return (0);
	}

	std::wstring empty_str = L"";
	std::wregex needless_pattern(L"^[\\s|　]+|[\\s|　]+$");
	std::wstring comment_str = L";";
	size_t comment_str_index = 0U;
	std::wstring equal_str = L"=";
	size_t equal_str_index = 0U;
	std::wstring section_start_str = L"[";
	size_t section_start_str_index = 0U;
	std::wstring section_end_str = L"]";
	size_t section_end_str_index = 0U;
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

	return (-1);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::INIFile::Write(void)
{
	return (-1);
}
