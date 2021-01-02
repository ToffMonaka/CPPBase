/**
 * @file
 * @brief ShaderStructuredBufferコードファイル
 */


#include "ShaderStructuredBuffer.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::ShaderStructuredBufferDesc::ShaderStructuredBufferDesc() :
	element_size(0U),
	element_limit(0U),
	cpu_flag(false),
	uasr_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ShaderStructuredBufferDesc::~ShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ShaderStructuredBufferDesc::Init(void)
{
	this->element_size = 0U;
	this->element_limit = 0U;
	this->cpu_flag = false;
	this->uasr_flag = false;

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::ShaderStructuredBuffer::ShaderStructuredBuffer() :
	buf_(nullptr),
	sr_(nullptr),
	uasr_(nullptr),
	element_size_(0U),
	element_limit_(0U),
	element_cnt_(0U),
	cpu_flg_(false),
	uasr_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ShaderStructuredBuffer::~ShaderStructuredBuffer()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::ShaderStructuredBuffer::Release(void)
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

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::ShaderStructuredBuffer::Init(void)
{
	this->element_size_ = 0U;
	this->element_limit_ = 0U;
	this->element_cnt_ = 0U;
	this->cpu_flg_ = false;
	this->uasr_flg_ = false;

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ShaderStructuredBuffer::Create(const tml::ShaderStructuredBufferDesc &desc)
{
	if (((this->element_size_ * this->element_limit_) <= 0U)
	|| ((desc.element_size % 16) > 0)) {
		return (-1);
	}

	if (tml::GraphicResource::Create(desc) < 0) {
		return (-1);
	}

	this->element_size_ = desc.element_size;
	this->element_limit_ = desc.element_limit;
	this->cpu_flg_ = desc.cpu_flag;
	this->uasr_flg_ = desc.uasr_flag;

	if (!this->uasr_flg_) {
		CD3D11_BUFFER_DESC buf_desc = CD3D11_BUFFER_DESC(this->element_size_ * this->element_limit_, D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_DEFAULT, 0U, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, this->element_size_);

		if (this->cpu_flg_) {
			buf_desc.Usage = D3D11_USAGE_DYNAMIC;
			buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&buf_desc, nullptr, &this->buf_))) {
			return (-1);
		}

		CD3D11_SHADER_RESOURCE_VIEW_DESC sr_desc = CD3D11_SHADER_RESOURCE_VIEW_DESC(D3D11_SRV_DIMENSION_BUFFER, DXGI_FORMAT_UNKNOWN, 0U, this->element_limit_);

		if (FAILED(this->GetManager()->GetDevice()->CreateShaderResourceView(this->buf_, &sr_desc, &this->sr_))) {
			return (-1);
		}

		this->element_cnt_ = 0U;
	} else {
		CD3D11_BUFFER_DESC buf_desc = CD3D11_BUFFER_DESC(this->element_size_ * this->element_limit_, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, D3D11_USAGE_DEFAULT, 0U, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, this->element_size_);

		if (FAILED(this->GetManager()->GetDevice()->CreateBuffer(&buf_desc, nullptr, &this->buf_))) {
			return (-1);
		}

		CD3D11_SHADER_RESOURCE_VIEW_DESC sr_desc = CD3D11_SHADER_RESOURCE_VIEW_DESC(D3D11_SRV_DIMENSION_BUFFER, DXGI_FORMAT_UNKNOWN, 0U, this->element_limit_);

		if (FAILED(this->GetManager()->GetDevice()->CreateShaderResourceView(this->buf_, &sr_desc, &this->sr_))) {
			return (-1);
		}

		CD3D11_UNORDERED_ACCESS_VIEW_DESC uasr_desc = CD3D11_UNORDERED_ACCESS_VIEW_DESC(D3D11_UAV_DIMENSION_BUFFER, DXGI_FORMAT_UNKNOWN, 0U, this->element_limit_);

		if (FAILED(this->GetManager()->GetDevice()->CreateUnorderedAccessView(this->buf_, &uasr_desc, &this->uasr_))) {
			return (-1);
		}

		this->element_cnt_ = this->element_limit_;
	}

	return (0);
}


/**
 * @brief Update関数
 * @param element_ary (element_array)
 */
void tml::ShaderStructuredBuffer::Update(void *element_ary)
{
	if (this->element_cnt_ <= 0U) {
		return;
	}

	if (!this->uasr_flg_) {
		if (this->cpu_flg_) {
			D3D11_MAPPED_SUBRESOURCE msr;

			if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->buf_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
				memcpy(msr.pData, element_ary, this->element_size_ * this->element_cnt_);

				this->GetManager()->GetDeviceContext()->Unmap(this->buf_, 0U);
			}
		} else {
			CD3D11_BOX box = CD3D11_BOX(0L, 0L, 0L, this->element_size_ * this->element_cnt_, 1L, 1L);

			this->GetManager()->GetDeviceContext()->UpdateSubresource(this->buf_, 0U, &box, element_ary, 0U, 0U);
		}
	} else {
		ID3D11Buffer *cpu_buf = nullptr;
		D3D11_BUFFER_DESC cpu_buf_desc;

		this->buf_->GetDesc(&cpu_buf_desc);

		cpu_buf_desc.Usage = D3D11_USAGE_STAGING;
		cpu_buf_desc.BindFlags = 0U;
		cpu_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		cpu_buf_desc.MiscFlags = 0U;

		if (SUCCEEDED(this->GetManager()->GetDevice()->CreateBuffer(&cpu_buf_desc, nullptr, &cpu_buf))) {
			this->GetManager()->GetDeviceContext()->CopyResource(cpu_buf, this->buf_);

			D3D11_MAPPED_SUBRESOURCE msr;

			if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(cpu_buf, 0U, D3D11_MAP_READ, 0U, &msr))) {
				if ((msr.DepthPitch >= (this->element_size_ * this->element_cnt_))
				&& (msr.DepthPitch <= (this->element_size_ * this->element_limit_))) {
					memcpy(static_cast<BYTE *>(element_ary), static_cast<BYTE *>(msr.pData), this->element_size_ * this->element_cnt_);
				}

				this->GetManager()->GetDeviceContext()->Unmap(cpu_buf, 0U);
			}

			cpu_buf->Release();
		}
	}

	return;
}
