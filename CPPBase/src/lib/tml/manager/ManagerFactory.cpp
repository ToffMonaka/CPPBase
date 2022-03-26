/**
 * @file
 * @brief ManagerFactoryコードファイル
 */


#include "ManagerFactory.h"


/**
 * @brief コンストラクタ
 */
tml::ManagerFactoryDesc::ManagerFactoryDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerFactoryDesc::~ManagerFactoryDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerFactoryDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ManagerFactory::ManagerFactory()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ManagerFactory::Init(void)
{
	this->Release();

	this->res_func_cont_.clear();
	this->task_func_cont_.clear();
	this->event_func_cont_.clear();
	this->value_container.clear();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerFactory::Create(const tml::ManagerFactoryDesc &desc)
{
	this->Init();

	return (0);
}


/**
 * @brief AddResourceFunction関数
 * @param class_name (class_name)
 * @param res_func (resource_function)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerFactory::AddResourceFunction(const WCHAR *class_name, std::function<tml::shared_ptr<tml::ManagerResource>(const tml::INIFileReadDesc &, INT *)> res_func)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (-1);
	}

	this->res_func_cont_[class_name] = res_func;

	return (0);
}


/**
 * @brief RemoveResourceFunction関数
 * @param class_name (class_name)
 */
void tml::ManagerFactory::RemoveResourceFunction(const WCHAR *class_name)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return;
	}

	this->res_func_cont_.erase(class_name);

	return;
}


/**
 * @brief AddTaskFunction関数
 * @param class_name (class_name)
 * @param task_func (task_function)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerFactory::AddTaskFunction(const WCHAR *class_name, std::function<tml::shared_ptr<tml::ManagerTask>(const tml::INIFileReadDesc &, INT *)> task_func)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (-1);
	}

	this->task_func_cont_[class_name] = task_func;

	return (0);
}


/**
 * @brief RemoveTaskFunction関数
 * @param class_name (class_name)
 */
void tml::ManagerFactory::RemoveTaskFunction(const WCHAR *class_name)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return;
	}

	this->task_func_cont_.erase(class_name);

	return;
}


/**
 * @brief AddEventFunction関数
 * @param class_name (class_name)
 * @param event_func (event_function)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ManagerFactory::AddEventFunction(const WCHAR *class_name, std::function<tml::shared_ptr<tml::ManagerEvent>(const tml::INIFileReadDesc &, INT *)> event_func)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (-1);
	}

	this->event_func_cont_[class_name] = event_func;

	return (0);
}


/**
 * @brief RemoveEventFunction関数
 * @param class_name (class_name)
 */
void tml::ManagerFactory::RemoveEventFunction(const WCHAR *class_name)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return;
	}

	this->event_func_cont_.erase(class_name);

	return;
}
