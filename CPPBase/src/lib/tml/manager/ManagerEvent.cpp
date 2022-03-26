/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerEventData::ManagerEventData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerEventData::~ManagerEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerEventData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr),
	run_flag(true)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerEventDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->event_name.clear();
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
INT tml::ManagerEventDesc::Read(const tml::INIFileReadDesc &conf_file_read_desc)
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
INT tml::ManagerEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"EVENT");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->event_name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief OnSetManager�֐�
 * @param mgr (manager)
 */
void tml::ManagerEventDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_type_(0U),
	run_flg_(false),
	run_added_flg_(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerEvent::~ManagerEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerEvent::Init(void)
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
INT tml::ManagerEvent::Create(const tml::ManagerEventDesc &desc)
{
	if (this->mgr_ == nullptr) {
		return (-1);
	}

	this->func_ = desc.function;

	return (0);
}


/**
 * @brief Run�֐�
 * @param dat (data)
 */
void tml::ManagerEvent::Run(const tml::ManagerEventData *dat)
{
	if (!this->run_flg_) {
		return;
	}

	this->OnRun(dat);

	auto func = this->func_;

	if (func != nullptr) {
		func(dat);
	}

	return;
}


/**
 * @brief OnSetManager�֐�
 * @param mgr (manager)
 */
void tml::ManagerEvent::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief SetRunFlag�֐�
 * @param run_flg (run_flag)
 */
void tml::ManagerEvent::SetRunFlag(const bool run_flg)
{
	this->mgr_->SetEventRunFlag(this, run_flg);

	return;
}
