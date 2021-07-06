/**
 * @file
 * @brief Model2DShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "Model2DShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Model2DShaderStructuredBufferDesc::Model2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Model2DShaderStructuredBufferDesc::~Model2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Model2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Model2DShaderStructuredBuffer::Model2DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Model2DShaderStructuredBuffer::~Model2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Model2DShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Model2DShaderStructuredBuffer::Create(const tml::graphic::Model2DShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param w_mat (world_matrix)
 * @param v_mat (view_matrix)
 * @param p_mat (projection_matrix)
 * @param col (color)
 */
void tml::graphic::Model2DShaderStructuredBuffer::SetElement(const UINT index, const DirectX::XMMATRIX &w_mat, const DirectX::XMMATRIX &v_mat, const DirectX::XMMATRIX &p_mat, const tml::XMFLOAT4EX &col)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	DirectX::XMMATRIX wvp_mat = w_mat;

	wvp_mat *= v_mat;
	wvp_mat *= p_mat;

	DirectX::XMStoreFloat4x4(&element->world_view_projection_matrix, DirectX::XMMatrixTranspose(wvp_mat));
	element->color = col;

	return;
}
