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

	this->buffer.Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileReadDescData::BinaryFileReadDescData()
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

	this->buffer.Init();

	tml::FileReadDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileWriteDescData::BinaryFileWriteDescData() :
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
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::BinaryFile::Read(void)
{
	auto file_read_desc_dat = this->read_desc.GetDataByParent();

	if (file_read_desc_dat->file_path.empty()) {
		if (file_read_desc_dat->buffer.GetLength() > 0U) {
			this->data.Init();

			this->data.buffer = file_read_desc_dat->buffer;

			return (0);
		}

		this->data.Init();

		return (0);
	}

	tml::DynamicBuffer buf;
	BYTE *read_buf = nullptr;
	size_t read_buf_size = 0U;
	size_t read_size = 0U;

	{tml::ThreadLockBlock th_lock_block(tml::FileUtil::GetFileThreadLock());
		std::ifstream ifs;

		ifs.open(file_read_desc_dat->file_path.c_str(), std::ios_base::in | std::ios_base::binary);

		if (!ifs) {
			return (-1);
		}

		tml::FileUtil::GetReadBuffer(read_buf, read_buf_size);

		while (1) {
			ifs.read(reinterpret_cast<CHAR *>(read_buf), read_buf_size);

			read_size = static_cast<size_t>(ifs.gcount());

			if (read_size > 0U) {
				buf.SetSize(buf.GetSize() + read_size);
				buf.WriteArray(read_buf, read_size, read_size);
			}

			if (ifs.eof()) {
				break;
			}
		}

		ifs.close();
	}

	this->data.Init();

	this->data.buffer = std::move(buf);

	return (0);
}


/**
 * @brief Write関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::BinaryFile::Write(void)
{
	auto file_write_desc_dat = this->write_desc.GetDataByParent();

	if (file_write_desc_dat->file_path.empty()) {
		return (-1);
	}

	size_t buf_index = 0U;
	BYTE *write_buf = nullptr;
	size_t write_buf_size = 0U;
	size_t write_size = 0U;

	{tml::ThreadLockBlock th_lock_block(tml::FileUtil::GetFileThreadLock());
		std::ofstream ofs;

		if (file_write_desc_dat->add_flag) {
			ofs.open(file_write_desc_dat->file_path.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::app);
		} else {
			ofs.open(file_write_desc_dat->file_path.c_str(), std::ios_base::out | std::ios_base::binary);
		}

		if (!ofs) {
			return (-1);
		}

		if (this->data.buffer.GetLength() <= 0U) {
			ofs.close();

			return (0);
		}

		tml::FileUtil::GetWriteBuffer(write_buf, write_buf_size);

		while (1) {
			write_size = tml::Min(this->data.buffer.GetLength() - buf_index, write_buf_size);

			tml::Copy(write_buf, &this->data.buffer.Get()[buf_index], write_size);

			ofs.write(reinterpret_cast<CHAR *>(write_buf), write_size);

			buf_index += write_size;

			if (buf_index >= this->data.buffer.GetLength()) {
				break;
			}
		}

		ofs.close();
	}

	return (0);
}
