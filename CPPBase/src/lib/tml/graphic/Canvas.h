/**
 * @file
 * @brief Canvas�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"
#include "Viewport.h"


namespace tml {
namespace graphic {
/**
 * @brief CanvasDesc�N���X
 */
class CanvasDesc : public tml::graphic::ManagerResourceDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	CanvasDesc();
	virtual ~CanvasDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::CanvasDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Canvas�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Canvas : public tml::graphic::ManagerResource
{
public: Canvas(const tml::graphic::Canvas &) = delete;
public: tml::graphic::Canvas &operator =(const tml::graphic::Canvas &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::GRAPHIC::CANVAS_TYPE type_;
	tml::shared_ptr<tml::graphic::Texture> rt_tex_;
	bool rt_tex_clear_flg_;
	tml::shared_ptr<tml::graphic::Texture> dt_tex_;
	bool dt_tex_clear_flg_;
	FLOAT vp_x_;
	FLOAT vp_y_;
	FLOAT vp_w_;
	FLOAT vp_h_;

protected:
	tml::graphic::Viewport vp_;

protected:
	void Release(void);
	INT Create(const tml::graphic::CanvasDesc &, const tml::ConstantUtil::GRAPHIC::CANVAS_TYPE);

public:
	Canvas();
	virtual ~Canvas();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::CANVAS_TYPE GetType(void) const;
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
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Canvas::Release(void)
{
	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::CANVAS_TYPE tml::graphic::Canvas::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRenderTargetTexture�֐�
 * @return rt_tex (render_target_texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Canvas::GetRenderTargetTexture(void)
{
	return (this->rt_tex_);
}


/**
 * @brief GetRenderTargetTextureClearFlag�֐�
 * @return rt_tex_clear_flg (render_target_texture_clear_flag)
 */
inline bool tml::graphic::Canvas::GetRenderTargetTextureClearFlag(void) const
{
	return (this->rt_tex_clear_flg_);
}


/**
 * @brief SetRenderTargetTextureClearFlag�֐�
 * @param rt_tex_clear_flg (render_target_texture_clear_flag)
 */
inline void tml::graphic::Canvas::SetRenderTargetTextureClearFlag(const bool rt_tex_clear_flg)
{
	this->rt_tex_clear_flg_ = rt_tex_clear_flg;

	return;
}


/**
 * @brief GetDepthTargetTexture�֐�
 * @return dt_tex (depth_target_texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Canvas::GetDepthTargetTexture(void)
{
	return (this->dt_tex_);
}


/**
 * @brief GetDepthTargetTextureClearFlag�֐�
 * @return dt_tex_clear_flg (depth_target_texture_clear_flag)
 */
inline bool tml::graphic::Canvas::GetDepthTargetTextureClearFlag(void) const
{
	return (this->dt_tex_clear_flg_);
}


/**
 * @brief SetDepthTargetTextureClearFlag�֐�
 * @param dt_tex_clear_flg (depth_target_texture_clear_flag)
 */
inline void tml::graphic::Canvas::SetDepthTargetTextureClearFlag(const bool dt_tex_clear_flg)
{
	this->dt_tex_clear_flg_ = dt_tex_clear_flg;

	return;
}


/**
 * @brief GetViewportX�֐�
 * @return vp_x (viewport_x)
 */
inline FLOAT tml::graphic::Canvas::GetViewportX(void) const
{
	return (this->vp_x_);
}


/**
 * @brief SetViewportX�֐�
 * @param vp_x (viewport_x)
 */
inline void tml::graphic::Canvas::SetViewportX(const FLOAT vp_x)
{
	this->vp_x_ = vp_x;

	return;
}


/**
 * @brief GetViewportY�֐�
 * @return vp_y (viewport_y)
 */
inline FLOAT tml::graphic::Canvas::GetViewportY(void) const
{
	return (this->vp_y_);
}


/**
 * @brief SetViewportY�֐�
 * @param vp_y (viewport_y)
 */
inline void tml::graphic::Canvas::SetViewportY(const FLOAT vp_y)
{
	this->vp_y_ = vp_y;

	return;
}


/**
 * @brief GetViewportWidth�֐�
 * @return vp_w (viewport_width)
 */
inline FLOAT tml::graphic::Canvas::GetViewportWidth(void) const
{
	return (this->vp_w_);
}


/**
 * @brief SetViewportWidth�֐�
 * @param vp_w (viewport_width)
 */
inline void tml::graphic::Canvas::SetViewportWidth(const FLOAT vp_w)
{
	this->vp_w_ = vp_w;

	return;
}


/**
 * @brief GetViewportHeight�֐�
 * @return vp_h (viewport_height)
 */
inline FLOAT tml::graphic::Canvas::GetViewportHeight(void) const
{
	return (this->vp_h_);
}


/**
 * @brief SetViewportHeight�֐�
 * @param vp_h (viewport_height)
 */
inline void tml::graphic::Canvas::SetViewportHeight(const FLOAT vp_h)
{
	this->vp_h_ = vp_h;

	return;
}
