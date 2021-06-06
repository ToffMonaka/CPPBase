/**
 * @file
 * @brief CSVFile�R�[�h�t�@�C��
 */


#include "CSVFile.h"
#include <regex>
#include "../string/StringUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::CSVFileData::CSVFileData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFileData::~CSVFileData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFileData::Init(void)
{
	this->Release();

	this->value_container.clear();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::CSVFileReadDescData::CSVFileReadDescData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFileReadDescData::~CSVFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFileReadDescData::Init(void)
{
	this->Release();

	tml::TextFileReadDescData::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::CSVFileWriteDescData::CSVFileWriteDescData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFileWriteDescData::~CSVFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFileWriteDescData::Init(void)
{
	this->Release();

	tml::TextFileWriteDescData::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::CSVFile::CSVFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFile::~CSVFile()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFile::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_desc.Init();
	this->write_desc.Init();

	tml::File::Init();

	return;
}


/**
 * @brief Read�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::CSVFile::Read(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	tml::TextFile txt_file;

	txt_file.read_desc.parent_data = read_desc_dat;

	if (txt_file.Read() < 0) {
		return (-1);
	}

	this->data.Init();

	if (txt_file.data.string_container.empty()) {
		return (0);
	}

	const std::wstring empty_str = L"";
	const std::wstring comma_str = L",";
	const std::wstring dq_str = L"\"";
	const std::wstring double_dq_str = L"\"\"";
	const std::wstring comment_str = L"#";
	const std::wregex needless_pattern(L"^[\\s|�@]+|[\\s|�@]+$");
	std::wstring line_str;
	size_t comma_str_index = 0U;
	size_t dq_str_index = 0U;
	size_t dq_str_sub_index = 0U;
	size_t dq_str_cnt = 0U;
	size_t double_dq_str_index = 0U;
	size_t comment_str_index = 0U;
	std::wstring newline_code_str = tml::ConstantUtil::NEWLINE_CODE::GetString(read_desc_dat->newline_code_type);
	std::vector<std::wstring> column_val_cont;
	size_t column_cnt = 0U;

	for (auto &txt_file_str : txt_file.data.string_container) {
		if (txt_file_str.empty()) {
			continue;
		}

		line_str = txt_file_str;

		{// �R�����g���폜
			dq_str_index = 0U;
			dq_str_sub_index = 0U;
			dq_str_cnt = 0U;

			comment_str_index = line_str.find(comment_str);

			while (comment_str_index != std::wstring::npos) {
				dq_str_index = line_str.find(dq_str, dq_str_sub_index);

				while (dq_str_index != std::wstring::npos) {
					if (dq_str_index >= comment_str_index) {
						break;
					}

					++dq_str_cnt;

					dq_str_sub_index = dq_str_index + dq_str.length();

					dq_str_index = line_str.find(dq_str, dq_str_index + dq_str.length());
				}

				if ((dq_str_cnt & 1U) == 0U) {
					line_str.erase(comment_str_index);

					break;
				} else {
					dq_str_sub_index = comment_str_index + comment_str.length();

					comment_str_index = line_str.find(comment_str, comment_str_index + comment_str.length());
				}
			}
		}

		if (line_str.empty()) {
			continue;
		}

		{// �,������s������ɕϊ�
			dq_str_index = 0U;
			dq_str_sub_index = 0U;
			dq_str_cnt = 0U;

			comma_str_index = line_str.find(comma_str);

			while (comma_str_index != std::wstring::npos) {
				dq_str_index = line_str.find(dq_str, dq_str_sub_index);

				while (dq_str_index != std::wstring::npos) {
					if (dq_str_index >= comma_str_index) {
						break;
					}

					++dq_str_cnt;

					dq_str_index = line_str.find(dq_str, dq_str_index + dq_str.length());
				}

				if ((dq_str_cnt & 1U) == 0U) {
					line_str.replace(comma_str_index, comma_str.length(), newline_code_str);

					dq_str_sub_index = comma_str_index + newline_code_str.length();

					comma_str_index = line_str.find(comma_str, comma_str_index + newline_code_str.length());
				} else {
					dq_str_sub_index = comma_str_index + comma_str.length();

					comma_str_index = line_str.find(comma_str, comma_str_index + comma_str.length());
				}
			}
		}

		tml::StringUtil::Split(column_val_cont, line_str.c_str(), newline_code_str.c_str());

		for (auto &column_val : column_val_cont) {
			{// �""���"��ɕϊ�
				double_dq_str_index = column_val.find(double_dq_str);

				while (double_dq_str_index != std::wstring::npos) {
					column_val.replace(double_dq_str_index, double_dq_str.length(), dq_str);

					double_dq_str_index = column_val.find(double_dq_str, double_dq_str_index + dq_str.length());
				}
			}

			{// �擪�̢"����폜
				dq_str_index = column_val.find(dq_str);

				if (dq_str_index != std::wstring::npos) {
					column_val.erase(0U, dq_str_index + dq_str.length());
				}
			}

			{// �����̢"����폜
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
 * @brief Write�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::CSVFile::Write(void)
{
	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	if (!this->data.value_container.empty()) {
		const std::wstring empty_str = L"";
		const std::wstring comma_str = L",";
		std::wstring line_str;

		for (auto &val_cont : this->data.value_container) {
			tml::StringUtil::Join(line_str, val_cont, comma_str.c_str());

			txt_file.data.string_container.push_back(line_str);
		}

		txt_file.data.string_container.push_back(empty_str);
	}

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
