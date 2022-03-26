/**
 * @file
 * @brief Camera2DShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "Camera2DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Camera2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Camera2DShaderStructuredBufferDesc::Camera2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Camera2DShaderStructuredBufferDesc::~Camera2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Camera2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Camera2DShaderStructuredBuffer::Camera2DShaderStructuredBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Camera2DShaderStructuredBuffer::~Camera2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Camera2DShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Camera2DShaderStructuredBuffer::OnCreate(void)
{
	if (tml::graphic::ShaderStructuredBuffer::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Camera2DShaderStructuredBuffer::OnCreateDeferred(void)
{
	if (tml::graphic::ShaderStructuredBuffer::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::graphic::Camera2DShaderStructuredBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::Camera2DShaderStructuredBufferDesc *>(desc);

	tml::graphic::ShaderStructuredBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param v_mat (view_matrix)
 * @param inv_v_mat (inverse_view_matrix)
 * @param p_mat (projection_matrix)
 */
void tml::graphic::Camera2DShaderStructuredBuffer::SetElement(const UINT index, const DirectX::XMMATRIX &v_mat, const DirectX::XMMATRIX &inv_v_mat, const DirectX::XMMATRIX &p_mat)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	DirectX::XMStoreFloat4x4(&element->view_matrix, DirectX::XMMatrixTranspose(v_mat));
	DirectX::XMStoreFloat4x4(&element->inverse_view_matrix, DirectX::XMMatrixTranspose(inv_v_mat));
	DirectX::XMStoreFloat4x4(&element->projection_matrix, DirectX::XMMatrixTranspose(p_mat));

	return;
}
