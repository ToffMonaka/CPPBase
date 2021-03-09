/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_device_context_handle(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::ManagerDesc::Init(void)
{
	this->Release();

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	event_index_(0U),
	event_cnt_ary_{},
	stock_event_cnt_ary_{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::input::Manager::Release(void)
{
	for (auto &stock_event_cont : this->stock_event_cont_ary_) {
		stock_event_cont.clear();
	}

	for (auto &event_cont : this->event_cont_ary_) {
		event_cont.clear();
	}

	this->common_.Init();

	for (auto &res_cont : this->res_cont_ary_) {
		for (auto &res : res_cont) {
			res->Init();
		}

		res_cont.clear();
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::input::Manager::Init(void)
{
	this->Release();

	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;
	this->event_index_ = 0U;
	this->event_cnt_ary_.fill(0U);
	this->stock_event_cnt_ary_.fill(0U);

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::Manager::Create(const tml::input::ManagerDesc &desc)
{
	if ((desc.window_handle == nullptr)
	|| (desc.window_device_context_handle == nullptr)) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->wnd_handle_ = desc.window_handle;
	this->wnd_dc_handle_ = desc.window_device_context_handle;

	if (this->common_.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::input::Manager::Update(void)
{
	return;
}
