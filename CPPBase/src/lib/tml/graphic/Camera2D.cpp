/**
 * @file
 * @brief Camera2D�R�[�h�t�@�C��
 */


#include "Camera2D.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Camera2DDesc::Camera2DDesc() :
	projection_type(tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::NONE),
	fov_size(0.0f)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Camera2DDesc::~Camera2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Camera2DDesc::Init(void)
{
	this->Release();

	this->position.Init();
	this->projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::NONE;
	this->fov_size = 0.0f;

	tml::graphic::CameraDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Camera2DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::CameraDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Camera2D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"CAMERA_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Camera2D::Camera2D() :
	proj_type_(tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::NONE),
	fov_size_(0.0f)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Camera2D::~Camera2D()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Camera2D::Init(void)
{
	this->Release();

	this->position.Init();
	this->proj_type_ = tml::ConstantUtil::GRAPHIC::CAMERA_2D_PROJECTION_TYPE::NONE;
	this->fov_size_ = 0.0f;

	tml::graphic::Camera::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Camera2D::Create(const tml::graphic::Camera2DDesc &desc)
{
	this->Init();

	if (tml::graphic::Camera::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->position = desc.position;
	this->proj_type_ = desc.projection_type;
	this->fov_size_ = desc.fov_size;

	return (0);
}
