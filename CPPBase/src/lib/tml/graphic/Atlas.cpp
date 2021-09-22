/**
 * @file
 * @brief Atlas�R�[�h�t�@�C��
 */


#include "Atlas.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::AtlasDesc::AtlasDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::AtlasDesc::~AtlasDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::AtlasDesc::Init(void)
{
	this->Release();

	this->atlas_file_read_desc.Init();
	this->atlas_directory_path.clear();

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::AtlasDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Atlas Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"ATLAS");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Atlas::Atlas()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Atlas::~Atlas()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Atlas::Init(void)
{
	this->Release();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Atlas::Create(const tml::graphic::AtlasDesc &desc)
{
	this->Init();

	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto atlas_file_read_desc_dat = desc.atlas_file_read_desc.GetDataByParent();

	tml::XMLFile atlas_file;

	atlas_file.read_desc.parent_data = atlas_file_read_desc_dat;

	if (atlas_file.Read() < 0) {
		this->Init();

		return (-1);
	}

	auto &atlas_file_root_node = atlas_file.data.GetRootNode();

	if (atlas_file_root_node->GetChildNodeContainer().empty()) {
		this->Init();

		return (-1);
	}

	return (0);
}
