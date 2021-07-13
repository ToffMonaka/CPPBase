/**
 * @file
 * @brief Model2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief Model2DLayerクラス
 */
class Model2DLayer : public tml::graphic::ModelLayer
{
public: Model2DLayer(const tml::graphic::Model2DLayer &) = delete;
public: tml::graphic::Model2DLayer &operator =(const tml::graphic::Model2DLayer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	Model2DLayer();
	virtual ~Model2DLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model2DStageクラス
 */
class Model2DStage : public tml::graphic::ModelStage
{
public: Model2DStage(const tml::graphic::Model2DStage &) = delete;
public: tml::graphic::Model2DStage &operator =(const tml::graphic::Model2DStage &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	Model2DStage();
	virtual ~Model2DStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::Model2DLayer *GetLayer(const UINT);
	tml::graphic::Model2DLayer *GetLayerFast(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::Model2DLayer> &);
};
}
}


/**
 * @brief GetLayer関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::Model2DLayer *tml::graphic::Model2DStage::GetLayer(const UINT index)
{
	return (static_cast<tml::graphic::Model2DLayer *>(tml::graphic::ModelStage::GetLayer(index)));
}


/**
 * @brief GetLayerFast関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::Model2DLayer *tml::graphic::Model2DStage::GetLayerFast(const UINT index)
{
	return (static_cast<tml::graphic::Model2DLayer *>(tml::graphic::ModelStage::GetLayerFast(index)));
}


/**
 * @brief SetLayer関数
 * @param index (index)
 * @param layer (layer)
 */
inline void tml::graphic::Model2DStage::SetLayer(const UINT index, tml::unique_ptr<tml::graphic::Model2DLayer> &layer)
{
	tml::unique_ptr<tml::graphic::ModelLayer> tmp_layer = std::move(layer);

	tml::graphic::ModelStage::SetLayer(index, tmp_layer);

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model2DDescクラス
 */
class Model2DDesc : public tml::graphic::ModelDesc
{
public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;
	tml::XMFLOAT4EX color;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	Model2DDesc();
	virtual ~Model2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Model2DDesc::Release(void)
{
	tml::graphic::ModelDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model2Dクラス
 */
class Model2D : public tml::graphic::Model
{
public: Model2D(const tml::graphic::Model2D &) = delete;
public: tml::graphic::Model2D &operator =(const tml::graphic::Model2D &) = delete;
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

private:
	tml::shared_ptr<tml::graphic::Model2DShaderStructuredBuffer> ssb_;
	tml::shared_ptr<tml::graphic::Model2DLayerShaderStructuredBuffer> layer_ssb_;

public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;
	tml::XMFLOAT4EX color;

protected:
	void Release(void);

public:
	Model2D();
	virtual ~Model2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Model2DDesc &);

	tml::graphic::Model2DStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	tml::graphic::Model2DStage *GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::Model2DStage> &);

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
inline tml::graphic::Model2DStage *tml::graphic::Model2D::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::Model2DStage *>(tml::graphic::Model::GetStage(type)));
}


/**
 * @brief GetStageFast関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::Model2DStage *tml::graphic::Model2D::GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::Model2DStage *>(tml::graphic::Model::GetStageFast(type)));
}


/**
 * @brief SetStage関数
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::Model2D::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::Model2DStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model::SetStage(type, tmp_stage);

	return;
}
