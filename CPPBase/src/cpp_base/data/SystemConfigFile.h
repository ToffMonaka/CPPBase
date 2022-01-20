/**
 * @file
 * @brief SystemConfigFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/math/XNAMathVector.h"
#include "../../lib/tml/file/INIFile.h"


namespace cpp_base {
/**
 * @brief SystemConfigFileDataクラス
 *
 * Rawタイプ
 */
class SystemConfigFileData
{
public: SystemConfigFileData(const cpp_base::SystemConfigFileData &) = delete;
public: cpp_base::SystemConfigFileData &operator =(const cpp_base::SystemConfigFileData &) = delete;

private:

public:
	UINT application_frame_rate_limit;
	tml::XMUINT2EX window_position;
	tml::XMUINT2EX window_size;
	UINT graphic_frame_rate_limit;
	bool graphic_vsync_flag;
	FLOAT sound_bgm_volume;
	bool sound_bgm_mute_flag;
	FLOAT sound_se_volume;
	bool sound_se_mute_flag;

private:
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
 *
 * Rawタイプ
 */
class SystemConfigFile : public tml::File
{
public: SystemConfigFile(const cpp_base::SystemConfigFile &) = delete;
public: cpp_base::SystemConfigFile &operator =(const cpp_base::SystemConfigFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	cpp_base::SystemConfigFileData data;
	tml::RawINIFileReadDesc read_desc;
	tml::RawINIFileWriteDesc write_desc;

private:
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
	return;
}
