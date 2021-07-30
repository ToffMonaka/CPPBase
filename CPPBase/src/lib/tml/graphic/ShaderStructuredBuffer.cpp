/**
 * @file
 * @brief ShaderStructuredBufferコードファイル
 */


#include "ShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ShaderStructuredBufferDesc::ShaderStructuredBufferDesc() :
	buffer_desc(0U, 0U),
	element_size(0U),
	element_limit(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ShaderStructuredBufferDesc::~ShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	this->buffer_desc = CD3D11_BUFFER_DESC(0U, 0U);
	this->element_size = 0U;
	this->element_limit = 0U;

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ShaderStructuredBufferDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// ShaderStructuredBuffer Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SSB");

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
 * @param element_limit (element_limit)
 * @param dynamic_flg (dynamic_flag)
 */
void tml::graphic::ShaderStructuredBufferDesc::SetBufferDesc(const tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG bind_flg, const UINT element_size, const UINT element_limit, const bool dynamic_flg)
{
	this->buffer_desc = CD3D11_BUFFER_DESC(element_size * element_limit, 0U, D3D11_USAGE_DEFAULT, 0U, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, element_size);

	if (static_cast<bool>(bind_flg & tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::SR)) {
		this->buffer_desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	}

	if (static_cast<bool>(bind_flg & tml::ConstantUtil::GRAPHIC::SHADER_STRUCTURED_BUFFER_DESC_BIND_FLAG::UASR)) {
		this->buffer_desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	}

	if (dynamic_flg) {
		this->buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		this->buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	this->element_size = element_size;
	this->element_limit = element_limit;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ShaderStructuredBuffer::ShaderStructuredBuffer() :
	buf_(nullptr),
	buf_desc_(0U, 0U),
	element_size_(0U),
	element_limit_(0U),
	element_cnt_(0U),
	msr_{},
	sr_(nullptr),
	uasr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ShaderStructuredBuffer::~ShaderStructuredBuffer()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ShaderStructuredBuffer::Release(void)
{
	if (this->uasr_ != nullptr) {
		this->uasr_->Release();

		this->uasr_ = nullptr;
	}

	if (this->sr_ != nullptr) {
		this->sr_->Release();

		this->sr_ = nullptr;
	}

	if (this->buf_ != nullptr) {
		this->buf_->Release();

		this->buf_ = nullptr;
	}

	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ShaderStructuredBuffer::Init(void)
{
	this->buf_desc_ = CD3D11_BUFFER_DESC(0U, 0U);
	this->element_size_ = 0U;
	this->element_limit_ = 0U;
	this->element_cnt_ = 0U;
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
INT tml::graphic::ShaderStructuredBuffer::Create(const tml::graphic::ShaderStructuredBufferDesc &desc)
{
	if (((desc.element_size * desc.element_limit) <= 0U)
	|| ((desc.element_size % 16) > 0)) {
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
	this->element_limit_ = desc.element_limit;

	INT result = 0;

	this->GetManager()->GetCPUBuffer(this->cpu_buf_, this->msr_, this->buf_, &result);

	if (result < 0) {
		return (-1);
	}

	if (this->buf_desc_.BindFlags & D3D11_BIND_SHADER_RESOURCE) {
		CD3D11_SHADER_RESOURCE_VIEW_DESC sr_desc = CD3D11_SHADER_RESOURCE_VIEW_DESC(D3D11_SRV_DIMENSION_BUFFER, DXGI_FORMAT_UNKNOWN, 0U, this->element_limit_);

		if (FAILED(this->GetManager()->GetDevice()->CreateShaderResourceView(this->buf_, &sr_desc, &this->sr_))) {
			return (-1);
		}
	}

	if (this->buf_desc_.BindFlags & D3D11_BIND_UNORDERED_ACCESS) {
		CD3D11_UNORDERED_ACCESS_VIEW_DESC uasr_desc = CD3D11_UNORDERED_ACCESS_VIEW_DESC(D3D11_UAV_DIMENSION_BUFFER, DXGI_FORMAT_UNKNOWN, 0U, this->element_limit_);

		if (FAILED(this->GetManager()->GetDevice()->CreateUnorderedAccessView(this->buf_, &uasr_desc, &this->uasr_))) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief UploadCPUBuffer関数
 */
void tml::graphic::ShaderStructuredBuffer::UploadCPUBuffer(void)
{
	if ((this->cpu_buf_.GetLength() <= 0U)
	|| (this->element_cnt_ <= 0U)) {
		return;
	}

	if (this->buf_desc_.Usage == D3D11_USAGE_DYNAMIC) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->buf_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
			if (msr.DepthPitch >= (this->element_size_ * this->element_cnt_)) {
				memcpy(msr.pData, this->cpu_buf_.Get(), this->element_size_ * this->element_cnt_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(this->buf_, 0U);
		}
	} else {
		CD3D11_BOX box(0L, 0L, 0L, this->element_size_ * this->element_cnt_, 1L, 1L);

		this->GetManager()->GetDeviceContext()->UpdateSubresource(this->buf_, 0U, &box, this->cpu_buf_.Get(), 0U, 0U);
	}

	return;
}


/**
 * @brief DownloadCPUBuffer関数
 */
void tml::graphic::ShaderStructuredBuffer::DownloadCPUBuffer(void)
{
	if ((this->cpu_buf_.GetLength() <= 0U)
	|| (this->element_cnt_ <= 0U)) {
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
			if (msr.DepthPitch >= (this->element_size_ * this->element_cnt_)) {
				memcpy(this->cpu_buf_.Get(), msr.pData, this->element_size_ * this->element_cnt_);
			}

			this->GetManager()->GetDeviceContext()->Unmap(tmp_buf, 0U);
		}

		tmp_buf->Release();
	}

	return;
}
