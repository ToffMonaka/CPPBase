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
	this->task_cont_.clear();
	this->task_itr_ = this->task_cont_.end();
	this->event_cont_.clear();
	this->event_itr_ = this->event_cont_.end();

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
	this->DeleteTaskContainer();
	this->DeleteEventContainer();

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

	if (this->CreateTaskContainer(desc.task_count_container) < 0) {
		return (-1);
	}

	if (this->CreateEventContainer(desc.event_count_container) < 0) {
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

	UINT loop_cnt = 0U;
	UINT use_cnt = 0U;

	loop_cnt = 0U;

	while (this->res_itr_ != this->res_cont_.end()) {
		use_cnt = 3U;

		if (!(*this->res_itr_)->res_name_.empty()) {
			++use_cnt;
		}

		if (this->res_itr_->use_count() <= static_cast<LONG>(use_cnt)) {
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

		if (++loop_cnt >= 10U) {
			break;
		}
	}

	loop_cnt = 0U;

	while (this->task_itr_ != this->task_cont_.end()) {
		use_cnt = 3U;

		if (!(*this->task_itr_)->task_name_.empty()) {
			++use_cnt;
		}

		if (this->task_itr_->use_count() <= static_cast<LONG>(use_cnt)) {
			auto task = (*this->task_itr_);

			task->Init();
			task->task_shared_p_.reset();

			this->task_cont_by_index_[task->task_index_].remove(task);

			if (!task->task_name_.empty()) {
				this->task_cont_by_name_.erase(task->task_name_);
			}

			this->task_itr_ = this->task_cont_.erase(this->task_itr_);
		} else {
			++this->task_itr_;
		}

		if (++loop_cnt >= 10U) {
			break;
		}
	}

	loop_cnt = 0U;

	while (this->event_itr_ != this->event_cont_.end()) {
		use_cnt = 3U;

		if (!(*this->event_itr_)->event_name_.empty()) {
			++use_cnt;
		}

		if (this->event_itr_->use_count() <= static_cast<LONG>(use_cnt)) {
			auto event = (*this->event_itr_);

			event->Init();
			event->event_shared_p_.reset();

			this->event_cont_by_index_[event->event_index_].remove(event);

			if (!event->event_name_.empty()) {
				this->event_cont_by_name_.erase(event->event_name_);
			}

			this->event_itr_ = this->event_cont_.erase(this->event_itr_);
		} else {
			++this->event_itr_;
		}

		if (++loop_cnt >= 10U) {
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

	this->RunTask();

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


/**
 * @brief CreateTaskContainer関数
 * @param task_cnt_cont (task_count_container)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::Manager::CreateTaskContainer(const std::vector<UINT> &task_cnt_cont)
{
	this->DeleteTaskContainer();

	this->task_cont_by_index_.resize(task_cnt_cont.size());

	return (0);
}


/**
 * @brief DeleteTaskContainer関数
 */
void tml::test::Manager::DeleteTaskContainer(void)
{
	for (auto &task : this->task_cont_) {
		task->Init();
		task->task_shared_p_.reset();
	}

	this->task_cont_.clear();
	this->task_itr_ = this->task_cont_.end();
	this->task_cont_by_index_.clear();
	this->task_cont_by_name_.clear();

	return;
}


/**
 * @brief GetTaskInitPart関数
 * @param task (task)
 */
void tml::test::Manager::GetTaskInitPart(tml::shared_ptr<tml::test::ManagerTask> &task)
{
	task->task_shared_p_.reset();

	return;
}


/**
 * @brief SetTaskName関数
 * @param task (task)
 * @param task_name (task_name)
 */
void tml::test::Manager::SetTaskName(tml::test::ManagerTask *task, const WCHAR *task_name)
{
	if ((task == nullptr)
	|| (task_name == nullptr)) {
		return;
	}

	if (task_name[0] != 0) {
		auto task_itr = this->task_cont_by_name_.find(task_name);

		if (task_itr != this->task_cont_by_name_.end()) {
			return;
		}
	}

	if (!task->task_name_.empty()) {
		this->task_cont_by_name_.erase(task->task_name_);
	}

	task->task_name_ = task_name;

	if (!task->task_name_.empty()) {
		this->task_cont_by_name_.emplace(task->task_name_, task->task_shared_p_);
	}

	return;
}


/**
 * @brief SetTaskRunFlag関数
 * @param task (task)
 * @param run_flg (run_flag)
 */
void tml::test::Manager::SetTaskRunFlag(tml::test::ManagerTask *task, const bool run_flg)
{
	return;
}


/**
 * @brief RunTask関数
 */
void tml::test::Manager::RunTask(void)
{
	return;
}


/**
 * @brief CreateEventContainer関数
 * @param event_cnt_cont (event_count_container)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::Manager::CreateEventContainer(const std::vector<UINT> &event_cnt_cont)
{
	this->DeleteEventContainer();

	this->event_cont_by_index_.resize(event_cnt_cont.size());

	return (0);
}


/**
 * @brief DeleteEventContainer関数
 */
void tml::test::Manager::DeleteEventContainer(void)
{
	for (auto &event : this->event_cont_) {
		event->Init();
		event->event_shared_p_.reset();
	}

	this->event_cont_.clear();
	this->event_itr_ = this->event_cont_.end();
	this->event_cont_by_index_.clear();
	this->event_cont_by_name_.clear();

	return;
}


/**
 * @brief GetEventInitPart関数
 * @param event (event)
 */
void tml::test::Manager::GetEventInitPart(tml::shared_ptr<tml::test::ManagerEvent> &event)
{
	event->event_shared_p_.reset();

	return;
}


/**
 * @brief SetEventName関数
 * @param event (event)
 * @param event_name (event_name)
 */
void tml::test::Manager::SetEventName(tml::test::ManagerEvent *event, const WCHAR *event_name)
{
	if ((event == nullptr)
	|| (event_name == nullptr)) {
		return;
	}

	if (event_name[0] != 0) {
		auto event_itr = this->event_cont_by_name_.find(event_name);

		if (event_itr != this->event_cont_by_name_.end()) {
			return;
		}
	}

	if (!event->event_name_.empty()) {
		this->event_cont_by_name_.erase(event->event_name_);
	}

	event->event_name_ = event_name;

	if (!event->event_name_.empty()) {
		this->event_cont_by_name_.emplace(event->event_name_, event->event_shared_p_);
	}

	return;
}


/**
 * @brief SetEventRunFlag関数
 * @param event (event)
 * @param run_flg (run_flag)
 */
void tml::test::Manager::SetEventRunFlag(tml::test::ManagerEvent *event, const bool run_flg)
{
	return;
}


/**
 * @brief RunEvent関数
 * @param event_index (event_index)
 */
void tml::test::Manager::RunEvent(const UINT event_index)
{
	return;
}
