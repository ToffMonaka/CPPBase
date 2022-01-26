/**
 * @file
 * @brief BinaryFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <fstream>
#include "../memory/DynamicBuffer.h"
#include "FileUtil.h"
#include "File.h"


namespace tml {
/**
 * @brief BaseBinaryFileDataクラス
 */
template <bool R>
class BaseBinaryFileData
{
public: BaseBinaryFileData(const tml::BaseBinaryFileData<R> &) = delete;
public: tml::BaseBinaryFileData<R> &operator =(const tml::BaseBinaryFileData<R> &) = delete;

private:

public:
	tml::BaseDynamicBuffer<R> buffer;

private:
	void Release(void);

public:
	BaseBinaryFileData();
	virtual ~BaseBinaryFileData();

	virtual void Init(void);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseBinaryFileData<R>::BaseBinaryFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseBinaryFileData<R>::~BaseBinaryFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseBinaryFileData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseBinaryFileData<R>::Init(void)
{
	this->Release();

	this->buffer.Init();

	return;
}


namespace tml {
/**
 * @brief BaseBinaryFileReadDescDataクラス
 */
template <bool R>
class BaseBinaryFileReadDescData : public tml::FileReadDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::BaseDynamicBuffer<R> buffer;

private:
	void Release(void);

public:
	BaseBinaryFileReadDescData();
	virtual ~BaseBinaryFileReadDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

template <bool R>
using BaseBinaryFileReadDesc = tml::FileReadDesc<tml::BaseBinaryFileReadDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseBinaryFileReadDescData<R>::BaseBinaryFileReadDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseBinaryFileReadDescData<R>::~BaseBinaryFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseBinaryFileReadDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseBinaryFileReadDescData<R>::Init(void)
{
	this->Release();

	this->buffer.Init();

	tml::FileReadDescData::Init();

	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
template <bool R>
inline bool tml::BaseBinaryFileReadDescData<R>::IsEmpty(void) const
{
	if (this->buffer.GetLength() > 0U) {
		return (false);
	}

	return (tml::FileReadDescData::IsEmpty());
}


namespace tml {
/**
 * @brief BaseBinaryFileWriteDescDataクラス
 */
template <bool R>
class BaseBinaryFileWriteDescData : public tml::FileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	bool add_flag;

private:
	void Release(void);

public:
	BaseBinaryFileWriteDescData();
	virtual ~BaseBinaryFileWriteDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

template <bool R>
using BaseBinaryFileWriteDesc = tml::FileWriteDesc<tml::BaseBinaryFileWriteDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseBinaryFileWriteDescData<R>::BaseBinaryFileWriteDescData() :
	add_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseBinaryFileWriteDescData<R>::~BaseBinaryFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseBinaryFileWriteDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseBinaryFileWriteDescData<R>::Init(void)
{
	this->Release();

	this->add_flag = false;

	tml::FileWriteDescData::Init();

	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
template <bool R>
inline bool tml::BaseBinaryFileWriteDescData<R>::IsEmpty(void) const
{
	return (tml::FileWriteDescData::IsEmpty());
}


namespace tml {
/**
 * @brief BaseBinaryFileクラス
 */
template <bool R>
class BaseBinaryFile : public tml::File
{
public: BaseBinaryFile(const tml::BaseBinaryFile<R> &) = delete;
public: tml::BaseBinaryFile<R> &operator =(const tml::BaseBinaryFile<R> &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::BaseBinaryFileData<R> data;
	tml::BaseBinaryFileReadDesc<R> read_desc;
	tml::BaseBinaryFileWriteDesc<R> write_desc;

private:
	void Release(void);

protected:
	virtual INT OnRead(void);
	virtual INT OnWrite(void);

public:
	BaseBinaryFile();
	virtual ~BaseBinaryFile();

	virtual void Init(void);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseBinaryFile<R>::BaseBinaryFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseBinaryFile<R>::~BaseBinaryFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseBinaryFile<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseBinaryFile<R>::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_desc.Init();
	this->write_desc.Init();

	tml::File::Init();

	return;
}


/**
 * @brief OnRead関数
 * @return result (result)<br>
 * 0未満=失敗
 */
template <bool R>
inline INT tml::BaseBinaryFile<R>::OnRead(void)
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

	tml::BaseDynamicBuffer<R> buf;
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
 * @brief OnWrite関数
 * @return result (result)<br>
 * 0未満=失敗
 */
template <bool R>
inline INT tml::BaseBinaryFile<R>::OnWrite(void)
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


namespace tml {
using BinaryFile = tml::BaseBinaryFile<false>;
using BinaryFileData = tml::BaseBinaryFileData<false>;
using BinaryFileReadDesc = tml::BaseBinaryFileReadDesc<false>;
using BinaryFileReadDescData = tml::BaseBinaryFileReadDescData<false>;
using BinaryFileWriteDesc = tml::BaseBinaryFileWriteDesc<false>;
using BinaryFileWriteDescData = tml::BaseBinaryFileWriteDescData<false>;

using RawBinaryFile = tml::BaseBinaryFile<true>;
using RawBinaryFileData = tml::BaseBinaryFileData<true>;
using RawBinaryFileReadDesc = tml::BaseBinaryFileReadDesc<true>;
using RawBinaryFileReadDescData = tml::BaseBinaryFileReadDescData<true>;
using RawBinaryFileWriteDesc = tml::BaseBinaryFileWriteDesc<true>;
using RawBinaryFileWriteDescData = tml::BaseBinaryFileWriteDescData<true>;
}
