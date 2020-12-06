/**
 * @file
 * @brief ConfigFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include "File.h"


namespace tml {
/**
 * @brief ConfigFileDataクラス
 */
class ConfigFileData
{
public: ConfigFileData(const tml::ConfigFileData &) = delete;
public: tml::ConfigFileData &operator =(const tml::ConfigFileData &) = delete;

public:

private:
	void Release(void);

public:
	ConfigFileData();
	virtual ~ConfigFileData();

	void Init(void);
};
}


namespace tml {
/**
 * @brief ConfigFileReadPlanクラス
 */
class ConfigFileReadPlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	ConfigFileReadPlan();
	virtual ~ConfigFileReadPlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief ConfigFileWritePlanクラス
 */
class ConfigFileWritePlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	bool add_flag;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	ConfigFileWritePlan();
	virtual ~ConfigFileWritePlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief ConfigFileクラス
 */
class ConfigFile : public tml::File
{
public: ConfigFile(const tml::ConfigFile &) = delete;
public: tml::ConfigFile &operator =(const tml::ConfigFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::ConfigFileData data;
	tml::ConfigFileReadPlan read_plan;
	tml::ConfigFileWritePlan write_plan;

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
