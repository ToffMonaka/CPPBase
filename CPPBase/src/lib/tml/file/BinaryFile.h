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
public: BinaryFileData(const tml::BinaryFileData &) = delete;
public: tml::BinaryFileData &operator =(const tml::BinaryFileData &) = delete;

private:

public:
	tml::DynamicBuffer buffer;

private:
	void Release(void);

public:
	BinaryFileData();
	virtual ~BinaryFileData();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::BinaryFileData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief BinaryFileReadDescDataクラス
 */
class BinaryFileReadDescData : public tml::FileReadDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::DynamicBuffer buffer;

private:
	void Release(void);

public:
	BinaryFileReadDescData();
	virtual ~BinaryFileReadDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

using BinaryFileReadDesc = tml::FileReadDesc<tml::BinaryFileReadDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::BinaryFileReadDescData::Release(void)
{
	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
inline bool tml::BinaryFileReadDescData::IsEmpty(void) const
{
	if (this->buffer.GetLength() > 0U) {
		return (false);
	}

	return (tml::FileReadDescData::IsEmpty());
}


namespace tml {
/**
 * @brief BinaryFileWriteDescDataクラス
 */
class BinaryFileWriteDescData : public tml::FileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	bool add_flag;

private:
	void Release(void);

public:
	BinaryFileWriteDescData();
	virtual ~BinaryFileWriteDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

using BinaryFileWriteDesc = tml::FileWriteDesc<tml::BinaryFileWriteDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::BinaryFileWriteDescData::Release(void)
{
	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
inline bool tml::BinaryFileWriteDescData::IsEmpty(void) const
{
	return (tml::FileWriteDescData::IsEmpty());
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
	tml::BinaryFileReadDesc read_desc;
	tml::BinaryFileWriteDesc write_desc;

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


/**
 * @brief Release関数
 */
inline void tml::BinaryFile::Release(void)
{
	return;
}
