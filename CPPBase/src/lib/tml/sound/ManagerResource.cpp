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
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::sound::ManagerResourceDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::sound::Manager *>(mgr);

	tml::ManagerResourceDesc::OnSetManager(this->mgr_);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerResource::ManagerResource() :
	desc_(nullptr),
	mgr_(nullptr)
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

	tml::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::ManagerResource::OnCreate(void)
{
	if (tml::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	return (0);
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


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::sound::ManagerResource::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::sound::ManagerResourceDesc *>(desc);

	tml::ManagerResource::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::sound::ManagerResource::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::sound::Manager *>(mgr);

	tml::ManagerResource::OnSetManager(this->mgr_);

	return;
}
