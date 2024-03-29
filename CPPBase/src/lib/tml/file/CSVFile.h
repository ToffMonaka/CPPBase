/**
 * @file
 * @brief CSVFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <regex>
#include "TextFile.h"


namespace tml {
/**
 * @brief CSVFileDataクラス
 */
class CSVFileData
{
public: CSVFileData(const tml::CSVFileData &) = delete;
public: tml::CSVFileData &operator =(const tml::CSVFileData &) = delete;

private:

public:
	std::vector<std::vector<std::wstring>> value_container;

private:
	void Release(void);

public:
	CSVFileData();
	virtual ~CSVFileData();

	virtual void Init(void);

	size_t GetRowCount(void) const;
	size_t GetColumnCount(void) const;
	const std::wstring *GetValue(const size_t, const size_t) const;
	const std::wstring *GetValueFast(const size_t, const size_t) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::CSVFileData::Release(void)
{
	return;
}


/**
 * @brief GetRowCount関数
 * @return row_cnt (row_count)
 */
inline size_t tml::CSVFileData::GetRowCount(void) const
{
	return (this->value_container.size());
}


/**
 * @brief GetColumnCount関数
 * @return column_cnt (column_count)
 */
inline size_t tml::CSVFileData::GetColumnCount(void) const
{
	return ((this->value_container.empty()) ? 0U : this->value_container[0].size());
}


/**
 * @brief GetValue関数
 * @param row_index (row_index)
 * @param column_index (column_index)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline const std::wstring *tml::CSVFileData::GetValue(const size_t row_index, const size_t column_index) const
{
	if ((row_index >= this->value_container.size())
	|| (column_index >= this->value_container[row_index].size())) {
		return (nullptr);
	}

	return (&this->value_container[row_index][column_index]);
}


/**
 * @brief GetValueFast関数
 * @param row_index (row_index)
 * @param column_index (column_index)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline const std::wstring *tml::CSVFileData::GetValueFast(const size_t row_index, const size_t column_index) const
{
	return (&this->value_container[row_index][column_index]);
}


namespace tml {
/**
 * @brief CSVFileReadDescDataクラス
 */
class CSVFileReadDescData : public tml::TextFileReadDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:

private:
	void Release(void);

public:
	CSVFileReadDescData();
	virtual ~CSVFileReadDescData();

	virtual void Init(void);
};

using CSVFileReadDesc = tml::FileReadDesc<tml::CSVFileReadDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::CSVFileReadDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief CSVFileWriteDescDataクラス
 */
class CSVFileWriteDescData : public tml::TextFileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:

private:
	void Release(void);

public:
	CSVFileWriteDescData();
	virtual ~CSVFileWriteDescData();

	virtual void Init(void);
};

using CSVFileWriteDesc = tml::FileWriteDesc<tml::CSVFileWriteDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::CSVFileWriteDescData::Release(void)
{
	return;
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
	tml::CSVFileReadDesc read_desc;
	tml::CSVFileWriteDesc write_desc;

private:
	void Release(void);

protected:
	virtual INT OnRead(void);
	virtual INT OnWrite(void);

public:
	CSVFile();
	virtual ~CSVFile();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::CSVFile::Release(void)
{
	return;
}
