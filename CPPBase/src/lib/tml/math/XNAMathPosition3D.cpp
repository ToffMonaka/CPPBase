/**
 * @file
 * @brief XNAMathPosition3Dコードファイル
 */


#include "XNAMathPosition3D.h"


/**
 * @brief コンストラクタ
 */
tml::XMPosition3D::XMPosition3D() :
	pos_(0.0f),
	quat_(tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE),
	angle_(0.0f),
	x_axis_vec_(tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE),
	y_axis_vec_(tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE),
	z_axis_vec_(tml::ConstantUtil::XNAMATH::Z_VECTOR::TYPE)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 */
tml::XMPosition3D::XMPosition3D(const tml::XMFLOAT3EX &pos) :
	pos_(pos),
	quat_(tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE),
	angle_(0.0f),
	x_axis_vec_(tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE),
	y_axis_vec_(tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE),
	z_axis_vec_(tml::ConstantUtil::XNAMATH::Z_VECTOR::TYPE)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param quat (quaternion)
 */
tml::XMPosition3D::XMPosition3D(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat) :
	pos_(pos),
	quat_(quat)
{
	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param angle (angle)
 */
tml::XMPosition3D::XMPosition3D(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT3EX &angle) :
	pos_(pos),
	angle_(angle)
{
	this->UpdateQuaternionFromAngle();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::XMPosition3D::XMPosition3D(const tml::XMPosition3D &src)
{
	this->pos_ = src.pos_;
	this->quat_ = src.quat_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;
	this->z_axis_vec_ = src.z_axis_vec_;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::XMPosition3D &tml::XMPosition3D::operator =(const tml::XMPosition3D &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->pos_ = src.pos_;
	this->quat_ = src.quat_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;
	this->z_axis_vec_ = src.z_axis_vec_;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::XMPosition3D::XMPosition3D(tml::XMPosition3D &&src) noexcept
{
	this->pos_ = src.pos_;
	this->quat_ = src.quat_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;
	this->z_axis_vec_ = src.z_axis_vec_;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::XMPosition3D &tml::XMPosition3D::operator =(tml::XMPosition3D &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->pos_ = src.pos_;
	this->quat_ = src.quat_;
	this->angle_ = src.angle_;
	this->x_axis_vec_ = src.x_axis_vec_;
	this->y_axis_vec_ = src.y_axis_vec_;
	this->z_axis_vec_ = src.z_axis_vec_;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
tml::XMPosition3D::~XMPosition3D()
{
	this->Release();

	return;
}


/**
 * @brief operator +関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition3D tml::XMPosition3D::operator +(const tml::XMPosition3D &pos) const
{
	tml::XMFLOAT3EX tmp_pos(this->pos_);
	tml::XMFLOAT4EX tmp_quat(this->quat_);

	tmp_pos += pos.pos_;
	DirectX::XMStoreFloat4(&tmp_quat, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&tmp_quat), DirectX::XMLoadFloat4(&pos.quat_))));

	return (tml::XMPosition3D(tmp_pos, tmp_quat));
}


/**
 * @brief operator +=関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition3D &tml::XMPosition3D::operator +=(const tml::XMPosition3D &pos)
{
	this->pos_ += pos.pos_;
	DirectX::XMStoreFloat4(&this->quat_, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&this->quat_), DirectX::XMLoadFloat4(&pos.quat_))));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return ((*this));
}


/**
 * @brief operator -関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition3D tml::XMPosition3D::operator -(const tml::XMPosition3D &pos) const
{
	tml::XMFLOAT3EX tmp_pos(this->pos_);
	tml::XMFLOAT4EX tmp_quat(this->quat_);

	tmp_pos -= pos.pos_;
	DirectX::XMStoreFloat4(&tmp_quat, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&tmp_quat), DirectX::XMQuaternionInverse(DirectX::XMLoadFloat4(&pos.quat_)))));

	return (tml::XMPosition3D(tmp_pos, tmp_quat));
}


/**
 * @brief operator -=関数
 * @param pos (position)
 * @return pos (position)
 */
tml::XMPosition3D &tml::XMPosition3D::operator -=(const tml::XMPosition3D &pos)
{
	this->pos_ -= pos.pos_;
	DirectX::XMStoreFloat4(&this->quat_, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&this->quat_), DirectX::XMQuaternionInverse(DirectX::XMLoadFloat4(&pos.quat_)))));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return ((*this));
}


/**
 * @brief Init関数
 */
void tml::XMPosition3D::Init(void)
{
	this->Release();

	this->pos_ = 0.0f;
	this->quat_ = tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE;
	this->angle_ = 0.0f;
	this->x_axis_vec_ = tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE;
	this->y_axis_vec_ = tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE;
	this->z_axis_vec_ = tml::ConstantUtil::XNAMATH::Z_VECTOR::TYPE;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 */
void tml::XMPosition3D::Init(const tml::XMFLOAT3EX &pos)
{
	this->Release();

	this->pos_ = pos;
	this->quat_ = tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE;
	this->angle_ = 0.0f;
	this->x_axis_vec_ = tml::ConstantUtil::XNAMATH::X_VECTOR::TYPE;
	this->y_axis_vec_ = tml::ConstantUtil::XNAMATH::Y_VECTOR::TYPE;
	this->z_axis_vec_ = tml::ConstantUtil::XNAMATH::Z_VECTOR::TYPE;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param quat (quaternion)
 */
void tml::XMPosition3D::Init(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat)
{
	this->Release();

	this->pos_ = pos;
	this->quat_ = quat;

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param angle (angle)
 */
void tml::XMPosition3D::Init(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT3EX &angle)
{
	this->Release();

	this->pos_ = pos;
	this->angle_ = angle;

	this->UpdateQuaternionFromAngle();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief Look関数
 * @param pos (position)
 */
void tml::XMPosition3D::Look(const tml::XMFLOAT3EX &pos)
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat3(&this->pos_);
	DirectX::XMVECTOR tmp_vec = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&pos), tmp_pos);

	if (DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(tmp_vec)) <= 0.0f) {
		return;
	}

	DirectX::XMMATRIX rot_mat = DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixLookToLH(tmp_pos, tmp_vec, DirectX::XMLoadFloat3(&this->y_axis_vec_)));

	if (DirectX::XMMatrixIsNaN(rot_mat)) {
		tmp_vec = DirectX::XMVectorAdd(tmp_vec, DirectX::XMVectorSet(0.0f, 0.0f, 0.0001f, 0.0f));
		rot_mat = DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixLookToLH(tmp_pos, tmp_vec, DirectX::XMLoadFloat3(&this->y_axis_vec_)));
	}

	DirectX::XMStoreFloat4(&this->quat_, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionRotationMatrix(rot_mat)));

	this->UpdateAngleFromQuaternion();
	this->UpdateAxisVectorFromQuaternion();

	return;
}


/**
 * @brief UpdateQuaternionFromAngle関数
 *
 * three.jsを参考
 */
void tml::XMPosition3D::UpdateQuaternionFromAngle(void)
{
	DirectX::XMStoreFloat4(&this->quat_, DirectX::XMQuaternionRotationRollPitchYaw(this->angle_.x, this->angle_.y, this->angle_.z));

	return;
}


/**
 * @brief UpdateAngleFromQuaternion関数
 *
 * three.jsを参考
 */
void tml::XMPosition3D::UpdateAngleFromQuaternion(void)
{
	tml::XMFLOAT3X3EX rot_mat;
		
	DirectX::XMStoreFloat3x3(&rot_mat, DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&this->quat_))));

	this->angle_.x = std::asin(-tml::Clamp(rot_mat._23, -1.0f, 1.0f));

	if (std::abs(rot_mat._23) < 0.99999f) {
		this->angle_.y = std::atan2(rot_mat._13, rot_mat._33);
		this->angle_.z = std::atan2(rot_mat._21, rot_mat._22);
	} else {
		this->angle_.y = std::atan2(-rot_mat._31, rot_mat._11);
		this->angle_.z = 0.0f;
	}

	return;
}


/**
 * @brief UpdateAxisVectorFromQuaternion関数
 */
void tml::XMPosition3D::UpdateAxisVectorFromQuaternion(void)
{
	DirectX::XMVECTOR tmp_quat = DirectX::XMLoadFloat4(&this->quat_);

	DirectX::XMStoreFloat3(&this->x_axis_vec_, DirectX::XMVector3Rotate(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), tmp_quat));
	DirectX::XMStoreFloat3(&this->y_axis_vec_, DirectX::XMVector3Rotate(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), tmp_quat));
	DirectX::XMStoreFloat3(&this->z_axis_vec_, DirectX::XMVector3Rotate(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), tmp_quat));

	return;
}
