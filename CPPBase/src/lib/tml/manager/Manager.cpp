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
	window_device_context_handle(nullptr)
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
	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;
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
	|| (desc.window_device_context_handle == nullptr)) {
		return (-1);
	}

	this->wnd_handle_ = desc.window_handle;
	this->wnd_dc_handle_ = desc.window_device_context_handle;

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
 * @brief GetResourceInitResourcePart関数
 * @param res (resource)
 */
void tml::Manager::GetResourceInitResourcePart(tml::shared_ptr<tml::ManagerResource> &res)
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
 * @brief AddEventInitEventPart関数
 * @param event (event)
 */
void tml::Manager::AddEventInitEventPart(tml::unique_ptr<tml::ManagerEvent> &event)
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
