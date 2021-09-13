/**
 * @file
 * @brief GroundModel2DShaderStructuredBufferコードファイル
 */


#include "GroundModel2DShaderStructuredBuffer.h"
#include "Manager.h"
#include "GroundModel2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DShaderStructuredBufferDesc::GroundModel2DShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DShaderStructuredBufferDesc::~GroundModel2DShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DShaderStructuredBuffer::GroundModel2DShaderStructuredBuffer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DShaderStructuredBuffer::~GroundModel2DShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DShaderStructuredBuffer::Init(void)
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
INT tml::graphic::GroundModel2DShaderStructuredBuffer::Create(const tml::graphic::GroundModel2DShaderStructuredBufferDesc &desc)
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
 * @param w_mat (world_matrix)
 * @param v_mat (view_matrix)
 * @param p_mat (projection_matrix)
 * @param col (color)
 * @param tileset_tile_cnt (tileset_tile_count)
 */
void tml::graphic::GroundModel2DShaderStructuredBuffer::SetElement(const UINT index, const DirectX::XMMATRIX &w_mat, const DirectX::XMMATRIX &v_mat, const DirectX::XMMATRIX &p_mat, const tml::XMFLOAT4EX &col, const tml::XMUINT2EX &tileset_tile_cnt)
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
	element->tileset_tile_count = tileset_tile_cnt;

	return;
}
