/**
 * @file
 * @brief GroundModel2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
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
 * @brief GroundModel2DDescクラス
 */
class GroundModel2DDesc : public tml::graphic::Model2DDesc
{
public:

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

private:

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
