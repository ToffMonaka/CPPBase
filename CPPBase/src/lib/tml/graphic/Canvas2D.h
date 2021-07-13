/**
 * @file
 * @brief Canvas2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Canvas.h"
#include "Viewport.h"


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
	tml::shared_ptr<tml::graphic::Texture> rt_tex_;
	bool rt_tex_clear_flg_;
	FLOAT vp_x_;
	FLOAT vp_y_;
	FLOAT vp_w_;
	FLOAT vp_h_;

	tml::graphic::Camera2D *draw_camera_;
	UINT draw_light_cnt_;
	std::array<tml::graphic::Light *, tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT> draw_light_ary_;
	UINT draw_fog_cnt_;
	std::array<tml::graphic::Fog *, tml::ConstantUtil::GRAPHIC::FOG_LIMIT> draw_fog_ary_;
	UINT draw_model_cnt_;
	std::array<tml::graphic::Model2D *, tml::ConstantUtil::GRAPHIC::MODEL_LIMIT> draw_model_ary_;

protected:
	tml::graphic::Viewport vp_;

protected:
	void Release(void);

public:
	Canvas2D();
	virtual ~Canvas2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Canvas2DDesc &);

	const tml::shared_ptr<tml::graphic::Texture> &GetRenderTargetTexture(void);
	void SetRenderTargetTexture(const tml::shared_ptr<tml::graphic::Texture> &);
	bool GetRenderTargetTextureClearFlag(void) const;
	void SetRenderTargetTextureClearFlag(const bool);
	FLOAT GetViewportX(void) const;
	void SetViewportX(const FLOAT);
	FLOAT GetViewportY(void) const;
	void SetViewportY(const FLOAT);
	FLOAT GetViewportWidth(void) const;
	void SetViewportWidth(const FLOAT);
	FLOAT GetViewportHeight(void) const;
	void SetViewportHeight(const FLOAT);

	virtual void Draw(void);
	void SetDrawCamera(tml::graphic::Camera2D *);
	void ClearDrawCamera(void);
	void SetDrawLight(tml::graphic::Light *);
	void ClearDrawLight(void);
	void SetDrawFog(tml::graphic::Fog *);
	void ClearDrawFog(void);
	void SetDrawModel(tml::graphic::Model2D *);
	void ClearDrawModel(void);
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
 * @brief GetRenderTargetTexture関数
 * @return rt_tex (render_target_texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Canvas2D::GetRenderTargetTexture(void)
{
	return (this->rt_tex_);
}


/**
 * @brief GetRenderTargetTextureClearFlag関数
 * @return rt_tex_clear_flg (render_target_texture_clear_flag)
 */
inline bool tml::graphic::Canvas2D::GetRenderTargetTextureClearFlag(void) const
{
	return (this->rt_tex_clear_flg_);
}


/**
 * @brief SetRenderTargetTextureClearFlag関数
 * @param rt_tex_clear_flg (render_target_texture_clear_flag)
 */
inline void tml::graphic::Canvas2D::SetRenderTargetTextureClearFlag(const bool rt_tex_clear_flg)
{
	this->rt_tex_clear_flg_ = rt_tex_clear_flg;

	return;
}


/**
 * @brief GetViewportX関数
 * @return vp_x (viewport_x)
 */
inline FLOAT tml::graphic::Canvas2D::GetViewportX(void) const
{
	return (this->vp_x_);
}


/**
 * @brief SetViewportX関数
 * @param vp_x (viewport_x)
 */
inline void tml::graphic::Canvas2D::SetViewportX(const FLOAT vp_x)
{
	this->vp_x_ = vp_x;

	return;
}


/**
 * @brief GetViewportY関数
 * @return vp_y (viewport_y)
 */
inline FLOAT tml::graphic::Canvas2D::GetViewportY(void) const
{
	return (this->vp_y_);
}


/**
 * @brief SetViewportY関数
 * @param vp_y (viewport_y)
 */
inline void tml::graphic::Canvas2D::SetViewportY(const FLOAT vp_y)
{
	this->vp_y_ = vp_y;

	return;
}


/**
 * @brief GetViewportWidth関数
 * @return vp_w (viewport_width)
 */
inline FLOAT tml::graphic::Canvas2D::GetViewportWidth(void) const
{
	return (this->vp_w_);
}


/**
 * @brief SetViewportWidth関数
 * @param vp_w (viewport_width)
 */
inline void tml::graphic::Canvas2D::SetViewportWidth(const FLOAT vp_w)
{
	this->vp_w_ = vp_w;

	return;
}


/**
 * @brief GetViewportHeight関数
 * @return vp_h (viewport_height)
 */
inline FLOAT tml::graphic::Canvas2D::GetViewportHeight(void) const
{
	return (this->vp_h_);
}


/**
 * @brief SetViewportHeight関数
 * @param vp_h (viewport_height)
 */
inline void tml::graphic::Canvas2D::SetViewportHeight(const FLOAT vp_h)
{
	this->vp_h_ = vp_h;

	return;
}


/**
 * @brief SetDrawCamera関数
 * @param camera (camera)
 */
inline void tml::graphic::Canvas2D::SetDrawCamera(tml::graphic::Camera2D *camera)
{
	this->draw_camera_ = camera;

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
 * @brief SetDrawLight関数
 * @param light (light)
 */
inline void tml::graphic::Canvas2D::SetDrawLight(tml::graphic::Light *light)
{
	if ((light == nullptr)
	|| (this->draw_light_cnt_ >= tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT)) {
		return;
	}

	this->draw_light_ary_[this->draw_light_cnt_++] = light;

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
 * @brief SetDrawFog関数
 * @param fog (fog)
 */
inline void tml::graphic::Canvas2D::SetDrawFog(tml::graphic::Fog *fog)
{
	if ((fog == nullptr)
	|| (this->draw_fog_cnt_ >= tml::ConstantUtil::GRAPHIC::FOG_LIMIT)) {
		return;
	}

	this->draw_fog_ary_[this->draw_fog_cnt_++] = fog;

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
 * @brief SetDrawModel関数
 * @param model (model)
 */
inline void tml::graphic::Canvas2D::SetDrawModel(tml::graphic::Model2D *model)
{
	if ((model == nullptr)
	|| (this->draw_model_cnt_ >= tml::ConstantUtil::GRAPHIC::MODEL_LIMIT)) {
		return;
	}

	this->draw_model_ary_[this->draw_model_cnt_++] = model;

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
