/**
 * @file
 * @brief Resourceコードファイル
 */


#include "Resource.h"
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param mgr (manager)
 */
tml::sound::ResourceDesc::ResourceDesc(tml::sound::Manager *mgr) :
	manager(mgr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ResourceDesc::~ResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ResourceDesc::Init(void)
{
	this->Release();

	this->manager = nullptr;
	this->name.clear();

	return;
}


/**
 * @brief Init関数
 * @param mgr (manager)
 */
void tml::sound::ResourceDesc::Init(tml::sound::Manager *mgr)
{
	this->Release();

	this->manager = mgr;
	this->name.clear();

	return;
}


/**
 * @brief Read関数
 * @param read_desc (read_desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::ResourceDesc::Read(const tml::INIFileReadDesc &read_desc)
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
INT tml::sound::ResourceDesc::ReadValue(const tml::INIFile &ini_file)
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
tml::sound::Resource::Resource() :
	res_type_(tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE),
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::Resource::~Resource()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::Resource::Init(void)
{
	this->res_type_ = tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE;
	this->mgr_ = nullptr;
	this->name_.clear();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param res_type (resource_type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::Resource::Create(const tml::sound::ResourceDesc &desc, const tml::ConstantUtil::SOUND::RESOURCE_TYPE res_type)
{
	if ((res_type == tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE)
	|| (desc.manager == nullptr)) {
		return (-1);
	}

	this->res_type_ = res_type;
	this->mgr_ = desc.manager;
	this->name_ = desc.name;

	return (0);
}
