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
 * @brief TextFileReadDescDataクラス
 */
class TextFileReadDescData : public tml::BinaryFileReadDescData
{
public:
	tml::ConstantUtil::NEWLINE_CODE::TYPE newline_code_type;

public:
	TextFileReadDescData();
	virtual ~TextFileReadDescData();

	virtual void Init(void);
};

using TextFileReadDesc = tml::FileReadDesc<tml::TextFileReadDescData>;
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

public:
	TextFileWriteDescData();
	virtual ~TextFileWriteDescData();

	virtual void Init(void);
};

using TextFileWriteDesc = tml::FileWriteDesc<tml::TextFileWriteDescData>;
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
