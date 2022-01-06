/**
 * @file
 * @brief Atlasコードファイル
 */


#include "Atlas.h"
#include "../string/StringUtil.h"
#include "Manager.h"
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::AtlasRect::AtlasRect() :
	pos_(0U),
	size_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::AtlasRect::~AtlasRect()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::AtlasRect::Init(void)
{
	this->Release();

	this->name_.clear();
	this->pos_ = 0U;
	this->size_ = 0U;

	return;
}


/**
 * @brief Create関数
 * @param name (name)
 * @param pos (position)
 * @param size (size)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::AtlasRect::Create(const WCHAR *name, const tml::XMUINT2EX &pos, const tml::XMUINT2EX &size)
{
	if (name == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->name_ = name;
	this->pos_ = pos;
	this->size_ = size;

	return (0);
}


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

	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Atlas Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"ATLAS");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"ATLAS_FILE_PATH");

			if (val != nullptr) {
				this->atlas_file_read_desc.data.file_path = (*val);
			}

			val = conf_file.data.GetValue((*val_name_cont), L"ATLAS_DIR_PATH");

			if (val != nullptr) {
				this->atlas_directory_path = (*val);
			}
		}
	}

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

	this->rect_cont_.clear();
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

	tml::XMLFileNode *atlas_file_frames_dict_node = nullptr;
	tml::XMLFileNode *atlas_file_metadata_dict_node = nullptr;

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

	std::vector<std::wstring> rect_str_cont(4U);

	for (auto node_itr = atlas_file_frames_dict_node->GetChildNodeContainer().begin(), node_end_itr = atlas_file_frames_dict_node->GetChildNodeContainer().end(); node_itr != node_end_itr; ++node_itr) {
		if ((*node_itr)->name != L"key") {
			continue;
		}

		tml::graphic::AtlasRect rect;

		rect.name_ = (*node_itr)->string;

		++node_itr;

		if (node_itr != node_end_itr) {
			if ((*node_itr)->name == L"dict") {
				for (auto node2_itr = (*node_itr)->GetChildNodeContainer().begin(), node2_end_itr = (*node_itr)->GetChildNodeContainer().end(); node2_itr != node2_end_itr; ++node2_itr) {
					if ((*node2_itr)->name != L"key") {
						continue;
					}

					if ((*node2_itr)->string == L"textureRect") {
						++node2_itr;

						if (node2_itr != node2_end_itr) {
							if ((*node2_itr)->name == L"string") {
								tml::StringUtil::Split(rect_str_cont, (*node2_itr)->string.c_str(), L",");

								if (rect_str_cont[0].length() >= 3U) {
									rect_str_cont[0].erase(0U, 2U);

									rect.pos_.x = tml::StringUtil::GetUInt(rect_str_cont[0].c_str());
								}

								if (rect_str_cont[1].length() >= 2U) {
									rect_str_cont[1].erase(rect_str_cont[1].length() - 1U);

									rect.pos_.y = tml::StringUtil::GetUInt(rect_str_cont[1].c_str());
								}

								if (rect_str_cont[2].length() >= 2U) {
									rect_str_cont[2].erase(0U, 1U);

									rect.size_.x = tml::StringUtil::GetUInt(rect_str_cont[2].c_str());
								}

								if (rect_str_cont[3].length() >= 3U) {
									rect_str_cont[3].erase(rect_str_cont[3].length() - 2U);

									rect.size_.y = tml::StringUtil::GetUInt(rect_str_cont[3].c_str());
								}
							}
						}

						--node2_itr;
					}
				}
			}
		}

		--node_itr;

		this->rect_cont_.emplace(rect.name_, rect);
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
		tml::graphic::TextureDesc tex_desc;

		tex_desc.SetManager(this->GetManager());
		tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
		tex_desc.image_file_read_desc_container[0].data.file_path = img_file_path;

		if (this->GetManager()->GetResource<tml::graphic::Texture>(this->tex_, tex_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
