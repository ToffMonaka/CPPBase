/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::input::ManagerDesc::ManagerDesc()
{
	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT);
	this->event_count = tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT;

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

	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT);
	this->event_count = tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT;

	tml::ManagerDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::Manager::Manager() :
	mouse_pos_(0),
	mouse_code_stat_ary_{},
	keyboard_code_stat_ary_{}
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
	this->DeleteCommon();
	this->DeleteResourceContainer();

	tml::Manager::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::Manager::Init(void)
{
	this->Release();

	this->mouse_pos_ = 0;
	this->mouse_code_stat_ary_.fill(false);
	this->keyboard_code_stat_ary_.fill(false);

	tml::Manager::Init();

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
	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	POINT mouse_sys_pos;

	GetCursorPos(&mouse_sys_pos);
	ScreenToClient(this->GetWindowHandle(), &mouse_sys_pos);

	this->mouse_pos_ = tml::XMINT2EX(mouse_sys_pos.x, mouse_sys_pos.y);

	if (this->CreateCommon() < 0) {
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
	tml::Manager::Update();

	return;
}


/**
 * @brief CreateCommon関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::Manager::CreateCommon(void)
{
	if (this->common_.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon関数
 */
void tml::input::Manager::DeleteCommon(void)
{
	this->common_.Init();

	return;
}
