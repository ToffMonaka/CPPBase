/**
 * @file
 * @brief TextFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_NEWLINE_CODE.h"
#include <list>
#include "BinaryFile.h"


namespace tml {
/**
 * @brief TextFileData�N���X
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
 * @brief TextFileReadDescData�N���X
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
}


namespace tml {
/**
 * @brief TextFileReadDesc�N���X
 */
class TextFileReadDesc
{
public:
	tml::TextFileReadDescData data;
	tml::TextFileReadDescData *parent_data;

public:
	TextFileReadDesc();
	virtual ~TextFileReadDesc();

	virtual void Init(void);

	tml::TextFileReadDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::TextFileReadDescData *tml::TextFileReadDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief TextFileWriteDescData�N���X
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
}


namespace tml {
/**
 * @brief TextFileWriteDesc�N���X
 */
class TextFileWriteDesc
{
public:
	tml::TextFileWriteDescData data;
	tml::TextFileWriteDescData *parent_data;

public:
	TextFileWriteDesc();
	virtual ~TextFileWriteDesc();

	virtual void Init(void);

	tml::TextFileWriteDescData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::TextFileWriteDescData *tml::TextFileWriteDesc::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief TextFile�N���X
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
