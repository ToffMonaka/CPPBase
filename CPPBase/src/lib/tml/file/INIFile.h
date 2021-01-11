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
public:
	std::map<std::wstring, std::map<std::wstring, std::wstring>> value_container;

public:
	INIFileData();
	virtual ~INIFileData();

	virtual void Init(void);

	std::map<std::wstring, std::wstring> *GetValueNameContainer(const WCHAR *);
	std::wstring *GetValue(const WCHAR *, const WCHAR *);
	std::wstring *GetValue(std::map<std::wstring, std::wstring> &, const WCHAR *);
};
}


/**
 * @brief GetValueNameContainer関数
 * @param section_name (section_name)
 * @return val_name_cont (valalue_name_container)<br>
 * nullptr=失敗
 */
inline std::map<std::wstring, std::wstring> *tml::INIFileData::GetValueNameContainer(const WCHAR *section_name)
{
	auto val_name_itr = this->value_container.find(section_name);

	if (val_name_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_name_itr->second);
}


/**
 * @brief GetValue関数
 * @param section_name (section_name)
 * @param val_name (valalue_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline std::wstring *tml::INIFileData::GetValue(const WCHAR *section_name, const WCHAR *val_name)
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


/**
 * @brief GetValue関数
 * @param val_name_cont (valalue_name_container)
 * @param val_name (valalue_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline std::wstring *tml::INIFileData::GetValue(std::map<std::wstring, std::wstring> &val_name_cont, const WCHAR *val_name)
{
	auto val_itr = val_name_cont.find(val_name);

	if (val_itr == val_name_cont.end()) {
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
	INIFileReadDescData();
	virtual ~INIFileReadDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief INIFileReadDescクラス
 */
class INIFileReadDesc
{
public:
	tml::INIFileReadDescData data;
	tml::INIFileReadDescData *parent_data;

public:
	INIFileReadDesc();
	virtual ~INIFileReadDesc();

	virtual void Init(void);

	tml::INIFileReadDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::INIFileReadDescData *tml::INIFileReadDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief INIFileWriteDescDataクラス
 */
class INIFileWriteDescData : public tml::TextFileWriteDescData
{
public:
	INIFileWriteDescData();
	virtual ~INIFileWriteDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief INIFileWriteDescクラス
 */
class INIFileWriteDesc
{
public:
	tml::INIFileWriteDescData data;
	tml::INIFileWriteDescData *parent_data;

public:
	INIFileWriteDesc();
	virtual ~INIFileWriteDesc();

	virtual void Init(void);

	tml::INIFileWriteDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::INIFileWriteDescData *tml::INIFileWriteDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
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
