/**
 * @file
 * @brief TextFileコードファイル
 */


#include "TextFile.h"
#include "BinaryFile.h"
#include "../memory/MemoryUtil.h"
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
 * @brief Release関数
 */
void tml::TextFileData::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::TextFileData::Init(void)
{
	this->Release();

	this->string_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::TextFileReadPlan::TextFileReadPlan() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextFileReadPlan::~TextFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::TextFileReadPlan::Init(void)
{
	this->file_path.clear();
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::TextFileWritePlan::TextFileWritePlan() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextFileWritePlan::~TextFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::TextFileWritePlan::Init(void)
{
	this->file_path.clear();
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

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
 * @brief Release関数
 */
void tml::TextFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TextFile::Init(void)
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
INT tml::TextFile::Read(void)
{
	tml::BinaryFile bin_file;

	bin_file.read_plan.file_path = this->read_plan.file_path;

	if (bin_file.Read()) {
		return (-1);
	}

	BYTE *buf = nullptr;
	size_t buf_size = 0U;
	std::wstring buf_str;
	CHAR *tmp_buf_str = nullptr;

	buf_size = bin_file.data.buffer_size + sizeof(CHAR);
	buf = tml::MemoryUtil::Get<BYTE>(buf_size);
	tml::MemoryUtil::Copy(buf, bin_file.data.buffer, bin_file.data.buffer_size);
	buf[bin_file.data.buffer_size] = 0;
	tmp_buf_str = reinterpret_cast<CHAR *>(buf);

	tml::StringUtil::GetString(buf_str, tmp_buf_str);

	tml::StringUtil::Split(this->data.string_container, buf_str.c_str(), tml::ConstantUtil::NEWLINE_CODE::GetString(this->read_plan.newline_code_type));

	tml::MemoryUtil::Release(&buf);
	buf_size = 0U;

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::TextFile::Write(void)
{
	BYTE *buf = nullptr;
	size_t buf_size = 0U;
	std::wstring buf_str;
	std::string tmp_buf_str;

	tml::StringUtil::Join(buf_str, this->data.string_container, tml::ConstantUtil::NEWLINE_CODE::GetString(this->write_plan.newline_code_type));

	tml::StringUtil::GetString(tmp_buf_str, buf_str.c_str());

	buf_size = tmp_buf_str.length();
	buf = tml::MemoryUtil::Get<BYTE>(buf_size);
	tml::MemoryUtil::Copy(buf, reinterpret_cast<const BYTE *>(tmp_buf_str.c_str()), buf_size);

	tml::BinaryFile bin_file;

	bin_file.data.buffer = buf;
	bin_file.data.buffer_size = buf_size;

	bin_file.write_plan.file_path = this->write_plan.file_path;

	if (bin_file.Write()) {
		return (-1);
	}

	return (0);
}
