/**
 * @file
 * @brief FigureModel2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Model2D.h"


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2DLayerクラス
 */
class FigureModel2DLayer : public tml::graphic::Model2DLayer
{
public: FigureModel2DLayer(const tml::graphic::FigureModel2DLayer &) = delete;
public: tml::graphic::FigureModel2DLayer &operator =(const tml::graphic::FigureModel2DLayer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	FigureModel2DLayer();
	virtual ~FigureModel2DLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2DStageクラス
 */
class FigureModel2DStage : public tml::graphic::Model2DStage
{
public: FigureModel2DStage(const tml::graphic::FigureModel2DStage &) = delete;
public: tml::graphic::FigureModel2DStage &operator =(const tml::graphic::FigureModel2DStage &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	FigureModel2DStage();
	virtual ~FigureModel2DStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::FigureModel2DLayer *GetLayer(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::FigureModel2DLayer> &);
};
}
}


/**
 * @brief GetLayer関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::FigureModel2DLayer *tml::graphic::FigureModel2DStage::GetLayer(const UINT index)
{
	return (reinterpret_cast<tml::graphic::FigureModel2DLayer *>(tml::graphic::Model2DStage::GetLayer(index)));
}


/**
 * @brief SetLayer関数
 * @param index (index)
 * @param layer (layer)
 */
inline void tml::graphic::FigureModel2DStage::SetLayer(const UINT index, tml::unique_ptr<tml::graphic::FigureModel2DLayer> &layer)
{
	tml::unique_ptr<tml::graphic::ModelLayer> tmp_layer = std::move(layer);

	tml::graphic::Model2DStage::SetLayer(index, tmp_layer);

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2DDescクラス
 */
class FigureModel2DDesc : public tml::graphic::Model2DDesc
{
public:
	tml::BinaryFileReadDesc image_file_read_desc;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	FigureModel2DDesc();
	virtual ~FigureModel2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::FigureModel2DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2Dクラス
 */
class FigureModel2D : public tml::graphic::Model2D
{
public: FigureModel2D(const tml::graphic::FigureModel2D &) = delete;
public: tml::graphic::FigureModel2D &operator =(const tml::graphic::FigureModel2D &) = delete;
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
	static const D3D11_INPUT_ELEMENT_DESC INPUT_ELEMENT_DESC_ARRAY[tml::graphic::FigureModel2D::INPUT_ELEMENT_DESC_COUNT];

private:
	tml::shared_ptr<tml::graphic::FigureModel2DShaderStructuredBuffer> ssb_;
	tml::shared_ptr<tml::graphic::FigureModel2DLayerShaderStructuredBuffer> layer_ssb_;

private:
	void Release(void);

public:
	FigureModel2D();
	virtual ~FigureModel2D();

	virtual void Init(void);
	INT Create(const tml::graphic::FigureModel2DDesc &);

	tml::graphic::FigureModel2DStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::FigureModel2DStage> &);
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
inline tml::graphic::FigureModel2DStage *tml::graphic::FigureModel2D::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (reinterpret_cast<tml::graphic::FigureModel2DStage *>(tml::graphic::Model2D::GetStage(type)));
}


/**
 * @brief SetStage関数
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::FigureModel2D::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::FigureModel2DStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model2D::SetStage(type, tmp_stage);

	return;
}
