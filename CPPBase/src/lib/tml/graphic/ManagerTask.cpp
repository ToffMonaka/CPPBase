/**
 * @file
 * @brief ManagerTaskコードファイル
 */


#include "ManagerTask.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerTaskDesc::ManagerTaskDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerTaskDesc::~ManagerTaskDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerTaskDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::ManagerTaskDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ManagerTaskDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::ManagerTaskDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Task Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"TASK");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::graphic::ManagerTaskDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::graphic::Manager *>(mgr);

	tml::ManagerTaskDesc::OnSetManager(this->mgr_);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerTask::ManagerTask() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerTask::~ManagerTask()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ManagerTask::Init(void)
{
	this->Release();

	tml::ManagerTask::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ManagerTask::Create(const tml::graphic::ManagerTaskDesc &desc)
{
	if (tml::ManagerTask::Create(desc) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void tml::graphic::ManagerTask::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::graphic::Manager *>(mgr);

	tml::ManagerTask::OnSetManager(this->mgr_);

	return;
}
