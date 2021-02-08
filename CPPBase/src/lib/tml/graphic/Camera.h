/**
 * @file
 * @brief Cameraヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief CameraDescクラス
 */
class CameraDesc : public tml::graphic::ResourceDesc
{
public:
	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE type;
	tml::XMPosition position;
	bool position_set_flag;
	FLOAT fov_angle;
	tml::XMFLOAT2EX fov_size;
	FLOAT near_clip;
	FLOAT far_clip;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	CameraDesc();
	virtual ~CameraDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::CameraDesc::Release(void)
{
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Cameraクラス
 */
class Camera : public tml::graphic::Resource
{
public: Camera(const tml::graphic::Camera &) = delete;
public: tml::graphic::Camera &operator =(const tml::graphic::Camera &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE type_;
	FLOAT fov_angle_;
	tml::XMFLOAT2EX fov_size_;
	FLOAT near_clip_;
	FLOAT far_clip_;

public:
	tml::shared_ptr<tml::XMPosition> position;

protected:
	void Release(void);

public:
	Camera();
	virtual ~Camera();

	virtual void Init(void);
	INT Create(const tml::graphic::CameraDesc &, tml::shared_ptr<tml::XMPosition> *pos = nullptr);

	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE GetType(void) const;
	FLOAT GetFOVAngle(void) const;
	void SetFOVAngle(const FLOAT);
	const tml::XMFLOAT2EX &GetFOVSize(void) const;
	void SetFOVSize(const tml::XMFLOAT2EX &);
	FLOAT GetNearClip(void) const;
	void SetNearClip(const FLOAT);
	FLOAT GetFarClip(void) const;
	void SetFarClip(const FLOAT);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::CAMERA_TYPE tml::graphic::Camera::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetFOVAngle関数
 * @return fov_angle (fov_angle)
 */
inline FLOAT tml::graphic::Camera::GetFOVAngle(void) const
{
	return (this->fov_angle_);
}


/**
 * @brief SetFOVAngle関数
 * @param fov_angle (fov_angle)
 */
inline void tml::graphic::Camera::SetFOVAngle(const FLOAT fov_angle)
{
	this->fov_angle_ = fov_angle;
	
	return;
}


/**
 * @brief GetFOVSize関数
 * @return fov_size (fov_size)
 */
inline const tml::XMFLOAT2EX &tml::graphic::Camera::GetFOVSize(void) const
{
	return (this->fov_size_);
}


/**
 * @brief SetFOVSize関数
 * @param fov_size (fov_size)
 */
inline void tml::graphic::Camera::SetFOVSize(const tml::XMFLOAT2EX &fov_size)
{
	this->fov_size_ = fov_size;
	
	return;
}


/**
 * @brief GetNearClip関数
 * @return near_clip (near_clip)
 */
inline FLOAT tml::graphic::Camera::GetNearClip(void) const
{
	return (this->near_clip_);
}


/**
 * @brief SetNearClip関数
 * @param near_clip (near_clip)
 */
inline void tml::graphic::Camera::SetNearClip(const FLOAT near_clip)
{
	this->near_clip_ = near_clip;
	
	return;
}


/**
 * @brief GetFarClip関数
 * @return far_clip (far_clip)
 */
inline FLOAT tml::graphic::Camera::GetFarClip(void) const
{
	return (this->far_clip_);
}


/**
 * @brief SetFarClip関数
 * @param far_clip (far_clip)
 */
inline void tml::graphic::Camera::SetFarClip(const FLOAT far_clip)
{
	this->far_clip_ = far_clip;
	
	return;
}
