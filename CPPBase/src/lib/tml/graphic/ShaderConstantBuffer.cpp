/**
 * @file
 * @brief ShaderConstantBufferコードファイル
 */


#include "ShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ShaderConstantBufferDesc::ShaderConstantBufferDesc() :
	buffer_desc(0U, D3D11_BIND_CONSTANT_BUFFER),
	element_size(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ShaderConstantBufferDesc::~ShaderConstantBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ShaderConstantBufferDesc::Init(void)
{
	this->Release();

	this->buffer_desc = CD3D11_BUFFER_DESC(0U, D3D11_BIND_CONSTANT_BUFFER);
	this->element_size = 0U;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ShaderConstantBufferDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// ShaderConstantBuffer Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SCB");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetBufferDesc関数
 * @param element_size (element_size)
 * @param dynamic_flg (dynamic_flag)
 */
void tml::graphic::ShaderConstantBufferDesc::SetBufferDesc(const UINT element_size, const bool dynamic_flg)
{
	this->buffer_desc = CD3D11_BUFFER_DESC(element_size, D3D11_BIND_CONSTANT_BUFFER);

	if (dynamic_flg) {
		this->buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		this->buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	this->element_size = element_size;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ShaderConstantBuffer::ShaderConstantBuffer() :
	buf_(nullptr),
	buf_desc_(0U, D3D11_BIND_CONSTANT_BUFFER),
	element_size_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ShaderConstantBuffer::~ShaderConstantBuffer()
{
	return;
}


/**
 * @brief Release関数
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
 * @brief Init関数
 */
void tml::graphic::ShaderConstantBuffer::Init(void)
{
	this->buf_desc_ = CD3D11_BUFFER_DESC(0U, D3D11_BIND_CONSTANT_BUFFER);
	this->element_size_ = 0U;

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ShaderConstantBuffer::Create(const tml::graphic::ShaderConstantBufferDesc &desc)
{
	if ((desc.element_size <= 0U)
	|| ((desc.element_size % 16) > 0)) {
		return (-1);
	}

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SHADER_CONSTANT_BUFFER) < 0) {
		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&desc.buffer_desc, nullptr, &this->buf_))) {
		return (-1);
	}

	this->buf_->GetDesc(&this->buf_desc_);
	this->element_size_ = desc.element_size;

	return (0);
}


/**
 * @brief UploadCPUBuffer関数
 * @param cpu_buf (cpu_buffer)
 */
void tml::graphic::ShaderConstantBuffer::UploadCPUBuffer(BYTE *cpu_buf)
{
	if (this->buf_desc_.Usage == D3D11_USAGE_DYNAMIC) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->buf_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
			memcpy(msr.pData, cpu_buf, this->element_size_);

			this->GetManager()->GetDeviceContext()->Unmap(this->buf_, 0U);
		}
	} else {
		this->GetManager()->GetDeviceContext()->UpdateSubresource(this->buf_, 0U, nullptr, cpu_buf, 0U, 0U);
	}

	return;
}


/**
 * @brief DownloadCPUBuffer関数
 * @param cpu_buf (cpu_buffer)
 */
void tml::graphic::ShaderConstantBuffer::DownloadCPUBuffer(BYTE *cpu_buf)
{
	return;
}
