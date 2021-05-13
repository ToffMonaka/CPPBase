/**
 * @file
 * @brief ManagerResourceコードファイル
 */


#include "ManagerResource.h"


/**
 * @brief コンストラクタ
 */
tml::ManagerResourceDesc::ManagerResourceDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->resource_name.clear();

	return;
}


/**
 * @brief Read関数
 * @param read_desc (read_desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResourceDesc::Read(const tml::INIFileReadDesc &read_desc)
{
	auto read_desc_dat = read_desc.GetDataByParent();

	tml::INIFile ini_file;

	ini_file.read_desc.parent_data = read_desc_dat;

	if (ini_file.Read() < 0) {
		return (-1);
	}

	if (ini_file.data.value_container.empty()) {
		return (0);
	}

	return (this->ReadValue(ini_file));
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResourceDesc::ReadValue(const tml::INIFile &ini_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"RES");

		if (val_name_cont != nullptr) {
			val = ini_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->resource_name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::ManagerResource::ManagerResource() :
	res_main_index_(0U),
	res_sub_index_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerResource::~ManagerResource()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerResource::Init(void)
{
	this->res_main_index_ = 0U;
	this->res_sub_index_ = 0U;
	this->res_name_.clear();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param res_main_index (resource_main_index)
 * @param res_sub_index (resource_sub_index)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResource::Create(const tml::ManagerResourceDesc &desc, const UINT res_main_index, const UINT res_sub_index)
{
	this->res_main_index_ = res_main_index;
	this->res_sub_index_ = res_sub_index;
	this->res_name_ = desc.resource_name;

	return (0);
}
