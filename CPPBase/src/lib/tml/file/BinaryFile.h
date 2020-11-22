/**
 * @file
 * @brief BinaryFileヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "File.h"


namespace tml {
/**
 * @brief BinaryFileReadPlanクラス
 */
class BinaryFileReadPlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;

public:
	BinaryFileReadPlan();
	virtual ~BinaryFileReadPlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileWritePlanクラス
 */
class BinaryFileWritePlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;

public:
	BinaryFileWritePlan();
	virtual ~BinaryFileWritePlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileクラス
 */
class BinaryFile : public tml::File
{
public: BinaryFile(const BinaryFile &) = delete;
public: BinaryFile &operator =(const BinaryFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	BYTE *buf_;
	size_t buf_size_;

public:
	tml::BinaryFileReadPlan read_plan;
	tml::BinaryFileWritePlan write_plan;

private:
	void Release(void);

public:
	BinaryFile();
	virtual ~BinaryFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
	const BYTE *GetBuffer(void) const;
	void SetBuffer(const BYTE *, const size_t);
	size_t GetBufferSize(void) const;
};
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline const BYTE *tml::BinaryFile::GetBuffer(void) const
{
	return (this->buf_);
}


/**
 * @brief GetBufferSize関数
 * @return buf_size (buffer_size)
 */
inline size_t tml::BinaryFile::GetBufferSize(void) const
{
	return (this->buf_size_);
}
