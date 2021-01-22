/**
 * @file
 * @brief File�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/DynamicBuffer.h"


namespace tml {
/**
 * @brief FileReadDescData�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
 * @brief FileReadDesc�N���X
 */
template <typename T>
class FileReadDesc
{
public:
	T data;
	const T *parent_data;

public:
	FileReadDesc();
	FileReadDesc(const WCHAR *);
	FileReadDesc(const tml::DynamicBuffer &);
	FileReadDesc(tml::DynamicBuffer &&);
	FileReadDesc(const T *);
	virtual ~FileReadDesc();

	virtual void Init(void);

	void Set(const WCHAR *);
	void Set(const tml::DynamicBuffer &);
	void Set(tml::DynamicBuffer &&);
	void Set(const T *);
	const T *GetDataByParent(void) const;
};
}


/**
 * @brief �R���X�g���N�^
 */
template <typename T>
tml::FileReadDesc<T>::FileReadDesc() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param file_path (file_path)
 */
template <typename T>
tml::FileReadDesc<T>::FileReadDesc(const WCHAR *file_path) :
	parent_data(nullptr)
{
	this->data.file_path = file_path;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param file_buf (file_buffer)
 */
template <typename T>
tml::FileReadDesc<T>::FileReadDesc(const tml::DynamicBuffer &file_buf) :
	parent_data(nullptr)
{
	this->data.file_buffer = file_buf;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param file_buf (file_buf)
 */
template <typename T>
tml::FileReadDesc<T>::FileReadDesc(tml::DynamicBuffer &&file_buf) :
	parent_data(nullptr)
{
	this->data.file_buffer = std::move(file_buf);

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param parent_dat (parent_data)
 */
template <typename T>
tml::FileReadDesc<T>::FileReadDesc(const T *parent_dat) :
	parent_data(parent_dat)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
template <typename T>
tml::FileReadDesc<T>::~FileReadDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
template <typename T>
void tml::FileReadDesc<T>::Init(void)
{
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief Set�֐�
 * @param file_path (file_path)
 */
template <typename T>
void tml::FileReadDesc<T>::Set(const WCHAR *file_path)
{
	this->data.Init();
	this->data.file_path = file_path;

	return;
}


/**
 * @brief Set�֐�
 * @param file_buf (file_buffer)
 */
template <typename T>
void tml::FileReadDesc<T>::Set(const tml::DynamicBuffer &file_buf)
{
	this->data.Init();
	this->data.file_buffer = file_buf;

	return;
}


/**
 * @brief Set�֐�
 * @param file_buf (file_buf)
 */
template <typename T>
void tml::FileReadDesc<T>::Set(tml::DynamicBuffer &&file_buf)
{
	this->data.Init();
	this->data.file_buffer = std::move(file_buf);

	return;
}


/**
 * @brief Set�֐�
 * @param parent_dat (parent_data)
 */
template <typename T>
void tml::FileReadDesc<T>::Set(const T *parent_dat)
{
	this->data.Init();
	this->parent_data = parent_dat;

	return;
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
template <typename T>
inline const T *tml::FileReadDesc<T>::GetDataByParent(void) const
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief FileWriteDescData�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
 * @brief FileWriteDesc�N���X
 */
template <typename T>
class FileWriteDesc
{
public:
	T data;
	const T *parent_data;

public:
	FileWriteDesc();
	FileWriteDesc(const WCHAR *);
	FileWriteDesc(const T *);
	virtual ~FileWriteDesc();

	virtual void Init(void);

	void Set(const WCHAR *);
	void Set(const T *);
	const T *GetDataByParent(void) const;
};
}


/**
 * @brief �R���X�g���N�^
 */
template <typename T>
tml::FileWriteDesc<T>::FileWriteDesc() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param file_path (file_path)
 */
template <typename T>
tml::FileWriteDesc<T>::FileWriteDesc(const WCHAR *file_path) :
	parent_data(nullptr)
{
	this->data.file_path = file_path;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param parent_dat (parent_data)
 */
template <typename T>
tml::FileWriteDesc<T>::FileWriteDesc(const T *parent_dat) :
	parent_data(parent_dat)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
template <typename T>
tml::FileWriteDesc<T>::~FileWriteDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
template <typename T>
void tml::FileWriteDesc<T>::Init(void)
{
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief Set�֐�
 * @param file_path (file_path)
 */
template <typename T>
void tml::FileWriteDesc<T>::Set(const WCHAR *file_path)
{
	this->data.Init();
	this->data.file_path = file_path;

	return;
}


/**
 * @brief Set�֐�
 * @param parent_dat (parent_data)
 */
template <typename T>
void tml::FileWriteDesc<T>::Set(const T *parent_dat)
{
	this->data.Init();
	this->parent_data = parent_dat;

	return;
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
template <typename T>
inline const T *tml::FileWriteDesc<T>::GetDataByParent(void) const
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief File�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
