/**
 * @file
 * @brief ManagerResource�R�[�h�t�@�C��
 */


#include "ManagerResource.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::ManagerResourceDesc::ManagerResourceDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::ManagerResourceDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"RES");

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
void tml::scene::ManagerResourceDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::scene::Manager *>(mgr);

	tml::ManagerResourceDesc::OnSetManager(this->mgr_);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::ManagerResource::ManagerResource() :
	desc_(nullptr),
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::ManagerResource::~ManagerResource()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::ManagerResource::Init(void)
{
	this->Release();

	tml::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::ManagerResource::OnCreate(void)
{
	if (tml::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::ManagerResource::OnCreateDeferred(void)
{
	if (tml::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::scene::ManagerResource::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::scene::ManagerResourceDesc *>(desc);

	tml::ManagerResource::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief OnSetManager�֐�
 * @param mgr (manager)
 */
void tml::scene::ManagerResource::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<tml::scene::Manager *>(mgr);

	tml::ManagerResource::OnSetManager(this->mgr_);

	return;
}
