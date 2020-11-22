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
tml::TextFileReadPlan::TextFileReadPlan()
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

	return;
}


/**
 * @brief コンストラクタ
 */
tml::TextFileWritePlan::TextFileWritePlan()
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
	this->str_cont_.clear();

	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TextFile::Init(void)
{
	this->Release();

	this->read_plan.Init();
	this->write_plan.Init();

	tml::File::Init();

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
	size_t buf_size = bin_file.GetBufferSize() + sizeof(WCHAR);
	std::wstring buf_str;

	buf = tml::MemoryUtil::Get<BYTE>(buf_size);
	tml::MemoryUtil::Copy(buf, bin_file.GetBuffer(), bin_file.GetBufferSize());
	reinterpret_cast<WCHAR *>(&buf[bin_file.GetBufferSize()])[0] = 0;

	tml::StringUtil::GetString(buf_str, reinterpret_cast<CHAR *>(buf));

	tml::StringUtil::Split(this->str_cont_, buf_str.c_str(), L"\r\n");

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

	size_t str_i = 0U;

	for (auto &str : this->str_cont_) {
		if (str_i > 0U) {
			buf_str += L"\r\n";
		}

		buf_str += str;

		++str_i;
	}

	tml::StringUtil::GetString(tmp_buf_str, buf_str.c_str());

	buf_size = tmp_buf_str.length();
	buf = tml::MemoryUtil::Get<BYTE>(buf_size);
	tml::MemoryUtil::Copy(buf, reinterpret_cast<const BYTE *>(tmp_buf_str.c_str()), buf_size);

	tml::BinaryFile bin_file;

	bin_file.SetBuffer(buf, buf_size);

	tml::MemoryUtil::Release(&buf);
	buf_size = 0U;

	bin_file.write_plan.file_path = this->write_plan.file_path;

	if (bin_file.Write()) {
	    return (-1);
	}

	return (0);
}
