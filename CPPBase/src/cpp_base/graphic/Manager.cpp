/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::graphic::ManagerDesc::ManagerDesc()
{
	this->resource_count = cpp_base::ConstantUtil::GRAPHIC::RESOURCE_TYPE_COUNT;
	this->task_count = cpp_base::ConstantUtil::GRAPHIC::TASK_TYPE_COUNT;
	this->event_count = cpp_base::ConstantUtil::GRAPHIC::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::graphic::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::graphic::ManagerDesc::Init(void)
{
	this->Release();

	tml::graphic::ManagerDesc::Init();

	this->resource_count = cpp_base::ConstantUtil::GRAPHIC::RESOURCE_TYPE_COUNT;
	this->task_count = cpp_base::ConstantUtil::GRAPHIC::TASK_TYPE_COUNT;
	this->event_count = cpp_base::ConstantUtil::GRAPHIC::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::graphic::Manager::Manager()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::graphic::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::graphic::Manager::Release(void)
{
	this->common2.Init();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::graphic::Manager::Init(void)
{
	this->Release();

	tml::graphic::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::graphic::Manager::Create(const cpp_base::graphic::ManagerDesc &desc)
{
	this->Init();

	if (tml::graphic::Manager::Create(desc) < 0) {
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
