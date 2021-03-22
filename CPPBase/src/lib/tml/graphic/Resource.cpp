/**
 * @file
 * @brief Resource�R�[�h�t�@�C��
 */


#include "Resource.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ResourceDesc::ResourceDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ResourceDesc::~ResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ResourceDesc::Init(void)
{
	this->Release();

	this->manager = nullptr;
	this->name.clear();

	return;
}


/**
 * @brief Read�֐�
 * @param read_desc (read_desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ResourceDesc::Read(const tml::INIFileReadDesc &read_desc)
{
	auto read_desc_dat = read_desc.GetDataByParent();

	tml::INIFile ini_file;

	ini_file.read_desc.parent_data = read_desc_dat;

	if (ini_file.Read()) {
		return (-1);
	}

	if (ini_file.data.value_container.empty()) {
		return (0);
	}

	return (this->ReadValue(ini_file));
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ResourceDesc::ReadValue(const tml::INIFile &ini_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"RES");

		if (val_name_cont != nullptr) {
			val = ini_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Resource::Resource() :
	res_type_(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE),
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Resource::~Resource()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Resource::Init(void)
{
	this->res_type_ = tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE;
	this->mgr_ = nullptr;
	this->name_.clear();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param res_type (resource_type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Resource::Create(const tml::graphic::ResourceDesc &desc, const tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type)
{
	if ((res_type == tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::NONE)
	|| (desc.manager == nullptr)) {
		return (-1);
	}

	this->res_type_ = res_type;
	this->mgr_ = desc.manager;
	this->name_ = desc.name;

	return (0);
}
