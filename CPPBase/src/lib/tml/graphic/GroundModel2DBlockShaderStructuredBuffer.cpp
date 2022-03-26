/**
 * @file
 * @brief GroundModel2DBlockShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "GroundModel2DBlockShaderStructuredBuffer.h"
#include "Manager.h"
#include "GroundModel2D.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc::GroundModel2DBlockShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc::~GroundModel2DBlockShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::GroundModel2DBlockShaderStructuredBuffer::GroundModel2DBlockShaderStructuredBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::GroundModel2DBlockShaderStructuredBuffer::~GroundModel2DBlockShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::GroundModel2DBlockShaderStructuredBuffer::Init(void)
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
INT tml::graphic::GroundModel2DBlockShaderStructuredBuffer::OnCreate(void)
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
INT tml::graphic::GroundModel2DBlockShaderStructuredBuffer::OnCreateDeferred(void)
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
void tml::graphic::GroundModel2DBlockShaderStructuredBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc *>(desc);

	tml::graphic::ShaderStructuredBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement�֐�
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
