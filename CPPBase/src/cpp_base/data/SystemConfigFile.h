/**
 * @file
 * @brief SystemConfigFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/math/XNAMath.h"
#include "../../lib/tml/file/INIFile.h"


namespace cpp_base {
/**
 * @brief SystemConfigFileDataクラス
 */
class SystemConfigFileData
{
public:
	size_t application_memory_allocator_size;
	std::string application_locale_name;
	tml::XMUINT2EX window_position;
	tml::XMUINT2EX window_size;

protected:
	void Release(void);

public:
	SystemConfigFileData();
	virtual ~SystemConfigFileData();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void cpp_base::SystemConfigFileData::Release(void)
{
	return;
}


namespace cpp_base {
/**
 * @brief SystemConfigFileクラス
 */
class SystemConfigFile : public tml::File
{
public: SystemConfigFile(const cpp_base::SystemConfigFile &) = delete;
public: cpp_base::SystemConfigFile &operator =(const cpp_base::SystemConfigFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	cpp_base::SystemConfigFileData data;
	tml::INIFileReadDesc read_desc;
	tml::INIFileWriteDesc write_desc;

protected:
	void Release(void);

public:
	SystemConfigFile();
	virtual ~SystemConfigFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release関数
 */
inline void cpp_base::SystemConfigFile::Release(void)
{
	tml::File::Release();

	return;
}
