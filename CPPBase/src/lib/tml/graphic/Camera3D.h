/**
 * @file
 * @brief Camera3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Camera.h"


namespace tml {
namespace graphic {
/**
 * @brief Camera3DDescクラス
 */
class Camera3DDesc : public tml::graphic::CameraDesc
{
public:
	tml::Transform3D transform;
	tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE projection_type;
	tml::XMFLOAT2EX fov_size;
	FLOAT fov_angle;
	FLOAT near_clip;
	FLOAT far_clip;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Camera3DDesc();
	virtual ~Camera3DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera3DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Camera3Dクラス
 */
class Camera3D : public tml::graphic::Camera
{
public: Camera3D(const tml::graphic::Camera3D &) = delete;
public: tml::graphic::Camera3D &operator =(const tml::graphic::Camera3D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	const tml::graphic::Camera3DDesc *desc_;
	tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE proj_type_;
	tml::XMFLOAT2EX fov_size_;
	FLOAT fov_angle_;
	FLOAT near_clip_;
	FLOAT far_clip_;

public:
	tml::Transform3D transform;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Camera3D();
	virtual ~Camera3D();

	virtual void Init(void);

	const tml::graphic::Camera3DDesc *GetDesc(void) const;
	tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE GetProjectionType(void) const;
	const tml::XMFLOAT2EX &GetFOVSize(void) const;
	void SetFOVSize(const tml::XMFLOAT2EX &);
	FLOAT GetFOVAngle(void) const;
	void SetFOVAngle(const FLOAT);
	FLOAT GetNearClip(void) const;
	void SetNearClip(const FLOAT);
	FLOAT GetFarClip(void) const;
	void SetFarClip(const FLOAT);
	virtual DirectX::XMMATRIX &GetViewMatrix(DirectX::XMMATRIX &);
	virtual DirectX::XMMATRIX &GetProjectionMatrix(DirectX::XMMATRIX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera3D::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::Camera3DDesc *tml::graphic::Camera3D::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetProjectionType関数
 * @return proj_type (projection_type)
 */
inline tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE tml::graphic::Camera3D::GetProjectionType(void) const
{
	return (this->proj_type_);
}


/**
 * @brief GetFOVSize関数
 * @return fov_size (fov_size)
 */
inline const tml::XMFLOAT2EX &tml::graphic::Camera3D::GetFOVSize(void) const
{
	return (this->fov_size_);
}


/**
 * @brief SetFOVSize関数
 * @param fov_size (fov_size)
 */
inline void tml::graphic::Camera3D::SetFOVSize(const tml::XMFLOAT2EX &fov_size)
{
	this->fov_size_ = fov_size;
	
	return;
}


/**
 * @brief GetFOVAngle関数
 * @return fov_angle (fov_angle)
 */
inline FLOAT tml::graphic::Camera3D::GetFOVAngle(void) const
{
	return (this->fov_angle_);
}


/**
 * @brief SetFOVAngle関数
 * @param fov_angle (fov_angle)
 */
inline void tml::graphic::Camera3D::SetFOVAngle(const FLOAT fov_angle)
{
	this->fov_angle_ = fov_angle;
	
	return;
}


/**
 * @brief GetNearClip関数
 * @return near_clip (near_clip)
 */
inline FLOAT tml::graphic::Camera3D::GetNearClip(void) const
{
	return (this->near_clip_);
}


/**
 * @brief SetNearClip関数
 * @param near_clip (near_clip)
 */
inline void tml::graphic::Camera3D::SetNearClip(const FLOAT near_clip)
{
	this->near_clip_ = near_clip;
	
	return;
}


/**
 * @brief GetFarClip関数
 * @return far_clip (far_clip)
 */
inline FLOAT tml::graphic::Camera3D::GetFarClip(void) const
{
	return (this->far_clip_);
}


/**
 * @brief SetFarClip関数
 * @param far_clip (far_clip)
 */
inline void tml::graphic::Camera3D::SetFarClip(const FLOAT far_clip)
{
	this->far_clip_ = far_clip;
	
	return;
}
