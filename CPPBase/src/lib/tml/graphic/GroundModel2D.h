/**
 * @file
 * @brief GroundModel2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Map.h"
#include "Model2D.h"


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DLayerクラス
 */
class GroundModel2DLayer : public tml::graphic::Model2DLayer
{
public: GroundModel2DLayer(const tml::graphic::GroundModel2DLayer &) = delete;
public: tml::graphic::GroundModel2DLayer &operator =(const tml::graphic::GroundModel2DLayer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	GroundModel2DLayer();
	virtual ~GroundModel2DLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DStageクラス
 */
class GroundModel2DStage : public tml::graphic::Model2DStage
{
public: GroundModel2DStage(const tml::graphic::GroundModel2DStage &) = delete;
public: tml::graphic::GroundModel2DStage &operator =(const tml::graphic::GroundModel2DStage &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	GroundModel2DStage();
	virtual ~GroundModel2DStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::GroundModel2DLayer *GetLayer(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::GroundModel2DLayer> &);
};
}
}


/**
 * @brief GetLayer関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::GroundModel2DLayer *tml::graphic::GroundModel2DStage::GetLayer(const UINT index)
{
	return (reinterpret_cast<tml::graphic::GroundModel2DLayer *>(tml::graphic::Model2DStage::GetLayer(index)));
}


/**
 * @brief SetLayer関数
 * @param index (index)
 * @param layer (layer)
 */
inline void tml::graphic::GroundModel2DStage::SetLayer(const UINT index, tml::unique_ptr<tml::graphic::GroundModel2DLayer> &layer)
{
	tml::unique_ptr<tml::graphic::ModelLayer> tmp_layer = std::move(layer);

	tml::graphic::Model2DStage::SetLayer(index, tmp_layer);

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DDescクラス
 */
class GroundModel2DDesc : public tml::graphic::Model2DDesc
{
public:
	tml::shared_ptr<tml::graphic::Texture> diffuse_texture;
	tml::shared_ptr<tml::graphic::TextureDesc> diffuse_texture_desc;
	tml::shared_ptr<tml::graphic::Map> map;
	tml::shared_ptr<tml::graphic::MapDesc> map_desc;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	GroundModel2DDesc();
	virtual ~GroundModel2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::GroundModel2DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2Dクラス
 */
class GroundModel2D : public tml::graphic::Model2D
{
public: GroundModel2D(const tml::graphic::GroundModel2D &) = delete;
public: tml::graphic::GroundModel2D &operator =(const tml::graphic::GroundModel2D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief VERTEX_BUFFER_ELEMENT構造体
	 */
	typedef struct VERTEX_BUFFER_ELEMENT_
	{
		tml::XMFLOAT4EX position;
		tml::XMFLOAT2EX texture_position;
		UINT layer_index;
		UINT block_index;
		UINT block_tile_index;

		/**
		 * @brief コンストラクタ
		 */
		VERTEX_BUFFER_ELEMENT_() :
			layer_index(0U),
			block_index(0U),
			block_tile_index(0U)
		{
			return;
		};

		/**
		 * @brief コンストラクタ
		 * @param pos (position)
		 * @param tex_pos (texture_position)
		 * @param layer_index (layer_index)
		 * @param block_index (block_index)
		 * @param block_tile_index (block_tile_index)
		 */
		VERTEX_BUFFER_ELEMENT_(const tml::XMFLOAT4EX &pos, const tml::XMFLOAT2EX &tex_pos, const UINT layer_index, const UINT block_index, const UINT block_tile_index) :
			position(pos),
			texture_position(tex_pos),
			layer_index(layer_index),
			block_index(block_index),
			block_tile_index(block_tile_index)
		{
			return;
		};
	} VERTEX_BUFFER_ELEMENT;

public:
	static const UINT INPUT_ELEMENT_DESC_COUNT = 5U;
	static const D3D11_INPUT_ELEMENT_DESC INPUT_ELEMENT_DESC_ARRAY[tml::graphic::GroundModel2D::INPUT_ELEMENT_DESC_COUNT];

private:
	const tml::graphic::GroundModel2DDesc *desc_;
	tml::shared_ptr<tml::graphic::Map> map_;
	tml::shared_ptr<tml::graphic::GroundModel2DShaderStructuredBuffer> ssb_;
	tml::shared_ptr<tml::graphic::GroundModel2DLayerShaderStructuredBuffer> layer_ssb_;
	tml::shared_ptr<tml::graphic::GroundModel2DBlockShaderStructuredBuffer> block_ssb_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	GroundModel2D();
	virtual ~GroundModel2D();

	virtual void Init(void);

	const tml::graphic::GroundModel2DDesc *GetDesc(void) const;
	tml::graphic::GroundModel2DStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::GroundModel2DStage> &);
	const tml::XMUINT2EX &GetTileCount(void) const;
	const UINT *GetTileType(const UINT, const UINT) const;
	const UINT *GetTileTypeFast(const UINT, const UINT) const;
	void SetTileType(const UINT, const UINT, const UINT);
	void SetTileTypeFast(const UINT, const UINT, const UINT);

	virtual bool IsHitByMouseDevice(const tml::XMINT2EX &);

	virtual void DrawStageInit(void);
	virtual void DrawStageForward2D(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::GroundModel2DDesc *tml::graphic::GroundModel2D::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetStage関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::GroundModel2DStage *tml::graphic::GroundModel2D::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (reinterpret_cast<tml::graphic::GroundModel2DStage *>(tml::graphic::Model2D::GetStage(type)));
}


/**
 * @brief SetStage関数
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::GroundModel2D::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::GroundModel2DStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model2D::SetStage(type, tmp_stage);

	return;
}


/**
 * @brief GetTileCount関数
 * @return tile_cnt (tile_count)
 */
inline const tml::XMUINT2EX &tml::graphic::GroundModel2D::GetTileCount(void) const
{
	return (this->map_->GetTileCount());
}


/**
 * @brief GetTileType関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @return tile_type (tile_type)<br>
 * nullptr=失敗
 */
inline const UINT *tml::graphic::GroundModel2D::GetTileType(const UINT tile_index_x, const UINT tile_index_y) const
{
	return (this->map_->GetTileType(tile_index_x, tile_index_y));
}


/**
 * @brief GetTileTypeFast関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @return tile_type (tile_type)<br>
 * nullptr=失敗
 */
inline const UINT *tml::graphic::GroundModel2D::GetTileTypeFast(const UINT tile_index_x, const UINT tile_index_y) const
{
	return (this->map_->GetTileTypeFast(tile_index_x, tile_index_y));
}


/**
 * @brief SetTileType関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @param tile_type (tile_type)
 */
inline void tml::graphic::GroundModel2D::SetTileType(const UINT tile_index_x, const UINT tile_index_y, const UINT tile_type)
{
	this->map_->SetTileType(tile_index_x, tile_index_y, tile_type);

	return;
}


/**
 * @brief SetTileTypeFast関数
 * @param tile_index_x (tile_index_x)
 * @param tile_index_y (tile_index_y)
 * @param tile_type (tile_type)
 */
inline void tml::graphic::GroundModel2D::SetTileTypeFast(const UINT tile_index_x, const UINT tile_index_y, const UINT tile_type)
{
	this->map_->SetTileTypeFast(tile_index_x, tile_index_y, tile_type);

	return;
}
