/**
 * @file
 * @brief Transform3Dコードファイル
 */


#include "Transform3D.h"


/**
 * @brief コンストラクタ
 */
tml::Transform3D::Transform3D() :
	position(0.0f),
	quaternion(tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE),
	scale(1.0f)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 */
tml::Transform3D::Transform3D(const tml::XMFLOAT3EX &pos) :
	position(pos),
	quaternion(tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE),
	scale(1.0f)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param quat (quaternion)
 */
tml::Transform3D::Transform3D(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat) :
	position(pos),
	quaternion(quat),
	scale(1.0f)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param quat (quaternion)
 * @param scale (scale)
 */
tml::Transform3D::Transform3D(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat, const tml::XMFLOAT3EX &scale) :
	position(pos),
	quaternion(quat),
	scale(scale)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Transform3D::Transform3D(const tml::Transform3D &src)
{
	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Transform3D &tml::Transform3D::operator =(const tml::Transform3D &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Transform3D::Transform3D(tml::Transform3D &&src) noexcept
{
	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Transform3D &tml::Transform3D::operator =(tml::Transform3D &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->position = src.position;
	this->quaternion = src.quaternion;
	this->scale = src.scale;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
tml::Transform3D::~Transform3D()
{
	this->Release();

	return;
}


/**
 * @brief operator +関数
 * @param trans (transform)
 * @return trans (transform)
 */
tml::Transform3D tml::Transform3D::operator +(const tml::Transform3D &trans) const
{
	tml::XMFLOAT3EX tmp_pos(this->position);
	tml::XMFLOAT4EX tmp_quat(this->quaternion);
	tml::XMFLOAT3EX tmp_scale(this->scale);

	tmp_pos += trans.position;
	DirectX::XMStoreFloat4(&tmp_quat, DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&tmp_quat), DirectX::XMLoadFloat4(&trans.quaternion)));
	tmp_scale += trans.scale;

	return (tml::Transform3D(tmp_pos, tmp_quat, tmp_scale));
}


/**
 * @brief operator +=関数
 * @param trans (transform)
 * @return trans (transform)
 */
tml::Transform3D &tml::Transform3D::operator +=(const tml::Transform3D &trans)
{
	this->position += trans.position;
	DirectX::XMStoreFloat4(&this->quaternion, DirectX::XMQuaternionMultiply(DirectX::XMLoadFloat4(&this->quaternion), DirectX::XMLoadFloat4(&trans.quaternion)));
	this->scale += trans.scale;

	return ((*this));
}


/**
 * @brief Init関数
 */
void tml::Transform3D::Init(void)
{
	this->Release();

	this->position = 0.0f;
	this->quaternion = tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE;
	this->scale = 1.0f;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 */
void tml::Transform3D::Init(const tml::XMFLOAT3EX &pos)
{
	this->Release();

	this->position = pos;
	this->quaternion = tml::ConstantUtil::XNAMATH::IDENTITY_VECTOR::TYPE;
	this->scale = 1.0f;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param quat (quaternion)
 */
void tml::Transform3D::Init(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat)
{
	this->Release();

	this->position = pos;
	this->quaternion = quat;
	this->scale = 1.0f;

	return;
}


/**
 * @brief Init関数
 * @param pos (position)
 * @param quat (quaternion)
 * @param scale (scale)
 */
void tml::Transform3D::Init(const tml::XMFLOAT3EX &pos, const tml::XMFLOAT4EX &quat, const tml::XMFLOAT3EX &scale)
{
	this->Release();

	this->position = pos;
	this->quaternion = quat;
	this->scale = scale;

	return;
}


/**
 * @brief Look関数
 * @param pos (position)
 */
void tml::Transform3D::Look(const tml::XMFLOAT3EX &pos)
{
	DirectX::XMVECTOR tmp_pos = DirectX::XMLoadFloat3(&this->position);
	DirectX::XMVECTOR tmp_vec = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&pos), tmp_pos);

	if (DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(tmp_vec)) <= 0.0f) {
		return;
	}

	tml::XMFLOAT3EX y_axis_vec = this->GetYAxisVector();

	DirectX::XMMATRIX rot_mat = DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixLookToLH(tmp_pos, tmp_vec, DirectX::XMLoadFloat3(&y_axis_vec)));

	if (DirectX::XMMatrixIsNaN(rot_mat)) {
		tmp_vec = DirectX::XMVectorAdd(tmp_vec, DirectX::XMVectorSet(0.0f, 0.0f, 0.0001f, 0.0f));
		rot_mat = DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixLookToLH(tmp_pos, tmp_vec, DirectX::XMLoadFloat3(&y_axis_vec)));
	}

	DirectX::XMStoreFloat4(&this->quaternion, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionRotationMatrix(rot_mat)));

	return;
}
