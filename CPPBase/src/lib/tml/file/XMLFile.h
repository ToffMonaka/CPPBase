/**
 * @file
 * @brief XMLFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "TextFile.h"


namespace tml {
/**
 * @brief XMLFileDataクラス
 */
class XMLFileData
{
public:

protected:
	void Release(void);

public:
	XMLFileData();
	virtual ~XMLFileData();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::XMLFileData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief XMLFileReadDescDataクラス
 */
class XMLFileReadDescData : public tml::TextFileReadDescData
{
public:

protected:
	void Release(void);

public:
	XMLFileReadDescData();
	virtual ~XMLFileReadDescData();

	virtual void Init(void);
};

using XMLFileReadDesc = tml::FileReadDesc<tml::XMLFileReadDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::XMLFileReadDescData::Release(void)
{
	tml::TextFileReadDescData::Release();

	return;
}


namespace tml {
/**
 * @brief XMLFileWriteDescDataクラス
 */
class XMLFileWriteDescData : public tml::TextFileWriteDescData
{
public:

protected:
	void Release(void);

public:
	XMLFileWriteDescData();
	virtual ~XMLFileWriteDescData();

	virtual void Init(void);
};

using XMLFileWriteDesc = tml::FileWriteDesc<tml::XMLFileWriteDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::XMLFileWriteDescData::Release(void)
{
	tml::TextFileWriteDescData::Release();

	return;
}


namespace tml {
/**
 * @brief XMLFileクラス
 */
class XMLFile : public tml::File
{
public: XMLFile(const tml::XMLFile &) = delete;
public: tml::XMLFile &operator =(const tml::XMLFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::XMLFileData data;
	tml::XMLFileReadDesc read_desc;
	tml::XMLFileWriteDesc write_desc;

protected:
	void Release(void);

public:
	XMLFile();
	virtual ~XMLFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::XMLFile::Release(void)
{
	tml::File::Release();

	return;
}
