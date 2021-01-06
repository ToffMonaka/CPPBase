/**
 * @file
 * @brief Camera�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief CameraDesc�N���X
 */
class CameraDesc : public tml::GraphicResourceDesc
{
public:
	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE type;
	tml::XMPosition position;
	FLOAT fov_angle;
	tml::XMFLOAT2EX fov_size;
	FLOAT near_clip;
	FLOAT far_clip;

public:
	CameraDesc();
	virtual ~CameraDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Camera�N���X
 */
class Camera : public tml::GraphicResource
{
public: Camera(const tml::Camera &) = delete;
public: tml::Camera &operator =(const tml::Camera &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE type_;
	FLOAT fov_angle_;
	tml::XMFLOAT2EX fov_size_;
	FLOAT near_clip_;
	FLOAT far_clip_;

public:
	tml::XMPosition position;

private:
	void Release(void);

public:
	Camera();
	virtual ~Camera();

	virtual void Init(void);
	INT Create(tml::CameraDesc &);

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


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::CAMERA_TYPE tml::Camera::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetFOVAngle�֐�
 * @return fov_angle (fov_angle)
 */
inline FLOAT tml::Camera::GetFOVAngle(void) const
{
	return (this->fov_angle_);
}


/**
 * @brief SetFOVAngle�֐�
 * @param fov_angle (fov_angle)
 */
inline void tml::Camera::SetFOVAngle(const FLOAT fov_angle)
{
	this->fov_angle_ = fov_angle;
	
	return;
}


/**
 * @brief GetFOVSize�֐�
 * @return fov_size (fov_size)
 */
inline const tml::XMFLOAT2EX &tml::Camera::GetFOVSize(void) const
{
	return (this->fov_size_);
}


/**
 * @brief SetFOVSize�֐�
 * @param fov_size (fov_size)
 */
inline void tml::Camera::SetFOVSize(const tml::XMFLOAT2EX &fov_size)
{
	this->fov_size_ = fov_size;
	
	return;
}


/**
 * @brief GetNearClip�֐�
 * @return near_clip (near_clip)
 */
inline FLOAT tml::Camera::GetNearClip(void) const
{
	return (this->near_clip_);
}


/**
 * @brief SetNearClip�֐�
 * @param near_clip (near_clip)
 */
inline void tml::Camera::SetNearClip(const FLOAT near_clip)
{
	this->near_clip_ = near_clip;
	
	return;
}


/**
 * @brief GetFarClip�֐�
 * @return far_clip (far_clip)
 */
inline FLOAT tml::Camera::GetFarClip(void) const
{
	return (this->far_clip_);
}


/**
 * @brief SetFarClip�֐�
 * @param far_clip (far_clip)
 */
inline void tml::Camera::SetFarClip(const FLOAT far_clip)
{
	this->far_clip_ = far_clip;
	
	return;
}
