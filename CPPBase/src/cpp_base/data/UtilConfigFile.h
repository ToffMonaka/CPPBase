/**
 * @file
 * @brief UtilConfigFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/math/XNAMathVector.h"
#include "../../lib/tml/file/INIFile.h"


namespace cpp_base {
/**
 * @brief UtilConfigFileDataクラス
 *
 * Rawタイプ
 */
class UtilConfigFileData
{
public: UtilConfigFileData(const cpp_base::UtilConfigFileData &) = delete;
public: cpp_base::UtilConfigFileData &operator =(const cpp_base::UtilConfigFileData &) = delete;

private:

public:
	size_t util_memory_allocator_size;
	std::string util_locale_name;

private:
	void Release(void);

public:
	UtilConfigFileData();
	virtual ~UtilConfigFileData();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void cpp_base::UtilConfigFileData::Release(void)
{
	return;
}


namespace cpp_base {
/**
 * @brief UtilConfigFileクラス
 *
 * Rawタイプ
 */
class UtilConfigFile : public tml::File
{
public: UtilConfigFile(const cpp_base::UtilConfigFile &) = delete;
public: cpp_base::UtilConfigFile &operator =(const cpp_base::UtilConfigFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	cpp_base::UtilConfigFileData data;
	tml::RawINIFileReadDesc read_desc;
	tml::RawINIFileWriteDesc write_desc;

private:
	void Release(void);

public:
	UtilConfigFile();
	virtual ~UtilConfigFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release関数
 */
inline void cpp_base::UtilConfigFile::Release(void)
{
	return;
}
