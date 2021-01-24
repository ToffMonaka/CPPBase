/**
 * @file
 * @brief SystemConfigFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/math/XNAMath.h"
#include "../../lib/tml/file/INIFile.h"


namespace cpp_base {
/**
 * @brief SystemConfigFileData�N���X
 */
class SystemConfigFileData
{
public:
	size_t application_memory_allocator_size;
	std::string application_locale_name;
	tml::XMUINT2EX window_position;
	tml::XMUINT2EX window_size;

public:
	SystemConfigFileData();
	virtual ~SystemConfigFileData();

	virtual void Init(void);
};
}


namespace cpp_base {
/**
 * @brief SystemConfigFile�N���X
 */
class SystemConfigFile : public tml::File
{
public: SystemConfigFile(const cpp_base::SystemConfigFile &) = delete;
public: cpp_base::SystemConfigFile &operator =(const cpp_base::SystemConfigFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	cpp_base::SystemConfigFileData data;
	tml::INIFileReadDesc read_desc;
	tml::INIFileWriteDesc write_desc;

private:
	void Release(void);

public:
	SystemConfigFile();
	virtual ~SystemConfigFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}
