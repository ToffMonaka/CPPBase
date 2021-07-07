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
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::CameraDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Camera Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"CAMERA");

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
	type_(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera::~Camera()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Camera::Create(const tml::graphic::CameraDesc &desc, const tml::ConstantUtil::GRAPHIC::CAMERA_TYPE type)
{
	if (type == tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE) {
		return (-1);
	}

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CAMERA, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}
