/**
 * @file
 * @brief INIFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <map>
#include "TextFile.h"


namespace tml {
/**
 * @brief INIFileDataクラス
 */
class INIFileData
{
public: INIFileData(const tml::INIFileData &) = delete;
public: tml::INIFileData &operator =(const tml::INIFileData &) = delete;

private:

public:
	std::map<std::wstring, std::map<std::wstring, std::wstring>> value_container;

private:
	void Release(void);

public:
	INIFileData();
	virtual ~INIFileData();

	virtual void Init(void);

	const std::map<std::wstring, std::wstring> *GetValueNameContainer(const WCHAR *) const;
	const std::wstring *GetValue(const std::map<std::wstring, std::wstring> &, const WCHAR *) const;
	const std::wstring *GetValue(const WCHAR *, const WCHAR *) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::INIFileData::Release(void)
{
	return;
}


/**
 * @brief GetValueNameContainer関数
 * @param section_name (section_name)
 * @return val_name_cont (valalue_name_container)<br>
 * nullptr=失敗
 */
inline const std::map<std::wstring, std::wstring> *tml::INIFileData::GetValueNameContainer(const WCHAR *section_name) const
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
inline const std::wstring *tml::INIFileData::GetValue(const std::map<std::wstring, std::wstring> &val_name_cont, const WCHAR *val_name) const
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
inline const std::wstring *tml::INIFileData::GetValue(const WCHAR *section_name, const WCHAR *val_name) const
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
 * @brief INIFileReadDescDataクラス
 */
class INIFileReadDescData : public tml::TextFileReadDescData
{
public:

private:
	void Release(void);

public:
	INIFileReadDescData();
	virtual ~INIFileReadDescData();

	virtual void Init(void);
};

using INIFileReadDesc = tml::FileReadDesc<tml::INIFileReadDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::INIFileReadDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief INIFileWriteDescDataクラス
 */
class INIFileWriteDescData : public tml::TextFileWriteDescData
{
public:

private:
	void Release(void);

public:
	INIFileWriteDescData();
	virtual ~INIFileWriteDescData();

	virtual void Init(void);
};

using INIFileWriteDesc = tml::FileWriteDesc<tml::INIFileWriteDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::INIFileWriteDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief INIFileクラス
 */
class INIFile : public tml::File
{
public: INIFile(const tml::INIFile &) = delete;
public: tml::INIFile &operator =(const tml::INIFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::INIFileData data;
	tml::INIFileReadDesc read_desc;
	tml::INIFileWriteDesc write_desc;

private:
	void Release(void);

public:
	INIFile();
	virtual ~INIFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::INIFile::Release(void)
{
	return;
}
