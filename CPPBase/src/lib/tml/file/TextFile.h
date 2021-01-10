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

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief TextFileReadPlanDataクラス
 */
class TextFileReadPlanData : public tml::BinaryFileReadPlanData
{
public:
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	TextFileReadPlanData();
	virtual ~TextFileReadPlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief TextFileReadPlanクラス
 */
class TextFileReadPlan
{
public:
	tml::TextFileReadPlanData data;
	tml::TextFileReadPlanData *parent_data;

public:
	TextFileReadPlan();
	virtual ~TextFileReadPlan();

	virtual void Init(void);

	tml::TextFileReadPlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::TextFileReadPlanData *tml::TextFileReadPlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief TextFileWritePlanDataクラス
 */
class TextFileWritePlanData : public tml::BinaryFileWritePlanData
{
public:
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;
	size_t add_newline_code_count;

public:
	TextFileWritePlanData();
	virtual ~TextFileWritePlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief TextFileWritePlanクラス
 */
class TextFileWritePlan
{
public:
	tml::TextFileWritePlanData data;
	tml::TextFileWritePlanData *parent_data;

public:
	TextFileWritePlan();
	virtual ~TextFileWritePlan();

	virtual void Init(void);

	tml::TextFileWritePlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::TextFileWritePlanData *tml::TextFileWritePlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
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
