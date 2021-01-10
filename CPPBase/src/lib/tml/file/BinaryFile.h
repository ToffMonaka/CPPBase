/**
 * @file
 * @brief BinaryFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/DynamicBuffer.h"
#include "File.h"


namespace tml {
/**
 * @brief BinaryFileDataクラス
 */
class BinaryFileData
{
public:
	tml::DynamicBuffer file_buffer;

public:
	BinaryFileData();
	virtual ~BinaryFileData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileReadPlanDataクラス
 */
class BinaryFileReadPlanData
{
public:
	std::wstring file_path;
	tml::DynamicBuffer file_buffer;
	size_t one_buffer_size;

public:
	BinaryFileReadPlanData();
	virtual ~BinaryFileReadPlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileReadPlanクラス
 */
class BinaryFileReadPlan
{
public:
	tml::BinaryFileReadPlanData data;
	tml::BinaryFileReadPlanData *parent_data;

public:
	BinaryFileReadPlan();
	virtual ~BinaryFileReadPlan();

	virtual void Init(void);

	tml::BinaryFileReadPlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::BinaryFileReadPlanData *tml::BinaryFileReadPlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief BinaryFileWritePlanDataクラス
 */
class BinaryFileWritePlanData
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	bool add_flag;

public:
	BinaryFileWritePlanData();
	virtual ~BinaryFileWritePlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileWritePlanクラス
 */
class BinaryFileWritePlan
{
public:
	tml::BinaryFileWritePlanData data;
	tml::BinaryFileWritePlanData *parent_data;

public:
	BinaryFileWritePlan();
	virtual ~BinaryFileWritePlan();

	virtual void Init(void);

	tml::BinaryFileWritePlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::BinaryFileWritePlanData *tml::BinaryFileWritePlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief BinaryFileクラス
 */
class BinaryFile : public tml::File
{
public: BinaryFile(const tml::BinaryFile &) = delete;
public: tml::BinaryFile &operator =(const tml::BinaryFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::BinaryFileData data;
	tml::BinaryFileReadPlan read_plan;
	tml::BinaryFileWritePlan write_plan;

private:
	void Release(void);

public:
	BinaryFile();
	virtual ~BinaryFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}
