/**
 * @file
 * @brief GroundModel2DBlockShaderStructuredBufferコードファイル
 */


#include "GroundModel2DBlockShaderStructuredBuffer.h"
#include "Manager.h"
#include "GroundModel2D.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc::GroundModel2DBlockShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc::~GroundModel2DBlockShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::GroundModel2DBlockShaderStructuredBuffer::GroundModel2DBlockShaderStructuredBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::GroundModel2DBlockShaderStructuredBuffer::~GroundModel2DBlockShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::GroundModel2DBlockShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2DBlockShaderStructuredBuffer::OnCreate(void)
{
	if (tml::graphic::ShaderStructuredBuffer::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::GroundModel2DBlockShaderStructuredBuffer::OnCreateDeferred(void)
{
	if (tml::graphic::ShaderStructuredBuffer::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::GroundModel2DBlockShaderStructuredBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc *>(desc);

	tml::graphic::ShaderStructuredBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement関数
 * @param index (index)
 * @param map (map)
 */
void tml::graphic::GroundModel2DBlockShaderStructuredBuffer::SetElement(const UINT index, const tml::graphic::Map *map)
{
	for (UINT block_i = 0U, block_end_i = map->GetBlockCount().x * map->GetBlockCount().y; block_i < block_end_i; ++block_i) {
		auto element = this->GetElement(index + block_i);

		if (element == nullptr) {
			break;
		}

		auto &block = map->GetBlockArray()[block_i];

		element->tile_count = block.GetTileCount();
		tml::Copy(element->tile_type_array, block.GetTileTypeArray(), block.GetTileCount().x * block.GetTileCount().y);
	}

	return;
}
