/**
 * @file
 * @brief BinaryFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "File.h"


namespace tml {
/**
 * @brief BinaryFileData�N���X
 */
class BinaryFileData
{
public:
	tml::DynamicBuffer file_buffer;

protected:
	void Release(void);

public:
	BinaryFileData();
	virtual ~BinaryFileData();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::BinaryFileData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief BinaryFileReadDescData�N���X
 */
class BinaryFileReadDescData : public tml::FileReadDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	size_t one_buffer_size;

protected:
	void Release(void);

public:
	BinaryFileReadDescData();
	virtual ~BinaryFileReadDescData();

	virtual void Init(void);
};

using BinaryFileReadDesc = tml::FileReadDesc<tml::BinaryFileReadDescData>;
}


/**
 * @brief Release�֐�
 */
inline void tml::BinaryFileReadDescData::Release(void)
{
	tml::FileReadDescData::Release();

	return;
}


namespace tml {
/**
 * @brief BinaryFileWriteDescData�N���X
 */
class BinaryFileWriteDescData : public tml::FileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	size_t one_buffer_size;
	bool add_flag;

protected:
	void Release(void);

public:
	BinaryFileWriteDescData();
	virtual ~BinaryFileWriteDescData();

	virtual void Init(void);
};

using BinaryFileWriteDesc = tml::FileWriteDesc<tml::BinaryFileWriteDescData>;
}


/**
 * @brief Release�֐�
 */
inline void tml::BinaryFileWriteDescData::Release(void)
{
	tml::FileWriteDescData::Release();

	return;
}


namespace tml {
/**
 * @brief BinaryFile�N���X
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

protected:
	void Release(void);

public:
	BinaryFile();
	virtual ~BinaryFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::BinaryFile::Release(void)
{
	tml::File::Release();

	return;
}
