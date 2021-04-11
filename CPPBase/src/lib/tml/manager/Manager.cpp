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

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr)
	/*
	event_cnt_ary_{},
	front_event_index_(0U),
	back_event_index_(0U),
	stock_event_cnt_ary_{},
	device_(nullptr),
	device_context_(nullptr)
	*/
{
	/*
	this->volume_ary_.fill(0.5f);
	this->mute_flg_ary_.fill(false);
	*/

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
	/*
	for (auto &res_cont : this->res_cont_ary_) {
		for (auto &res : res_cont) {
			res->Init();
		}

		res_cont.clear();
	}
	*/

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

	/*
	this->event_cnt_ary_.fill(0U);

	for (auto &event_cont : this->event_cont_ary_) {
		event_cont.clear();
	}

	this->front_event_index_ = 0U;
	this->back_event_index_ = 0U;

	this->stock_event_cnt_ary_.fill(0U);

	for (auto &stock_event_cont : this->stock_event_cont_ary_) {
		stock_event_cont.clear();
	}
	*/

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
		this->Init();

		return (-1);
	}

	this->Init();

	this->wnd_handle_ = desc.window_handle;
	this->wnd_dc_handle_ = desc.window_device_context_handle;

	return (0);
}


/**
 * @brief Update関数
 */
void tml::Manager::Update(void)
{
	/*
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
		tml::unique_ptr<tml::Event> &event = back_event_cont[back_event_i];

		auto event_index = static_cast<UINT>(event->GetEventType());
		auto &stock_event_cnt = this->stock_event_cnt_ary_[event_index];
		auto &stock_event_cont = this->stock_event_cont_ary_[event_index];

		if (stock_event_cnt >= stock_event_cont.size()) {
			stock_event_cont.resize(stock_event_cnt + 128U);
		}

		stock_event_cont[stock_event_cnt] = std::move(event);

		++stock_event_cnt;
	}

	back_event_cnt = 0U;
	*/

	return;
}
