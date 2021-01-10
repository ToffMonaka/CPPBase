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
tml::ConfigFileReadPlanData::ConfigFileReadPlanData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ConfigFileReadPlanData::~ConfigFileReadPlanData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ConfigFileReadPlanData::Init(void)
{
	tml::TextFileReadPlanData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ConfigFileReadPlan::ConfigFileReadPlan() :
	parent_data(nullptr)
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
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ConfigFileWritePlanData::ConfigFileWritePlanData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ConfigFileWritePlanData::~ConfigFileWritePlanData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ConfigFileWritePlanData::Init(void)
{
	tml::TextFileWritePlanData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ConfigFileWritePlan::ConfigFileWritePlan() :
	parent_data(nullptr)
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
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ConfigFile::ConfigFile()
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
	this->write_plan.Init();

	return;
}


/**
 * @brief Read関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ConfigFile::Read(void)
{
	auto read_plan_dat = this->read_plan.GetDataByParent();

	tml::TextFile txt_file;

	txt_file.read_plan.parent_data = read_plan_dat;

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
	auto write_plan_dat = this->write_plan.GetDataByParent();

	if (write_plan_dat->file_path.empty()) {
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

	txt_file.write_plan.parent_data = write_plan_dat;

	if (txt_file.Write()) {
		return (-1);
	}

	return (0);
}
