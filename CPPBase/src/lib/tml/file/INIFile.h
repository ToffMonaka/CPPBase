/**
 * @file
 * @brief INIFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include "File.h"


namespace tml {
/**
 * @brief INIFileDataクラス
 */
class INIFileData
{
public: INIFileData(const tml::INIFileData &) = delete;
public: tml::INIFileData &operator =(const tml::INIFileData &) = delete;

public:

private:
	void Release(void);

public:
	INIFileData();
	virtual ~INIFileData();

	void Init(void);
};
}


namespace tml {
/**
 * @brief INIFileReadPlanクラス
 */
class INIFileReadPlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	INIFileReadPlan();
	virtual ~INIFileReadPlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief INIFileWritePlanクラス
 */
class INIFileWritePlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	bool add_flag;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	INIFileWritePlan();
	virtual ~INIFileWritePlan();

	void Init(void);
};
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
	tml::INIFileReadPlan read_plan;
	tml::INIFileWritePlan write_plan;

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
