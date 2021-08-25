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
	tml::graphic::FigureModel2DLayer *GetLayerFast(const UINT);
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
 * @brief GetLayerFast関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::FigureModel2DLayer *tml::graphic::FigureModel2DStage::GetLayerFast(const UINT index)
{
	return (reinterpret_cast<tml::graphic::FigureModel2DLayer *>(tml::graphic::Model2DStage::GetLayerFast(index)));
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

private:

private:
	void Release(void);

public:
	FigureModel2D();
	virtual ~FigureModel2D();

	virtual void Init(void);
	INT Create(const tml::graphic::FigureModel2DDesc &);

	tml::graphic::FigureModel2DStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	tml::graphic::FigureModel2DStage *GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::FigureModel2DStage> &);

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
 * @brief GetStageFast関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::FigureModel2DStage *tml::graphic::FigureModel2D::GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (reinterpret_cast<tml::graphic::FigureModel2DStage *>(tml::graphic::Model2D::GetStageFast(type)));
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
