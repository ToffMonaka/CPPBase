/**
 * @file
 * @brief Textureコードファイル
 */


#include "Texture.h"
#include "Manager.h"
#include "Font.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::TextureDesc::TextureDesc() :
	swap_chain(nullptr),
	texture_desc(DXGI_FORMAT_UNKNOWN, 0U, 0U, 0U, 0U, 0U),
	cpu_buffer_flag(false),
	render_target_format(DXGI_FORMAT_UNKNOWN),
	render_target_desc_null_flag(false),
	depth_target_format(DXGI_FORMAT_UNKNOWN),
	depth_target_desc_null_flag(false),
	sr_format(DXGI_FORMAT_UNKNOWN),
	sr_desc_null_flag(false),
	uasr_format(DXGI_FORMAT_UNKNOWN),
	uasr_desc_null_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::TextureDesc::~TextureDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::TextureDesc::Init(void)
{
	this->Release();

	this->swap_chain = nullptr;
	this->file_read_desc_container.clear();
	this->texture_desc = CD3D11_TEXTURE2D_DESC(DXGI_FORMAT_UNKNOWN, 0U, 0U, 0U, 0U, 0U);
	this->cpu_buffer_flag = false;
	this->render_target_format = DXGI_FORMAT_UNKNOWN;
	this->render_target_desc_null_flag = false;
	this->depth_target_format = DXGI_FORMAT_UNKNOWN;
	this->depth_target_desc_null_flag = false;
	this->sr_format = DXGI_FORMAT_UNKNOWN;
	this->sr_desc_null_flag = false;
	this->uasr_format = DXGI_FORMAT_UNKNOWN;
	this->uasr_desc_null_flag = false;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::TextureDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Texture Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"TEX");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetTextureDesc関数
 * @param bind_flg (bind_flag)
 * @param format (format)
 * @param size (size)
 * @param buf_cnt (buffer_count)
 * @param mm_cnt (mipmap_count)
 * @param ms_desc (multisample_desc)
 * @param dynamic_flg (dynamic_flag)
 */
void tml::graphic::TextureDesc::SetTextureDesc(const tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG bind_flg, const DXGI_FORMAT format, const XMUINT2EX &size, const UINT buf_cnt, const UINT mm_cnt, const DXGI_SAMPLE_DESC &ms_desc, const bool dynamic_flg)
{
	this->file_read_desc_container.clear();
	this->file_read_desc_container.resize(buf_cnt);
	this->texture_desc = CD3D11_TEXTURE2D_DESC(format, size.x, size.y, buf_cnt, mm_cnt, 0U);

	if (static_cast<bool>(bind_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::RENDER_TARGET)) {
		this->texture_desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
	}

	if (static_cast<bool>(bind_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::DEPTH_TARGET)) {
		this->texture_desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	}

	if (static_cast<bool>(bind_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR)) {
		this->texture_desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	}

	if (static_cast<bool>(bind_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::UASR)) {
		this->texture_desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	}

	if (dynamic_flg) {
		this->texture_desc.Usage = D3D11_USAGE_DYNAMIC;
		this->texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	this->texture_desc.SampleDesc = ms_desc;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Texture::Texture() :
	tex_(nullptr),
	tex_desc_(DXGI_FORMAT_UNKNOWN, 0U, 0U, 0U, 0U, 0U),
	size_(0U),
	rt_(nullptr),
	dt_(nullptr),
	sr_(nullptr),
	uasr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Texture::~Texture()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Texture::Release(void)
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

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Texture::Init(void)
{
	this->Release();

	this->tex_desc_ = CD3D11_TEXTURE2D_DESC(DXGI_FORMAT_UNKNOWN, 0U, 0U, 0U, 0U, 0U);
	this->size_ = 0U;
	this->cpu_buf_.Init();
	this->clear_cpu_buf_.Init();

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Texture::Create(const tml::graphic::TextureDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::TEXTURE) < 0) {
		this->Init();

		return (-1);
	}

	if (desc.swap_chain != nullptr) {
		if (FAILED(desc.swap_chain->GetBuffer(0U, IID_PPV_ARGS(&this->tex_)))) {
			this->Init();

			return (-1);
		}
	} else if (desc.file_read_desc_container.size() > 1U) {
		CD3D11_TEXTURE2D_DESC tmp_tex_desc = desc.texture_desc;
		bool tmp_tex_desc_fixed_flg = false;
		std::list<D3D11_SUBRESOURCE_DATA> srd_cont;
		std::list<tml::DynamicBuffer> srd_buf_cont;
		ID3D11Texture2D *tex = nullptr;
		CD3D11_TEXTURE2D_DESC tex_desc;

		for (auto &file_read_desc : desc.file_read_desc_container) {
			auto file_read_desc_dat = file_read_desc.GetDataByParent();

			if (!file_read_desc_dat->file_path.empty()
			|| (file_read_desc_dat->file_buffer.GetLength() > 0U)) {
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

				img_load_info.Width = (tmp_tex_desc.Width <= 0U) ? D3DX11_DEFAULT : tmp_tex_desc.Width;
				img_load_info.Height = (tmp_tex_desc.Height <= 0U) ? D3DX11_DEFAULT : tmp_tex_desc.Height;
				img_load_info.FirstMipLevel = 0U;
				img_load_info.MipLevels = tmp_tex_desc.MipLevels;
				img_load_info.Usage = static_cast<D3D11_USAGE>(D3DX11_DEFAULT);
				img_load_info.BindFlags = D3DX11_DEFAULT;
				img_load_info.CpuAccessFlags = D3DX11_DEFAULT;
				img_load_info.Format = (tmp_tex_desc.Format == DXGI_FORMAT_UNKNOWN) ? DXGI_FORMAT_FROM_FILE : tmp_tex_desc.Format;

				if (FAILED(D3DX11CreateTextureFromMemory(this->GetManager()->GetDevice(), reinterpret_cast<LPCVOID>(bin_file.data.file_buffer.Get()), bin_file.data.file_buffer.GetLength(), &img_load_info, nullptr, reinterpret_cast<ID3D11Resource **>(&tex), nullptr))) {
					this->Init();

					return (-1);
				}
			} else {
				if ((tmp_tex_desc.Width * tmp_tex_desc.Height) <= 0U) {
					this->Init();

					return (-1);
				}

				tex_desc = tmp_tex_desc;
				tex_desc.ArraySize = 1U;
				tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				tex_desc.Usage = D3D11_USAGE_DEFAULT;
				tex_desc.CPUAccessFlags = 0U;

				if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&tex_desc, nullptr, &tex))) {
					this->Init();

					return (-1);
				}
			}

			tex->GetDesc(&tex_desc);

			if (tmp_tex_desc_fixed_flg) {
				if ((tmp_tex_desc.Width != tex_desc.Width)
				|| (tmp_tex_desc.Height != tex_desc.Height)
				|| (tmp_tex_desc.MipLevels != tex_desc.MipLevels)
				|| (tmp_tex_desc.Format != tex_desc.Format)) {
					tex->Release();

					tex = nullptr;

					this->Init();

					return (-1);
				}
			} else {
				tmp_tex_desc.Width = tex_desc.Width;
				tmp_tex_desc.Height = tex_desc.Height;
				tmp_tex_desc.MipLevels = tex_desc.MipLevels;
				tmp_tex_desc.Format = tex_desc.Format;

				tmp_tex_desc_fixed_flg = true;
			}

			std::vector<tml::DynamicBuffer> buf_cont;
			std::vector<D3D11_MAPPED_SUBRESOURCE> msr_cont;
			INT res = 0;

			this->GetManager()->GetBuffer(buf_cont, msr_cont, tex, &res);

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

		if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&tmp_tex_desc, tmp_srd_cont.data(), &this->tex_))) {
			this->Init();

			return (-1);
		}
	} else if (desc.file_read_desc_container.size() == 1U) {
		CD3D11_TEXTURE2D_DESC tmp_tex_desc = desc.texture_desc;

		auto file_read_desc_dat = desc.file_read_desc_container[0].GetDataByParent();

		if (!file_read_desc_dat->file_path.empty()
		|| (file_read_desc_dat->file_buffer.GetLength() > 0U)) {
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

			img_load_info.Width = (tmp_tex_desc.Width <= 0U) ? D3DX11_DEFAULT : tmp_tex_desc.Width;
			img_load_info.Height = (tmp_tex_desc.Height <= 0U) ? D3DX11_DEFAULT : tmp_tex_desc.Height;
			img_load_info.FirstMipLevel = 0U;
			img_load_info.MipLevels = tmp_tex_desc.MipLevels;
			img_load_info.Usage = tmp_tex_desc.Usage;
			img_load_info.BindFlags = tmp_tex_desc.BindFlags;
			img_load_info.CpuAccessFlags = tmp_tex_desc.CPUAccessFlags;
			img_load_info.Format = (tmp_tex_desc.Format == DXGI_FORMAT_UNKNOWN) ? DXGI_FORMAT_FROM_FILE : tmp_tex_desc.Format;

			if (FAILED(D3DX11CreateTextureFromMemory(this->GetManager()->GetDevice(), reinterpret_cast<LPCVOID>(bin_file.data.file_buffer.Get()), bin_file.data.file_buffer.GetLength(), &img_load_info, nullptr, reinterpret_cast<ID3D11Resource **>(&this->tex_), nullptr))) {
				this->Init();

				return (-1);
			}
		} else {
			if ((tmp_tex_desc.Width * tmp_tex_desc.Height) <= 0U) {
				this->Init();

				return (-1);
			}

			if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&tmp_tex_desc, nullptr, &this->tex_))) {
				this->Init();

				return (-1);
			}
		}
	} else {
		this->Init();

		return (-1);
	}

	this->tex_->GetDesc(&this->tex_desc_);
	this->size_ = tml::XMUINT2EX(this->tex_desc_.Width, this->tex_desc_.Height);

	if (desc.cpu_buffer_flag) {
		if (this->tex_desc_.ArraySize > 1U) {
			this->Init();

			return (-1);
		}

		D3D11_MAPPED_SUBRESOURCE msr;
		INT res = 0;

		this->GetManager()->GetBuffer(this->cpu_buf_, msr, this->tex_, &res);

		if (res < 0) {
			this->Init();

			return (-1);
		}

		this->clear_cpu_buf_ = this->cpu_buf_;

		UINT pixel_cnt = this->size_.x * this->size_.y;

		for (UINT pixel_i = 0U; pixel_i < pixel_cnt; ++pixel_i) {
			reinterpret_cast<UINT *>(this->clear_cpu_buf_.Get())[pixel_i] = 0U;
		}
	}

	if (this->tex_desc_.BindFlags & D3D11_BIND_RENDER_TARGET) {
		if (desc.render_target_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateRenderTargetView(this->tex_, nullptr, &this->rt_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_RTV_DIMENSION dimension;

			if (this->tex_desc_.SampleDesc.Count > 1U) {
				if (this->tex_desc_.ArraySize > 1U) {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (this->tex_desc_.ArraySize > 1U) {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				}
			}

			DXGI_FORMAT format = desc.render_target_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = this->tex_desc_.Format;
			}

			CD3D11_RENDER_TARGET_VIEW_DESC rt_desc = CD3D11_RENDER_TARGET_VIEW_DESC(this->tex_, dimension, format);

			if (FAILED(this->GetManager()->GetDevice()->CreateRenderTargetView(this->tex_, &rt_desc, &this->rt_))) {
				this->Init();

				return (-1);
			}
		}
	}

	if (this->tex_desc_.BindFlags & D3D11_BIND_DEPTH_STENCIL) {
		if (desc.depth_target_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilView(this->tex_, nullptr, &this->dt_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_DSV_DIMENSION dimension;

			if (this->tex_desc_.SampleDesc.Count > 1U) {
				if (this->tex_desc_.ArraySize > 1U) {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (this->tex_desc_.ArraySize > 1U) {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				}
			}

			DXGI_FORMAT format = desc.depth_target_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = this->tex_desc_.Format;
			}

			CD3D11_DEPTH_STENCIL_VIEW_DESC dt_desc = CD3D11_DEPTH_STENCIL_VIEW_DESC(this->tex_, dimension, format);

			if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilView(this->tex_, &dt_desc, &this->dt_))) {
				this->Init();

				return (-1);
			}
		}
	}

	if (this->tex_desc_.BindFlags & D3D11_BIND_SHADER_RESOURCE) {
		if (desc.sr_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateShaderResourceView(this->tex_, nullptr, &this->sr_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_SRV_DIMENSION dimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			if (this->tex_desc_.SampleDesc.Count > 1U) {
				if (this->tex_desc_.ArraySize > 1U) {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (this->tex_desc_.ArraySize > 1U) {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				}
			}

			DXGI_FORMAT format = desc.sr_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = this->tex_desc_.Format;
			}

			CD3D11_SHADER_RESOURCE_VIEW_DESC sr_desc = CD3D11_SHADER_RESOURCE_VIEW_DESC(this->tex_, dimension, format);

			if (FAILED(this->GetManager()->GetDevice()->CreateShaderResourceView(this->tex_, &sr_desc, &this->sr_))) {
				this->Init();

				return (-1);
			}
		}
	}

	if (this->tex_desc_.BindFlags & D3D11_BIND_UNORDERED_ACCESS) {
		if (desc.uasr_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateUnorderedAccessView(this->tex_, nullptr, &this->uasr_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_UAV_DIMENSION dimension = D3D11_UAV_DIMENSION_TEXTURE2D;

			if (this->tex_desc_.SampleDesc.Count > 1U) {
				this->Init();

				return (-1);
			} else {
				if (this->tex_desc_.ArraySize > 1U) {
					dimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_UAV_DIMENSION_TEXTURE2D;
				}
			}

			DXGI_FORMAT format = desc.uasr_format;

			if (format == DXGI_FORMAT_UNKNOWN) {
				format = this->tex_desc_.Format;
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
 * @brief UploadCPUBuffer関数
 */
void tml::graphic::Texture::UploadCPUBuffer(void)
{
	if (this->cpu_buf_.GetLength() <= 0U) {
		return;
	}

	if (this->tex_desc_.Usage == D3D11_USAGE_DYNAMIC) {
		D3D11_MAPPED_SUBRESOURCE msr;

		if (SUCCEEDED(this->GetManager()->GetDeviceContext()->Map(this->tex_, 0U, D3D11_MAP_WRITE_DISCARD, 0U, &msr))) {
			memcpy(msr.pData, this->cpu_buf_.Get(), this->size_.x * this->size_.y * 4U);

			this->GetManager()->GetDeviceContext()->Unmap(this->tex_, 0U);
		}
	} else {
		this->GetManager()->GetDeviceContext()->UpdateSubresource(this->tex_, 0U, nullptr, this->cpu_buf_.Get(), this->size_.x * 4U, this->size_.x * this->size_.y * 4U);
	}

	return;
}


/**
 * @brief DownloadCPUBuffer関数
 */
void tml::graphic::Texture::DownloadCPUBuffer(void)
{
	if (this->cpu_buf_.GetLength() <= 0U) {
		return;
	}

	return;
}


/**
 * @brief ClearCPUBuffer関数
 */
void tml::graphic::Texture::ClearCPUBuffer(void)
{
	if (this->cpu_buf_.GetLength() <= 0U) {
		return;
	}

	tml::MemoryUtil::Copy(this->cpu_buf_.Get(), this->clear_cpu_buf_.Get(), this->clear_cpu_buf_.GetLength());

	return;
}


/**
 * @brief DrawCPUBufferString関数
 * @param str (string)
 * @param pos (position)
 * @param font (font)
 */
void tml::graphic::Texture::DrawCPUBufferString(const WCHAR *str, const tml::XMUINT2EX &pos, tml::graphic::Font *font)
{
	if ((this->cpu_buf_.GetLength() <= 0U)
	|| (str[0] == 0)
	|| (font == nullptr)) {
		return;
	}

	size_t str_len = wcslen(str);
	UINT *buf = reinterpret_cast<UINT *>(this->cpu_buf_.Get());
	UINT buf_w = this->size_.x;
	UINT buf_h = this->size_.y;
	UINT buf_x = 0U;
	UINT buf_y = 0U;
	UINT buf_offset_x = pos.x;
	UINT buf_offset_y = pos.y;
	UINT tmp_buf_offset_x = 0U;
	UINT tmp_buf_offset_y = 0U;
	WCHAR code = 0;
	const BYTE *bm_buf = nullptr;
	UINT bm_w = 0U;
	UINT bm_h = 0U;

	auto &font_tm = font->GetTextMetric();

	for (size_t str_i = 0U; str_i < str_len; ++str_i) {
		code = str[str_i];

		auto bm = font->GetBitmap(code);

		if (bm == nullptr) {
			continue;
		}

		auto &bm_gm = bm->GetGlyphMetrics();

		bm_buf = bm->GetBuffer().Get();
		bm_w = bm_gm.gmBlackBoxX + ((4U - (bm_gm.gmBlackBoxX & 3U)) & 3U);
		bm_h = bm_gm.gmBlackBoxY;

		tmp_buf_offset_x = buf_offset_x + bm_gm.gmptGlyphOrigin.x;
		tmp_buf_offset_y = buf_offset_y + font_tm.tmAscent - bm_gm.gmptGlyphOrigin.y;

		for (UINT bm_y = 0U; bm_y < bm_h; ++bm_y) {
			buf_y = tmp_buf_offset_y + bm_y;

			if (buf_y >= buf_h) {
				break;
			}

			for(UINT bm_x = 0U; bm_x < bm_w; ++bm_x) {
				buf_x = tmp_buf_offset_x + bm_x;

				if (buf_x >= buf_w) {
					break;
				}

				buf[buf_x + buf_y * buf_w] = 0x00FFFFFF | (static_cast<UINT>(bm_buf[bm_x + bm_y * bm_w]) << 24);
			}
		}

		buf_offset_x += bm_gm.gmCellIncX;
	}

	return;
}


/**
 * @brief ClearRenderTarget関数
 * @param col (color)
 */
void tml::graphic::Texture::ClearRenderTarget(const tml::XMFLOAT4EX &col)
{
	if (this->rt_ == nullptr) {
		return;
	}

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
void tml::graphic::Texture::ClearDepthTarget(void)
{
	if (this->dt_ == nullptr) {
		return;
	}

	this->GetManager()->GetDeviceContext()->ClearDepthStencilView(this->dt_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return;
}
