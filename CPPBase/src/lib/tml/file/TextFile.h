/**
 * @file
 * @brief TextFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include <list>
#include "BinaryFile.h"


namespace tml {
/**
 * @brief TextFileDataクラス
 */
class TextFileData
{
public:
	std::list<std::wstring> string_container;

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
class TextFileReadPlan : public tml::BinaryFileReadPlan
{
public:
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
class TextFileWritePlan : public tml::BinaryFileWritePlan
{
public:
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;
	size_t add_newline_code_count;

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
