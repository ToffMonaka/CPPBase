/**
 * @file
 * @brief ConfigFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <map>
#include "TextFile.h"


namespace tml {
/**
 * @brief ConfigFileData�N���X
 */
class ConfigFileData
{
public:
	std::map<std::wstring, std::wstring> value_container;

public:
	ConfigFileData();
	virtual ~ConfigFileData();

	virtual void Init(void);

	std::wstring *GetValue(const WCHAR *);
};
}


/**
 * @brief GetValue�֐�
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=���s
 */
inline std::wstring *tml::ConfigFileData::GetValue(const WCHAR *val_name)
{
	auto val_itr = this->value_container.find(val_name);

	if (val_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}


namespace tml {
/**
 * @brief ConfigFileReadPlanData�N���X
 */
class ConfigFileReadPlanData : public tml::TextFileReadPlanData
{
public:
	ConfigFileReadPlanData();
	virtual ~ConfigFileReadPlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief ConfigFileReadPlan�N���X
 */
class ConfigFileReadPlan
{
public:
	tml::ConfigFileReadPlanData data;
	tml::ConfigFileReadPlanData *parent_data;

public:
	ConfigFileReadPlan();
	virtual ~ConfigFileReadPlan();

	virtual void Init(void);

	tml::ConfigFileReadPlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::ConfigFileReadPlanData *tml::ConfigFileReadPlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief ConfigFileWritePlanData�N���X
 */
class ConfigFileWritePlanData : public tml::TextFileWritePlanData
{
public:
	ConfigFileWritePlanData();
	virtual ~ConfigFileWritePlanData();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief ConfigFileWritePlan�N���X
 */
class ConfigFileWritePlan
{
public:
	tml::ConfigFileWritePlanData data;
	tml::ConfigFileWritePlanData *parent_data;

public:
	ConfigFileWritePlan();
	virtual ~ConfigFileWritePlan();

	virtual void Init(void);

	tml::ConfigFileWritePlanData *GetDataByParent(void);
};
}


/**
 * @brief GetDataByParent�֐�
 * @return dat (data)
 */
inline tml::ConfigFileWritePlanData *tml::ConfigFileWritePlan::GetDataByParent(void)
{
	return ((this->parent_data != nullptr) ? this->parent_data : &this->data);
}


namespace tml {
/**
 * @brief ConfigFile�N���X
 */
class ConfigFile : public tml::File
{
public: ConfigFile(const tml::ConfigFile &) = delete;
public: tml::ConfigFile &operator =(const tml::ConfigFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::ConfigFileData data;
	tml::ConfigFileReadPlan read_plan;
	tml::ConfigFileWritePlan write_plan;

private:
	void Release(void);

public:
	ConfigFile();
	virtual ~ConfigFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}
