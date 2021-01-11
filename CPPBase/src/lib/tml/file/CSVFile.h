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
 * @brief CSVFileReadDescData�N���X
 */
class CSVFileReadDescData : public tml::TextFileReadDescData
{
public:
	CSVFileReadDescData();
	virtual ~CSVFileReadDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief CSVFileReadDesc�N���X
 */
class CSVFileReadDesc
{
public:
	tml::CSVFileReadDescData data;
	tml::CSVFileReadDescData *parent_data;

public:
	CSVFileReadDesc();
	virtual ~CSVFileReadDesc();

	virtual void Init(void);

	tml::CSVFileReadDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::CSVFileReadDescData *tml::CSVFileReadDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief CSVFileWriteDescData�N���X
 */
class CSVFileWriteDescData : public tml::TextFileWriteDescData
{
public:
	CSVFileWriteDescData();
	virtual ~CSVFileWriteDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief CSVFileWriteDesc�N���X
 */
class CSVFileWriteDesc
{
public:
	tml::CSVFileWriteDescData data;
	tml::CSVFileWriteDescData *parent_data;

public:
	CSVFileWriteDesc();
	virtual ~CSVFileWriteDesc();

	virtual void Init(void);

	tml::CSVFileWriteDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::CSVFileWriteDescData *tml::CSVFileWriteDesc::GetDataByParent(void)
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
	tml::CSVFileReadDesc read_desc;
	tml::CSVFileWriteDesc write_desc;

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
