/**
 * @file
 * @brief ManagerResourceコードファイル
 */


#include "ManagerResource.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerResourceDesc::ManagerResourceDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::ManagerResourceDesc::ReadValue(const tml::INIFile &ini_file)
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
 * @brief SetManager関数
 * @param mgr (manager)
 */
void tml::input::ManagerResourceDesc::SetManager(tml::input::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerResourceDesc::SetManager(mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::ManagerResource::ManagerResource() :
	mgr_(nullptr),
	res_type_(tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE)
	
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerResource::~ManagerResource()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerResource::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->res_type_ = tml::ConstantUtil::INPUT::RESOURCE_TYPE::NONE;

	tml::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::input::ManagerResource::Create(const tml::input::ManagerResourceDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	if (tml::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->res_type_ = static_cast<tml::ConstantUtil::INPUT::RESOURCE_TYPE>(this->GetResourceMainIndex());

	return (0);
}
