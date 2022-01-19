/**
 * @file
 * @brief INIFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <map>
#include <regex>
#include "TextFile.h"


namespace tml {
/**
 * @brief BaseINIFileDataクラス
 */
template <bool R>
class BaseINIFileData
{
public: BaseINIFileData(const tml::BaseINIFileData<R> &) = delete;
public: tml::BaseINIFileData<R> &operator =(const tml::BaseINIFileData<R> &) = delete;

private:

public:
	std::map<std::wstring, std::map<std::wstring, std::wstring>> value_container;

private:
	void Release(void);

public:
	BaseINIFileData();
	virtual ~BaseINIFileData();

	virtual void Init(void);

	const std::map<std::wstring, std::wstring> *GetValueNameContainer(const WCHAR *) const;
	const std::wstring *GetValue(const std::map<std::wstring, std::wstring> &, const WCHAR *) const;
	const std::wstring *GetValue(const WCHAR *, const WCHAR *) const;
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseINIFileData<R>::BaseINIFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseINIFileData<R>::~BaseINIFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseINIFileData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseINIFileData<R>::Init(void)
{
	this->Release();

	this->value_container.clear();

	return;
}


/**
 * @brief GetValueNameContainer関数
 * @param section_name (section_name)
 * @return val_name_cont (valalue_name_container)<br>
 * nullptr=失敗
 */
template <bool R>
inline const std::map<std::wstring, std::wstring> *tml::BaseINIFileData<R>::GetValueNameContainer(const WCHAR *section_name) const
{
	auto val_name_itr = this->value_container.find(section_name);

	if (val_name_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_name_itr->second);
}


/**
 * @brief GetValue関数
 * @param val_name_cont (valalue_name_container)
 * @param val_name (valalue_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
template <bool R>
inline const std::wstring *tml::BaseINIFileData<R>::GetValue(const std::map<std::wstring, std::wstring> &val_name_cont, const WCHAR *val_name) const
{
	auto val_itr = val_name_cont.find(val_name);

	if (val_itr == val_name_cont.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}


/**
 * @brief GetValue関数
 * @param section_name (section_name)
 * @param val_name (valalue_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
template <bool R>
inline const std::wstring *tml::BaseINIFileData<R>::GetValue(const WCHAR *section_name, const WCHAR *val_name) const
{
	auto val_name_itr = this->value_container.find(section_name);

	if (val_name_itr == this->value_container.end()) {
		return (nullptr);
	}

	auto val_itr = val_name_itr->second.find(val_name);

	if (val_itr == val_name_itr->second.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}


namespace tml {
/**
 * @brief BaseINIFileReadDescDataクラス
 */
template <bool R>
class BaseINIFileReadDescData : public tml::BaseTextFileReadDescData<R>
{
public:

private:
	void Release(void);

public:
	BaseINIFileReadDescData();
	virtual ~BaseINIFileReadDescData();

	virtual void Init(void);
};

template <bool R>
using BaseINIFileReadDesc = tml::FileReadDesc<tml::BaseINIFileReadDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseINIFileReadDescData<R>::BaseINIFileReadDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseINIFileReadDescData<R>::~BaseINIFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseINIFileReadDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseINIFileReadDescData<R>::Init(void)
{
	this->Release();

	tml::BaseTextFileReadDescData<R>::Init();

	return;
}


namespace tml {
/**
 * @brief BaseINIFileWriteDescDataクラス
 */
template <bool R>
class BaseINIFileWriteDescData : public tml::BaseTextFileWriteDescData<R>
{
public:

private:
	void Release(void);

public:
	BaseINIFileWriteDescData();
	virtual ~BaseINIFileWriteDescData();

	virtual void Init(void);
};

template <bool R>
using BaseINIFileWriteDesc = tml::FileWriteDesc<tml::BaseINIFileWriteDescData<R>>;
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseINIFileWriteDescData<R>::BaseINIFileWriteDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseINIFileWriteDescData<R>::~BaseINIFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseINIFileWriteDescData<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseINIFileWriteDescData<R>::Init(void)
{
	this->Release();

	tml::BaseTextFileWriteDescData<R>::Init();

	return;
}


namespace tml {
/**
 * @brief BaseINIFileクラス
 */
template <bool R>
class BaseINIFile : public tml::File
{
public: BaseINIFile(const tml::BaseINIFile<R> &) = delete;
public: tml::BaseINIFile<R> &operator =(const tml::BaseINIFile<R> &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::BaseINIFileData<R> data;
	tml::BaseINIFileReadDesc<R> read_desc;
	tml::BaseINIFileWriteDesc<R> write_desc;

private:
	void Release(void);

public:
	BaseINIFile();
	virtual ~BaseINIFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseINIFile<R>::BaseINIFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseINIFile<R>::~BaseINIFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseINIFile<R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseINIFile<R>::Init(void)
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
inline INT tml::BaseINIFile<R>::Read(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring section_start_str = L"[";
	static const std::wstring section_end_str = L"]";
	static const std::wstring equal_str = L"=";
	static const std::wstring comment_str = L";";
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
	size_t section_start_str_index = 0U;
	size_t section_end_str_index = 0U;
	size_t equal_str_index = 0U;
	size_t comment_str_index = 0U;
	std::wstring section_name;
	std::wstring tmp_section_name;
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
				section_start_str_index = line_str.find(section_start_str);

				if (section_start_str_index == std::wstring::npos) {
					continue;
				}

				section_end_str_index = line_str.find(section_end_str, section_start_str_index + section_start_str.length());

				if (section_end_str_index == std::wstring::npos) {
					continue;
				}

				tmp_section_name = line_str.substr(section_start_str_index + section_start_str.length(), section_end_str_index - (section_start_str_index + section_start_str.length()));

				if (!tmp_section_name.empty()) {
					section_name = tmp_section_name;

					auto val_name_itr = this->data.value_container.find(section_name);

					if (val_name_itr == this->data.value_container.end()) {
						std::map<std::wstring, std::wstring> val_name_cont;

						this->data.value_container.insert(std::make_pair(section_name, val_name_cont));
					}
				}

				continue;
			}
		}

		auto val_name_itr = this->data.value_container.find(section_name);

		if (val_name_itr == this->data.value_container.end()) {
			continue;
		}

		val_name = line_str.substr(0U, equal_str_index);
		val_name = std::regex_replace(val_name.c_str(), needless_pattern, empty_str);

		if (val_name.empty()) {
			continue;
		}

		val = line_str.substr(equal_str_index + equal_str.length());
		val = std::regex_replace(val.c_str(), needless_pattern, empty_str);

		val_name_itr->second.insert(std::make_pair(val_name, val));
	}

	return (0);
}


/**
 * @brief Write関数
 * @return result (result)<br>
 * 0未満=失敗
 */
template <bool R>
inline INT tml::BaseINIFile<R>::Write(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring section_start_str = L"[";
	static const std::wstring section_end_str = L"]";
	static const std::wstring equal_str = L"=";

	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::BaseTextFile<R> txt_file;

	if (!this->data.value_container.empty()) {
		std::wstring line_str;

		for (auto &val_name_cont : this->data.value_container) {
			line_str = section_start_str;
			line_str += val_name_cont.first;
			line_str += section_end_str;

			txt_file.data.line_string_container.push_back(line_str);

			for (auto &val : val_name_cont.second) {
				line_str = val.first;
				line_str += equal_str;
				line_str += val.second;

				txt_file.data.line_string_container.push_back(line_str);
			}

			txt_file.data.line_string_container.push_back(empty_str);
		}
	}

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write() < 0) {
		return (-1);
	}

	return (0);
}


namespace tml {
using INIFile = tml::BaseINIFile<false>;
using INIFileData = tml::BaseINIFileData<false>;
using INIFileReadDesc = tml::BaseINIFileReadDesc<false>;
using INIFileReadDescData = tml::BaseINIFileReadDescData<false>;
using INIFileWriteDesc = tml::BaseINIFileWriteDesc<false>;
using INIFileWriteDescData = tml::BaseINIFileWriteDescData<false>;

using RawINIFile = tml::BaseINIFile<true>;
using RawINIFileData = tml::BaseINIFileData<true>;
using RawINIFileReadDesc = tml::BaseINIFileReadDesc<true>;
using RawINIFileReadDescData = tml::BaseINIFileReadDescData<true>;
using RawINIFileWriteDesc = tml::BaseINIFileWriteDesc<true>;
using RawINIFileWriteDescData = tml::BaseINIFileWriteDescData<true>;
}
