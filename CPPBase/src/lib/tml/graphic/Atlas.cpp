/**
 * @file
 * @brief Atlasコードファイル
 */


#include "Atlas.h"
#include "Manager.h"
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::AtlasDesc::AtlasDesc() :
	texture_flag(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::AtlasDesc::~AtlasDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::AtlasDesc::Init(void)
{
	this->Release();

	this->atlas_file_read_desc.Init();
	this->atlas_directory_path.clear();
	this->texture_flag = true;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
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
 * @brief コンストラクタ
 */
tml::graphic::Atlas::Atlas()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Atlas::~Atlas()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Atlas::Init(void)
{
	this->Release();

	this->tex_.reset();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
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

	auto &atlas_file_root_dict_node = atlas_file_root_node->GetChildNode(L"dict");

	if (atlas_file_root_dict_node == nullptr) {
		this->Init();

		return (-1);
	}

	tml::XMLFileDataNode *atlas_file_frames_dict_node = nullptr;
	tml::XMLFileDataNode *atlas_file_metadata_dict_node = nullptr;

	for (auto node_itr = atlas_file_root_dict_node->GetChildNodeContainer().begin(), node_end_itr = atlas_file_root_dict_node->GetChildNodeContainer().end(); node_itr != node_end_itr; ++node_itr) {
		if ((*node_itr)->name != L"key") {
			continue;
		}

		if ((*node_itr)->string == L"frames") {
			++node_itr;

			if (node_itr != node_end_itr) {
				if ((*node_itr)->name == L"dict") {
					atlas_file_frames_dict_node = (*node_itr).get();
				}
			}

			--node_itr;
		} else if ((*node_itr)->string == L"metadata") {
			++node_itr;

			if (node_itr != node_end_itr) {
				if ((*node_itr)->name == L"dict") {
					atlas_file_metadata_dict_node = (*node_itr).get();
				}
			}

			--node_itr;
		}
	}

	if (atlas_file_frames_dict_node == nullptr) {
		this->Init();

		return (-1);
	}

	if (atlas_file_metadata_dict_node == nullptr) {
		this->Init();

		return (-1);
	}

	std::wstring img_file_path;

	for (auto node_itr = atlas_file_metadata_dict_node->GetChildNodeContainer().begin(), node_end_itr = atlas_file_metadata_dict_node->GetChildNodeContainer().end(); node_itr != node_end_itr; ++node_itr) {
		if ((*node_itr)->name != L"key") {
			continue;
		}

		if ((*node_itr)->string == L"textureFileName") {
			++node_itr;

			if (node_itr != node_end_itr) {
				if ((*node_itr)->name == L"string") {
					img_file_path = desc.atlas_directory_path;
					img_file_path += L"/";
					img_file_path += (*node_itr)->string;
				}
			}

			--node_itr;
		}
	}

	// Texture Create
	if (desc.texture_flag) {
		tml::graphic::TextureDesc desc;

		desc.SetManager(this->GetManager());
		desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
		desc.image_file_read_desc_container[0].data.file_path = img_file_path;

		if (this->GetManager()->GetResource<tml::graphic::Texture>(this->tex_, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
