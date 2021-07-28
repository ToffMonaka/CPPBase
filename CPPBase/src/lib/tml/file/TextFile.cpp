/**
 * @file
 * @brief TextFileコードファイル
 */


#include "TextFile.h"
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::TextFileData::TextFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextFileData::~TextFileData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TextFileData::Init(void)
{
	this->Release();

	this->line_string_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::TextFileReadDescData::TextFileReadDescData() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextFileReadDescData::~TextFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TextFileReadDescData::Init(void)
{
	this->Release();

	this->string.clear();
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	tml::BinaryFileReadDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::TextFileWriteDescData::TextFileWriteDescData() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF),
	add_newline_code_count(1U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextFileWriteDescData::~TextFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TextFileWriteDescData::Init(void)
{
	this->Release();

	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;
	this->add_newline_code_count = 1U;

	tml::BinaryFileWriteDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::TextFile::TextFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextFile::~TextFile()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TextFile::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_desc.Init();
	this->write_desc.Init();

	tml::File::Init();

	return;
}


/**
 * @brief Read関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::TextFile::Read(void)
{
	auto file_read_desc_dat = this->read_desc.GetDataByParent();

	if (file_read_desc_dat->file_path.empty()) {
		if (file_read_desc_dat->buffer.GetLength() <= 0U) {
			if (!file_read_desc_dat->string.empty()) {
				this->data.Init();

				tml::StringUtil::Split(this->data.line_string_container, file_read_desc_dat->string.c_str(), tml::ConstantUtil::NEWLINE_CODE::GetStringW(file_read_desc_dat->newline_code_type));

				return (0);
			}

			this->data.Init();

			return (0);
		}
	}

	tml::BinaryFile bin_file;

	bin_file.read_desc.parent_data = file_read_desc_dat;

	if (bin_file.Read() < 0) {
		return (-1);
	}

	this->data.Init();

	if (bin_file.data.buffer.GetLength() <= 0U) {
		return (0);
	}

	bin_file.data.buffer.SetSize(bin_file.data.buffer.GetSize() + sizeof(CHAR));
	bin_file.data.buffer.WriteChar(0);

	CHAR *tmp_str = reinterpret_cast<CHAR *>(bin_file.data.buffer.Get());

	std::wstring str;

	tml::StringUtil::GetString(str, tmp_str);

	tml::StringUtil::Split(this->data.line_string_container, str.c_str(), tml::ConstantUtil::NEWLINE_CODE::GetStringW(file_read_desc_dat->newline_code_type));

	return (0);
}


/**
 * @brief Write関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::TextFile::Write(void)
{
	auto file_write_desc_dat = this->write_desc.GetDataByParent();

	if (file_write_desc_dat->file_path.empty()) {
		return (-1);
	}

	std::wstring tmp_str;

	tml::StringUtil::Join(tmp_str, this->data.line_string_container, tml::ConstantUtil::NEWLINE_CODE::GetStringW(file_write_desc_dat->newline_code_type));

	if (!tmp_str.empty()) {
		if ((file_write_desc_dat->add_flag)
		&& (file_write_desc_dat->add_newline_code_count > 0U)) {
			std::wstring add_newline_code_str;

			for (size_t add_newline_code_i = 0U; add_newline_code_i < file_write_desc_dat->add_newline_code_count; ++add_newline_code_i) {
				add_newline_code_str += tml::ConstantUtil::NEWLINE_CODE::GetStringW(file_write_desc_dat->newline_code_type);
			}

			tmp_str.insert(0U, add_newline_code_str);
		}
	}

	std::string str;

	tml::StringUtil::GetString(str, tmp_str.c_str());

	tml::BinaryFile bin_file;

	bin_file.data.buffer.SetSize(str.length());
	bin_file.data.buffer.WriteArray(reinterpret_cast<const BYTE *>(str.c_str()), str.length(), str.length());

	bin_file.write_desc.parent_data = file_write_desc_dat;

	if (bin_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
