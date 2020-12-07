/**
 * @file
 * @brief CSVFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include <vector>
#include "File.h"


namespace tml {
/**
 * @brief CSVFileData�N���X
 */
class CSVFileData
{
public: CSVFileData(const tml::CSVFileData &) = delete;
public: tml::CSVFileData &operator =(const tml::CSVFileData &) = delete;

public:
	std::vector<std::vector<std::wstring>> value_container;

private:
	void Release(void);

public:
	CSVFileData();
	virtual ~CSVFileData();

	void Init(void);

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
	if (this->value_container.size() <= 0U) {
		return (0U);
	}
	
	return (this->value_container[0].size());
}


/**
 * @brief GetValue�֐�
 * @param row_cnt (row_index)
 * @param column_cnt (column_index)
 * @return val (value)<br>
 * nullptr=���s
 */
inline std::wstring *tml::CSVFileData::GetValue(const size_t row_index, const size_t column_index)
{
	if (row_index >= this->value_container.size()) {
		return (nullptr);
	}

	if (column_index >= this->value_container[row_index].size()) {
		return (nullptr);
	}

	return (&this->value_container[row_index][column_index]);
}


namespace tml {
/**
 * @brief CSVFileReadPlan�N���X
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
 * @brief CSVFileWritePlan�N���X
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
