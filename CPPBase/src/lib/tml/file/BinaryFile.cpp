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
	one_buffer_size(1024U)
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
	this->file_path.clear();
	this->one_buffer_size = 1024U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileWritePlan::BinaryFileWritePlan() :
	one_buffer_size(1024U)
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
	this->file_path.clear();
	this->one_buffer_size = 1024U;

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

	ifs.open(this->read_plan.file_path.c_str(), std::ios_base::in | std::ios_base::binary);

	if (!ifs) {
	    return (-1);
	}

	BYTE *buf = nullptr;
	size_t buf_size = 0U;
	BYTE *tmp_buf = nullptr;
	size_t tmp_buf_size = 0U;
	CHAR *read_buf = nullptr;
	size_t read_buf_size = std::max(this->read_plan.one_buffer_size, sizeof(size_t));
	size_t read_size = 0U;

	read_buf = tml::MemoryUtil::Get<CHAR>(read_buf_size);

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

	tml::MemoryUtil::Release(&read_buf);
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
	std::ofstream ofs;

	ofs.open(this->write_plan.file_path.c_str(), std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
	    return (-1);
	}

	if (this->buf_size_ <= 0U) {
		ofs.close();

		return (0);
	}

	size_t buf_index = 0U;
	CHAR *write_buf = nullptr;
	size_t write_buf_size = std::max(this->write_plan.one_buffer_size, sizeof(size_t));
	size_t write_size = 0U;

	write_buf = tml::MemoryUtil::Get<CHAR>(write_buf_size);

	while (1) {
		write_size = std::min(this->buf_size_ - buf_index, write_buf_size);

		tml::MemoryUtil::Copy(write_buf, reinterpret_cast<CHAR *>(&this->buf_[buf_index]), write_size);

		ofs.write(write_buf, write_size);

		buf_index += write_size;

		if (buf_index >= this->buf_size_) {
			break;
		}
	}

	ofs.close();

	tml::MemoryUtil::Release(&write_buf);
	write_buf_size = 0U;

	return (0);
}
