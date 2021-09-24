/**
 * @file
 * @brief Mapコードファイル
 */


#include "Map.h"
#include "Manager.h"
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::MapDesc::MapDesc() :
	texture_flag(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::MapDesc::~MapDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::MapDesc::Init(void)
{
	this->Release();

	this->map_file_read_desc.Init();
	this->map_directory_path.clear();
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
 * @brief コンストラクタ
 */
tml::graphic::Map::Map()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Map::~Map()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Map::Init(void)
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

	auto &map_file_img_node = map_file_root_node->GetChildNode(L"image");

	if (map_file_img_node == nullptr) {
		this->Init();

		return (-1);
	}

	const std::wstring *val = nullptr;

	std::wstring img_file_path;

	val = map_file_img_node->GetValue(L"source");

	if (val != nullptr) {
		img_file_path = desc.map_directory_path;
		img_file_path += L"/";
		img_file_path += (*val);
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
