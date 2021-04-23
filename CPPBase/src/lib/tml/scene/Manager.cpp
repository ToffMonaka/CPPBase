/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerDesc::ManagerDesc()
{
	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);
	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::ManagerDesc::Init(void)
{
	this->Release();

	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);
	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

	tml::ManagerDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::scene::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::scene::Manager::Release(void)
{
	this->common_.Init();
	this->DeleteResourceContainer();

	tml::Manager::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Manager::Init(void)
{
	this->Release();

	tml::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Manager::Create(const tml::scene::ManagerDesc &desc)
{
	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (this->common_.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::scene::Manager::Update(void)
{
	tml::Manager::Update();

	return;
}
