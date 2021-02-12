/**
 * @file
 * @brief XNAMathPosition3Dコードファイル
 */


#include "XNAMathPosition3D.h"
#include "MathUtil.h"


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
	XMStoreFloat4(&tmp_quat, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&tmp_quat), XMLoadFloat4(&pos.quat_))));

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
	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&this->quat_), XMLoadFloat4(&pos.quat_))));

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
	XMStoreFloat4(&tmp_quat, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&tmp_quat), XMQuaternionInverse(XMLoadFloat4(&pos.quat_)))));

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
	XMStoreFloat4(&this->quat_, XMQuaternionNormalize(XMQuaternionMultiply(XMLoadFloat4(&this->quat_), XMQuaternionInverse(XMLoadFloat4(&pos.quat_)))));

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
 * @brief UpdateQuaternionFromAngle関数
 */
void tml::XMPosition3D::UpdateQuaternionFromAngle(void)
{
	XMStoreFloat4(&this->quat_, XMQuaternionRotationRollPitchYaw(this->angle_.x, this->angle_.y, this->angle_.z));

	return;
}


/**
 * @brief UpdateAngleFromQuaternion関数
 */
void tml::XMPosition3D::UpdateAngleFromQuaternion(void)
{
	XMVECTOR determinant;

	tml::XMFLOAT3X3EX rot_mat;
		
	XMStoreFloat3x3(&rot_mat, XMMatrixInverse(&determinant, XMMatrixRotationQuaternion(XMLoadFloat4(&this->quat_))));

	this->angle_.x = std::asin(-tml::MathUtil::Clamp(rot_mat._23, -1.0f, 1.0f));

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
	XMMATRIX rot_mat = XMMatrixRotationQuaternion(XMLoadFloat4(&this->quat_));

	XMStoreFloat3(&this->x_axis_vec_, XMVector2Transform(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rot_mat));
	XMStoreFloat3(&this->y_axis_vec_, XMVector2Transform(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rot_mat));
	XMStoreFloat3(&this->z_axis_vec_, XMVector2Transform(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rot_mat));

	return;
}
