/**
 * @file
 * @brief TextFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include <list>
#include "../string/StringUtil.h"
#include "BinaryFile.h"


namespace tml {
/**
 * @brief BaseTextFileDataクラス
 */
template <bool R>
class BaseTextFileData
{
public: BaseTextFileData(const tml::BaseTextFileData<R> &) = delete;
public: tml::BaseTextFileData<R> &operator =(const tml::BaseTextFileData<R> &) = delete;

private:

public:
	std::list<std::wstring> line_string_container;

private:
	void Release(void);

public:
	BaseTextFileData();
	virtual ~BaseTextFileData();

	virtual void Init(void);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseTextFileData<R>::BaseTextFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseTextFileData<R>::~BaseTextFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseTextFileData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseTextFileData<R>::Init(void)
{
	this->Release();

	this->line_string_container.clear();

	return;
}


namespace tml {
/**
 * @brief BaseTextFileReadDescDataクラス
 */
template <bool R>
class BaseTextFileReadDescData : public tml::BaseBinaryFileReadDescData<R>
{
public:
	std::wstring string;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

private:
	void Release(void);

public:
	BaseTextFileReadDescData();
	virtual ~BaseTextFileReadDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

template <bool R>
using BaseTextFileReadDesc = tml::FileReadDesc<tml::BaseTextFileReadDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseTextFileReadDescData<R>::BaseTextFileReadDescData() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseTextFileReadDescData<R>::~BaseTextFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseTextFileReadDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseTextFileReadDescData<R>::Init(void)
{
	this->Release();

	this->string.clear();
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	tml::BaseBinaryFileReadDescData<R>::Init();

	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
template <bool R>
inline bool tml::BaseTextFileReadDescData<R>::IsEmpty(void) const
{
	if (!this->string.empty()) {
		return (false);
	}

	return (tml::BaseBinaryFileReadDescData<R>::IsEmpty());
}


namespace tml {
/**
 * @brief BaseTextFileWriteDescDataクラス
 */
template <bool R>
class BaseTextFileWriteDescData : public tml::BaseBinaryFileWriteDescData<R>
{
public:
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;
	size_t add_newline_code_count;

private:
	void Release(void);

public:
	BaseTextFileWriteDescData();
	virtual ~BaseTextFileWriteDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

template <bool R>
using BaseTextFileWriteDesc = tml::FileWriteDesc<tml::BaseTextFileWriteDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseTextFileWriteDescData<R>::BaseTextFileWriteDescData() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF),
	add_newline_code_count(1U)
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseTextFileWriteDescData<R>::~BaseTextFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseTextFileWriteDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseTextFileWriteDescData<R>::Init(void)
{
	this->Release();

	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;
	this->add_newline_code_count = 1U;

	tml::BaseBinaryFileWriteDescData<R>::Init();

	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
template <bool R>
inline bool tml::BaseTextFileWriteDescData<R>::IsEmpty(void) const
{
	return (tml::BaseBinaryFileWriteDescData<R>::IsEmpty());
}


namespace tml {
/**
 * @brief BaseTextFileクラス
 */
template <bool R>
class BaseTextFile : public tml::File
{
public: BaseTextFile(const tml::BaseTextFile<R> &) = delete;
public: tml::BaseTextFile<R> &operator =(const tml::BaseTextFile<R> &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::BaseTextFileData<R> data;
	tml::BaseTextFileReadDesc<R> read_desc;
	tml::BaseTextFileWriteDesc<R> write_desc;

private:
	void Release(void);

public:
	BaseTextFile();
	virtual ~BaseTextFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseTextFile<R>::BaseTextFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseTextFile<R>::~BaseTextFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseTextFile<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseTextFile<R>::Init(void)
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
template <bool R>
inline INT tml::BaseTextFile<R>::Read(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	if (read_desc_dat->file_path.empty()) {
		if (read_desc_dat->buffer.GetLength() <= 0U) {
			if (!read_desc_dat->string.empty()) {
				this->data.Init();

				tml::StringUtil::Split(this->data.line_string_container, read_desc_dat->string.c_str(), tml::ConstantUtil::NEWLINE_CODE::GetStringW(read_desc_dat->newline_code_type));

				return (0);
			}

			this->data.Init();

			return (0);
		}
	}

	tml::BaseBinaryFile<R> bin_file;

	bin_file.read_desc.parent_data = read_desc_dat;

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

	tml::StringUtil::GetStringBase<R>(str, tmp_str);

	tml::StringUtil::Split(this->data.line_string_container, str.c_str(), tml::ConstantUtil::NEWLINE_CODE::GetStringW(read_desc_dat->newline_code_type));

	return (0);
}


/**
 * @brief Write関数
 * @return result (result)<br>
 * 0未満=失敗
 */
template <bool R>
inline INT tml::BaseTextFile<R>::Write(void)
{
	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	std::wstring tmp_str;

	tml::StringUtil::Join(tmp_str, this->data.line_string_container, tml::ConstantUtil::NEWLINE_CODE::GetStringW(write_desc_dat->newline_code_type));

	if (!tmp_str.empty()) {
		if ((write_desc_dat->add_flag)
		&& (write_desc_dat->add_newline_code_count > 0U)) {
			std::wstring add_newline_code_str;

			for (size_t add_newline_code_i = 0U; add_newline_code_i < write_desc_dat->add_newline_code_count; ++add_newline_code_i) {
				add_newline_code_str += tml::ConstantUtil::NEWLINE_CODE::GetStringW(write_desc_dat->newline_code_type);
			}

			tmp_str.insert(0U, add_newline_code_str);
		}
	}

	std::string str;

	tml::StringUtil::GetStringBase<R>(str, tmp_str.c_str());

	tml::BaseBinaryFile<R> bin_file;

	bin_file.data.buffer.SetSize(str.length());
	bin_file.data.buffer.WriteArray(reinterpret_cast<const BYTE *>(str.c_str()), str.length(), str.length());

	bin_file.write_desc.parent_data = write_desc_dat;

	if (bin_file.Write() < 0) {
		return (-1);
	}

	return (0);
}


namespace tml {
using TextFile = tml::BaseTextFile<false>;
using TextFileData = tml::BaseTextFileData<false>;
using TextFileReadDesc = tml::BaseTextFileReadDesc<false>;
using TextFileReadDescData = tml::BaseTextFileReadDescData<false>;
using TextFileWriteDesc = tml::BaseTextFileWriteDesc<false>;
using TextFileWriteDescData = tml::BaseTextFileWriteDescData<false>;

using RawTextFile = tml::BaseTextFile<true>;
using RawTextFileData = tml::BaseTextFileData<true>;
using RawTextFileReadDesc = tml::BaseTextFileReadDesc<true>;
using RawTextFileReadDescData = tml::BaseTextFileReadDescData<true>;
using RawTextFileWriteDesc = tml::BaseTextFileWriteDesc<true>;
using RawTextFileWriteDescData = tml::BaseTextFileWriteDescData<true>;
}
