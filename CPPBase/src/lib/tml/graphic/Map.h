/**
 * @file
 * @brief Mapヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathUINT.h"
#include "../file/XMLFile.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief MapTileクラス
 */
class MapTile
{
friend class tml::graphic::Map;

private:
	UINT type_;

private:
	void Release(void);

public:
	MapTile();
	virtual ~MapTile();

	virtual void Init(void);

	UINT GetType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::MapTile::Release(void)
{
	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline UINT tml::graphic::MapTile::GetType(void) const
{
	return (this->type_);
}


namespace tml {
namespace graphic {
/**
 * @brief MapBlockクラス
 */
class MapBlock
{
friend class tml::graphic::Map;

private:
	tml::XMUINT2EX tile_cnt_;
	std::vector<tml::graphic::MapTile> tile_cont_;

private:
	void Release(void);

public:
	MapBlock();
	virtual ~MapBlock();

	virtual void Init(void);

	const tml::XMUINT2EX &GetTileCount(void) const;
	const std::vector<tml::graphic::MapTile> &GetTileContainer(void) const;
	const tml::graphic::MapTile *GetTile(const UINT, const UINT) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::MapBlock::Release(void)
{
	return;
}


/**
 * @brief GetTileCount関数
 * @return tile_cnt (tile_count)
 */
inline const tml::XMUINT2EX &tml::graphic::MapBlock::GetTileCount(void) const
{
	return (this->tile_cnt_);
}


/**
 * @brief GetTileContainer関数
 * @return tile_cont (tile_container)
 */
inline const std::vector<tml::graphic::MapTile> &tml::graphic::MapBlock::GetTileContainer(void) const
{
	return (this->tile_cont_);
}


/**
 * @brief GetTile関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @return tile (tile)<br>
 * nullptr=失敗
 */
inline const tml::graphic::MapTile *tml::graphic::MapBlock::GetTile(const UINT tile_index_x, const UINT tile_index_y) const
{
	if ((tile_index_x >= this->tile_cnt_.x)
	|| (tile_index_y >= this->tile_cnt_.y)) {
		return (nullptr);
	}

	return (&this->tile_cont_[tile_index_y * this->tile_cnt_.x + tile_index_x]);
}


namespace tml {
namespace graphic {
/**
 * @brief MapDescクラス
 */
class MapDesc : public tml::graphic::ManagerResourceDesc
{
public:
	tml::XMLFileReadDesc map_file_read_desc;
	std::wstring map_directory_path;
	bool texture_flag;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	MapDesc();
	virtual ~MapDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::MapDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Mapクラス
 */
class Map : public tml::graphic::ManagerResource
{
public: Map(const tml::graphic::Map &) = delete;
public: tml::graphic::Map &operator =(const tml::graphic::Map &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MAP);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MAP_TYPE::BASE);

private:
	tml::XMUINT2EX tile_cnt_;
	tml::XMUINT2EX block_cnt_;
	std::vector<tml::graphic::MapBlock> block_cont_;
	tml::XMUINT2EX tileset_tile_size_;
	tml::XMUINT2EX tileset_tile_cnt_;
	tml::shared_ptr<tml::graphic::Texture> tex_;

private:
	void Release(void);

public:
	Map();
	virtual ~Map();

	virtual void Init(void);
	INT Create(const tml::graphic::MapDesc &);

	const tml::XMUINT2EX &GetTileCount(void) const;
	const tml::XMUINT2EX &GetBlockCount(void) const;
	const std::vector<tml::graphic::MapBlock> &GetBlockContainer(void) const;
	const tml::graphic::MapBlock *GetBlock(const UINT, const UINT) const;
	const tml::XMUINT2EX &GetTilesetTileSize(void) const;
	const tml::XMUINT2EX &GetTilesetTileCount(void) const;
	const tml::shared_ptr<tml::graphic::Texture> &GetTexture(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Map::Release(void)
{
	return;
}


/**
 * @brief GetTileCount関数
 * @return tile_cnt (tile_count)
 */
inline const tml::XMUINT2EX &tml::graphic::Map::GetTileCount(void) const
{
	return (this->tile_cnt_);
}


/**
 * @brief GetBlockCount関数
 * @return block_cnt (block_count)
 */
inline const tml::XMUINT2EX &tml::graphic::Map::GetBlockCount(void) const
{
	return (this->block_cnt_);
}


/**
 * @brief GetBlockContainer関数
 * @return block_cont (block_container)
 */
inline const std::vector<tml::graphic::MapBlock> &tml::graphic::Map::GetBlockContainer(void) const
{
	return (this->block_cont_);
}


/**
 * @brief GetBlock関数
 * @param block_index_x (block_index_x)
 * @param block_index_y (block_index_y)
 * @return block (block)<br>
 * nullptr=失敗
 */
inline const tml::graphic::MapBlock *tml::graphic::Map::GetBlock(const UINT block_index_x, const UINT block_index_y) const
{
	if ((block_index_x >= this->block_cnt_.x)
	|| (block_index_y >= this->block_cnt_.y)) {
		return (nullptr);
	}

	return (&this->block_cont_[block_index_y * this->block_cnt_.x + block_index_x]);
}


/**
 * @brief GetTilesetTileSize関数
 * @return tileset_tile_size (tileset_tile_size)
 */
inline const tml::XMUINT2EX &tml::graphic::Map::GetTilesetTileSize(void) const
{
	return (this->tileset_tile_size_);
}


/**
 * @brief GetTilesetTileCount関数
 * @return tileset_tile_cnt (tileset_tile_count)
 */
inline const tml::XMUINT2EX &tml::graphic::Map::GetTilesetTileCount(void) const
{
	return (this->tileset_tile_cnt_);
}


/**
 * @brief GetTexture関数
 * @return tex (texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Map::GetTexture(void)
{
	return (this->tex_);
}
