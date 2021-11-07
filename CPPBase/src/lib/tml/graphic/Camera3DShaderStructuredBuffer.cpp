/**
 * @file
 * @brief Camera3DShaderStructuredBufferコードファイル
 */


#include "Camera3DShaderStructuredBuffer.h"
#include "Manager.h"
#include "Camera3D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::Camera3DShaderStructuredBufferDesc::Camera3DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera3DShaderStructuredBufferDesc::~Camera3DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera3DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Camera3DShaderStructuredBuffer::Camera3DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Camera3DShaderStructuredBuffer::~Camera3DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Camera3DShaderStructuredBuffer::Init(void)
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
INT tml::graphic::Camera3DShaderStructuredBuffer::Create(const tml::graphic::Camera3DShaderStructuredBufferDesc &desc)
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
void tml::graphic::Camera3DShaderStructuredBuffer::SetElement(const UINT index, const DirectX::XMMATRIX &v_mat, const DirectX::XMMATRIX &inv_v_mat, const DirectX::XMMATRIX &p_mat)
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
