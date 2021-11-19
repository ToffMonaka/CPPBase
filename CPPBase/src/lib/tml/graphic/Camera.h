/**
 * @file
 * @brief Cameraヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/Transform.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief CameraDescクラス
 */
class CameraDesc : public tml::graphic::ManagerResourceDesc
{
public:

private:
	void Release(void);

protected:
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
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Cameraクラス
 *
 * インターフェースパターン
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
	bool draw_set_flg_;

private:
	void Release(void);

public:
	Camera();
	virtual ~Camera();

	virtual void Init(void);
	INT Create(const tml::graphic::CameraDesc &);

	tml::ConstantUtil::GRAPHIC::CAMERA_TYPE GetType(void) const;
	virtual DirectX::XMMATRIX &GetViewMatrix(DirectX::XMMATRIX &) = 0;
	virtual DirectX::XMMATRIX &GetProjectionMatrix(DirectX::XMMATRIX &) = 0;
	bool GetDrawSetFlag(void) const;
	void SetDrawSetFlag(const bool);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera::Release(void)
{
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
 * @brief GetDrawSetFlag関数
 * @return draw_set_flg (draw_set_flag)
 */
inline bool tml::graphic::Camera::GetDrawSetFlag(void) const
{
	return (this->draw_set_flg_);
}


/**
 * @brief SetDrawSetFlag関数
 * @param draw_set_flg (draw_set_flag)
 */
inline void tml::graphic::Camera::SetDrawSetFlag(const bool draw_set_flg)
{
	this->draw_set_flg_ = draw_set_flg;

	return;
}
