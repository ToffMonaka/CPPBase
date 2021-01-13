/**
 * @file
 * @brief ShaderConstantBuffer�R�[�h�t�@�C��
 */


#include "ShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ShaderConstantBufferDesc::ShaderConstantBufferDesc() :
	element_size(0U),
	cpu_flag(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ShaderConstantBufferDesc::~ShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ShaderConstantBufferDesc::Init(void)
{
	this->element_size = 0U;
	this->cpu_flag = false;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ShaderConstantBuffer::ShaderConstantBuffer() :
	buf_(nullptr),
	element_size_(0U),
	cpu_flg_(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ShaderConstantBuffer::~ShaderConstantBuffer()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::ShaderConstantBuffer::Release(void)
{
	if (this->buf_ != nullptr) {
		this->buf_->Release();

		this->buf_ = nullptr;
	}

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ShaderConstantBuffer::Init(void)
{
	this->element_size_ = 0U;
	this->cpu_flg_ = false;

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ShaderConstantBuffer::Create(tml::graphic::ShaderConstantBufferDesc &desc)
{
	if ((desc.element_size <= 0U)
	|| ((desc.element_size % 16) > 0)) {
		return (-1);
	}

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SHADER_CONSTANT_BUFFER, desc) < 0) {
		return (-1);
	}

	this->cpu_flg_ = desc.cpu_flag;

	this->element_size_ = desc.element_size;

	CD3D11_BUFFER_DESC buf_desc = CD3D11_BUFFER_DESC(this->element_size_, D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DEFAULT, 0U);

	if (this->cpu_flg_) {
		buf_desc.Usage = D3D11_USAGE_DYNAMIC;
		buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&buf_desc, nullptr, &this->buf_))) {
		return (-1);
	}

	return (0);
}


/**
 * @brief UpdateBuffer�֐�
 * @param element (element)
 */
void tml::graphic::ShaderConstantBuffer::UpdateBuffer(void *element)
{
	if (this->cpu_flg_) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->buf_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
			memcpy(msr.pData, element, this->element_size_);

			this->GetManager()->GetDeviceContext()->Unmap(this->buf_, 0U);
		}
	} else {
		this->GetManager()->GetDeviceContext()->UpdateSubresource(this->buf_, 0U, nullptr, element, 0U, 0U);
	}

	return;
}
