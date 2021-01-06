/**
 * @file
 * @brief ConfigFileコードファイル
 */


#include "ConfigFile.h"
#include <regex>
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::ConfigFileData::ConfigFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ConfigFileData::~ConfigFileData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ConfigFileData::Init(void)
{
	this->value_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ConfigFileReadPlan::ConfigFileReadPlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ConfigFileReadPlan::~ConfigFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ConfigFileReadPlan::Init(void)
{
	tml::TextFileReadPlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ConfigFileWritePlan::ConfigFileWritePlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ConfigFileWritePlan::~ConfigFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ConfigFileWritePlan::Init(void)
{
	tml::TextFileWritePlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ConfigFile::ConfigFile() :
	parent_read_plan(nullptr),
	parent_write_plan(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ConfigFile::~ConfigFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::ConfigFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ConfigFile::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_plan.Init();
	this->parent_read_plan = nullptr;
	this->write_plan.Init();
	this->parent_write_plan = nullptr;

	return;
}


/**
 * @brief Read関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ConfigFile::Read(void)
{
	auto read_plan = (this->parent_read_plan != nullptr) ? this->parent_read_plan : &this->read_plan;

	tml::TextFile txt_file;

	txt_file.parent_read_plan = read_plan;

	if (txt_file.Read()) {
		return (-1);
	}

	this->data.Init();

	if (txt_file.data.string_container.empty()) {
		return (0);
	}

	const std::wstring empty_str = L"";
	const std::wstring equal_str = L"=";
	const std::wstring comment_str = L"#";
	const std::wregex needless_pattern(L"^[\\s|　]+|[\\s|　]+$");
	size_t equal_str_index = 0U;
	size_t comment_str_index = 0U;
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
				continue;
			}
		}

		val_name = txt_str.substr(0U, equal_str_index);
		val_name = std::regex_replace(val_name.c_str(), needless_pattern, empty_str);

		if (val_name.empty()) {
			continue;
		}

		val = txt_str.substr(equal_str_index + equal_str.length());
		val = std::regex_replace(val.c_str(), needless_pattern, empty_str);

		this->data.value_container.insert(std::make_pair(val_name, val));
	}

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ConfigFile::Write(void)
{
	auto write_plan = (this->parent_write_plan != nullptr) ? this->parent_write_plan : &this->write_plan;

	if (write_plan->file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	if (!this->data.value_container.empty()) {
		const std::wstring empty_str = L"";
		const std::wstring equal_str = L"=";
		std::wstring str;

		for (auto &val : this->data.value_container) {
			str = val.first + equal_str + val.second;

			txt_file.data.string_container.push_back(str);
		}

		txt_file.data.string_container.push_back(empty_str);
	}

	txt_file.parent_write_plan = write_plan;

	if (txt_file.Write()) {
		return (-1);
	}

	return (0);
}
