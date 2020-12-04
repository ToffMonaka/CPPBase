/**
 * @file
 * @brief TextFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include <list>
#include "File.h"


namespace tml {
/**
 * @brief TextFileDataクラス
 */
class TextFileData
{
public: TextFileData(const tml::TextFileData &) = delete;
public: tml::TextFileData &operator =(const tml::TextFileData &) = delete;

public:
	std::list<std::wstring> string_container;

private:
	void Release(void);

public:
	TextFileData();
	virtual ~TextFileData();

	void Init(void);
};
}


namespace tml {
/**
 * @brief TextFileReadPlanクラス
 */
class TextFileReadPlan
{
public:
	std::wstring file_path;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	TextFileReadPlan();
	virtual ~TextFileReadPlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief TextFileWritePlanクラス
 */
class TextFileWritePlan
{
public:
	std::wstring file_path;
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	TextFileWritePlan();
	virtual ~TextFileWritePlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief TextFileクラス
 */
class TextFile : public tml::File
{
public: TextFile(const tml::TextFile &) = delete;
public: tml::TextFile &operator =(const tml::TextFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::TextFileData data;
	tml::TextFileReadPlan read_plan;
	tml::TextFileWritePlan write_plan;

private:
	void Release(void);

public:
	TextFile();
	virtual ~TextFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}
