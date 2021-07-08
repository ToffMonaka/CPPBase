/**
 * @file
 * @brief Canvas2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Canvas.h"


namespace tml {
namespace graphic {
/**
 * @brief Canvas2DDescクラス
 */
class Canvas2DDesc : public tml::graphic::CanvasDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	Canvas2DDesc();
	virtual ~Canvas2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Canvas2DDesc::Release(void)
{
	tml::graphic::CanvasDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Canvas2Dクラス
 */
class Canvas2D : public tml::graphic::Canvas
{
public: Canvas2D(const tml::graphic::Canvas2D &) = delete;
public: tml::graphic::Canvas2D &operator =(const tml::graphic::Canvas2D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::graphic::Camera *draw_camera_;
	UINT draw_light_cnt_;
	std::array<tml::graphic::Light *, tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT> draw_light_ary_;
	UINT draw_fog_cnt_;
	std::array<tml::graphic::Fog *, tml::ConstantUtil::GRAPHIC::FOG_LIMIT> draw_fog_ary_;
	UINT draw_model_cnt_;
	std::array<tml::graphic::Model *, tml::ConstantUtil::GRAPHIC::MODEL_LIMIT> draw_model_ary_;

protected:
	void Release(void);

public:
	Canvas2D();
	virtual ~Canvas2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Canvas2DDesc &);

	void SetDrawCamera(tml::graphic::Camera2D *);
	void ClearDrawCamera(void);
	void SetDrawLight(tml::graphic::Light *);
	void ClearDrawLight(void);
	void SetDrawFog(tml::graphic::Fog *);
	void ClearDrawFog(void);
	void SetDrawModel(tml::graphic::Model2D *);
	void ClearDrawModel(void);

	virtual void Draw(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Canvas2D::Release(void)
{
	tml::graphic::Canvas::Release();

	return;
}


/**
 * @brief ClearDrawCamera関数
 */
inline void tml::graphic::Canvas2D::ClearDrawCamera(void)
{
	this->draw_camera_ = nullptr;

	return;
}


/**
 * @brief ClearDrawLight関数
 */
inline void tml::graphic::Canvas2D::ClearDrawLight(void)
{
	this->draw_light_cnt_ = 0U;

	return;
}


/**
 * @brief ClearDrawFog関数
 */
inline void tml::graphic::Canvas2D::ClearDrawFog(void)
{
	this->draw_fog_cnt_ = 0U;

	return;
}


/**
 * @brief ClearDrawModel関数
 */
inline void tml::graphic::Canvas2D::ClearDrawModel(void)
{
	this->draw_model_cnt_ = 0U;

	return;
}
