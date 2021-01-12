/**
 * @file
 * @brief Fileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/DynamicBuffer.h"


namespace tml {
/**
 * @brief FileReadDescDataクラス
 *
 * インターフェースパターン
 */
class FileReadDescData
{
protected: virtual void InterfaceDummy(void) = 0;

public:
	std::wstring file_path;
	tml::DynamicBuffer file_buffer;

public:
	FileReadDescData();
	virtual ~FileReadDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief FileReadDescクラス
 */
template <typename T>
class FileReadDesc
{
public:
	T data;
	T *parent_data;

public:
	FileReadDesc();
	virtual ~FileReadDesc();

	virtual void Init(void);

	T *GetDataByParent(void);
};
}


/**
 * @brief コンストラクタ
 */
template <typename T>
tml::FileReadDesc<T>::FileReadDesc() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
template <typename T>
tml::FileReadDesc<T>::~FileReadDesc()
{
	return;
}


/**
 * @brief Init関数
 */
template <typename T>
void tml::FileReadDesc<T>::Init(void)
{
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
template <typename T>
inline T *tml::FileReadDesc<T>::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief FileWriteDescDataクラス
 *
 * インターフェースパターン
 */
class FileWriteDescData
{
protected: virtual void InterfaceDummy(void) = 0;

public:
	std::wstring file_path;

public:
	FileWriteDescData();
	virtual ~FileWriteDescData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief FileWriteDescクラス
 */
template <typename T>
class FileWriteDesc
{
public:
	T data;
	T *parent_data;

public:
	FileWriteDesc();
	virtual ~FileWriteDesc();

	virtual void Init(void);

	T *GetDataByParent(void);
};
}


/**
 * @brief コンストラクタ
 */
template <typename T>
tml::FileWriteDesc<T>::FileWriteDesc() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
template <typename T>
tml::FileWriteDesc<T>::~FileWriteDesc()
{
	return;
}


/**
 * @brief Init関数
 */
template <typename T>
void tml::FileWriteDesc<T>::Init(void)
{
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
template <typename T>
inline T *tml::FileWriteDesc<T>::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief Fileクラス
 *
 * インターフェースパターン
 */
class File
{
public: File(const tml::File &) = delete;
public: tml::File &operator =(const tml::File &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);

public:
	File();
	virtual ~File();

	virtual void Init(void);

	virtual INT Read(void) = 0;
	virtual INT Write(void) = 0;
};
}
