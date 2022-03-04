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
	this->resource_count = 0U;

	return;
}


/**
 * @brief InitTaskCount関数
 */
void tml::test::ManagerDesc::InitTaskCount(void)
{
	this->task_count = 0U;

	return;
}


/**
 * @brief InitEventCount関数
 */
void tml::test::ManagerDesc::InitEventCount(void)
{
	this->event_count = 0U;

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

	if (this->CreateResourceContainer(desc.resource_count) < 0) {
		return (-1);
	}

	if (this->CreateTaskContainer(desc.task_count) < 0) {
		return (-1);
	}

	if (this->CreateEventContainer(desc.event_count) < 0) {
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

			this->InitResourcePart(res);

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

			this->InitTaskPart(task);

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

			this->InitEventPart(event);

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
		|| ((*res_itr)->IsDeferredCreated())) {
			this->deferred_create_res_cont_.erase(res_itr);
		}
	}

	this->RunTask();

	return;
}


/**
 * @brief CreateResourceContainer関数
 * @param res_cnt (resource_count)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::Manager::CreateResourceContainer(const UINT res_cnt)
{
	this->DeleteResourceContainer();

	this->res_cont_by_index_.resize(res_cnt);

	return (0);
}


/**
 * @brief DeleteResourceContainer関数
 */
void tml::test::Manager::DeleteResourceContainer(void)
{
	for (auto &res : this->res_cont_) {
		res->Init();

		this->InitResourcePart(res);
	}

	this->res_cont_.clear();
	this->res_itr_ = this->res_cont_.end();
	this->res_cont_by_index_.clear();
	this->res_cont_by_name_.clear();
	this->deferred_create_res_cont_.clear();

	return;
}


/**
 * @brief InitResourcePart関数
 * @param res (resource)
 */
void tml::test::Manager::InitResourcePart(tml::shared_ptr<tml::test::ManagerResource> &res)
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
 * @param task_cnt (task_count)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::Manager::CreateTaskContainer(const UINT task_cnt)
{
	this->DeleteTaskContainer();

	this->task_cont_by_index_.resize(task_cnt);

	return (0);
}


/**
 * @brief DeleteTaskContainer関数
 */
void tml::test::Manager::DeleteTaskContainer(void)
{
	for (auto &task : this->task_cont_) {
		task->Init();

		this->InitTaskPart(task);
	}

	this->task_cont_.clear();
	this->task_itr_ = this->task_cont_.end();
	this->task_cont_by_index_.clear();
	this->task_cont_by_name_.clear();
	this->run_task_cont_.clear();
	this->add_run_task_cont_.clear();

	return;
}


/**
 * @brief InitTaskPart関数
 * @param task (task)
 */
void tml::test::Manager::InitTaskPart(tml::shared_ptr<tml::test::ManagerTask> &task)
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
	if ((task == nullptr)
	|| (task->run_flg_ == run_flg)) {
		return;
	}

	task->run_flg_ = run_flg;

	if (run_flg) {
		this->add_run_task_cont_.push_back(task->task_shared_p_);
	} else {
		this->add_run_task_cont_.remove(task->task_shared_p_);
	}

	return;
}


/**
 * @brief RunTask関数
 */
void tml::test::Manager::RunTask(void)
{
	for (auto &task : this->add_run_task_cont_) {
		this->run_task_cont_.push_back(std::move(task));
	}

	this->add_run_task_cont_.clear();

	for (auto task_itr = this->run_task_cont_.begin(); task_itr != this->run_task_cont_.end();) {
		(*task_itr)->Run();

		if ((*task_itr)->GetRunFlag()) {
			++task_itr;
		} else {
			task_itr = this->run_task_cont_.erase(task_itr);
		}
	}

	return;
}


/**
 * @brief CreateEventContainer関数
 * @param event_cnt (event_count)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::Manager::CreateEventContainer(const UINT event_cnt)
{
	this->DeleteEventContainer();

	this->event_cont_by_index_.resize(event_cnt);
	this->run_event_cont_.resize(event_cnt);
	this->add_run_event_cont_.resize(event_cnt);

	return (0);
}


/**
 * @brief DeleteEventContainer関数
 */
void tml::test::Manager::DeleteEventContainer(void)
{
	for (auto &event : this->event_cont_) {
		event->Init();

		this->InitEventPart(event);
	}

	this->event_cont_.clear();
	this->event_itr_ = this->event_cont_.end();
	this->event_cont_by_index_.clear();
	this->event_cont_by_name_.clear();
	this->run_event_cont_.clear();
	this->add_run_event_cont_.clear();

	return;
}


/**
 * @brief InitEventPart関数
 * @param event (event)
 */
void tml::test::Manager::InitEventPart(tml::shared_ptr<tml::test::ManagerEvent> &event)
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
	if ((event == nullptr)
	|| (event->run_flg_ == run_flg)) {
		return;
	}

	event->run_flg_ = run_flg;

	if (run_flg) {
		this->add_run_event_cont_[event->event_index_].push_back(event->event_shared_p_);
	} else {
		this->add_run_event_cont_[event->event_index_].remove(event->event_shared_p_);
	}

	return;
}


/**
 * @brief RunEvent関数
 * @param event_index (event_index)
 */
void tml::test::Manager::RunEvent(const UINT event_index)
{
	if (event_index >= this->run_event_cont_.size()) {
		return;
	}

	for (auto &event : this->add_run_event_cont_[event_index]) {
		this->run_event_cont_[event_index].push_back(std::move(event));
	}

	this->add_run_event_cont_[event_index].clear();

	for (auto event_itr = this->run_event_cont_[event_index].begin(); event_itr != this->run_event_cont_[event_index].end();) {
		(*event_itr)->Run();

		if ((*event_itr)->GetRunFlag()) {
			++event_itr;
		} else {
			event_itr = this->run_event_cont_[event_index].erase(event_itr);
		}
	}

	return;
}
