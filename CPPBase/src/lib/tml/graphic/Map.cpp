/**
 * @file
 * @brief Mapコードファイル
 */


#include "Map.h"
#include "../string/StringUtil.h"
#include "Manager.h"
#include "Texture.h"
#include "Sampler.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::MapBlock::MapBlock() :
	tile_cnt_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::MapBlock::~MapBlock()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::MapBlock::Init(void)
{
	this->Release();

	this->tile_cnt_ = 0U;
	this->tile_type_cont_.clear();

	return;
}


/**
 * @brief Create関数
 * @param tile_cnt (tile_count)
 * @param tile_type_cont (tile_type_container)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::MapBlock::Create(const tml::XMUINT2EX &tile_cnt, const std::vector<UINT> &tile_type_cont)
{
	this->Init();

	this->tile_cnt_ = tile_cnt;
	this->tile_type_cont_ = tile_type_cont;

	return (0);
}


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

	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Map Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MAP");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"MAP_FILE_PATH");

			if (val != nullptr) {
				this->map_file_read_desc.data.file_path = (*val);
			}

			val = conf_file.data.GetValue((*val_name_cont), L"MAP_DIR_PATH");

			if (val != nullptr) {
				this->map_directory_path = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Map::Map() :
	desc_(nullptr),
	tile_cnt_(0U),
	block_cnt_(0U),
	tileset_tile_size_(0U),
	tileset_tile_cnt_(0U)
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
 * @brief Release関数
 */
void tml::graphic::Map::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Map::Init(void)
{
	this->Release();

	this->tile_cnt_ = 0U;
	this->block_cnt_ = 0U;
	this->block_cont_.clear();
	this->tileset_tile_size_ = 0U;
	this->tileset_tile_cnt_ = 0U;
	this->tex_.reset();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Map::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	auto map_file_read_desc_dat = this->desc_->map_file_read_desc.GetDataByParent();

	tml::XMLFile map_file;

	map_file.read_desc.parent_data = map_file_read_desc_dat;

	if (map_file.Read() < 0) {
		return (-1);
	}

	auto &map_file_root_node = map_file.data.GetRootNode();

	if (map_file_root_node->GetChildNodeContainer().empty()) {
		return (-1);
	}

	auto &map_file_map_node = map_file_root_node->GetChildNode(L"map");

	if (map_file_map_node == nullptr) {
		return (-1);
	}

	auto &map_file_tileset_node = map_file_root_node->GetChildNode(L"tileset");

	if (map_file_tileset_node == nullptr) {
		return (-1);
	}

	auto &map_file_img_node = map_file_root_node->GetChildNode(L"image");

	if (map_file_img_node == nullptr) {
		return (-1);
	}

	auto &map_file_dat_node = map_file_root_node->GetChildNode(L"data");

	if (map_file_dat_node == nullptr) {
		return (-1);
	}

	const std::wstring *val = nullptr;

	val = map_file_map_node->GetValue(L"width");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tile_cnt_.x, val->c_str());
	} else {
		return (-1);
	}

	val = map_file_map_node->GetValue(L"height");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tile_cnt_.y, val->c_str());
	} else {
		return (-1);
	}

	std::vector<UINT> tile_type_cont;
	std::vector<std::wstring> tile_type_str_cont;

	tml::StringUtil::Split(tile_type_str_cont, map_file_dat_node->string.c_str(), L",");

	tile_type_cont.resize(tile_type_str_cont.size());

	for (size_t val_i = 0U, val_end_i = tile_type_str_cont.size(); val_i < val_end_i; ++val_i) {
		tml::StringUtil::GetValue(tile_type_cont[val_i], tile_type_str_cont[val_i].c_str());
	}

	this->block_cnt_.x = static_cast<UINT>(std::ceil(static_cast<FLOAT>(this->tile_cnt_.x) / 16.0f));
	this->block_cnt_.y = static_cast<UINT>(std::ceil(static_cast<FLOAT>(this->tile_cnt_.y) / 16.0f));
	this->block_cont_.resize(this->block_cnt_.x * this->block_cnt_.y);

	for (UINT block_index_y = 0U, block_index_end_y = this->block_cnt_.y; block_index_y < block_index_end_y; ++block_index_y) {
		for (UINT block_index_x = 0U, block_index_end_x = this->block_cnt_.x; block_index_x < block_index_end_x; ++block_index_x) {
			auto &block = this->block_cont_[block_index_y * this->block_cnt_.x + block_index_x];

			block.tile_cnt_.x = (block_index_x == (this->block_cnt_.x - 1U)) ? this->tile_cnt_.x - (block_index_x * 16U) : 16U;
			block.tile_cnt_.y = (block_index_y == (this->block_cnt_.y - 1U)) ? this->tile_cnt_.y - (block_index_y * 16U) : 16U;
			block.tile_type_cont_.resize(block.tile_cnt_.x * block.tile_cnt_.y);

			for (UINT block_tile_index_y = 0U, block_tile_index_end_y = block.tile_cnt_.y; block_tile_index_y < block_tile_index_end_y; ++block_tile_index_y) {
				for (UINT block_tile_index_x = 0U, block_tile_index_end_x = block.tile_cnt_.x; block_tile_index_x < block_tile_index_end_x; ++block_tile_index_x) {
					auto &block_tile_type = block.tile_type_cont_[block_tile_index_y * block.tile_cnt_.x + block_tile_index_x];

					block_tile_type = tile_type_cont[((block_index_y * 16U + block_tile_index_y) * this->tile_cnt_.x) + (block_index_x * 16U + block_tile_index_x)];
				}
			}
		}
	}

	val = map_file_tileset_node->GetValue(L"tilewidth");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_size_.x, val->c_str());
	} else {
		return (-1);
	}

	val = map_file_tileset_node->GetValue(L"tileheight");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_size_.y, val->c_str());
	} else {
		return (-1);
	}

	val = map_file_tileset_node->GetValue(L"columns");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_cnt_.x, val->c_str());
	} else {
		return (-1);
	}

	val = map_file_tileset_node->GetValue(L"tilecount");

	if (val != nullptr) {
		tml::StringUtil::GetValue(this->tileset_tile_cnt_.y, val->c_str());

		this->tileset_tile_cnt_.y /= this->tileset_tile_cnt_.x;
	} else {
		return (-1);
	}

	std::wstring img_file_path;

	val = map_file_img_node->GetValue(L"source");

	if (val != nullptr) {
		img_file_path = this->desc_->map_directory_path;
		img_file_path += L"/";
		img_file_path += (*val);
	}

	// Texture Create
	if (this->desc_->texture_flag) {
		tml::graphic::TextureDesc tex_desc;

		tex_desc.SetManager(this->GetManager());
		tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
		tex_desc.image_file_read_desc_container[0].data.file_path = img_file_path;

		if (this->GetManager()->GetResource<tml::graphic::Texture>(this->tex_, tex_desc) == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Map::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Map::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::MapDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}
