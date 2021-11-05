/**
 * @file
 * @brief Canvas3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Canvas.h"
#include "Viewport.h"


namespace tml {
namespace graphic {
/**
 * @brief Canvas3DDescクラス
 */
class Canvas3DDesc : public tml::graphic::CanvasDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Canvas3DDesc();
	virtual ~Canvas3DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Canvas3DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Canvas3Dクラス
 */
class Canvas3D : public tml::graphic::Canvas
{
public: Canvas3D(const tml::graphic::Canvas3D &) = delete;
public: tml::graphic::Canvas3D &operator =(const tml::graphic::Canvas3D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_3D);

private:
	tml::shared_ptr<tml::graphic::Camera3D> camera_;
	tml::shared_ptr<tml::graphic::Texture> rt_tex_;
	bool rt_tex_clear_flg_;
	tml::shared_ptr<tml::graphic::Texture> dt_tex_;
	bool dt_tex_clear_flg_;
	FLOAT vp_x_;
	FLOAT vp_y_;
	FLOAT vp_w_;
	FLOAT vp_h_;

	UINT draw_light_cnt_;
	std::array<tml::graphic::Light3D *, tml::ConstantUtil::GRAPHIC::LIGHT_LIMIT> draw_light_ary_;
	UINT draw_fog_cnt_;
	std::array<tml::graphic::Fog3D *, tml::ConstantUtil::GRAPHIC::FOG_LIMIT> draw_fog_ary_;
	UINT draw_model_cnt_;
	std::array<tml::graphic::Model3D *, tml::ConstantUtil::GRAPHIC::MODEL_LIMIT> draw_model_ary_;

protected:
	tml::graphic::Viewport vp_;

private:
	void Release(void);

public:
	Canvas3D();
	virtual ~Canvas3D();

	virtual void Init(void);
	INT Create(const tml::graphic::Canvas3DDesc &);

	const tml::shared_ptr<tml::graphic::Camera3D> &GetCamera(void);
	void SetCamera(const tml::shared_ptr<tml::graphic::Camera3D> &);
	const tml::shared_ptr<tml::graphic::Texture> &GetRenderTargetTexture(void);
	void SetRenderTargetTexture(const tml::shared_ptr<tml::graphic::Texture> &);
	bool GetRenderTargetTextureClearFlag(void) const;
	void SetRenderTargetTextureClearFlag(const bool);
	const tml::shared_ptr<tml::graphic::Texture> &GetDepthTargetTexture(void);
	void SetDepthTargetTexture(const tml::shared_ptr<tml::graphic::Texture> &);
	bool GetDepthTargetTextureClearFlag(void) const;
	void SetDepthTargetTextureClearFlag(const bool);
	FLOAT GetViewportX(void) const;
	void SetViewportX(const FLOAT);
	FLOAT GetViewportY(void) const;
	void SetViewportY(const FLOAT);
	FLOAT GetViewportWidth(void) const;
	void SetViewportWidth(const FLOAT);
	FLOAT GetViewportHeight(void) const;
	void SetViewportHeight(const FLOAT);

	virtual void Draw(void);
	void SetDrawLight(tml::graphic::Light3D *);
	void ClearDrawLight(void);
	void SetDrawFog(tml::graphic::Fog3D *);
	void ClearDrawFog(void);
	void SetDrawModel(tml::graphic::Model3D *);
	void ClearDrawModel(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Canvas3D::Release(void)
{
	return;
}


/**
 * @brief GetCamera関数
 * @return camera (camera)
 */
inline const tml::shared_ptr<tml::graphic::Camera3D> &tml::graphic::Canvas3D::GetCamera(void)
{
	return (this->camera_);
}


/**
 * @brief GetRenderTargetTexture関数
 * @return rt_tex (render_target_texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Canvas3D::GetRenderTargetTexture(void)
{
	return (this->rt_tex_);
}


/**
 * @brief GetRenderTargetTextureClearFlag関数
 * @return rt_tex_clear_flg (render_target_texture_clear_flag)
 */
inline bool tml::graphic::Canvas3D::GetRenderTargetTextureClearFlag(void) const
{
	return (this->rt_tex_clear_flg_);
}


/**
 * @brief SetRenderTargetTextureClearFlag関数
 * @param rt_tex_clear_flg (render_target_texture_clear_flag)
 */
inline void tml::graphic::Canvas3D::SetRenderTargetTextureClearFlag(const bool rt_tex_clear_flg)
{
	this->rt_tex_clear_flg_ = rt_tex_clear_flg;

	return;
}


/**
 * @brief GetDepthTargetTexture関数
 * @return dt_tex (depth_target_texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Canvas3D::GetDepthTargetTexture(void)
{
	return (this->dt_tex_);
}


/**
 * @brief GetDepthTargetTextureClearFlag関数
 * @return dt_tex_clear_flg (depth_target_texture_clear_flag)
 */
inline bool tml::graphic::Canvas3D::GetDepthTargetTextureClearFlag(void) const
{
	return (this->dt_tex_clear_flg_);
}


/**
 * @brief SetDepthTargetTextureClearFlag関数
 * @param dt_tex_clear_flg (depth_target_texture_clear_flag)
 */
inline void tml::graphic::Canvas3D::SetDepthTargetTextureClearFlag(const bool dt_tex_clear_flg)
{
	this->dt_tex_clear_flg_ = dt_tex_clear_flg;

	return;
}


/**
 * @brief GetViewportX関数
 * @return vp_x (viewport_x)
 */
inline FLOAT tml::graphic::Canvas3D::GetViewportX(void) const
{
	return (this->vp_x_);
}


/**
 * @brief SetViewportX関数
 * @param vp_x (viewport_x)
 */
inline void tml::graphic::Canvas3D::SetViewportX(const FLOAT vp_x)
{
	this->vp_x_ = vp_x;

	return;
}


/**
 * @brief GetViewportY関数
 * @return vp_y (viewport_y)
 */
inline FLOAT tml::graphic::Canvas3D::GetViewportY(void) const
{
	return (this->vp_y_);
}


/**
 * @brief SetViewportY関数
 * @param vp_y (viewport_y)
 */
inline void tml::graphic::Canvas3D::SetViewportY(const FLOAT vp_y)
{
	this->vp_y_ = vp_y;

	return;
}


/**
 * @brief GetViewportWidth関数
 * @return vp_w (viewport_width)
 */
inline FLOAT tml::graphic::Canvas3D::GetViewportWidth(void) const
{
	return (this->vp_w_);
}


/**
 * @brief SetViewportWidth関数
 * @param vp_w (viewport_width)
 */
inline void tml::graphic::Canvas3D::SetViewportWidth(const FLOAT vp_w)
{
	this->vp_w_ = vp_w;

	return;
}


/**
 * @brief GetViewportHeight関数
 * @return vp_h (viewport_height)
 */
inline FLOAT tml::graphic::Canvas3D::GetViewportHeight(void) const
{
	return (this->vp_h_);
}


/**
 * @brief SetViewportHeight関数
 * @param vp_h (viewport_height)
 */
inline void tml::graphic::Canvas3D::SetViewportHeight(const FLOAT vp_h)
{
	this->vp_h_ = vp_h;

	return;
}
