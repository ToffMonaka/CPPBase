/**
 * @file
 * @brief BinaryFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/DynamicBuffer.h"
#include "File.h"


namespace tml {
/**
 * @brief BinaryFileData�N���X
 */
class BinaryFileData
{
public:
	tml::DynamicBuffer buffer;

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
	tml::DynamicBuffer buffer;

protected:
	void Release(void);

public:
	BinaryFileReadDescData();
	virtual ~BinaryFileReadDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
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


/**
 * @brief IsEmpty�֐�
 * @return result_flg (result_flag)<br>
 * false=���,true=��
 */
inline bool tml::BinaryFileReadDescData::IsEmpty(void) const
{
	if (this->buffer.GetLength() > 0U) {
		return (false);
	}

	return (tml::FileReadDescData::IsEmpty());
}


namespace tml {
/**
 * @brief BinaryFileWriteDescData�N���X
 */
class BinaryFileWriteDescData : public tml::FileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	bool add_flag;

protected:
	void Release(void);

public:
	BinaryFileWriteDescData();
	virtual ~BinaryFileWriteDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
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


/**
 * @brief IsEmpty�֐�
 * @return result_flg (result_flag)<br>
 * false=���,true=��
 */
inline bool tml::BinaryFileWriteDescData::IsEmpty(void) const
{
	return (tml::FileWriteDescData::IsEmpty());
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
