/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_device_context_handle(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ManagerDesc::Init(void)
{
	this->Release();

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::sound::Manager::Release(void)
{
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
void tml::sound::Manager::Init(void)
{
	this->Release();

	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::Manager::Create(const tml::sound::ManagerDesc &desc)
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
void tml::sound::Manager::Update(void)
{
	return;
}
