/**
 * @file
 * @brief CommonShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "CommonShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::CommonShaderConstantBufferDesc::CommonShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::CommonShaderConstantBufferDesc::~CommonShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::CommonShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::CommonShaderConstantBuffer::CommonShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::CommonShaderConstantBuffer::~CommonShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::CommonShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::CommonShaderConstantBuffer::Init(void)
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
INT tml::graphic::CommonShaderConstantBuffer::Create(const tml::graphic::CommonShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::CommonShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::CommonShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief �v�f�Z�b�g�֐�
 * @param common_ssb_cnt �c���C�g�V�F�[�_�[�\�����o�b�t�@��
 */
/*
void tml::graphic::CommonShaderConstantBuffer::SetElement(const UINT common_ssb_cnt)
{
	auto element = this->GetElement();

	element->common_ssb_cnt = common_ssb_cnt;

	return;
}
*/
