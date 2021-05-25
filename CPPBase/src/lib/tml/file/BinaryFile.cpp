/**
 * @file
 * @brief BinaryFileコードファイル
 */


#include "BinaryFile.h"
#include <fstream>
#include "FileUtil.h"


/**
 * @brief コンストラクタ
 */
tml::BinaryFileData::BinaryFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileData::~BinaryFileData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileData::Init(void)
{
	this->Release();

	this->file_buffer.Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileReadDescData::BinaryFileReadDescData() :
	one_buffer_size(2048U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileReadDescData::~BinaryFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileReadDescData::Init(void)
{
	this->Release();

	this->one_buffer_size = 2048U;

	tml::FileReadDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileWriteDescData::BinaryFileWriteDescData() :
	one_buffer_size(2048U),
	add_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileWriteDescData::~BinaryFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileWriteDescData::Init(void)
{
	this->Release();

	this->one_buffer_size = 2048U;
	this->add_flag = false;

	tml::FileWriteDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFile::BinaryFile()
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
 * @brief Init関数
 */
void tml::BinaryFile::Init(void)
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
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::BinaryFile::Read(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	if (read_desc_dat->file_path.empty()) {
		if (read_desc_dat->file_buffer.GetLength() <= 0U) {
			this->data.Init();

			return (0);
		}

		this->data.Init();

		this->data.file_buffer = read_desc_dat->file_buffer;

		return (0);
	}

	tml::DynamicBuffer file_buf;
	CHAR *read_buf = nullptr;
	size_t read_buf_size = 0U;
	size_t read_size = 0U;

	{tml::ThreadLockBlock th_lock_block(tml::FileUtil::GetFileThreadLock());
		std::ifstream ifs;

		ifs.open(read_desc_dat->file_path.c_str(), std::ios_base::in | std::ios_base::binary);

		if (!ifs) {
			return (-1);
		}

		read_buf_size = tml::Max(read_desc_dat->one_buffer_size, sizeof(size_t));
		read_buf = tml::MemoryUtil::Get<CHAR>(read_buf_size);

		while (1) {
			ifs.read(read_buf, read_buf_size);

			read_size = static_cast<size_t>(ifs.gcount());

			if (read_size > 0U) {
				file_buf.SetSize(file_buf.GetSize() + read_size);
				file_buf.WriteArray(reinterpret_cast<BYTE *>(read_buf), read_size, read_size);
			}

			if (ifs.eof()) {
				break;
			}
		}

		ifs.close();
	}

	tml::MemoryUtil::Release(&read_buf);
	read_buf_size = 0U;

	this->data.Init();

	this->data.file_buffer = std::move(file_buf);

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::BinaryFile::Write(void)
{
	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	size_t file_buf_index = 0U;
	CHAR *write_buf = nullptr;
	size_t write_buf_size = 0U;
	size_t write_size = 0U;

	{tml::ThreadLockBlock th_lock_block(tml::FileUtil::GetFileThreadLock());
		std::ofstream ofs;

		if (write_desc_dat->add_flag) {
			ofs.open(write_desc_dat->file_path.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::app);
		} else {
			ofs.open(write_desc_dat->file_path.c_str(), std::ios_base::out | std::ios_base::binary);
		}

		if (!ofs) {
			return (-1);
		}

		if (this->data.file_buffer.GetLength() <= 0U) {
			ofs.close();

			return (0);
		}

		write_buf_size = tml::Max(write_desc_dat->one_buffer_size, sizeof(size_t));
		write_buf = tml::MemoryUtil::Get<CHAR>(write_buf_size);

		while (1) {
			write_size = tml::Min(this->data.file_buffer.GetLength() - file_buf_index, write_buf_size);

			tml::Copy(write_buf, reinterpret_cast<CHAR *>(&this->data.file_buffer.Get()[file_buf_index]), write_size);

			ofs.write(write_buf, write_size);

			file_buf_index += write_size;

			if (file_buf_index >= this->data.file_buffer.GetLength()) {
				break;
			}
		}

		ofs.close();
	}

	tml::MemoryUtil::Release(&write_buf);
	write_buf_size = 0U;

	return (0);
}
