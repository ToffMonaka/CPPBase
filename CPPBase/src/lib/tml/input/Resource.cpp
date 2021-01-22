/**
 * @file
 * @brief Resourceコードファイル
 */


#include "Resource.h"
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::input::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ResourceDesc::~ResourceDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::input::ResourceDesc::Init(void)
{
	this->manager = nullptr;
	this->name.clear();

	return;
}


/**
 * @brief Read関数
 * @param read_desc (read_desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::ResourceDesc::Read(const tml::INIFileReadDesc &read_desc)
{
	auto read_desc_dat = read_desc.GetDataByParent();

	tml::INIFile ini_file;

	ini_file.read_desc.parent_data = read_desc_dat;

	if (ini_file.Read()) {
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
INT tml::input::ResourceDesc::ReadValue(const tml::INIFile &ini_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"RES");

		if (val_name_cont != nullptr) {
			val = ini_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::input::Resource::Resource() :
	res_type_(tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE),
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::Resource::~Resource()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::input::Resource::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::input::Resource::Init(void)
{
	this->res_type_ = tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE;
	this->mgr_ = nullptr;
	this->name_.clear();

	return;
}


/**
 * @brief Create関数
 * @param res_type (resource_type)
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::Resource::Create(const tml::ConstantUtil::INPUT::RESOURCE_TYPE res_type, const tml::input::ResourceDesc &desc)
{
	if ((res_type == tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE)
	|| (desc.manager == nullptr)) {
		return (-1);
	}

	this->res_type_ = res_type;
	this->mgr_ = desc.manager;
	this->name_ = desc.name;

	return (0);
}
