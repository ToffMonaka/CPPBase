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

private:
	void Release(void);

public:
	ConfigFileData();
	virtual ~ConfigFileData();

	virtual void Init(void);

	const std::wstring *GetValue(const WCHAR *) const;
};
}


/**
 * @brief Release�֐�
 */
inline void tml::ConfigFileData::Release(void)
{
	return;
}


/**
 * @brief GetValue�֐�
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=���s
 */
inline const std::wstring *tml::ConfigFileData::GetValue(const WCHAR *val_name) const
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

private:
	void Release(void);

public:
	ConfigFileReadDescData();
	virtual ~ConfigFileReadDescData();

	virtual void Init(void);
};

using ConfigFileReadDesc = tml::FileReadDesc<tml::ConfigFileReadDescData>;
}


/**
 * @brief Release�֐�
 */
inline void tml::ConfigFileReadDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief ConfigFileWriteDescData�N���X
 */
class ConfigFileWriteDescData : public tml::TextFileWriteDescData
{
public:

private:
	void Release(void);

public:
	ConfigFileWriteDescData();
	virtual ~ConfigFileWriteDescData();

	virtual void Init(void);
};

using ConfigFileWriteDesc = tml::FileWriteDesc<tml::ConfigFileWriteDescData>;
}


/**
 * @brief Release�֐�
 */
inline void tml::ConfigFileWriteDescData::Release(void)
{
	return;
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


/**
 * @brief Release�֐�
 */
inline void tml::ConfigFile::Release(void)
{
	return;
}
