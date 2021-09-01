/**
 * @file
 * @brief ConfigFile�R�[�h�t�@�C��
 */


#include "ConfigFile.h"
#include <regex>
#include "../string/StringUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ConfigFileData::ConfigFileData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFileData::~ConfigFileData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFileData::Init(void)
{
	this->Release();

	this->value_container.clear();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ConfigFileReadDescData::ConfigFileReadDescData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFileReadDescData::~ConfigFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFileReadDescData::Init(void)
{
	this->Release();

	tml::TextFileReadDescData::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ConfigFileWriteDescData::ConfigFileWriteDescData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFileWriteDescData::~ConfigFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFileWriteDescData::Init(void)
{
	this->Release();

	tml::TextFileWriteDescData::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ConfigFile::ConfigFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFile::~ConfigFile()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFile::Init(void)
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
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::ConfigFile::Read(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring equal_str = L"=";
	static const std::wstring comment_str = L"#";
	static const std::wregex needless_pattern(L"^[\\s|�@]+|[\\s|�@]+$");

	auto read_desc_dat = this->read_desc.GetDataByParent();

	tml::TextFile txt_file;

	txt_file.read_desc.parent_data = read_desc_dat;

	if (txt_file.Read() < 0) {
		return (-1);
	}

	this->data.Init();

	if (txt_file.data.line_string_container.empty()) {
		return (0);
	}

	std::wstring line_str;
	size_t equal_str_index = 0U;
	size_t comment_str_index = 0U;
	std::wstring val_name;
	std::wstring val;

	for (auto &txt_file_line_str : txt_file.data.line_string_container) {
		if (txt_file_line_str.empty()) {
			continue;
		}

		line_str = txt_file_line_str;

		{// �R�����g���폜
			comment_str_index = line_str.find(comment_str);

			if (comment_str_index != std::wstring::npos) {
				line_str.erase(comment_str_index);
			}
		}

		if (line_str.empty()) {
			continue;
		}

		{// �=����m�F
			equal_str_index = line_str.find(equal_str);

			if (equal_str_index == std::wstring::npos) {
				continue;
			}
		}

		val_name = line_str.substr(0U, equal_str_index);
		val_name = std::regex_replace(val_name.c_str(), needless_pattern, empty_str);

		if (val_name.empty()) {
			continue;
		}

		val = line_str.substr(equal_str_index + equal_str.length());
		val = std::regex_replace(val.c_str(), needless_pattern, empty_str);

		this->data.value_container.insert(std::make_pair(val_name, val));
	}

	return (0);
}


/**
 * @brief Write�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::ConfigFile::Write(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring equal_str = L"=";

	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	if (!this->data.value_container.empty()) {
		std::wstring line_str;

		for (auto &val : this->data.value_container) {
			line_str = val.first;
			line_str += equal_str;
			line_str += val.second;

			txt_file.data.line_string_container.push_back(line_str);
		}

		txt_file.data.line_string_container.push_back(empty_str);
	}

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
