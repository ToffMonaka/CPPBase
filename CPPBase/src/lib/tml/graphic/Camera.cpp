/**
 * @file
 * @brief Camera�R�[�h�t�@�C��
 */


#include "Camera.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::CameraDesc::CameraDesc() :
	type(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE),
	fov_angle(0.0f),
	fov_size(0.0f),
	near_clip(0.0f),
	far_clip(0.0f)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::CameraDesc::~CameraDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::CameraDesc::Init(void)
{
	this->Release();

	this->type = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE;
	this->position.Init();
	this->fov_angle = 0.0f;
	this->fov_size = 0.0f;
	this->near_clip = 0.0f;
	this->far_clip = 0.0f;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
 */
tml::graphic::Camera::Camera() :
	type_(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE),
	fov_angle_(0.0f),
	fov_size_(0.0f),
	near_clip_(0.0f),
	far_clip_(0.0f)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Camera::~Camera()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Camera::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE;
	this->position.Init();
	this->fov_angle_ = 0.0f;
	this->fov_size_ = 0.0f;
	this->near_clip_ = 0.0f;
	this->far_clip_ = 0.0f;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Camera::Create(const tml::graphic::CameraDesc &desc)
{
	if (desc.type == tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CAMERA, static_cast<UINT>(desc.type)) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = desc.type;
	this->position = desc.position;
	this->fov_angle_ = desc.fov_angle;
	this->fov_size_ = desc.fov_size;
	this->near_clip_ = desc.near_clip;
	this->far_clip_ = desc.far_clip;

	return (0);
}
