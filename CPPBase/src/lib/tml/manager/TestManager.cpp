/**
 * @file
 * @brief Managerコードファイル
 */


#include "TestManager.h"


/**
 * @brief コンストラクタ
 */
tml::test::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_device_context_handle(nullptr),
	factory(nullptr)
{
	this->InitResourceCount();
	this->InitTaskCount();
	this->InitEventCount();

	return;
}


/**
 * @brief デストラクタ
 */
tml::test::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::test::ManagerDesc::Init(void)
{
	this->Release();

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;
	this->factory = nullptr;

	this->InitResourceCount();
	this->InitTaskCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void tml::test::ManagerDesc::InitResourceCount(void)
{
	this->resource_count_container.clear();

	return;
}


/**
 * @brief InitTaskCount関数
 */
void tml::test::ManagerDesc::InitTaskCount(void)
{
	this->task_count_container.clear();

	return;
}


/**
 * @brief InitEventCount関数
 */
void tml::test::ManagerDesc::InitEventCount(void)
{
	this->event_count_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::test::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	factory(nullptr)
{
	this->res_cont_.clear();
	this->res_itr_ = this->res_cont_.end();

	return;
}


/**
 * @brief デストラクタ
 */
tml::test::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::test::Manager::Release(void)
{
	this->DeleteResourceContainer();

	return;
}


/**
 * @brief Init関数
 */
void tml::test::Manager::Init(void)
{
	this->Release();

	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;
	this->factory = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::Manager::Create(const tml::test::ManagerDesc &desc)
{
	if ((desc.window_handle == nullptr)
	|| (desc.window_device_context_handle == nullptr)
	|| (desc.factory == nullptr)) {
		return (-1);
	}

	this->wnd_handle_ = desc.window_handle;
	this->wnd_dc_handle_ = desc.window_device_context_handle;
	this->factory = desc.factory;

	if (this->CreateResourceContainer(desc.resource_count_container) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::test::Manager::Update(void)
{
	if (this->res_itr_ == this->res_cont_.end()) {
		this->res_itr_ = this->res_cont_.begin();
	}

	UINT res_cnt = 0U;
	UINT res_use_cnt = 0U;

	while (this->res_itr_ != this->res_cont_.end()) {
		res_use_cnt = 3U;

		if (!(*this->res_itr_)->res_name_.empty()) {
			++res_use_cnt;
		}

		if (this->res_itr_->use_count() <= static_cast<LONG>(res_use_cnt)) {
			auto res = (*this->res_itr_);

			res->Init();
			res->res_shared_p_.reset();

			this->res_cont_by_index_[res->res_index_].remove(res);

			if (!res->res_name_.empty()) {
				this->res_cont_by_name_.erase(res->res_name_);
			}

			this->res_itr_ = this->res_cont_.erase(this->res_itr_);
		} else {
			++this->res_itr_;
		}

		if (++res_cnt >= 10U) {
			break;
		}
	}

	if (!this->deferred_create_res_cont_.empty()) {
		auto res_itr = this->deferred_create_res_cont_.begin();

		if (((*res_itr)->CreateDeferred() < 0)
		|| (!(*res_itr)->IsDeferredCreating())) {
			this->deferred_create_res_cont_.erase(res_itr);
		}
	}

	return;
}


/**
 * @brief CreateResourceContainer関数
 * @param res_cnt_cont (resource_count_container)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::Manager::CreateResourceContainer(const std::vector<UINT> &res_cnt_cont)
{
	this->DeleteResourceContainer();

	this->res_cont_by_index_.resize(res_cnt_cont.size());

	return (0);
}


/**
 * @brief DeleteResourceContainer関数
 */
void tml::test::Manager::DeleteResourceContainer(void)
{
	for (auto &res : this->res_cont_) {
		res->Init();
		res->res_shared_p_.reset();
	}

	this->res_cont_.clear();
	this->res_itr_ = this->res_cont_.end();
	this->res_cont_by_index_.clear();
	this->res_cont_by_name_.clear();
	this->deferred_create_res_cont_.clear();

	return;
}


/**
 * @brief GetResourceInitPart関数
 * @param res (resource)
 */
void tml::test::Manager::GetResourceInitPart(tml::shared_ptr<tml::test::ManagerResource> &res)
{
	res->deferred_create_desc_unique_p_.reset();
	res->deferred_create_desc_ = nullptr;

	res->res_shared_p_.reset();

	return;
}


/**
 * @brief SetResourceName関数
 * @param res (resource)
 * @param res_name (resource_name)
 */
void tml::test::Manager::SetResourceName(tml::test::ManagerResource *res, const WCHAR *res_name)
{
	if ((res == nullptr)
	|| (res_name == nullptr)) {
		return;
	}

	if (res_name[0] != 0) {
		auto res_itr = this->res_cont_by_name_.find(res_name);

		if (res_itr != this->res_cont_by_name_.end()) {
			return;
		}
	}

	if (!res->res_name_.empty()) {
		this->res_cont_by_name_.erase(res->res_name_);
	}

	res->res_name_ = res_name;

	if (!res->res_name_.empty()) {
		this->res_cont_by_name_.emplace(res->res_name_, res->res_shared_p_);
	}

	return;
}
