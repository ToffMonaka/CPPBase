/**
 * @file
 * @brief ManagerResourceコードファイル
 */


#include "ManagerResource.h"


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerResourceDesc::ManagerResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->manager = nullptr;

	tml::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::ManagerResourceDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"RES");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerResource::ManagerResource() :
	mgr_(nullptr),
	res_type_(tml::ConstantUtil::SCENE::RESOURCE_TYPE::NONE)
	
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::ManagerResource::~ManagerResource()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::scene::ManagerResource::Init(void)
{
	this->mgr_ = nullptr;
	this->res_type_ = tml::ConstantUtil::SCENE::RESOURCE_TYPE::NONE;

	tml::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param res_type (resource_type)
 * @param res_sub_index (resource_sub_index)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::ManagerResource::Create(const tml::scene::ManagerResourceDesc &desc, const tml::ConstantUtil::SCENE::RESOURCE_TYPE res_type, const UINT res_sub_index)
{
	if ((desc.manager == nullptr)
	|| (res_type == tml::ConstantUtil::SCENE::RESOURCE_TYPE::NONE)) {
		return (-1);
	}

	if (tml::ManagerResource::Create(desc, static_cast<UINT>(res_type), res_sub_index) < 0) {
		return (-1);
	}

	this->mgr_ = desc.manager;
	this->res_type_ = res_type;

	return (0);
}
