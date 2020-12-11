/**
 * @file
 * @brief CSVFileコードファイル
 */


#include "CSVFile.h"
#include <regex>
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::CSVFileData::CSVFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFileData::~CSVFileData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::CSVFileData::Init(void)
{
	this->value_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::CSVFileReadPlan::CSVFileReadPlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFileReadPlan::~CSVFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::CSVFileReadPlan::Init(void)
{
	tml::TextFileReadPlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::CSVFileWritePlan::CSVFileWritePlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFileWritePlan::~CSVFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::CSVFileWritePlan::Init(void)
{
	tml::TextFileWritePlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::CSVFile::CSVFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFile::~CSVFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::CSVFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::CSVFile::Init(void)
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
INT tml::CSVFile::Read(void)
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
	std::wstring comment_str = L"#";
	size_t comment_str_index = 0U;
	std::wstring comma_str = L",";
	size_t comma_str_index = 0U;
	std::wstring dq_str = L"\"";
	size_t dq_str_index = 0U;
	size_t dq_str_sub_index = 0U;
	size_t dq_str_cnt = 0U;
	std::wstring double_dq_str = L"\"\"";
	size_t double_dq_str_index = 0U;
	std::wstring newline_code_str = tml::ConstantUtil::NEWLINE_CODE::GetString(this->read_plan.newline_code_type);
	std::vector<std::wstring> column_val_cont;
	size_t column_cnt = 0U;

	for (auto txt_str : txt_file.data.string_container) {
		if (txt_str.empty()) {
			continue;
		}

		{// コメントを削除
			dq_str_index = 0U;
			dq_str_sub_index = 0U;
			dq_str_cnt = 0U;

			comment_str_index = txt_str.find(comment_str);

			while (comment_str_index != std::wstring::npos) {
				dq_str_index = txt_str.find(dq_str, dq_str_sub_index);

				while (dq_str_index != std::wstring::npos) {
					if (dq_str_index >= comment_str_index) {
						break;
					}

					++dq_str_cnt;

					dq_str_sub_index = dq_str_index + dq_str.length();

					dq_str_index = txt_str.find(dq_str, dq_str_index + dq_str.length());
				}

				if ((dq_str_cnt & 1U) == 0U) {
					txt_str.erase(comment_str_index);

					break;
				} else {
					dq_str_sub_index = comment_str_index + comment_str.length();

					comment_str_index = txt_str.find(comment_str, comment_str_index + comment_str.length());
				}
			}
		}

		if (txt_str.empty()) {
			continue;
		}

		{// ｢,｣を改行文字列に変換
			dq_str_index = 0U;
			dq_str_sub_index = 0U;
			dq_str_cnt = 0U;

			comma_str_index = txt_str.find(comma_str);

			while (comma_str_index != std::wstring::npos) {
				dq_str_index = txt_str.find(dq_str, dq_str_sub_index);

				while (dq_str_index != std::wstring::npos) {
					if (dq_str_index >= comma_str_index) {
						break;
					}

					++dq_str_cnt;

					dq_str_index = txt_str.find(dq_str, dq_str_index + dq_str.length());
				}

				if ((dq_str_cnt & 1U) == 0U) {
					txt_str.replace(comma_str_index, comma_str.length(), newline_code_str);

					dq_str_sub_index = comma_str_index + newline_code_str.length();

					comma_str_index = txt_str.find(comma_str, comma_str_index + newline_code_str.length());
				} else {
					dq_str_sub_index = comma_str_index + comma_str.length();

					comma_str_index = txt_str.find(comma_str, comma_str_index + comma_str.length());
				}
			}
		}

		tml::StringUtil::Split(column_val_cont, txt_str.c_str(), newline_code_str.c_str());

		for (auto &column_val : column_val_cont) {
			{// ｢""｣を｢"｣に変換
				double_dq_str_index = column_val.find(double_dq_str);

				while (double_dq_str_index != std::wstring::npos) {
					column_val.replace(double_dq_str_index, double_dq_str.length(), dq_str);

					double_dq_str_index = column_val.find(double_dq_str, double_dq_str_index + dq_str.length());
				}
			}

			{// 先頭の｢"｣を削除
				dq_str_index = column_val.find(dq_str);

				if (dq_str_index != std::wstring::npos) {
					column_val.erase(0U, dq_str_index + dq_str.length());
				}
			}

			{// 末尾の｢"｣を削除
				dq_str_index = column_val.rfind(dq_str);

				if (dq_str_index != std::wstring::npos) {
					column_val.erase(dq_str_index);
				}
			}

			column_val = std::regex_replace(column_val.c_str(), needless_pattern, empty_str);
		}

		if (column_val_cont.size() < column_cnt) {
			column_val_cont.resize(column_cnt, empty_str);
		} else if (column_val_cont.size() > column_cnt) {
			column_cnt = column_val_cont.size();

			for (size_t val_i = 0U; val_i < this->data.value_container.size(); ++val_i) {
				this->data.value_container[val_i].resize(column_cnt, empty_str);
			}
		}

		this->data.value_container.push_back(column_val_cont);
	}

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::CSVFile::Write(void)
{
	if (this->write_plan.file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	std::wstring empty_str = L"";
	std::wstring comma_str = L",";
	std::wstring str;

	for (auto &val_cont : this->data.value_container) {
		tml::StringUtil::Join(str, val_cont, comma_str.c_str());

		txt_file.data.string_container.push_back(str);
	}

	txt_file.data.string_container.push_back(empty_str);

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
