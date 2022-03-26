/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::ManagerEventDesc::Init(void)
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
INT tml::scene::ManagerEventDesc::ReadValue(const tml::INIFile &conf_file)
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
 * @brief OnSetManager�֐�
 * @param mgr (manager)
 */
void tml::scene::ManagerEventDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::scene::Manager *>(mgr);

	tml::ManagerEventDesc::OnSetManager(this->mgr_);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::ManagerEvent::ManagerEvent() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::ManagerEvent::~ManagerEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::ManagerEvent::Init(void)
{
	this->Release();

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::ManagerEvent::Create(const tml::scene::ManagerEventDesc &desc)
{
	if (tml::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetManager�֐�
 * @param mgr (manager)
 */
void tml::scene::ManagerEvent::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::scene::Manager *>(mgr);

	tml::ManagerEvent::OnSetManager(this->mgr_);

	return;
}
