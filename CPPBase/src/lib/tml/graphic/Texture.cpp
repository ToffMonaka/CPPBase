/**
 * @file
 * @brief Textureコードファイル
 */


#include "Texture.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::TextureDesc::TextureDesc() :
	texture_desc(DXGI_FORMAT_UNKNOWN, 0U, 0U),
	render_target_format(DXGI_FORMAT_UNKNOWN),
	render_target_desc_null_flag(false),
	depth_target_format(DXGI_FORMAT_UNKNOWN),
	depth_target_desc_null_flag(false),
	sr_format(DXGI_FORMAT_UNKNOWN),
	sr_desc_null_flag(false),
	uasr_format(DXGI_FORMAT_UNKNOWN),
	uasr_desc_null_flag(false),
	swap_chain_flag(false),
	array_flag(false)
{
	this->texture_desc.BindFlags = 0U;

	return;
}


/**
 * @brief デストラクタ
 */
tml::TextureDesc::~TextureDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::TextureDesc::Init(void)
{
	this->file_read_desc_container.clear();
	this->texture_desc = CD3D11_TEXTURE2D_DESC(DXGI_FORMAT_UNKNOWN, 0U, 0U);
	this->texture_desc.BindFlags = 0U;
	this->render_target_format = DXGI_FORMAT_UNKNOWN;
	this->render_target_desc_null_flag = false;
	this->depth_target_format = DXGI_FORMAT_UNKNOWN;
	this->depth_target_desc_null_flag = false;
	this->sr_format = DXGI_FORMAT_UNKNOWN;
	this->sr_desc_null_flag = false;
	this->uasr_format = DXGI_FORMAT_UNKNOWN;
	this->uasr_desc_null_flag = false;
	this->swap_chain_flag = false;
	this->array_flag = false;

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Texture::Texture() :
	tex_(nullptr),
	size_(0.0f, 0.0f),
	rt_(nullptr),
	dt_(nullptr),
	sr_(nullptr),
	uasr_(nullptr),
	swap_chain_flg_(false),
	ary_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Texture::~Texture()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Texture::Release(void)
{
	if (this->uasr_ != nullptr) {
		this->uasr_->Release();

		this->uasr_ = nullptr;
	}

	if (this->sr_ != nullptr) {
		this->sr_->Release();

		this->sr_ = nullptr;
	}

	if (this->dt_ != nullptr) {
		this->dt_->Release();

		this->dt_ = nullptr;
	}

	if (this->rt_ != nullptr) {
		this->rt_->Release();

		this->rt_ = nullptr;
	}

	if (this->tex_ != nullptr) {
		this->tex_->Release();

		this->tex_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Texture::Init(void)
{
	this->Release();

	this->size_ = 0.0f;
	this->swap_chain_flg_ = false;
	this->ary_flg_ = false;

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Texture::Create(tml::TextureDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->swap_chain_flg_ = desc.swap_chain_flag;
	this->ary_flg_ = desc.array_flag;

	if (this->swap_chain_flg_) {
		if (FAILED(this->GetManager()->GetSwapChain()->GetBuffer(0U, IID_PPV_ARGS(&this->tex_)))) {
			this->Init();

			return (-1);
		}
	} else if (this->ary_flg_) {
		if (desc.file_read_desc_container.empty()) {
			this->Init();

			return (-1);
		}

		desc.texture_desc.ArraySize = desc.file_read_desc_container.size();

		std::list<D3D11_SUBRESOURCE_DATA> srd_cont;
		std::list<tml::DynamicBuffer> srd_buf_cont;
		ID3D11Texture2D *tex = nullptr;
		CD3D11_TEXTURE2D_DESC tex_desc;
		bool tex_desc_fixed_flg = false;

		for (auto &file_read_desc : desc.file_read_desc_container) {
			auto file_read_desc_dat = file_read_desc.GetDataByParent();

			if (!file_read_desc_dat->file_path.empty() || file_read_desc_dat->file_buffer.GetLength() > 0U) {
				tml::BinaryFile bin_file;

				bin_file.read_desc.parent_data = file_read_desc_dat;

				if (bin_file.Read()) {
					this->Init();

					return (-1);
				}

				if (bin_file.data.file_buffer.GetSize() <= 0U) {
					this->Init();

					return (-1);
				}

				D3DX11_IMAGE_LOAD_INFO img_load_info;

				img_load_info.Width = (desc.texture_desc.Width <= 0U) ? D3DX11_DEFAULT : desc.texture_desc.Width;
				img_load_info.Height = (desc.texture_desc.Height <= 0U) ? D3DX11_DEFAULT : desc.texture_desc.Height;
				img_load_info.FirstMipLevel = 0U;
				img_load_info.MipLevels = desc.texture_desc.MipLevels;
				img_load_info.Usage = static_cast<D3D11_USAGE>(D3DX11_DEFAULT);
				img_load_info.BindFlags = D3DX11_DEFAULT;
				img_load_info.CpuAccessFlags = D3DX11_DEFAULT;
				img_load_info.Format = (desc.texture_desc.Format == DXGI_FORMAT_UNKNOWN) ? DXGI_FORMAT_FROM_FILE : desc.texture_desc.Format;

				if (FAILED(D3DX11CreateTextureFromMemory(this->GetManager()->GetDevice(), reinterpret_cast<LPCVOID>(bin_file.data.file_buffer.Get()), bin_file.data.file_buffer.GetLength(), &img_load_info, nullptr, reinterpret_cast<ID3D11Resource **>(&tex), nullptr))) {
					this->Init();

					return (-1);
				}
			} else {
				tex_desc = desc.texture_desc;
				tex_desc.ArraySize = 1U;

				if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&tex_desc, nullptr, &tex))) {
					this->Init();

					return (-1);
				}
			}

			tex->GetDesc(&tex_desc);

			if (tex_desc_fixed_flg) {
				if ((desc.texture_desc.Width != tex_desc.Width)
				|| (desc.texture_desc.Height != tex_desc.Height)
				|| (desc.texture_desc.MipLevels != tex_desc.MipLevels)
				|| (desc.texture_desc.Format != tex_desc.Format)) {
					tex->Release();

					tex = nullptr;

					this->Init();

					return (-1);
				}
			} else {
				desc.texture_desc.Width = tex_desc.Width;
				desc.texture_desc.Height = tex_desc.Height;
				desc.texture_desc.MipLevels = tex_desc.MipLevels;
				desc.texture_desc.Format = tex_desc.Format;

				tex_desc_fixed_flg = true;
			}

			std::vector<tml::DynamicBuffer> buf_cont;
			std::vector<D3D11_MAPPED_SUBRESOURCE> msr_cont;
			INT res = 0;

			tml::Texture::GetBuffer(buf_cont, msr_cont, this->GetManager(), tex, &res);

			if (res < 0) {
				tex->Release();

				tex = nullptr;

				this->Init();

				return (-1);
			}

			tex->Release();

			tex = nullptr;

			for (size_t buf_i = 0U; buf_i < buf_cont.size(); ++buf_i) {
				srd_cont.emplace_back();
				srd_buf_cont.emplace_back();

				auto &srd = srd_cont.back();
				auto &srd_buf = srd_buf_cont.back();

				srd.pSysMem = buf_cont[buf_i].Get();
				srd.SysMemPitch = msr_cont[buf_i].RowPitch;
				srd_buf = std::move(buf_cont[buf_i]);
			}
		}

		std::vector<D3D11_SUBRESOURCE_DATA> tmp_srd_cont(srd_cont.begin(), srd_cont.end());

		if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&desc.texture_desc, tmp_srd_cont.data(), &this->tex_))) {
			this->Init();

			return (-1);
		}
	} else {
		if (desc.file_read_desc_container.empty()) {
			this->Init();

			return (-1);
		}

		desc.texture_desc.ArraySize = 1U;

		auto file_read_desc_dat = desc.file_read_desc_container.front().GetDataByParent();

		if (!file_read_desc_dat->file_path.empty() || file_read_desc_dat->file_buffer.GetLength() > 0U) {
			tml::BinaryFile bin_file;

			bin_file.read_desc.parent_data = file_read_desc_dat;

			if (bin_file.Read()) {
				this->Init();

				return (-1);
			}

			if (bin_file.data.file_buffer.GetSize() <= 0U) {
				this->Init();

				return (-1);
			}

			D3DX11_IMAGE_LOAD_INFO img_load_info;

			img_load_info.Width = (desc.texture_desc.Width <= 0U) ? D3DX11_DEFAULT : desc.texture_desc.Width;
			img_load_info.Height = (desc.texture_desc.Height <= 0U) ? D3DX11_DEFAULT : desc.texture_desc.Height;
			img_load_info.FirstMipLevel = 0U;
			img_load_info.MipLevels = desc.texture_desc.MipLevels;
			img_load_info.Usage = desc.texture_desc.Usage;
			img_load_info.BindFlags = desc.texture_desc.BindFlags;
			img_load_info.CpuAccessFlags = desc.texture_desc.CPUAccessFlags;
			img_load_info.Format = (desc.texture_desc.Format == DXGI_FORMAT_UNKNOWN) ? DXGI_FORMAT_FROM_FILE : desc.texture_desc.Format;

			if (FAILED(D3DX11CreateTextureFromMemory(this->GetManager()->GetDevice(), reinterpret_cast<LPCVOID>(bin_file.data.file_buffer.Get()), bin_file.data.file_buffer.GetLength(), &img_load_info, nullptr, reinterpret_cast<ID3D11Resource **>(&this->tex_), nullptr))) {
				this->Init();

				return (-1);
			}
		} else {
			if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&desc.texture_desc, nullptr, &this->tex_))) {
				this->Init();

				return (-1);
			}
		}
	}

	CD3D11_TEXTURE2D_DESC tex_desc;

	this->tex_->GetDesc(&tex_desc);
	this->size_ = tml::XMFLOAT2EX(static_cast<FLOAT>(tex_desc.Width), static_cast<FLOAT>(tex_desc.Height));

	if (tex_desc.BindFlags & D3D11_BIND_RENDER_TARGET) {
		if (desc.render_target_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateRenderTargetView(this->tex_, nullptr, &this->rt_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_RTV_DIMENSION dimension;

			if (tex_desc.SampleDesc.Count > 1U) {
				dimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

				if (this->ary_flg_) {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
				}
			} else {
				dimension = D3D11_RTV_DIMENSION_TEXTURE2D;

				if (this->ary_flg_) {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
				}
			}

			DXGI_FORMAT format = desc.render_target_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = tex_desc.Format;
			}

			CD3D11_RENDER_TARGET_VIEW_DESC rt_desc = CD3D11_RENDER_TARGET_VIEW_DESC(this->tex_, dimension, format);

			if (FAILED(this->GetManager()->GetDevice()->CreateRenderTargetView(this->tex_, &rt_desc, &this->rt_))) {
				this->Init();

				return (-1);
			}
		}
	}

	if (tex_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL) {
		if (desc.depth_target_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilView(this->tex_, nullptr, &this->dt_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_DSV_DIMENSION dimension;

			if (tex_desc.SampleDesc.Count > 1U) {
				if (this->ary_flg_) {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (this->ary_flg_) {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				}
			}

			DXGI_FORMAT format = desc.depth_target_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = tex_desc.Format;
			}

			CD3D11_DEPTH_STENCIL_VIEW_DESC dt_desc = CD3D11_DEPTH_STENCIL_VIEW_DESC(this->tex_, dimension, format);

			if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilView(this->tex_, &dt_desc, &this->dt_))) {
				this->Init();

				return (-1);
			}
		}
	}

	if (tex_desc.BindFlags & D3D11_BIND_SHADER_RESOURCE) {
		if (desc.sr_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateShaderResourceView(this->tex_, nullptr, &this->sr_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_SRV_DIMENSION dimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			if (tex_desc.SampleDesc.Count > 1U) {
				if (this->ary_flg_) {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (this->ary_flg_) {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				}
			}

			DXGI_FORMAT format = desc.sr_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = tex_desc.Format;
			}

			CD3D11_SHADER_RESOURCE_VIEW_DESC sr_desc = CD3D11_SHADER_RESOURCE_VIEW_DESC(this->tex_, dimension, format);

			if (FAILED(this->GetManager()->GetDevice()->CreateShaderResourceView(this->tex_, &sr_desc, &this->sr_))) {
				this->Init();

				return (-1);
			}
		}
	}

	if (tex_desc.BindFlags & D3D11_BIND_UNORDERED_ACCESS) {
		if (desc.uasr_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateUnorderedAccessView(this->tex_, nullptr, &this->uasr_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_UAV_DIMENSION dimension = D3D11_UAV_DIMENSION_TEXTURE2D;

			if (tex_desc.SampleDesc.Count > 1U) {
				this->Init();

				return (-1);
			} else {
				if (this->ary_flg_) {
					dimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_UAV_DIMENSION_TEXTURE2D;
				}
			}

			DXGI_FORMAT format = desc.uasr_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = tex_desc.Format;
			}

			CD3D11_UNORDERED_ACCESS_VIEW_DESC uasr_desc = CD3D11_UNORDERED_ACCESS_VIEW_DESC(this->tex_, dimension, format);

			if (FAILED(this->GetManager()->GetDevice()->CreateUnorderedAccessView(this->tex_, &uasr_desc, &this->uasr_))) {
				this->Init();

				return (-1);
			}
		}
	}

	return (0);
}


/**
 * @brief ClearRenderTarget関数
 * @param col (color)
 */
void tml::Texture::ClearRenderTarget(const tml::XMFLOAT4EX &col)
{
	FLOAT col_ary[4] = {
		col.x,
		col.y,
		col.z,
		col.w
	};

	this->GetManager()->GetDeviceContext()->ClearRenderTargetView(this->rt_, col_ary);

	return;
}


/**
 * @brief ClearDepthTarget関数
 */
void tml::Texture::ClearDepthTarget(void)
{
	this->GetManager()->GetDeviceContext()->ClearDepthStencilView(this->dt_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return;
}


/**
 * @brief GetBuffer関数
 * @param dst_buf (dst_buffer)
 * @param dst_msr (dst_mapped_subresource)
 * @param mgr (manager)
 * @param tex (texture)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_buf (dst_buffer)
 */
tml::DynamicBuffer &tml::Texture::GetBuffer(tml::DynamicBuffer &dst_buf, D3D11_MAPPED_SUBRESOURCE &dst_msr, tml::GraphicManager *mgr, ID3D11Texture2D *tex, INT *dst_res)
{
	dst_buf.Init();
	tml::MemoryUtil::Clear(&dst_msr, 1U);

	if ((mgr == nullptr)
	|| (tex == nullptr)) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	ID3D11Texture2D *cpu_tex = nullptr;
	CD3D11_TEXTURE2D_DESC cpu_tex_desc;

	tex->GetDesc(&cpu_tex_desc);

	cpu_tex_desc.Usage = D3D11_USAGE_STAGING;
	cpu_tex_desc.BindFlags = 0U;
	cpu_tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	cpu_tex_desc.MiscFlags = 0U;

	if (FAILED(mgr->GetDevice()->CreateTexture2D(&cpu_tex_desc, nullptr, &cpu_tex))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	mgr->GetDeviceContext()->CopyResource(cpu_tex, tex);

	D3D11_MAPPED_SUBRESOURCE msr;

	if (FAILED(mgr->GetDeviceContext()->Map(cpu_tex, 0U, D3D11_MAP_READ, 0U, &msr))) {
		cpu_tex->Release();

		tml::SetResult(dst_res, -1);

		return (dst_buf);
	}

	dst_buf.Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
	dst_msr = msr;
	dst_msr.pData = nullptr;

	mgr->GetDeviceContext()->Unmap(cpu_tex, 0U);

	cpu_tex->Release();

	tml::SetResult(dst_res, 0);

	return (dst_buf);
}


/**
 * @brief GetBuffer関数
 * @param dst_buf_cont (dst_buffer_container)
 * @param dst_msr_cont (dst_mapped_subresource_container)
 * @param mgr (manager)
 * @param tex (texture)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_buf_cont (dst_buffer_container)
 */
std::vector<tml::DynamicBuffer> &tml::Texture::GetBuffer(std::vector<tml::DynamicBuffer> &dst_buf_cont, std::vector<D3D11_MAPPED_SUBRESOURCE> &dst_msr_cont, tml::GraphicManager *mgr, ID3D11Texture2D *tex, INT *dst_res)
{
	dst_buf_cont.clear();
	dst_buf_cont.clear();

	if ((mgr == nullptr)
	|| (tex == nullptr)) {
		tml::SetResult(dst_res, -1);

		return (dst_buf_cont);
	}

	ID3D11Texture2D *cpu_tex = nullptr;
	CD3D11_TEXTURE2D_DESC cpu_tex_desc;

	tex->GetDesc(&cpu_tex_desc);

	cpu_tex_desc.Usage = D3D11_USAGE_STAGING;
	cpu_tex_desc.BindFlags = 0U;
	cpu_tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	cpu_tex_desc.MiscFlags = 0U;

	if (FAILED(mgr->GetDevice()->CreateTexture2D(&cpu_tex_desc, nullptr, &cpu_tex))) {
		tml::SetResult(dst_res, -1);

		return (dst_buf_cont);
	}

	mgr->GetDeviceContext()->CopyResource(cpu_tex, tex);

	dst_buf_cont.resize(cpu_tex_desc.MipLevels);
	dst_msr_cont.resize(cpu_tex_desc.MipLevels);

	for (UINT mm_i = 0U; mm_i < cpu_tex_desc.MipLevels; ++mm_i) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (FAILED(mgr->GetDeviceContext()->Map(cpu_tex, mm_i, D3D11_MAP_READ, 0U, &msr))) {
			cpu_tex->Release();

			dst_buf_cont.clear();
			dst_buf_cont.clear();

			tml::SetResult(dst_res, -1);

			return (dst_buf_cont);
		}

		dst_buf_cont[mm_i].Set(static_cast<BYTE *>(msr.pData), msr.DepthPitch);
		dst_msr_cont[mm_i] = msr;
		dst_msr_cont[mm_i].pData = nullptr;

		mgr->GetDeviceContext()->Unmap(cpu_tex, mm_i);
	}

	cpu_tex->Release();

	tml::SetResult(dst_res, 0);

	return (dst_buf_cont);
}
