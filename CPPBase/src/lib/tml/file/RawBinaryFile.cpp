/**
 * @file
 * @brief RawBinaryFileコードファイル
 */


#include "RawBinaryFile.h"
#include <fstream>
#include "FileUtil.h"


/**
 * @brief コンストラクタ
 */
tml::RawBinaryFileData::RawBinaryFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RawBinaryFileData::~RawBinaryFileData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::RawBinaryFileData::Init(void)
{
	this->Release();

	this->buffer.Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::RawBinaryFileReadDescData::RawBinaryFileReadDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RawBinaryFileReadDescData::~RawBinaryFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::RawBinaryFileReadDescData::Init(void)
{
	this->Release();

	this->buffer.Init();

	tml::FileReadDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::RawBinaryFileWriteDescData::RawBinaryFileWriteDescData() :
	add_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RawBinaryFileWriteDescData::~RawBinaryFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::RawBinaryFileWriteDescData::Init(void)
{
	this->Release();

	this->add_flag = false;

	tml::FileWriteDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::RawBinaryFile::RawBinaryFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RawBinaryFile::~RawBinaryFile()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::RawBinaryFile::Init(void)
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
INT tml::RawBinaryFile::Read(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	if (read_desc_dat->file_path.empty()) {
		if (read_desc_dat->buffer.GetLength() > 0U) {
			this->data.Init();

			this->data.buffer = read_desc_dat->buffer;

			return (0);
		}

		this->data.Init();

		return (0);
	}

	tml::RawDynamicBuffer buf;
	BYTE *read_buf = nullptr;
	size_t read_buf_size = 0U;
	size_t read_size = 0U;

	{tml::ThreadLockBlock th_lock_block(tml::FileUtil::GetFileThreadLock());
		std::ifstream ifs;

		ifs.open(read_desc_dat->file_path.c_str(), std::ios_base::in | std::ios_base::binary);

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
INT tml::RawBinaryFile::Write(void)
{
	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	size_t buf_index = 0U;
	BYTE *write_buf = nullptr;
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
