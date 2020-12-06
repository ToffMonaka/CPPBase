/**
 * @file
 * @brief CSVFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include "File.h"


namespace tml {
/**
 * @brief CSVFileDataクラス
 */
class CSVFileData
{
public: CSVFileData(const tml::CSVFileData &) = delete;
public: tml::CSVFileData &operator =(const tml::CSVFileData &) = delete;

public:

private:
	void Release(void);

public:
	CSVFileData();
	virtual ~CSVFileData();

	void Init(void);
};
}


namespace tml {
/**
 * @brief CSVFileReadPlanクラス
 */
class CSVFileReadPlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	CSVFileReadPlan();
	virtual ~CSVFileReadPlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief CSVFileWritePlanクラス
 */
class CSVFileWritePlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	bool add_flag;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	CSVFileWritePlan();
	virtual ~CSVFileWritePlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief CSVFileクラス
 */
class CSVFile : public tml::File
{
public: CSVFile(const tml::CSVFile &) = delete;
public: tml::CSVFile &operator =(const tml::CSVFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::CSVFileData data;
	tml::CSVFileReadPlan read_plan;
	tml::CSVFileWritePlan write_plan;

private:
	void Release(void);

public:
	CSVFile();
	virtual ~CSVFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}
