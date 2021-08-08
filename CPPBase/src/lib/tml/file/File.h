/**
 * @file
 * @brief Fileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


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

private:
	void Release(void);

public:
	FileReadDescData();
	virtual ~FileReadDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::FileReadDescData::Release(void)
{
	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
inline bool tml::FileReadDescData::IsEmpty(void) const
{
	return (this->file_path.empty());
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
	const T *parent_data;

private:
	void Release(void);

public:
	FileReadDesc();
	FileReadDesc(const WCHAR *);
	virtual ~FileReadDesc();

	virtual void Init(void);
	virtual void Init(const WCHAR *);

	const T *GetDataByParent(void) const;
};
}


/**
 * @brief コンストラクタ
 */
template <typename T>
inline tml::FileReadDesc<T>::FileReadDesc() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param file_path (file_path)
 */
template <typename T>
inline tml::FileReadDesc<T>::FileReadDesc(const WCHAR *file_path) :
	parent_data(nullptr)
{
	this->data.file_path = file_path;

	return;
}


/**
 * @brief デストラクタ
 */
template <typename T>
inline tml::FileReadDesc<T>::~FileReadDesc()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <typename T>
inline void tml::FileReadDesc<T>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <typename T>
inline void tml::FileReadDesc<T>::Init(void)
{
	this->Release();

	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief Init関数
 * @param file_path (file_path)
 */
template <typename T>
inline void tml::FileReadDesc<T>::Init(const WCHAR *file_path)
{
	this->Release();

	this->data.Init();
	this->data.file_path = file_path;
	this->parent_data = nullptr;

	return;
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
template <typename T>
inline const T *tml::FileReadDesc<T>::GetDataByParent(void) const
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

private:
	void Release(void);

public:
	FileWriteDescData();
	virtual ~FileWriteDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::FileWriteDescData::Release(void)
{
	return;
}


/**
 * @brief IsEmpty関数
 * @return result_flg (result_flag)<br>
 * false=非空,true=空
 */
inline bool tml::FileWriteDescData::IsEmpty(void) const
{
	return (this->file_path.empty());
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
	const T *parent_data;

private:
	void Release(void);

public:
	FileWriteDesc();
	FileWriteDesc(const WCHAR *);
	virtual ~FileWriteDesc();

	virtual void Init(void);
	virtual void Init(const WCHAR *);

	const T *GetDataByParent(void) const;
};
}


/**
 * @brief コンストラクタ
 */
template <typename T>
inline tml::FileWriteDesc<T>::FileWriteDesc() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param file_path (file_path)
 */
template <typename T>
inline tml::FileWriteDesc<T>::FileWriteDesc(const WCHAR *file_path) :
	parent_data(nullptr)
{
	this->data.file_path = file_path;

	return;
}


/**
 * @brief デストラクタ
 */
template <typename T>
inline tml::FileWriteDesc<T>::~FileWriteDesc()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <typename T>
inline void tml::FileWriteDesc<T>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <typename T>
inline void tml::FileWriteDesc<T>::Init(void)
{
	this->Release();

	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief Init関数
 * @param file_path (file_path)
 */
template <typename T>
inline void tml::FileWriteDesc<T>::Init(const WCHAR *file_path)
{
	this->Release();

	this->data.Init();
	this->data.file_path = file_path;
	this->parent_data = nullptr;

	return;
}


/**
 * @brief GetDataByParent関数
 * @return dat (data)
 */
template <typename T>
inline const T *tml::FileWriteDesc<T>::GetDataByParent(void) const
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

private:
	void Release(void);

public:
	File();
	virtual ~File();

	virtual void Init(void);

	virtual INT Read(void) = 0;
	virtual INT Write(void) = 0;
};
}


/**
 * @brief Release関数
 */
inline void tml::File::Release(void)
{
	return;
}
