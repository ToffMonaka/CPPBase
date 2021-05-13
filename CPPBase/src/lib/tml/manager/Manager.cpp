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
	this->event_count = 0U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	event_cnt_ary_{},
	front_event_index_(0U),
	back_event_index_(0U)
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

	return;
}


/**
 * @brief Init関数
 */
void tml::Manager::Init(void)
{
	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;

	this->event_cnt_ary_.fill(0U);

	for (auto &event_cont : this->event_cont_ary_) {
		event_cont.clear();
	}

	this->front_event_index_ = 0U;
	this->back_event_index_ = 0U;
	this->stock_event_cnt_cont_.clear();
	this->stock_event_cont_cont_.clear();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
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

	this->front_event_index_ = 0U;
	this->back_event_index_ = 0U;
	this->stock_event_cnt_cont_.resize(desc.event_count);
	this->stock_event_cont_cont_.resize(desc.event_count);

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
	UINT use_res_cnt = 0U;

	while (this->check_res_itr_ != this->check_res_cont_.end()) {
		auto &res = (*this->check_res_itr_);

		use_res_cnt = 2U;

		if (!res->GetResourceName().empty()) {
			++use_res_cnt;
		}

		if (this->check_res_itr_->use_count() <= static_cast<LONG>(use_res_cnt)) {
			UINT res_main_index = res->GetResourceMainIndex();
			UINT res_sub_index = res->GetResourceSubIndex();

			if ((res_main_index < this->res_cont_.size())
			&& (res_sub_index < this->res_cont_[res_main_index].size())) {
				this->res_cont_[res_main_index][res_sub_index].remove(res);
			}

			if (!res->GetResourceName().empty()) {
				this->res_cont_by_name_.erase(res->GetResourceName());
			}

			this->check_res_itr_ = this->check_res_cont_.erase(this->check_res_itr_);
		} else {
			++this->check_res_itr_;
		}

		++check_res_cnt;

		if (check_res_cnt >= 10U) {
			break;
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

	auto &back_event_cnt = this->event_cnt_ary_[this->back_event_index_];
	auto &back_event_cont = this->event_cont_ary_[this->back_event_index_];

	for (UINT back_event_i = 0U; back_event_i < back_event_cnt; ++back_event_i) {
		tml::unique_ptr<tml::ManagerEvent> &event = back_event_cont[back_event_i];
		UINT event_index = event->GetEventIndex();

		auto &stock_event_cnt = this->stock_event_cnt_cont_[event_index];
		auto &stock_event_cont = this->stock_event_cont_cont_[event_index];

		if (stock_event_cnt >= stock_event_cont.size()) {
			stock_event_cont.resize(stock_event_cnt + 128U);
		}

		stock_event_cont[stock_event_cnt] = std::move(event);

		++stock_event_cnt;
	}

	back_event_cnt = 0U;

	return;
}


/**
 * @brief CreateResourceContainer関数
 * @param res_cnt_cont (resource_count_container)
 * @return res (result)<br>
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
			}

			res_sub_cont.clear();
		}

		res_main_cont.clear();
	}

	this->res_cont_.clear();
	this->res_cont_by_name_.clear();
	this->check_res_cont_.clear();
	this->check_res_itr_ = this->check_res_cont_.end();

	return;
}
