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
tml::INIFileReadDescData::INIFileReadDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileReadDescData::~INIFileReadDescData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileReadDescData::Init(void)
{
	tml::TextFileReadDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFileWriteDescData::INIFileWriteDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileWriteDescData::~INIFileWriteDescData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileWriteDescData::Init(void)
{
	tml::TextFileWriteDescData::Init();

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
	this->read_desc.Init();
	this->write_desc.Init();

	return;
}


/**
 * @brief Read関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::INIFile::Read(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	tml::TextFile txt_file;

	txt_file.read_desc.parent_data = read_desc_dat;

	if (txt_file.Read()) {
		return (-1);
	}

	this->data.Init();

	if (txt_file.data.string_container.empty()) {
		return (0);
	}

	const std::wstring empty_str = L"";
	const std::wstring section_start_str = L"[";
	const std::wstring section_end_str = L"]";
	const std::wstring equal_str = L"=";
	const std::wstring comment_str = L";";
	const std::wregex needless_pattern(L"^[\\s|　]+|[\\s|　]+$");
	size_t section_start_str_index = 0U;
	size_t section_end_str_index = 0U;
	size_t equal_str_index = 0U;
	size_t comment_str_index = 0U;
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
	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	if (!this->data.value_container.empty()) {
		const std::wstring empty_str = L"";
		const std::wstring section_start_str = L"[";
		const std::wstring section_end_str = L"]";
		const std::wstring equal_str = L"=";
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
	}

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write()) {
		return (-1);
	}

	return (0);
}
