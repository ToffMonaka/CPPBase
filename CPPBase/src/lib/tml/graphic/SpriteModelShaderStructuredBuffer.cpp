/**
 * @file
 * @brief SpriteModelShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "SpriteModelShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::SpriteModelShaderStructuredBufferDesc::SpriteModelShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::SpriteModelShaderStructuredBufferDesc::~SpriteModelShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::SpriteModelShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::SpriteModelShaderStructuredBuffer::SpriteModelShaderStructuredBuffer()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::SpriteModelShaderStructuredBuffer::~SpriteModelShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::SpriteModelShaderStructuredBuffer::Init(void)
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
INT tml::graphic::SpriteModelShaderStructuredBuffer::Create(const tml::graphic::SpriteModelShaderStructuredBufferDesc &desc)
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
void tml::graphic::SpriteModelShaderStructuredBuffer::SetElement(const UINT index, const XMMATRIX &w_mat, const XMMATRIX &p_mat, const tml::XMFLOAT4EX &col)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	XMMATRIX wp_mat = w_mat * p_mat;

	XMStoreFloat4x4(&element->world_projection_matrix, XMMatrixTranspose(wp_mat));
	element->color = col;

	return;
}
