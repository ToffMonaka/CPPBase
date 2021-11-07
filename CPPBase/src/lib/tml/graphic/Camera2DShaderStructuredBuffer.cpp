/**
 * @file
 * @brief Camera2DShaderStructuredBufferコードファイル
 */


#include "Camera2DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Camera2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Camera2DShaderStructuredBufferDesc::Camera2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera2DShaderStructuredBufferDesc::~Camera2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Camera2DShaderStructuredBuffer::Camera2DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera2DShaderStructuredBuffer::~Camera2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera2DShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Camera2DShaderStructuredBuffer::Create(const tml::graphic::Camera2DShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief SetElement関数
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
