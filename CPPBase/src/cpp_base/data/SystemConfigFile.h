/**
 * @file
 * @brief SystemConfigFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
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
	size_t window_x;
	size_t window_y;
	size_t window_width;
	size_t window_height;

public:
	SystemConfigFileData();
	virtual ~SystemConfigFileData();

	virtual void Init(void);
};
}


namespace cpp_base {
/**
 * @brief SystemConfigFileReadPlanクラス
 */
class SystemConfigFileReadPlan : public tml::INIFileReadPlan
{
public:
	SystemConfigFileReadPlan();
	virtual ~SystemConfigFileReadPlan();

	virtual void Init(void);
};
}


namespace cpp_base {
/**
 * @brief SystemConfigFileWritePlanクラス
 */
class SystemConfigFileWritePlan : public tml::INIFileWritePlan
{
public:
	SystemConfigFileWritePlan();
	virtual ~SystemConfigFileWritePlan();

	virtual void Init(void);
};
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
	cpp_base::SystemConfigFileReadPlan read_plan;
	cpp_base::SystemConfigFileWritePlan write_plan;

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
