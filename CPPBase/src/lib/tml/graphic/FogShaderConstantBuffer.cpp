/**
 * @file
 * @brief FogShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "FogShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FogShaderConstantBufferDesc::FogShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FogShaderConstantBufferDesc::~FogShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::FogShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FogShaderConstantBuffer::FogShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FogShaderConstantBuffer::~FogShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::FogShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::FogShaderConstantBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBuffer::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::FogShaderConstantBuffer::Create(const tml::graphic::FogShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::FogShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::FogShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief �v�f�Z�b�g�֐�
 * @param light_ssb_cnt �c���C�g�V�F�[�_�[�\�����o�b�t�@��
 */
/*
void tml::graphic::FogShaderConstantBuffer::SetElement(const UINT light_ssb_cnt)
{
	auto element = this->GetElement();

	element->light_ssb_cnt = light_ssb_cnt;

	return;
}
*/
