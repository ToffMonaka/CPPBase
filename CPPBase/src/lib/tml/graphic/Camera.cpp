/**
 * @file
 * @brief Cameraコードファイル
 */


#include "Camera.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::CameraDesc::CameraDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::CameraDesc::~CameraDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::CameraDesc::Init(void)
{
	this->Release();

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::CameraDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Camera Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"CAMERA");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Camera::Camera() :
	type_(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE),
	draw_set_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera::~Camera()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE;
	this->draw_set_flg_ = false;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Camera::Create(const tml::graphic::CameraDesc &desc)
{
	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::GRAPHIC::CAMERA_TYPE>(this->GetResourceSubIndex());

	return (0);
}
