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
 * @brief BinaryFileReadDescDataクラス
 */
class BinaryFileReadDescData
{
public:
	std::wstring file_path;
	tml::DynamicBuffer file_buffer;
	size_t one_buffer_size;

public:
	BinaryFileReadDescData();
	virtual ~BinaryFileReadDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileReadDescクラス
 */
class BinaryFileReadDesc
{
public:
	tml::BinaryFileReadDescData data;
	tml::BinaryFileReadDescData *parent_data;

public:
	BinaryFileReadDesc();
	virtual ~BinaryFileReadDesc();

	virtual void Init(void);

	tml::BinaryFileReadDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::BinaryFileReadDescData *tml::BinaryFileReadDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief BinaryFileWriteDescDataクラス
 */
class BinaryFileWriteDescData
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	bool add_flag;

public:
	BinaryFileWriteDescData();
	virtual ~BinaryFileWriteDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileWriteDescクラス
 */
class BinaryFileWriteDesc
{
public:
	tml::BinaryFileWriteDescData data;
	tml::BinaryFileWriteDescData *parent_data;

public:
	BinaryFileWriteDesc();
	virtual ~BinaryFileWriteDesc();

	virtual void Init(void);

	tml::BinaryFileWriteDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
inline tml::BinaryFileWriteDescData *tml::BinaryFileWriteDesc::GetDataByParent(void)
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
