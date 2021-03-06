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

protected:
	void Release(void);

public:
	TextFileData();
	virtual ~TextFileData();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::TextFileData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief TextFileReadDescDataクラス
 */
class TextFileReadDescData : public tml::BinaryFileReadDescData
{
public:
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

protected:
	void Release(void);

public:
	TextFileReadDescData();
	virtual ~TextFileReadDescData();

	virtual void Init(void);
};

using TextFileReadDesc = tml::FileReadDesc<tml::TextFileReadDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::TextFileReadDescData::Release(void)
{
	tml::BinaryFileReadDescData::Release();

	return;
}


namespace tml {
/**
 * @brief TextFileWriteDescDataクラス
 */
class TextFileWriteDescData : public tml::BinaryFileWriteDescData
{
public:
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;
	size_t add_newline_code_count;

protected:
	void Release(void);

public:
	TextFileWriteDescData();
	virtual ~TextFileWriteDescData();

	virtual void Init(void);
};

using TextFileWriteDesc = tml::FileWriteDesc<tml::TextFileWriteDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::TextFileWriteDescData::Release(void)
{
	tml::BinaryFileWriteDescData::Release();

	return;
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
	tml::TextFileReadDesc read_desc;
	tml::TextFileWriteDesc write_desc;

protected:
	void Release(void);

public:
	TextFile();
	virtual ~TextFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::TextFile::Release(void)
{
	tml::File::Release();

	return;
}
