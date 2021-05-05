/**
 * @file
 * @brief Object2DModelShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "Object2DModelShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Object2DModelShaderStructuredBufferDesc::Object2DModelShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Object2DModelShaderStructuredBufferDesc::~Object2DModelShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Object2DModelShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Object2DModelShaderStructuredBuffer::Object2DModelShaderStructuredBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Object2DModelShaderStructuredBuffer::~Object2DModelShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Object2DModelShaderStructuredBuffer::Init(void)
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
INT tml::graphic::Object2DModelShaderStructuredBuffer::Create(const tml::graphic::Object2DModelShaderStructuredBufferDesc &desc)
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
 * @param p_mat (projection_matrix)
 * @param col (color)
 */
void tml::graphic::Object2DModelShaderStructuredBuffer::SetElement(const UINT index, const DirectX::XMMATRIX &w_mat, const DirectX::XMMATRIX &p_mat, const tml::XMFLOAT4EX &col)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	DirectX::XMMATRIX wp_mat = w_mat * p_mat;

	DirectX::XMStoreFloat4x4(&element->world_projection_matrix, DirectX::XMMatrixTranspose(wp_mat));
	element->color = col;

	return;
}
