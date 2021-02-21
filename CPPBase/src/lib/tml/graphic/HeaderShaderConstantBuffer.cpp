/**
 * @file
 * @brief HeaderShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "HeaderShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::HeaderShaderConstantBufferDesc::HeaderShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::HeaderShaderConstantBufferDesc::~HeaderShaderConstantBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::HeaderShaderConstantBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::HeaderShaderConstantBuffer::HeaderShaderConstantBuffer() :
	element_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::HeaderShaderConstantBuffer::~HeaderShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::HeaderShaderConstantBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_);

	tml::graphic::ShaderConstantBuffer::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::HeaderShaderConstantBuffer::Init(void)
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
INT tml::graphic::HeaderShaderConstantBuffer::Create(const tml::graphic::HeaderShaderConstantBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderConstantBuffer::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ = tml::MemoryUtil::Get<tml::graphic::HeaderShaderConstantBuffer::ELEMENT>(1U);

	return (0);
}


/**
 * @brief SetElement�֐�
 * @param camera_cnt (camera_count)
 * @param light_cnt (light_count)
 * @param fog_cnt (fog_count)
 * @param model_cnt (model_count)
 */
void tml::graphic::HeaderShaderConstantBuffer::SetElement(const UINT camera_cnt, const UINT light_cnt, const UINT fog_cnt, const UINT model_cnt)
{
	auto element = this->GetElement();

	element->camera_count = camera_cnt;
	element->light_count = light_cnt;
	element->fog_count = fog_cnt;
	element->model_count = model_cnt;

	return;
}
