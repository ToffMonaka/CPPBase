/**
 * @file
 * @brief CSVFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "TextFile.h"


namespace tml {
/**
 * @brief CSVFileData�N���X
 */
class CSVFileData
{
public:
	std::vector<std::vector<std::wstring>> value_container;

public:
	CSVFileData();
	virtual ~CSVFileData();

	virtual void Init(void);

	size_t GetRowCount(void) const;
	size_t GetColumnCount(void) const;
	std::wstring *GetValue(const size_t, const size_t);
};
}


/**
 * @brief GetRowCount�֐�
 * @return row_cnt (row_count)
 */
inline size_t tml::CSVFileData::GetRowCount(void) const
{
	return (this->value_container.size());
}


/**
 * @brief GetColumnCount�֐�
 * @return column_cnt (column_count)
 */
inline size_t tml::CSVFileData::GetColumnCount(void) const
{
	if (this->value_container.empty()) {
		return (0U);
	}
	
	return (this->value_container[0].size());
}


/**
 * @brief GetValue�֐�
 * @param row_index (row_index)
 * @param column_index (column_index)
 * @return val (value)<br>
 * nullptr=���s
 */
inline std::wstring *tml::CSVFileData::GetValue(const size_t row_index, const size_t column_index)
{
	if ((row_index >= this->value_container.size())
	|| (column_index >= this->value_container[row_index].size())) {
		return (nullptr);
	}

	return (&this->value_container[row_index][column_index]);
}


namespace tml {
/**
 * @brief CSVFileReadPlanData�N���X
 */
class CSVFileReadPlanData : public tml::TextFileReadPlanData
{
public:
	CSVFileReadPlanData();
	virtual ~CSVFileReadPlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief CSVFileReadPlan�N���X
 */
class CSVFileReadPlan
{
public:
	tml::CSVFileReadPlanData data;
	tml::CSVFileReadPlanData *parent_data;

public:
	CSVFileReadPlan();
	virtual ~CSVFileReadPlan();

	virtual void Init(void);

	tml::CSVFileReadPlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::CSVFileReadPlanData *tml::CSVFileReadPlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief CSVFileWritePlanData�N���X
 */
class CSVFileWritePlanData : public tml::TextFileWritePlanData
{
public:
	CSVFileWritePlanData();
	virtual ~CSVFileWritePlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief CSVFileWritePlan�N���X
 */
class CSVFileWritePlan
{
public:
	tml::CSVFileWritePlanData data;
	tml::CSVFileWritePlanData *parent_data;

public:
	CSVFileWritePlan();
	virtual ~CSVFileWritePlan();

	virtual void Init(void);

	tml::CSVFileWritePlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::CSVFileWritePlanData *tml::CSVFileWritePlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief CSVFile�N���X
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
