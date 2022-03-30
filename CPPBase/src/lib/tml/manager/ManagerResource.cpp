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
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::ManagerResourceDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ManagerResource::ManagerResource() :
	desc_(nullptr),
	mgr_(nullptr),
	res_type_(0U),
	deferred_create_flg_(false),
	deferred_created_flg_(false),
	deferred_create_added_flg_(false)
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

	return;
}


/**
 * @brief Create関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResource::Create(void)
{
	this->Init();

	if ((this->desc_ == nullptr)
	|| (this->mgr_ == nullptr)) {
		this->Init();
		this->InitDeferredCreate(false);

		return (-1);
	}

	if (this->OnCreate() < 0) {
		this->Init();
		this->InitDeferredCreate(false);

		return (-1);
	}

	if (!this->desc_->deferred_create_flag) {
		if (!this->deferred_created_flg_) {
			if (this->OnCreateDeferred() < 0) {
				this->Init();
				this->InitDeferredCreate(false);

				return (-1);
			}

			this->InitDeferredCreate(true);
		}
	}

	return (0);
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResource::OnCreate(void)
{
	return (0);
}


/**
 * @brief CreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerResource::CreateDeferred(void)
{
	if (!this->deferred_create_flg_) {
		return (-1);
	}

	if (!this->deferred_created_flg_) {
		if (this->OnCreateDeferred() < 0) {
			this->Init();
			this->InitDeferredCreate(false);

			return (-1);
		}

		this->InitDeferredCreate(true);
	}

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
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::ManagerResource::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = desc;

	return;
}


/**
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::ManagerResource::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief InitDeferredCreate関数
 * @param deferred_created_flg (deferred_created_flag)
 */
void tml::ManagerResource::InitDeferredCreate(const bool deferred_created_flg)
{
	this->desc_unique_p_.reset();
	this->SetDesc(nullptr);
	this->deferred_create_flg_ = false;
	this->deferred_created_flg_ = deferred_created_flg;

	return;
}
