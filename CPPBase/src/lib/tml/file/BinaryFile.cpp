/**
 * @file
 * @brief BinaryFileコードファイル
 */


#include "BinaryFile.h"
#include <fstream>
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::BinaryFileReadPlan::BinaryFileReadPlan() :
	read_buffer_size(1024U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileReadPlan::~BinaryFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileReadPlan::Init(void)
{
	this->file_path = L"";
	this->read_buffer_size = 1024U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileWritePlan::BinaryFileWritePlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileWritePlan::~BinaryFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileWritePlan::Init(void)
{
	this->file_path = L"";

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFile::BinaryFile() :
	buf_(nullptr),
	buf_size_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFile::~BinaryFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::BinaryFile::Release(void)
{
	tml::MemoryUtil::Release(&this->buf_);
	this->buf_size_ = 0U;

	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFile::Init(void)
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
INT tml::BinaryFile::Read(void)
{
	std::ifstream ifs;

	ifs.open(read_plan.file_path.c_str(), std::ios_base::in | std::ios_base::binary);

	if (!ifs) {
	    return (-1);
	}

	BYTE *buf = nullptr;
	size_t buf_size = 0U;
	BYTE *tmp_buf = nullptr;
	size_t tmp_buf_size = 0U;
	CHAR *read_buf = tml::MemoryUtil::Get<CHAR>(this->read_plan.read_buffer_size);
	size_t read_buf_size = this->read_plan.read_buffer_size;
	size_t read_size = 0U;

	while (1) {
		ifs.read(read_buf, read_buf_size);

		read_size = static_cast<size_t>(ifs.gcount());

		if (read_size > 0U) {
			tmp_buf = buf;
			tmp_buf_size = buf_size;

			buf = tml::MemoryUtil::Get<BYTE>(tmp_buf_size + read_size);
			buf_size = tmp_buf_size + read_size;

			tml::MemoryUtil::Copy(buf, tmp_buf, tmp_buf_size);
			tml::MemoryUtil::Copy(&buf[tmp_buf_size], reinterpret_cast<BYTE *>(read_buf), read_size);

			tml::MemoryUtil::Release(&tmp_buf);
			tmp_buf_size = 0U;
		}

		if (ifs.eof()) {
			break;
		}
	}

	ifs.close();

	tml::MemoryUtil::Release(&this->buf_);
	read_buf_size = 0U;

	tml::MemoryUtil::Release(&this->buf_);
	this->buf_ = buf;
	this->buf_size_ = buf_size;

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::BinaryFile::Write(void)
{
	return (0);
}
