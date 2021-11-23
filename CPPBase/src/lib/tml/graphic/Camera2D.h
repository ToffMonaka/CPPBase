/**
 * @file
 * @brief Camera2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Camera.h"


namespace tml {
namespace graphic {
/**
 * @brief Camera2DDescクラス
 */
class Camera2DDesc : public tml::graphic::CameraDesc
{
public:
	tml::Transform2D transform;
	tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE projection_type;
	tml::XMFLOAT2EX fov_size;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Camera2DDesc();
	virtual ~Camera2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera2DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Camera2Dクラス
 */
class Camera2D : public tml::graphic::Camera
{
public: Camera2D(const tml::graphic::Camera2D &) = delete;
public: tml::graphic::Camera2D &operator =(const tml::graphic::Camera2D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE proj_type_;
	tml::XMFLOAT2EX fov_size_;

public:
	tml::Transform2D transform;

private:
	void Release(void);

public:
	Camera2D();
	virtual ~Camera2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Camera2DDesc &);

	tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE GetProjectionType(void) const;
	const tml::XMFLOAT2EX &GetFOVSize(void) const;
	void SetFOVSize(const tml::XMFLOAT2EX &);
	virtual DirectX::XMMATRIX &GetViewMatrix(DirectX::XMMATRIX &);
	virtual DirectX::XMMATRIX &GetProjectionMatrix(DirectX::XMMATRIX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera2D::Release(void)
{
	return;
}


/**
 * @brief GetProjectionType関数
 * @return proj_type (projection_type)
 */
inline tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE tml::graphic::Camera2D::GetProjectionType(void) const
{
	return (this->proj_type_);
}


/**
 * @brief GetFOVSize関数
 * @return fov_size (fov_size)
 */
inline const tml::XMFLOAT2EX &tml::graphic::Camera2D::GetFOVSize(void) const
{
	return (this->fov_size_);
}


/**
 * @brief SetFOVSize関数
 * @param fov_size (fov_size)
 */
inline void tml::graphic::Camera2D::SetFOVSize(const tml::XMFLOAT2EX &fov_size)
{
	this->fov_size_ = fov_size;
	
	return;
}
