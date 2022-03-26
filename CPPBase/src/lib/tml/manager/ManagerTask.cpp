/**
 * @file
 * @brief ManagerTask�R�[�h�t�@�C��
 */


#include "ManagerTask.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerTaskDesc::ManagerTaskDesc() :
	mgr_(nullptr),
	run_flag(true)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerTaskDesc::~ManagerTaskDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerTaskDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->task_name.clear();
	this->run_flag = true;
	this->function = nullptr;

	return;
}


/**
 * @brief Read�֐�
 * @param conf_file_read_desc (config_file_read_desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::ManagerTaskDesc::Read(const tml::INIFileReadDesc &conf_file_read_desc)
{
	auto conf_file_read_desc_dat = conf_file_read_desc.GetDataByParent();

	if (conf_file_read_desc_dat->IsEmpty()) {
		return (0);
	}

	tml::INIFile conf_file;

	conf_file.read_desc.parent_data = conf_file_read_desc_dat;

	if (conf_file.Read() < 0) {
		return (-1);
	}

	if (conf_file.data.value_container.empty()) {
		return (0);
	}

	return (this->ReadValue(conf_file));
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::ManagerTaskDesc::ReadValue(const tml::INIFile &conf_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"TASK");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->task_name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief OnSetManager�֐�
 * @param mgr (manager)
 */
void tml::ManagerTaskDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerTask::ManagerTask() :
	mgr_(nullptr),
	task_type_(0U),
	run_flg_(false),
	run_added_flg_(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerTask::~ManagerTask()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerTask::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::ManagerTask::Create(const tml::ManagerTaskDesc &desc)
{
	if (this->mgr_ == nullptr) {
		return (-1);
	}

	this->func_ = desc.function;

	return (0);
}


/**
 * @brief Run�֐�
 */
void tml::ManagerTask::Run(void)
{
	if (!this->run_flg_) {
		return;
	}

	this->OnRun();

	auto func = this->func_;

	if (func != nullptr) {
		func();
	}

	return;
}


/**
 * @brief OnSetManager�֐�
 * @param mgr (manager)
 */
void tml::ManagerTask::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief SetRunFlag�֐�
 * @param run_flg (run_flag)
 */
void tml::ManagerTask::SetRunFlag(const bool run_flg)
{
	this->mgr_->SetTaskRunFlag(this, run_flg);

	return;
}
