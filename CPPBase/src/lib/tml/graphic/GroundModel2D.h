/**
 * @file
 * @brief GroundModel2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathUINT.h"
#include "../file/XMLFile.h"
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
	tml::graphic::GroundModel2DLayer *GetLayerFast(const UINT);
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
 * @brief GetLayerFast関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::GroundModel2DLayer *tml::graphic::GroundModel2DStage::GetLayerFast(const UINT index)
{
	return (reinterpret_cast<tml::graphic::GroundModel2DLayer *>(tml::graphic::Model2DStage::GetLayerFast(index)));
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
 * @brief GroundModel2DBlockクラス
 */
class GroundModel2DBlock
{
public:
	tml::XMUINT2EX tile_count;
	std::vector<UINT> tile_type_container;

private:
	void Release(void);

public:
	GroundModel2DBlock();
	virtual ~GroundModel2DBlock();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::GroundModel2DBlock::Release(void)
{
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
	tml::BinaryFileReadDesc image_file_read_desc;
	tml::XMLFileReadDesc map_file_read_desc;
	std::wstring map_directory_path;

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

		/**
		 * @brief コンストラクタ
		 */
		VERTEX_BUFFER_ELEMENT_() :
			layer_index(0U)
		{
			return;
		};

		/**
		 * @brief コンストラクタ
		 * @param pos (position)
		 * @param tex_pos (texture_position)
		 * @param layer_index (layer_index)
		 */
		VERTEX_BUFFER_ELEMENT_(const tml::XMFLOAT4EX &pos, const tml::XMFLOAT2EX &tex_pos, const UINT layer_index) :
			position(pos),
			texture_position(tex_pos),
			layer_index(layer_index)
		{
			return;
		};
	} VERTEX_BUFFER_ELEMENT;

public:
	static const UINT INPUT_ELEMENT_DESC_COUNT = 3U;
	static const D3D11_INPUT_ELEMENT_DESC INPUT_ELEMENT_DESC_ARRAY[tml::graphic::GroundModel2D::INPUT_ELEMENT_DESC_COUNT];

private:
	tml::XMUINT2EX tile_cnt_;
	tml::XMUINT2EX block_cnt_;
	std::vector<tml::graphic::GroundModel2DBlock> block_cont_;
	tml::XMUINT2EX tileset_tile_size_;
	tml::XMUINT2EX tileset_tile_cnt_;
	tml::shared_ptr<tml::graphic::GroundModel2DShaderStructuredBuffer> ssb_;
	tml::shared_ptr<tml::graphic::GroundModel2DLayerShaderStructuredBuffer> layer_ssb_;
	tml::shared_ptr<tml::graphic::GroundModel2DBlockShaderStructuredBuffer> block_ssb_;

private:
	void Release(void);

public:
	GroundModel2D();
	virtual ~GroundModel2D();

	virtual void Init(void);
	INT Create(const tml::graphic::GroundModel2DDesc &);

	tml::graphic::GroundModel2DStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	tml::graphic::GroundModel2DStage *GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::GroundModel2DStage> &);
	virtual DirectX::XMMATRIX &GetWorldMatrix(DirectX::XMMATRIX &);

	virtual bool IsHitByMouseDevice(const tml::XMINT2EX &);

	virtual void DrawStageInit(void);
	virtual void DrawStageForward2D(void);
};
}
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
 * @brief GetStageFast関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::GroundModel2DStage *tml::graphic::GroundModel2D::GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (reinterpret_cast<tml::graphic::GroundModel2DStage *>(tml::graphic::Model2D::GetStageFast(type)));
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
