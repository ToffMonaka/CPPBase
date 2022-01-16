/**
 * @file
 * @brief RawBinaryFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/RawDynamicBuffer.h"
#include "File.h"


namespace tml {
/**
 * @brief RawBinaryFileData�N���X
 */
class RawBinaryFileData
{
public: RawBinaryFileData(const tml::RawBinaryFileData &) = delete;
public: tml::RawBinaryFileData &operator =(const tml::RawBinaryFileData &) = delete;

private:

public:
	tml::RawDynamicBuffer buffer;

private:
	void Release(void);

public:
	RawBinaryFileData();
	virtual ~RawBinaryFileData();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::RawBinaryFileData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief RawBinaryFileReadDescData�N���X
 */
class RawBinaryFileReadDescData : public tml::FileReadDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::RawDynamicBuffer buffer;

private:
	void Release(void);

public:
	RawBinaryFileReadDescData();
	virtual ~RawBinaryFileReadDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

using RawBinaryFileReadDesc = tml::FileReadDesc<tml::RawBinaryFileReadDescData>;
}


/**
 * @brief Release�֐�
 */
inline void tml::RawBinaryFileReadDescData::Release(void)
{
	return;
}


/**
 * @brief IsEmpty�֐�
 * @return result_flg (result_flag)<br>
 * false=���,true=��
 */
inline bool tml::RawBinaryFileReadDescData::IsEmpty(void) const
{
	if (this->buffer.GetLength() > 0U) {
		return (false);
	}

	return (tml::FileReadDescData::IsEmpty());
}


namespace tml {
/**
 * @brief RawBinaryFileWriteDescData�N���X
 */
class RawBinaryFileWriteDescData : public tml::FileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

public:
	bool add_flag;

private:
	void Release(void);

public:
	RawBinaryFileWriteDescData();
	virtual ~RawBinaryFileWriteDescData();

	virtual void Init(void);

	bool IsEmpty(void) const;
};

using RawBinaryFileWriteDesc = tml::FileWriteDesc<tml::RawBinaryFileWriteDescData>;
}


/**
 * @brief Release�֐�
 */
inline void tml::RawBinaryFileWriteDescData::Release(void)
{
	return;
}


/**
 * @brief IsEmpty�֐�
 * @return result_flg (result_flag)<br>
 * false=���,true=��
 */
inline bool tml::RawBinaryFileWriteDescData::IsEmpty(void) const
{
	return (tml::FileWriteDescData::IsEmpty());
}


namespace tml {
/**
 * @brief RawBinaryFile�N���X
 */
class RawBinaryFile : public tml::File
{
public: RawBinaryFile(const tml::RawBinaryFile &) = delete;
public: tml::RawBinaryFile &operator =(const tml::RawBinaryFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::RawBinaryFileData data;
	tml::RawBinaryFileReadDesc read_desc;
	tml::RawBinaryFileWriteDesc write_desc;

private:
	void Release(void);

public:
	RawBinaryFile();
	virtual ~RawBinaryFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::RawBinaryFile::Release(void)
{
	return;
}
