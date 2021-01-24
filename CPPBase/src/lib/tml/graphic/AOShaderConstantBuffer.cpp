/**
 * @file
 * @brief AOShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "AOShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::AOShaderConstantBufferDesc::AOShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::AOShaderConstantBufferDesc::~AOShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::AOShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::AOShaderConstantBuffer::AOShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::AOShaderConstantBuffer::~AOShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::AOShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::AOShaderConstantBuffer::Init(void)
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
INT tml::graphic::AOShaderConstantBuffer::Create(const tml::graphic::AOShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::AOShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::AOShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief �v�f�Z�b�g�֐�
 * @param light_ssb_cnt �c���C�g�V�F�[�_�[�\�����o�b�t�@��
 */
/*
void tml::graphic::AOShaderConstantBuffer::SetElement(const UINT light_ssb_cnt)
{
	auto element = this->GetElement();

	element->light_ssb_cnt = light_ssb_cnt;

	return;
}
*/
