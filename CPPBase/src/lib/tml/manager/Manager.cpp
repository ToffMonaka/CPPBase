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
	this->resource_count_container.clear();
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
	this->resource_count_container.clear();
	this->event_count = 0U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	front_event_index_(0U),
	back_event_index_(0U)
{
	this->event_cnt_ary_.fill(0U);

	for (auto &event_cont : this->event_cont_ary_) {
		event_cont.clear();
	}

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
	for (auto &res_main_cont : this->res_cont_cont_) {
		for (auto &res_sub_cont : res_main_cont) {
			for (auto &res : res_sub_cont) {
				res->Init();
			}

			res_sub_cont.clear();
		}

		res_main_cont.clear();
	}

	this->res_cont_cont_.clear();

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

	this->res_cont_cont_.resize(desc.resource_count_container.size());

	for (UINT res_cont_i = 0U; res_cont_i < this->res_cont_cont_.size(); ++res_cont_i) {
		this->res_cont_cont_[res_cont_i].resize(desc.resource_count_container[res_cont_i]);
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
