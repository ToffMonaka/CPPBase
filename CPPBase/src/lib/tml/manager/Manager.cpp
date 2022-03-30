/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_device_context_handle(nullptr),
	factory(nullptr)
{
	this->resource_count = 0U;
	this->task_count = 0U;
	this->event_count = 0U;

	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerDesc::Init(void)
{
	this->Release();

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;
	this->factory = nullptr;

	this->resource_count = 0U;
	this->task_count = 0U;
	this->event_count = 0U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Manager::Manager() :
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
tml::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Manager::Release(void)
{
	this->DeleteResourceContainer();
	this->DeleteTaskContainer();
	this->DeleteEventContainer();

	return;
}


/**
 * @brief Init関数
 */
void tml::Manager::Init(void)
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
INT tml::Manager::Create(const tml::ManagerDesc &desc)
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
void tml::Manager::Update(void)
{
	UINT loop_cnt = 0U;
	UINT use_cnt = 0U;

	loop_cnt = 0U;

	if (this->res_itr_ == this->res_cont_.end()) {
		this->res_itr_ = this->res_cont_.begin();
	}

	while (this->res_itr_ != this->res_cont_.end()) {
		use_cnt = 3U;

		if (!(*this->res_itr_)->res_name_.empty()) {
			++use_cnt;
		}

		if (this->res_itr_->use_count() <= static_cast<LONG>(use_cnt)) {
			auto res = (*this->res_itr_);

			res->Init();

			this->InitResourcePart(res);

			this->res_cont_by_type_[res->res_type_].remove(res);

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

	if (this->task_itr_ == this->task_cont_.end()) {
		this->task_itr_ = this->task_cont_.begin();
	}

	while (this->task_itr_ != this->task_cont_.end()) {
		use_cnt = 3U;

		if (!(*this->task_itr_)->task_name_.empty()) {
			++use_cnt;
		}

		if (this->task_itr_->use_count() <= static_cast<LONG>(use_cnt)) {
			auto task = (*this->task_itr_);

			task->Init();

			this->InitTaskPart(task);

			this->task_cont_by_type_[task->task_type_].remove(task);

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

	if (this->event_itr_ == this->event_cont_.end()) {
		this->event_itr_ = this->event_cont_.begin();
	}

	while (this->event_itr_ != this->event_cont_.end()) {
		use_cnt = 3U;

		if (!(*this->event_itr_)->event_name_.empty()) {
			++use_cnt;
		}

		if (this->event_itr_->use_count() <= static_cast<LONG>(use_cnt)) {
			auto event = (*this->event_itr_);

			event->Init();

			this->InitEventPart(event);

			this->event_cont_by_type_[event->event_type_].remove(event);

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

	if (!this->add_deferred_create_res_cont_.empty()) {
		for (auto &res : this->add_deferred_create_res_cont_) {
			if (!res->deferred_create_added_flg_) {
				res->deferred_create_added_flg_ = true;

				this->deferred_create_res_cont_.push_back(std::move(res));
			}
		}

		this->add_deferred_create_res_cont_.clear();
	}

	for (auto res_itr = this->deferred_create_res_cont_.begin(); res_itr != this->deferred_create_res_cont_.end();) {
		(*res_itr)->CreateDeferred();

		if (!(*res_itr)->deferred_create_flg_) {
			(*res_itr)->deferred_create_added_flg_ = false;

			res_itr = this->deferred_create_res_cont_.erase(res_itr);
		} else {
			++res_itr;
		}

		break;
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
INT tml::Manager::CreateResourceContainer(const UINT res_cnt)
{
	this->DeleteResourceContainer();

	this->res_cont_by_type_.resize(res_cnt);

	return (0);
}


/**
 * @brief DeleteResourceContainer関数
 */
void tml::Manager::DeleteResourceContainer(void)
{
	for (auto &res : this->res_cont_) {
		res->Init();

		this->InitResourcePart(res);
	}

	this->res_cont_.clear();
	this->res_itr_ = this->res_cont_.end();
	this->res_cont_by_type_.clear();
	this->res_cont_by_name_.clear();
	this->deferred_create_res_cont_.clear();
	this->add_deferred_create_res_cont_.clear();

	return;
}


/**
 * @brief InitResourcePart関数
 * @param res (resource)
 */
void tml::Manager::InitResourcePart(tml::shared_ptr<tml::ManagerResource> &res)
{
	res->desc_unique_p_.reset();
	res->SetDesc(nullptr);

	res->res_shared_p_.reset();

	return;
}


/**
 * @brief SetResourceName関数
 * @param res (resource)
 * @param res_name (resource_name)
 */
void tml::Manager::SetResourceName(tml::ManagerResource *res, const WCHAR *res_name)
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
INT tml::Manager::CreateTaskContainer(const UINT task_cnt)
{
	this->DeleteTaskContainer();

	this->task_cont_by_type_.resize(task_cnt);

	return (0);
}


/**
 * @brief DeleteTaskContainer関数
 */
void tml::Manager::DeleteTaskContainer(void)
{
	for (auto &task : this->task_cont_) {
		task->Init();

		this->InitTaskPart(task);
	}

	this->task_cont_.clear();
	this->task_itr_ = this->task_cont_.end();
	this->task_cont_by_type_.clear();
	this->task_cont_by_name_.clear();
	this->run_task_cont_.clear();
	this->add_run_task_cont_.clear();

	return;
}


/**
 * @brief InitTaskPart関数
 * @param task (task)
 */
void tml::Manager::InitTaskPart(tml::shared_ptr<tml::ManagerTask> &task)
{
	task->task_shared_p_.reset();

	return;
}


/**
 * @brief SetTaskName関数
 * @param task (task)
 * @param task_name (task_name)
 */
void tml::Manager::SetTaskName(tml::ManagerTask *task, const WCHAR *task_name)
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
void tml::Manager::SetTaskRunFlag(tml::ManagerTask *task, const bool run_flg)
{
	if ((task == nullptr)
	|| (task->run_flg_ == run_flg)) {
		return;
	}

	task->run_flg_ = run_flg;

	if (run_flg) {
		this->add_run_task_cont_.push_back(task->task_shared_p_);
	}

	return;
}


/**
 * @brief RunTask関数
 */
void tml::Manager::RunTask(void)
{
	if (!this->add_run_task_cont_.empty()) {
		for (auto &task : this->add_run_task_cont_) {
			if (!task->run_added_flg_) {
				task->run_added_flg_ = true;

				this->run_task_cont_.push_back(std::move(task));
			}
		}

		this->add_run_task_cont_.clear();
	}

	for (auto task_itr = this->run_task_cont_.begin(); task_itr != this->run_task_cont_.end();) {
		(*task_itr)->Run();

		if (!(*task_itr)->run_flg_) {
			(*task_itr)->run_added_flg_ = false;

			task_itr = this->run_task_cont_.erase(task_itr);
		} else {
			++task_itr;
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
INT tml::Manager::CreateEventContainer(const UINT event_cnt)
{
	this->DeleteEventContainer();

	this->event_cont_by_type_.resize(event_cnt);
	this->run_event_cont_.resize(event_cnt);

	return (0);
}


/**
 * @brief DeleteEventContainer関数
 */
void tml::Manager::DeleteEventContainer(void)
{
	for (auto &event : this->event_cont_) {
		event->Init();

		this->InitEventPart(event);
	}

	this->event_cont_.clear();
	this->event_itr_ = this->event_cont_.end();
	this->event_cont_by_type_.clear();
	this->event_cont_by_name_.clear();
	this->run_event_cont_.clear();
	this->add_run_event_cont_.clear();

	return;
}


/**
 * @brief InitEventPart関数
 * @param event (event)
 */
void tml::Manager::InitEventPart(tml::shared_ptr<tml::ManagerEvent> &event)
{
	event->event_shared_p_.reset();

	return;
}


/**
 * @brief SetEventName関数
 * @param event (event)
 * @param event_name (event_name)
 */
void tml::Manager::SetEventName(tml::ManagerEvent *event, const WCHAR *event_name)
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
void tml::Manager::SetEventRunFlag(tml::ManagerEvent *event, const bool run_flg)
{
	if ((event == nullptr)
	|| (event->run_flg_ == run_flg)) {
		return;
	}

	event->run_flg_ = run_flg;

	if (run_flg) {
		this->add_run_event_cont_.push_back(event->event_shared_p_);
	}

	return;
}


/**
 * @brief RunEvent関数
 * @param event_type (event_type)
 * @param dat (data)
 */
void tml::Manager::RunEvent(const UINT event_type, const tml::ManagerEventData *dat)
{
	if (!this->add_run_event_cont_.empty()) {
		for (auto &event : this->add_run_event_cont_) {
			if (!event->run_added_flg_) {
				event->run_added_flg_ = true;

				this->run_event_cont_[event->GetEventType()].push_back(std::move(event));
			}
		}

		this->add_run_event_cont_.clear();
	}

	if (event_type >= this->run_event_cont_.size()) {
		return;
	}

	for (auto event_itr = this->run_event_cont_[event_type].begin(); event_itr != this->run_event_cont_[event_type].end();) {
		(*event_itr)->Run(dat);

		if (!(*event_itr)->run_flg_) {
			(*event_itr)->run_added_flg_ = false;

			event_itr = this->run_event_cont_[(*event_itr)->GetEventType()].erase(event_itr);
		} else {
			++event_itr;
		}
	}

	return;
}


#if 0
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_device_context_handle(nullptr),
	factory(nullptr)
{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerDesc::Init(void)
{
	this->Release();

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;
	this->factory = nullptr;

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void tml::ManagerDesc::InitResourceCount(void)
{
	this->resource_count_container.clear();

	return;
}


/**
 * @brief InitEventCount関数
 */
void tml::ManagerDesc::InitEventCount(void)
{
	this->event_count_container.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	factory(nullptr),
	friend_res_(nullptr),
	front_event_index_(0U),
	back_event_index_(0U),
	friend_event_(nullptr)
{
	this->check_res_cont_.clear();
	this->check_res_itr_ = this->check_res_cont_.end();

	return;
}


/**
 * @brief デストラクタ
 */
tml::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Manager::Release(void)
{
	this->DeleteResourceContainer();
	this->DeleteEventContainer();

	return;
}


/**
 * @brief Init関数
 */
void tml::Manager::Init(void)
{
	this->Release();

	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;
	this->factory = nullptr;
	this->friend_res_ = nullptr;
	this->friend_event_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::Manager::Create(const tml::ManagerDesc &desc)
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

	if (this->CreateEventContainer(desc.event_count_container) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::Manager::Update(void)
{
	if (this->check_res_itr_ == this->check_res_cont_.end()) {
		this->check_res_itr_ = this->check_res_cont_.begin();
	}

	UINT check_res_cnt = 0U;
	UINT check_res_use_cnt = 0U;

	while (this->check_res_itr_ != this->check_res_cont_.end()) {
		check_res_use_cnt = 3U;

		if (!(*this->check_res_itr_)->GetResourceName().empty()) {
			++check_res_use_cnt;
		}

		if (this->check_res_itr_->use_count() <= static_cast<LONG>(check_res_use_cnt)) {
			tml::shared_ptr<tml::ManagerResource> res = (*this->check_res_itr_);

			res->Init();

			this->res_cont_[res->GetResourceMainIndex()][res->GetResourceSubIndex()].remove(res);

			if (!res->GetResourceName().empty()) {
				this->res_cont_by_name_.erase(res->GetResourceName());
			}

			this->check_res_itr_ = this->check_res_cont_.erase(this->check_res_itr_);

			this->friend_res_ = res.get();
			this->friend_res_->SetResourceSharedPointer(this, tml::shared_ptr<tml::ManagerResource>());
			this->friend_res_ = nullptr;
		} else {
			++this->check_res_itr_;
		}

		++check_res_cnt;

		if (check_res_cnt >= 10U) {
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

	if (this->front_event_index_ == this->back_event_index_) {
		this->front_event_index_ = 0U;
		this->back_event_index_ = 1U;
	} else {
		auto tmp_event_index = this->front_event_index_;

		this->front_event_index_ = this->back_event_index_;
		this->back_event_index_ = tmp_event_index;
	}

	auto &event_cnt_cont = this->event_cnt_cont_ary_[this->back_event_index_];
	auto &event_cont_cont = this->event_cont_ary_[this->back_event_index_];

	for (UINT event_main_i = 0U; event_main_i < event_cnt_cont.size(); ++event_main_i) {
		auto &event_cnt = event_cnt_cont[event_main_i];
		auto &event_cont = event_cont_cont[event_main_i];

		for (UINT event_i = 0U; event_i < event_cnt; ++event_i) {
			tml::unique_ptr<tml::ManagerEvent> &event = event_cont[event_i];

			auto &stock_event_cnt = this->stock_event_cnt_cont_cont_[event->GetEventMainIndex()][event->GetEventSubIndex()];
			auto &stock_event_cont = this->stock_event_cont_cont_[event->GetEventMainIndex()][event->GetEventSubIndex()];

			if (stock_event_cnt >= stock_event_cont.size()) {
				stock_event_cont.resize(stock_event_cnt + 128U);
			}

			stock_event_cont[stock_event_cnt] = std::move(event);

			++stock_event_cnt;
		}

		event_cnt = 0U;
	}

	return;
}


/**
 * @brief CreateResourceContainer関数
 * @param res_cnt_cont (resource_count_container)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::Manager::CreateResourceContainer(const std::vector<UINT> &res_cnt_cont)
{
	this->DeleteResourceContainer();

	this->res_cont_.resize(res_cnt_cont.size());

	for (size_t res_cont_i = 0U; res_cont_i < this->res_cont_.size(); ++res_cont_i) {
		this->res_cont_[res_cont_i].resize(res_cnt_cont[res_cont_i]);
	}

	return (0);
}


/**
 * @brief DeleteResourceContainer関数
 */
void tml::Manager::DeleteResourceContainer(void)
{
	for (auto &res_main_cont : this->res_cont_) {
		for (auto &res_sub_cont : res_main_cont) {
			for (auto &res : res_sub_cont) {
				res->Init();

				this->friend_res_ = res.get();
				this->friend_res_->SetResourceSharedPointer(this, tml::shared_ptr<tml::ManagerResource>());
				this->friend_res_ = nullptr;
			}
		}
	}

	this->res_cont_.clear();
	this->res_cont_by_name_.clear();
	this->check_res_cont_.clear();
	this->check_res_itr_ = this->check_res_cont_.end();
	this->deferred_create_res_cont_.clear();

	return;
}


/**
 * @brief GetResourceInitPart関数
 * @param res (resource)
 */
void tml::Manager::GetResourceInitPart(tml::shared_ptr<tml::ManagerResource> &res)
{
	res->SetDeferredCreateDesc(nullptr);

	this->friend_res_ = res.get();
	this->friend_res_->SetResourceSharedPointer(this, tml::shared_ptr<tml::ManagerResource>());
	this->friend_res_ = nullptr;

	return;
}


/**
 * @brief SetResourceName関数
 * @param res (resource)
 * @param res_name (resource_name)
 */
void tml::Manager::SetResourceName(tml::ManagerResource *res, const WCHAR *res_name)
{
	if ((res == nullptr)
	|| (res_name == nullptr)) {
		return;
	}

	auto &tmp_res = res->GetResourceSharedPointer();

	if (!tmp_res->GetResourceName().empty()) {
		this->res_cont_by_name_.erase(tmp_res->GetResourceName());
	}

	this->friend_res_ = tmp_res.get();
	this->friend_res_->SetResourceName(this, res_name);
	this->friend_res_ = nullptr;

	if (!tmp_res->GetResourceName().empty()) {
		this->res_cont_by_name_.insert(std::make_pair(tmp_res->GetResourceName(), tmp_res));
	}

	return;
}


/**
 * @brief CheckFriendResource関数
 * @param res (resource)
 * @return result_flg (result_flag)<br>
 * false=失敗,true=成功
 */
bool tml::Manager::CheckFriendResource(const tml::ManagerResource *res) const
{
	if (res == nullptr) {
		return (false);
	}

	return (res == this->friend_res_);
}


/**
 * @brief CreateEventContainer関数
 * @param event_cnt_cont (event_count_container)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::Manager::CreateEventContainer(const std::vector<UINT> &event_cnt_cont)
{
	this->DeleteEventContainer();

	for (size_t event_cnt_cont_i = 0U; event_cnt_cont_i < this->event_cnt_cont_ary_.size(); ++event_cnt_cont_i) {
		this->event_cnt_cont_ary_[event_cnt_cont_i].resize(event_cnt_cont.size());
		this->event_cont_ary_[event_cnt_cont_i].resize(event_cnt_cont.size());
	}

	this->stock_event_cnt_cont_cont_.resize(event_cnt_cont.size());

	for (size_t stock_event_cnt_cont_i = 0U; stock_event_cnt_cont_i < this->stock_event_cnt_cont_cont_.size(); ++stock_event_cnt_cont_i) {
		this->stock_event_cnt_cont_cont_[stock_event_cnt_cont_i].resize(event_cnt_cont[stock_event_cnt_cont_i]);
	}

	this->stock_event_cont_cont_.resize(event_cnt_cont.size());

	for (size_t stock_event_cont_i = 0U; stock_event_cont_i < this->stock_event_cont_cont_.size(); ++stock_event_cont_i) {
		this->stock_event_cont_cont_[stock_event_cont_i].resize(event_cnt_cont[stock_event_cont_i]);
	}

	return (0);
}


/**
 * @brief DeleteEventContainer関数
 */
void tml::Manager::DeleteEventContainer(void)
{
	for (size_t event_cnt_cont_i = 0U; event_cnt_cont_i < this->event_cnt_cont_ary_.size(); ++event_cnt_cont_i) {
		this->event_cnt_cont_ary_[event_cnt_cont_i].clear();
		this->event_cont_ary_[event_cnt_cont_i].clear();
	}

	this->front_event_index_ = 0U;
	this->back_event_index_ = 0U;
	this->stock_event_cnt_cont_cont_.clear();
	this->stock_event_cont_cont_.clear();

	return;
}


/**
 * @brief AddEventInitPart関数
 * @param event (event)
 */
void tml::Manager::AddEventInitPart(tml::unique_ptr<tml::ManagerEvent> &event)
{
	return;
}


/**
 * @brief CheckFriendEvent関数
 * @param event (event)
 * @return result_flg (result_flag)<br>
 * false=失敗,true=成功
 */
bool tml::Manager::CheckFriendEvent(const tml::ManagerEvent *event) const
{
	if (event == nullptr) {
		return (false);
	}

	return (event == this->friend_event_);
}
#endif
