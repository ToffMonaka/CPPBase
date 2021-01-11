/**
 * @file
 * @brief ConfigFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <map>
#include "TextFile.h"


namespace tml {
/**
 * @brief ConfigFileData�N���X
 */
class ConfigFileData
{
public:
	std::map<std::wstring, std::wstring> value_container;

public:
	ConfigFileData();
	virtual ~ConfigFileData();

	virtual void Init(void);

	std::wstring *GetValue(const WCHAR *);
};
}


/**
 * @brief GetValue�֐�
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=���s
 */
inline std::wstring *tml::ConfigFileData::GetValue(const WCHAR *val_name)
{
	auto val_itr = this->value_container.find(val_name);

	if (val_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}


namespace tml {
/**
 * @brief ConfigFileReadDescData�N���X
 */
class ConfigFileReadDescData : public tml::TextFileReadDescData
{
public:
	ConfigFileReadDescData();
	virtual ~ConfigFileReadDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief ConfigFileReadDesc�N���X
 */
class ConfigFileReadDesc
{
public:
	tml::ConfigFileReadDescData data;
	tml::ConfigFileReadDescData *parent_data;

public:
	ConfigFileReadDesc();
	virtual ~ConfigFileReadDesc();

	virtual void Init(void);

	tml::ConfigFileReadDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::ConfigFileReadDescData *tml::ConfigFileReadDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief ConfigFileWriteDescData�N���X
 */
class ConfigFileWriteDescData : public tml::TextFileWriteDescData
{
public:
	ConfigFileWriteDescData();
	virtual ~ConfigFileWriteDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief ConfigFileWriteDesc�N���X
 */
class ConfigFileWriteDesc
{
public:
	tml::ConfigFileWriteDescData data;
	tml::ConfigFileWriteDescData *parent_data;

public:
	ConfigFileWriteDesc();
	virtual ~ConfigFileWriteDesc();

	virtual void Init(void);

	tml::ConfigFileWriteDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::ConfigFileWriteDescData *tml::ConfigFileWriteDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief ConfigFile�N���X
 */
class ConfigFile : public tml::File
{
public: ConfigFile(const tml::ConfigFile &) = delete;
public: tml::ConfigFile &operator =(const tml::ConfigFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::ConfigFileData data;
	tml::ConfigFileReadDesc read_desc;
	tml::ConfigFileWriteDesc write_desc;

private:
	void Release(void);

public:
	ConfigFile();
	virtual ~ConfigFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}
