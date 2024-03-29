/**
 * @file
 * @brief Mapヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathVector.h"
#include "../file/XMLFile.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
class Map;
}
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
	std::vector<UINT> tile_type_cont_;

private:
	void Release(void);

public:
	MapBlock();
	virtual ~MapBlock();

	virtual void Init(void);
	INT Create(const tml::XMUINT2EX &, const std::vector<UINT> &);

	const tml::XMUINT2EX &GetTileCount(void) const;
	const UINT *GetTileTypeArray(void) const;
	const UINT *GetTileType(const UINT, const UINT) const;
	const UINT *GetTileTypeFast(const UINT, const UINT) const;
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
 * @brief GetTileTypeArray関数
 * @return tile_type_ary (tile_type_array)
 */
inline const UINT *tml::graphic::MapBlock::GetTileTypeArray(void) const
{
	return (this->tile_type_cont_.data());
}


/**
 * @brief GetTileType関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @return tile_type (tile_type)<br>
 * nullptr=失敗
 */
inline const UINT *tml::graphic::MapBlock::GetTileType(const UINT tile_index_x, const UINT tile_index_y) const
{
	if ((tile_index_x >= this->tile_cnt_.x)
	|| (tile_index_y >= this->tile_cnt_.y)) {
		return (nullptr);
	}

	return (&this->tile_type_cont_[tile_index_y * this->tile_cnt_.x + tile_index_x]);
}


/**
 * @brief GetTileTypeFast関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @return tile_type (tile_type)<br>
 * nullptr=失敗
 */
inline const UINT *tml::graphic::MapBlock::GetTileTypeFast(const UINT tile_index_x, const UINT tile_index_y) const
{
	return (&this->tile_type_cont_[tile_index_y * this->tile_cnt_.x + tile_index_x]);
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
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MAP);

private:
	const tml::graphic::MapDesc *desc_;
	tml::XMUINT2EX tile_cnt_;
	tml::XMUINT2EX block_cnt_;
	std::vector<tml::graphic::MapBlock> block_cont_;
	tml::XMUINT2EX tileset_tile_size_;
	tml::XMUINT2EX tileset_tile_cnt_;
	tml::shared_ptr<tml::graphic::Texture> tex_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Map();
	virtual ~Map();

	virtual void Init(void);

	const tml::graphic::MapDesc *GetDesc(void) const;
	const tml::XMUINT2EX &GetTileCount(void) const;
	const UINT *GetTileType(const UINT, const UINT) const;
	const UINT *GetTileTypeFast(const UINT, const UINT) const;
	void SetTileType(const UINT, const UINT, const UINT);
	void SetTileTypeFast(const UINT, const UINT, const UINT);
	const tml::XMUINT2EX &GetBlockCount(void) const;
	const tml::graphic::MapBlock *GetBlockArray(void) const;
	const tml::graphic::MapBlock *GetBlock(const UINT, const UINT) const;
	const tml::graphic::MapBlock *GetBlockFast(const UINT, const UINT) const;
	const tml::XMUINT2EX &GetTilesetTileSize(void) const;
	const tml::XMUINT2EX &GetTilesetTileCount(void) const;
	const tml::shared_ptr<tml::graphic::Texture> &GetTexture(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::MapDesc *tml::graphic::Map::GetDesc(void) const
{
	return (this->desc_);
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
 * @brief GetTileType関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @return tile_type (tile_type)<br>
 * nullptr=失敗
 */
inline const UINT *tml::graphic::Map::GetTileType(const UINT tile_index_x, const UINT tile_index_y) const
{
	if ((tile_index_x >= this->tile_cnt_.x)
	|| (tile_index_y >= this->tile_cnt_.y)) {
		return (nullptr);
	}

	UINT block_index = (tile_index_y / 16U * this->block_cnt_.x) + (tile_index_x / 16U);
	UINT block_tile_index = ((tile_index_y % 16U) * this->block_cont_[block_index].tile_cnt_.x) + (tile_index_x % 16U);

	return (&this->block_cont_[block_index].tile_type_cont_[block_tile_index]);
}


/**
 * @brief GetTileTypeFast関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @return tile_type (tile_type)<br>
 * nullptr=失敗
 */
inline const UINT *tml::graphic::Map::GetTileTypeFast(const UINT tile_index_x, const UINT tile_index_y) const
{
	UINT block_index = (tile_index_y / 16U * this->block_cnt_.x) + (tile_index_x / 16U);
	UINT block_tile_index = ((tile_index_y % 16U) * this->block_cont_[block_index].tile_cnt_.x) + (tile_index_x % 16U);

	return (&this->block_cont_[block_index].tile_type_cont_[block_tile_index]);
}


/**
 * @brief SetTileType関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @param tile_type (tile_type)
 */
inline void tml::graphic::Map::SetTileType(const UINT tile_index_x, const UINT tile_index_y, const UINT tile_type)
{
	if ((tile_index_x >= this->tile_cnt_.x)
	|| (tile_index_y >= this->tile_cnt_.y)) {
		return;
	}

	UINT block_index = (tile_index_y / 16U * this->block_cnt_.x) + (tile_index_x / 16U);
	UINT block_tile_index = ((tile_index_y % 16U) * this->block_cont_[block_index].tile_cnt_.x) + (tile_index_x % 16U);

	this->block_cont_[block_index].tile_type_cont_[block_tile_index] = tile_type;

	return;
}


/**
 * @brief SetTileTypeFast関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @param tile_type (tile_type)
 */
inline void tml::graphic::Map::SetTileTypeFast(const UINT tile_index_x, const UINT tile_index_y, const UINT tile_type)
{
	UINT block_index = (tile_index_y / 16U * this->block_cnt_.x) + (tile_index_x / 16U);
	UINT block_tile_index = ((tile_index_y % 16U) * this->block_cont_[block_index].tile_cnt_.x) + (tile_index_x % 16U);

	this->block_cont_[block_index].tile_type_cont_[block_tile_index] = tile_type;

	return;
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
 * @brief GetBlockArray関数
 * @return block_ary (block_array)
 */
inline const tml::graphic::MapBlock *tml::graphic::Map::GetBlockArray(void) const
{
	return (this->block_cont_.data());
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
 * @brief GetBlockFast関数
 * @param block_index_x (block_index_x)
 * @param block_index_y (block_index_y)
 * @return block (block)<br>
 * nullptr=失敗
 */
inline const tml::graphic::MapBlock *tml::graphic::Map::GetBlockFast(const UINT block_index_x, const UINT block_index_y) const
{
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
