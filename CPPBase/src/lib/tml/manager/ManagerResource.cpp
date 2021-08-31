/**
 * @file
 * @brief ManagerResourceコードファイル
 */


#include "ManagerResource.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::ManagerResourceDesc::ManagerResourceDesc() :
	mgr_(nullptr),
	deferred_create_flag(false)
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

	this->mgr_ = nullptr;
	this->resource_name.clear();
	this->deferred_create_flag = false;

	return;
}


/**
 * @brief Read関数
 * @param conf_file_read_desc (config_file_read_desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResourceDesc::Read(const tml::INIFileReadDesc &conf_file_read_desc)
{
	auto conf_file_read_desc_dat = conf_file_read_desc.GetDataByParent();

	if (conf_file_read_desc_dat->IsEmpty()) {
		return (0);
	}

	tml::INIFile conf_file;

	conf_file.read_desc.parent_data = conf_file_read_desc_dat;

	if (conf_file.Read() < 0) {
		return (-1);
	}

	if (conf_file.data.value_container.empty()) {
		return (0);
	}

	return (this->ReadValue(conf_file));
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResourceDesc::ReadValue(const tml::INIFile &conf_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"RES");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->resource_name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
void tml::ManagerResourceDesc::SetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ManagerResource::ManagerResource() :
	mgr_(nullptr),
	res_main_index_(0U),
	res_sub_index_(0U),
	deferred_create_desc_(nullptr),
	deferred_created_flg_(false),
	deferred_creating_flg_(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerResource::~ManagerResource()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerResource::Init(void)
{
	this->Release();

	this->deferred_create_desc_unique_p_.reset();
	this->deferred_create_desc_ = nullptr;
	this->deferred_created_flg_ = false;
	this->deferred_creating_flg_ = true;
	
	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResource::Create(const tml::ManagerResourceDesc &desc)
{
	if ((desc.GetManager() == nullptr)
	|| (this->res_main_index_ == 0U)
	|| (this->res_sub_index_ == 0U)) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}


/**
 * @brief InitDeferred関数
 */
void tml::ManagerResource::InitDeferred(void)
{
	this->ReleaseDeferred();

	return;
}


/**
 * @brief CreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗,1=作成済み
 */
INT tml::ManagerResource::CreateDeferred(void)
{
	if (this->deferred_created_flg_) {
		return (1);
	}

	if (!this->deferred_creating_flg_) {
		return (-1);
	}

	if (this->OnCreateDeferred() < 0) {
		this->InitDeferred();

		this->SetDeferredCreateDesc(nullptr);

		this->deferred_created_flg_ = false;
		this->deferred_creating_flg_ = false;

		return (-1);
	}

	this->SetDeferredCreateDesc(nullptr);

	this->deferred_created_flg_ = true;
	this->deferred_creating_flg_ = false;

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResource::OnCreateDeferred(void)
{
	return (0);
}


/**
 * @brief SetResourceMainIndex関数
 * @param mgr (manager)
 * @param res_main_index (resource_main_index)
 */
void tml::ManagerResource::SetResourceMainIndex(tml::Manager *mgr, const UINT res_main_index)
{
	if (mgr->CheckFriendResource(this)) {
		this->res_main_index_ = res_main_index;
	}

	return;
}


/**
 * @brief SetResourceSubIndex関数
 * @param mgr (manager)
 * @param res_sub_index (resource_sub_index)
 */
void tml::ManagerResource::SetResourceSubIndex(tml::Manager *mgr, const UINT res_sub_index)
{
	if (mgr->CheckFriendResource(this)) {
		this->res_sub_index_ = res_sub_index;
	}

	return;
}


/**
 * @brief SetResourceSharedPointer関数
 * @param mgr (manager)
 * @param res_shared_p (resource_shared_pointer)
 */
void tml::ManagerResource::SetResourceSharedPointer(tml::Manager *mgr, const tml::shared_ptr<tml::ManagerResource> &res_shared_p)
{
	if (mgr->CheckFriendResource(this)) {
		this->res_shared_p_ = res_shared_p;
	}

	return;
}


/**
 * @brief SetResourceName関数
 * @param mgr (manager)
 * @param res_name (resource_name)
 */
void tml::ManagerResource::SetResourceName(tml::Manager *mgr, const WCHAR *res_name)
{
	if (mgr->CheckFriendResource(this)) {
		this->res_name_ = res_name;
	}

	return;
}
