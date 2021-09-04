/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::sound::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::ManagerEventDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::ManagerEventDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::sound::ManagerEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::ManagerEventDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Event Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"EVENT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetManager�֐�
 * @param mgr (manager)
 */
void tml::sound::ManagerEventDesc::SetManager(tml::sound::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerEventDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::sound::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_type_(tml::ConstantUtil::SOUND::EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::ManagerEvent::~ManagerEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::ManagerEvent::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::SOUND::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::sound::ManagerEvent::Create(const tml::sound::ManagerEventDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_type_ = static_cast<tml::ConstantUtil::SOUND::EVENT_TYPE>(this->GetEventMainIndex());

	return (0);
}
