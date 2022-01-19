/**
 * @file
 * @brief ConfigFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <map>
#include <regex>
#include "TextFile.h"


namespace tml {
/**
 * @brief BaseConfigFileDataクラス
 */
template <bool R>
class BaseConfigFileData
{
public: BaseConfigFileData(const tml::BaseConfigFileData<R> &) = delete;
public: tml::BaseConfigFileData<R> &operator =(const tml::BaseConfigFileData<R> &) = delete;

private:

public:
	std::map<std::wstring, std::wstring> value_container;

private:
	void Release(void);

public:
	BaseConfigFileData();
	virtual ~BaseConfigFileData();

	virtual void Init(void);

	const std::wstring *GetValue(const WCHAR *) const;
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseConfigFileData<R>::BaseConfigFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseConfigFileData<R>::~BaseConfigFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseConfigFileData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseConfigFileData<R>::Init(void)
{
	this->Release();

	this->value_container.clear();

	return;
}


/**
 * @brief GetValue関数
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
template <bool R>
inline const std::wstring *tml::BaseConfigFileData<R>::GetValue(const WCHAR *val_name) const
{
	auto val_itr = this->value_container.find(val_name);

	if (val_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}


namespace tml {
/**
 * @brief BaseConfigFileReadDescDataクラス
 */
template <bool R>
class BaseConfigFileReadDescData : public tml::BaseTextFileReadDescData<R>
{
public:

private:
	void Release(void);

public:
	BaseConfigFileReadDescData();
	virtual ~BaseConfigFileReadDescData();

	virtual void Init(void);
};

template <bool R>
using BaseConfigFileReadDesc = tml::FileReadDesc<tml::BaseConfigFileReadDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseConfigFileReadDescData<R>::BaseConfigFileReadDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseConfigFileReadDescData<R>::~BaseConfigFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseConfigFileReadDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseConfigFileReadDescData<R>::Init(void)
{
	this->Release();

	tml::BaseTextFileReadDescData<R>::Init();

	return;
}


namespace tml {
/**
 * @brief BaseConfigFileWriteDescDataクラス
 */
template <bool R>
class BaseConfigFileWriteDescData : public tml::BaseTextFileWriteDescData<R>
{
public:

private:
	void Release(void);

public:
	BaseConfigFileWriteDescData();
	virtual ~BaseConfigFileWriteDescData();

	virtual void Init(void);
};

template <bool R>
using BaseConfigFileWriteDesc = tml::FileWriteDesc<tml::BaseConfigFileWriteDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseConfigFileWriteDescData<R>::BaseConfigFileWriteDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseConfigFileWriteDescData<R>::~BaseConfigFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseConfigFileWriteDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseConfigFileWriteDescData<R>::Init(void)
{
	this->Release();

	tml::BaseTextFileWriteDescData<R>::Init();

	return;
}


namespace tml {
/**
 * @brief BaseConfigFileクラス
 */
template <bool R>
class BaseConfigFile : public tml::File
{
public: BaseConfigFile(const tml::BaseConfigFile<R> &) = delete;
public: tml::BaseConfigFile<R> &operator =(const tml::BaseConfigFile<R> &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::BaseConfigFileData<R> data;
	tml::BaseConfigFileReadDesc<R> read_desc;
	tml::BaseConfigFileWriteDesc<R> write_desc;

private:
	void Release(void);

public:
	BaseConfigFile();
	virtual ~BaseConfigFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseConfigFile<R>::BaseConfigFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseConfigFile<R>::~BaseConfigFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseConfigFile<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseConfigFile<R>::Init(void)
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
inline INT tml::BaseConfigFile<R>::Read(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring equal_str = L"=";
	static const std::wstring comment_str = L"#";
	static const std::wregex needless_pattern(L"^[\\s|　]+|[\\s|　]+$");

	auto read_desc_dat = this->read_desc.GetDataByParent();

	tml::BaseTextFile<R> txt_file;

	txt_file.read_desc.parent_data = read_desc_dat;

	if (txt_file.Read() < 0) {
		return (-1);
	}

	this->data.Init();

	if (txt_file.data.line_string_container.empty()) {
		return (0);
	}

	std::wstring line_str;
	size_t equal_str_index = 0U;
	size_t comment_str_index = 0U;
	std::wstring val_name;
	std::wstring val;

	for (auto &txt_file_line_str : txt_file.data.line_string_container) {
		if (txt_file_line_str.empty()) {
			continue;
		}

		line_str = txt_file_line_str;

		{// コメントを削除
			comment_str_index = line_str.find(comment_str);

			if (comment_str_index != std::wstring::npos) {
				line_str.erase(comment_str_index);
			}
		}

		if (line_str.empty()) {
			continue;
		}

		{// ｢=｣を確認
			equal_str_index = line_str.find(equal_str);

			if (equal_str_index == std::wstring::npos) {
				continue;
			}
		}

		val_name = line_str.substr(0U, equal_str_index);
		val_name = std::regex_replace(val_name.c_str(), needless_pattern, empty_str);

		if (val_name.empty()) {
			continue;
		}

		val = line_str.substr(equal_str_index + equal_str.length());
		val = std::regex_replace(val.c_str(), needless_pattern, empty_str);

		this->data.value_container.insert(std::make_pair(val_name, val));
	}

	return (0);
}


/**
 * @brief Write関数
 * @return result (result)<br>
 * 0未満=失敗
 */
template <bool R>
inline INT tml::BaseConfigFile<R>::Write(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring equal_str = L"=";

	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::BaseTextFile<R> txt_file;

	if (!this->data.value_container.empty()) {
		std::wstring line_str;

		for (auto &val : this->data.value_container) {
			line_str = val.first;
			line_str += equal_str;
			line_str += val.second;

			txt_file.data.line_string_container.push_back(line_str);
		}

		txt_file.data.line_string_container.push_back(empty_str);
	}

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write() < 0) {
		return (-1);
	}

	return (0);
}


namespace tml {
using ConfigFile = tml::BaseConfigFile<false>;
using ConfigFileData = tml::BaseConfigFileData<false>;
using ConfigFileReadDesc = tml::BaseConfigFileReadDesc<false>;
using ConfigFileReadDescData = tml::BaseConfigFileReadDescData<false>;
using ConfigFileWriteDesc = tml::BaseConfigFileWriteDesc<false>;
using ConfigFileWriteDescData = tml::BaseConfigFileWriteDescData<false>;

using RawConfigFile = tml::BaseConfigFile<true>;
using RawConfigFileData = tml::BaseConfigFileData<true>;
using RawConfigFileReadDesc = tml::BaseConfigFileReadDesc<true>;
using RawConfigFileReadDescData = tml::BaseConfigFileReadDescData<true>;
using RawConfigFileWriteDesc = tml::BaseConfigFileWriteDesc<true>;
using RawConfigFileWriteDescData = tml::BaseConfigFileWriteDescData<true>;
}
