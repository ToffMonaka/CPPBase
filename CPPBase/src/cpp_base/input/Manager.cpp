/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::input::ManagerDesc::ManagerDesc()
{
	this->resource_count = cpp_base::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT;
	this->task_count = cpp_base::ConstantUtil::INPUT::TASK_TYPE_COUNT;
	this->event_count = cpp_base::ConstantUtil::INPUT::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::input::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::input::ManagerDesc::Init(void)
{
	this->Release();

	tml::input::ManagerDesc::Init();

	this->resource_count = cpp_base::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT;
	this->task_count = cpp_base::ConstantUtil::INPUT::TASK_TYPE_COUNT;
	this->event_count = cpp_base::ConstantUtil::INPUT::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::input::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::input::Manager::Release(void)
{
	this->common2.Init();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::input::Manager::Init(void)
{
	this->Release();

	tml::input::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::input::Manager::Create(const cpp_base::input::ManagerDesc &desc)
{
	this->Init();

	if (tml::input::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// ResourceFactory Set
	}

	{// EventFactory Set
	}

	if (this->common2.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
