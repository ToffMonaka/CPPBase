/**
 * @file
 * @brief CameraShaderStructuredBufferコードファイル
 */


#include "CameraShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::CameraShaderStructuredBufferDesc::CameraShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::CameraShaderStructuredBufferDesc::~CameraShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::CameraShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::CameraShaderStructuredBuffer::CameraShaderStructuredBuffer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::CameraShaderStructuredBuffer::~CameraShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::CameraShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::CameraShaderStructuredBuffer::Create(const tml::graphic::CameraShaderStructuredBufferDesc &desc)
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
 * @param camera (camera)
 * @param v_mat (view_matrix)
 * @param inv_v_mat (inverse_view_matrix)
 * @param p_mat (projection_matrix)
 */
void tml::graphic::CameraShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Camera *camera, const XMMATRIX &v_mat, const XMMATRIX &inv_v_mat, const XMMATRIX &p_mat)
{
	auto element = this->GetElement(index);

	if (element == nullptr) {
		return;
	}

	XMStoreFloat4x4(&element->view_matrix, XMMatrixTranspose(v_mat));
	XMStoreFloat4x4(&element->inverse_view_matrix, XMMatrixTranspose(inv_v_mat));
	XMStoreFloat4x4(&element->projection_matrix, XMMatrixTranspose(p_mat));

	return;
}
