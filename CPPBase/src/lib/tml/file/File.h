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
	T *parent_data;

public:
	FileReadDesc();
	virtual ~FileReadDesc();

	virtual void Init(void);

	T *GetDataByParent(void);
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
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
template <typename T>
inline T *tml::FileReadDesc<T>::GetDataByParent(void)
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
	T *parent_data;

public:
	FileWriteDesc();
	virtual ~FileWriteDesc();

	virtual void Init(void);

	T *GetDataByParent(void);
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
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
template <typename T>
inline T *tml::FileWriteDesc<T>::GetDataByParent(void)
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
