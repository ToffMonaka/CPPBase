/**
 * @file
 * @brief ModelShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "ModelShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelShaderConstantBufferDesc::ModelShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelShaderConstantBufferDesc::~ModelShaderConstantBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelShaderConstantBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelShaderConstantBuffer::ModelShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelShaderConstantBuffer::~ModelShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::ModelShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelShaderConstantBuffer::Init(void)
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
INT tml::graphic::ModelShaderConstantBuffer::Create(const tml::graphic::ModelShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::ModelShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::ModelShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief �v�f�Z�b�g�֐�
 * @param light_ssb_cnt �c���C�g�V�F�[�_�[�\�����o�b�t�@��
 */
/*
void tml::graphic::ModelShaderConstantBuffer::SetElement(const UINT light_ssb_cnt)
{
	auto element = this->GetElement();

	element->light_ssb_cnt = light_ssb_cnt;

	return;
}
*/
