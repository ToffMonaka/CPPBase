/**
 * @file
 * @brief FigureModel2DShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "FigureModel2DShaderStructuredBuffer.h"
#include "Manager.h"
#include "FigureModel2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FigureModel2DShaderStructuredBufferDesc::FigureModel2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FigureModel2DShaderStructuredBufferDesc::~FigureModel2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::FigureModel2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FigureModel2DShaderStructuredBuffer::FigureModel2DShaderStructuredBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FigureModel2DShaderStructuredBuffer::~FigureModel2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::FigureModel2DShaderStructuredBuffer::Init(void)
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
INT tml::graphic::FigureModel2DShaderStructuredBuffer::OnCreate(void)
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
INT tml::graphic::FigureModel2DShaderStructuredBuffer::OnCreateDeferred(void)
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
void tml::graphic::FigureModel2DShaderStructuredBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::FigureModel2DShaderStructuredBufferDesc *>(desc);

	tml::graphic::ShaderStructuredBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement�֐�
 * @param index (index)
 * @param w_mat (world_matrix)
 * @param v_mat (view_matrix)
 * @param p_mat (projection_matrix)
 * @param col (color)
 */
void tml::graphic::FigureModel2DShaderStructuredBuffer::SetElement(const UINT index, const DirectX::XMMATRIX &w_mat, const DirectX::XMMATRIX &v_mat, const DirectX::XMMATRIX &p_mat, const tml::XMFLOAT4EX &col)
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
