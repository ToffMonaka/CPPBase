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
tml::graphic::GroundModel2DBlockShaderStructuredBuffer::GroundModel2DBlockShaderStructuredBuffer()
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
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::GroundModel2DBlockShaderStructuredBuffer::Create(const tml::graphic::GroundModel2DBlockShaderStructuredBufferDesc &desc)
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
 * @param block_cont (block_container)
 */
void tml::graphic::GroundModel2DBlockShaderStructuredBuffer::SetElement(const UINT index, const std::vector<tml::graphic::GroundModel2DBlock> &block_cont)
{
	for (UINT block_i = 0U; block_i < block_cont.size(); ++block_i) {
		auto element = this->GetElement(index + block_i);

		if (element == nullptr) {
			break;
		}

		auto &block = block_cont[block_i];

		element->tile_count = block.tile_count;
		tml::Copy(element->tile_type_array, block.tile_type_container.data(), block.tile_type_container.size());
	}

	return;
}
