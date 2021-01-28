/**
 * @file
 * @brief SystemShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "SystemShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::SystemShaderConstantBufferDesc::SystemShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::SystemShaderConstantBufferDesc::~SystemShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::SystemShaderConstantBufferDesc::Init(void)
{
	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::SystemShaderConstantBuffer::SystemShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::SystemShaderConstantBuffer::~SystemShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::SystemShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::SystemShaderConstantBuffer::Init(void)
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
INT tml::graphic::SystemShaderConstantBuffer::Create(const tml::graphic::SystemShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc, sizeof(tml::graphic::SystemShaderConstantBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::SystemShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief SetElement�֐�
 * @param light_cnt (light_count)
 * @param fog_cnt (fog_count)
 */
void tml::graphic::SystemShaderConstantBuffer::SetElement(const UINT light_cnt, const UINT fog_cnt)
{
	auto element = this->GetElement();

	element->light_count = light_cnt;
	element->fog_count = fog_cnt;

	return;
}
