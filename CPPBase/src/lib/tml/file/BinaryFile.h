/**
 * @file
 * @brief BinaryFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
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
 * @brief BinaryFileReadDescDataクラス
 */
class BinaryFileReadDescData : public tml::FileReadDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	size_t one_buffer_size;

public:
	BinaryFileReadDescData();
	virtual ~BinaryFileReadDescData();

	virtual void Init(void);
};

using BinaryFileReadDesc = tml::FileReadDesc<tml::BinaryFileReadDescData>;
}


namespace tml {
/**
 * @brief BinaryFileWriteDescDataクラス
 */
class BinaryFileWriteDescData : public tml::FileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	size_t one_buffer_size;
	bool add_flag;

public:
	BinaryFileWriteDescData();
	virtual ~BinaryFileWriteDescData();

	virtual void Init(void);
};

using BinaryFileWriteDesc = tml::FileWriteDesc<tml::BinaryFileWriteDescData>;
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
