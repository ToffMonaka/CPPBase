/**
 * @file
 * @brief Camera�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief CameraDesc�N���X
 */
class CameraDesc : public tml::graphic::ManagerResourceDesc
{
public:

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
 * @brief Release�֐�
 */
inline void tml::graphic::CameraDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Camera�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Camera : public tml::graphic::ManagerResource
{
public: Camera(const tml::graphic::Camera &) = delete;
public: tml::graphic::Camera &operator =(const tml::graphic::Camera &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CAMERA);

private:
	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE type_;

protected:
	void Release(void);
	INT Create(const tml::graphic::CameraDesc &, const tml::ConstantUtil::GRAPHIC::CAMERA_TYPE);

public:
	Camera();
	virtual ~Camera();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE GetType(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Camera::Release(void)
{
	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::CAMERA_TYPE tml::graphic::Camera::GetType(void) const
{
	return (this->type_);
}
