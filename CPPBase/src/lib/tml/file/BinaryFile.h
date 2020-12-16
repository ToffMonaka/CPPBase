/**
 * @file
 * @brief BinaryFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "File.h"
#include "../memory/DynamicBuffer.h"


namespace tml {
/**
 * @brief BinaryFileData�N���X
 */
class BinaryFileData
{
public:
	tml::DynamicBuffer file_buffer;

public:
	BinaryFileData();
	virtual ~BinaryFileData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileReadPlan�N���X
 */
class BinaryFileReadPlan
{
public:
	std::wstring file_path;
	tml::DynamicBuffer file_buffer;
	size_t one_buffer_size;

public:
	BinaryFileReadPlan();
	virtual ~BinaryFileReadPlan();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief BinaryFileWritePlan�N���X
 */
class BinaryFileWritePlan
{
public:
	std::wstring file_path;
	size_t one_buffer_size;
	bool add_flag;

public:
	BinaryFileWritePlan();
	virtual ~BinaryFileWritePlan();

	virtual void Init(void);
};
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
