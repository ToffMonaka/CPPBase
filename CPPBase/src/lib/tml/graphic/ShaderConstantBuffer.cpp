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
	buffer_desc(0U, 0U),
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

	this->buffer_desc = CD3D11_BUFFER_DESC(0U, 0U);
	this->element_size = 0U;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ShaderConstantBufferDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// ShaderConstantBuffer Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SCB");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetBufferDesc関数
 * @param bind_flg (bind_flag)
 * @param element_size (element_size)
 * @param dynamic_flg (dynamic_flag)
 */
void tml::graphic::ShaderConstantBufferDesc::SetBufferDesc(const tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG bind_flg, const UINT element_size, const bool dynamic_flg)
{
	this->buffer_desc = CD3D11_BUFFER_DESC(element_size, 0U);

	if (static_cast<bool>(bind_flg & tml::ConstantUtil::GRAPHIC::SHADER_CONSTANT_BUFFER_DESC_BIND_FLAG::SR)) {
		this->buffer_desc.BindFlags |= D3D11_BIND_CONSTANT_BUFFER;
	}

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
	buf_desc_(0U, 0U),
	element_size_(0U),
	msr_{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ShaderConstantBuffer::~ShaderConstantBuffer()
{
	this->Release();

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

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ShaderConstantBuffer::Init(void)
{
	this->Release();

	this->buf_desc_ = CD3D11_BUFFER_DESC(0U, 0U);
	this->element_size_ = 0U;
	this->cpu_buf_.Init();
	tml::Clear(&this->msr_, 1U);

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ShaderConstantBuffer::Create(const tml::graphic::ShaderConstantBufferDesc &desc)
{
	if ((desc.element_size <= 0U)
	|| ((desc.element_size % 16U) > 0)) {
		return (-1);
	}

	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&desc.buffer_desc, nullptr, &this->buf_))) {
		return (-1);
	}

	this->buf_->GetDesc(&this->buf_desc_);
	this->element_size_ = desc.element_size;

	INT result = 0;

	this->GetManager()->GetCPUBuffer(this->cpu_buf_, this->msr_, this->buf_, &result);

	if (result < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief UploadCPUBuffer関数
 */
void tml::graphic::ShaderConstantBuffer::UploadCPUBuffer(void)
{
	if (this->cpu_buf_.GetLength() <= 0U) {
		return;
	}

	if (this->buf_desc_.Usage == D3D11_USAGE_DYNAMIC) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->buf_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
			if (msr.DepthPitch >= this->element_size_) {
				memcpy(msr.pData, this->cpu_buf_.Get(), this->element_size_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(this->buf_, 0U);
		}
	} else {
		this->GetManager()->GetDeviceContext()->UpdateSubresource(this->buf_, 0U, nullptr, this->cpu_buf_.Get(), 0U, 0U);
	}

	return;
}


/**
 * @brief DownloadCPUBuffer関数
 */
void tml::graphic::ShaderConstantBuffer::DownloadCPUBuffer(void)
{
	if (this->cpu_buf_.GetLength() <= 0U) {
		return;
	}

	ID3D11Buffer *tmp_buf = nullptr;
	CD3D11_BUFFER_DESC tmp_buf_desc = this->buf_desc_;

	tmp_buf_desc.BindFlags = 0U;
	tmp_buf_desc.Usage = D3D11_USAGE_STAGING;
	tmp_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	tmp_buf_desc.MiscFlags = 0U;

	if (SUCCEEDED(this->GetManager()->GetDevice()->CreateBuffer(&tmp_buf_desc, nullptr, &tmp_buf))) {
		this->GetManager()->GetDeviceContext()->CopyResource(tmp_buf, this->buf_);

		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(tmp_buf, 0U, D3D11_MAP_READ, 0U, &msr))) {
			if (msr.DepthPitch >= this->element_size_) {
				memcpy(this->cpu_buf_.Get(), msr.pData, this->element_size_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(tmp_buf, 0U);
		}

		tmp_buf->Release();
	}

	return;
}
