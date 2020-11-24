/**
 * @file
 * @brief BinaryFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "File.h"


namespace tml {
/**
 * @brief BinaryFileDataクラス
 */
class BinaryFileData
{
public: BinaryFileData(const BinaryFileData &) = delete;
public: BinaryFileData &operator =(const BinaryFileData &) = delete;

public:
	BYTE *buffer;
	size_t buffer_size;

private:
	void Release(void);

public:
	BinaryFileData();
	virtual ~BinaryFileData();

	void Init(void);
};
}


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

public:
	tml::BinaryFileData data;
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
};
}
