/**
 * @file
 * @brief Map�R�[�h�t�@�C��
 */


#include "Map.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::MapDesc::MapDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::MapDesc::~MapDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::MapDesc::Init(void)
{
	this->Release();

	this->map_file_read_desc.Init();
	this->map_directory_path.clear();

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::MapDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Map Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MAP");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Map::Map()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Map::~Map()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Map::Init(void)
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
INT tml::graphic::Map::Create(const tml::graphic::MapDesc &desc)
{
	this->Init();

	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto map_file_read_desc_dat = desc.map_file_read_desc.GetDataByParent();

	tml::XMLFile map_file;

	map_file.read_desc.parent_data = map_file_read_desc_dat;

	if (map_file.Read() < 0) {
		this->Init();

		return (-1);
	}

	auto &map_file_root_node = map_file.data.GetRootNode();

	if (map_file_root_node->GetChildNodeContainer().empty()) {
		this->Init();

		return (-1);
	}

	return (0);
}
