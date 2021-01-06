/**
 * @file
 * @brief Cameraコードファイル
 */


#include "Camera.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::CameraDesc::CameraDesc() :
	type(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE),
	fov_angle(0.0f),
	fov_size(0.0f, 0.0f),
	near_clip(0.0f),
	far_clip(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CameraDesc::~CameraDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::CameraDesc::Init(void)
{
	this->type = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE;
	this->position.Init();
	this->fov_angle = 0.0f;
	this->fov_size = 0.0f;
	this->near_clip = 0.0f;
	this->far_clip = 0.0f;

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Camera::Camera() :
	type_(tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE),
	fov_angle_(0.0f),
	fov_size_(0.0f, 0.0f),
	near_clip_(0.0f),
	far_clip_(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Camera::~Camera()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Camera::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Camera::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE;
	this->position.Init();
	this->fov_angle_ = 0.0f;
	this->fov_size_ = 0.0f;
	this->near_clip_ = 0.0f;
	this->far_clip_ = 0.0f;

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Camera::Create(tml::CameraDesc &desc)
{
	if (desc.type == tml::ConstantUtil::GRAPHIC::CAMERA_TYPE::NONE) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
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
