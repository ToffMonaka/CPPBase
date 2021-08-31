/**
 * @file
 * @brief ManagerResourceコードファイル
 */


#include "ManagerResource.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerResourceDesc::ManagerResourceDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::ManagerResourceDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"RES");

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
void tml::sound::ManagerResourceDesc::SetManager(tml::sound::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerResourceDesc::SetManager(mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerResource::ManagerResource() :
	mgr_(nullptr),
	res_type_(tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE)
	
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ManagerResource::~ManagerResource()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ManagerResource::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->res_type_ = tml::ConstantUtil::SOUND::RESOURCE_TYPE::NONE;

	tml::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::ManagerResource::Create(const tml::sound::ManagerResourceDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	if (tml::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->res_type_ = static_cast<tml::ConstantUtil::SOUND::RESOURCE_TYPE>(this->GetResourceMainIndex());

	return (0);
}


/**
 * @brief InitDeferred関数
 */
void tml::sound::ManagerResource::InitDeferred(void)
{
	this->ReleaseDeferred();

	tml::ManagerResource::InitDeferred();

	return;
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::ManagerResource::OnCreateDeferred(void)
{
	if (tml::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}
