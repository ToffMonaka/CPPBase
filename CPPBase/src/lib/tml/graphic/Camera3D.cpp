/**
 * @file
 * @brief Camera3Dコードファイル
 */


#include "Camera3D.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Camera3DDesc::Camera3DDesc() :
	projection_type(tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::NONE),
	fov_size(0.0f),
	fov_angle(0.0f),
	near_clip(0.0f),
	far_clip(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera3DDesc::~Camera3DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera3DDesc::Init(void)
{
	this->Release();

	this->transform.Init();
	this->projection_type = tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::NONE;
	this->fov_size = 0.0f;
	this->fov_angle = 0.0f;
	this->near_clip = 0.0f;
	this->far_clip = 0.0f;

	tml::graphic::CameraDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Camera3DDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::CameraDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Camera3D Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"CAMERA_3D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Camera3D::Camera3D() :
	desc_(nullptr),
	proj_type_(tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::NONE),
	fov_size_(0.0f),
	fov_angle_(0.0f),
	near_clip_(0.0f),
	far_clip_(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera3D::~Camera3D()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera3D::Init(void)
{
	this->Release();

	this->proj_type_ = tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::NONE;
	this->fov_size_ = 0.0f;
	this->fov_angle_ = 0.0f;
	this->near_clip_ = 0.0f;
	this->far_clip_ = 0.0f;

	this->transform.Init();

	tml::graphic::Camera::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Camera3D::OnCreate(void)
{
	if (tml::graphic::Camera::OnCreate() < 0) {
		return (-1);
	}

	this->SetDimensionType(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D);

	this->proj_type_ = this->desc_->projection_type;
	this->fov_size_ = this->desc_->fov_size;
	this->fov_angle_ = this->desc_->fov_angle;
	this->near_clip_ = this->desc_->near_clip;
	this->far_clip_ = this->desc_->far_clip;

	this->transform = this->desc_->transform;

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Camera3D::OnCreateDeferred(void)
{
	if (tml::graphic::Camera::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Camera3D::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Camera3DDesc *>(desc);

	tml::graphic::Camera::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief GetViewMatrix関数
 * @param dst_mat (dst_matrix)
 * @return dst_mat (dst_matrix)
 */
DirectX::XMMATRIX &tml::graphic::Camera3D::GetViewMatrix(DirectX::XMMATRIX &dst_mat)
{
	auto y_axis_vec = this->transform.GetYAxisVector();
	auto z_axis_vec = this->transform.GetZAxisVector();

	dst_mat = DirectX::XMMatrixLookToLH(DirectX::XMLoadFloat3(&this->transform.position), DirectX::XMLoadFloat3(&z_axis_vec), DirectX::XMLoadFloat3(&y_axis_vec));

	return (dst_mat);
}


/**
 * @brief GetProjectionMatrix関数
 * @param dst_mat (dst_matrix)
 * @return dst_mat (dst_matrix)
 */
DirectX::XMMATRIX &tml::graphic::Camera3D::GetProjectionMatrix(DirectX::XMMATRIX &dst_mat)
{
	switch (this->proj_type_) {
	case tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::PERSPECTIVE: {
		dst_mat = DirectX::XMMatrixPerspectiveFovLH(this->fov_angle_, this->fov_size_.x / this->fov_size_.y, this->near_clip_, this->far_clip_);

		break;
	}
	case tml::ConstantUtil::GRAPHIC::CAMERA_3D_PROJECTION_TYPE::ORTHOGRAPHIC: {
		dst_mat = DirectX::XMMatrixOrthographicLH(this->fov_size_.x, this->fov_size_.y, this->near_clip_, this->far_clip_);

		break;
	}
	default: {
		dst_mat = DirectX::XMMatrixIdentity();

		break;
	}
	}

	return (dst_mat);
}
