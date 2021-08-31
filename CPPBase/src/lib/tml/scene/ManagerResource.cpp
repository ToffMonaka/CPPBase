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
 * @brief SetManager�֐�
 * @param mgr (manager)
 */
void tml::scene::ManagerResourceDesc::SetManager(tml::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerResourceDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::ManagerResource::ManagerResource() :
	mgr_(nullptr),
	res_type_(tml::ConstantUtil::SCENE::RESOURCE_TYPE::NONE)
	
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

	this->mgr_ = nullptr;
	this->res_type_ = tml::ConstantUtil::SCENE::RESOURCE_TYPE::NONE;

	tml::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::ManagerResource::Create(const tml::scene::ManagerResourceDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	if (tml::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->res_type_ = static_cast<tml::ConstantUtil::SCENE::RESOURCE_TYPE>(this->GetResourceMainIndex());

	return (0);
}
