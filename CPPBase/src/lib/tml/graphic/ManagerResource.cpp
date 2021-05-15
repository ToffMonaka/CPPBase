/**
 * @file
 * @brief ManagerResource�R�[�h�t�@�C��
 */


#include "ManagerResource.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ManagerResourceDesc::ManagerResourceDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ManagerResourceDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"RES");

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
void tml::graphic::ManagerResourceDesc::SetManager(tml::graphic::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerResourceDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ManagerResource::ManagerResource() :
	mgr_(nullptr),
	res_type_(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE)
	
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ManagerResource::~ManagerResource()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ManagerResource::Init(void)
{
	this->mgr_ = nullptr;
	this->res_type_ = tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE;

	tml::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param res_type (resource_type)
 * @param res_sub_index (resource_sub_index)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ManagerResource::Create(const tml::graphic::ManagerResourceDesc &desc, const tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type, const UINT res_sub_index)
{
	if ((desc.GetManager() == nullptr)
	|| (res_type == tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE)) {
		return (-1);
	}

	if (tml::ManagerResource::Create(desc, static_cast<UINT>(res_type), res_sub_index) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->res_type_ = res_type;

	return (0);
}
