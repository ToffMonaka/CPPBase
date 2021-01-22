/**
 * @file
 * @brief Textureコードファイル
 */


#include "Texture.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::TextureDesc::TextureDesc() :
	swap_chain(nullptr),
	texture_desc(DXGI_FORMAT_UNKNOWN, 0U, 0U),
	render_target_format(DXGI_FORMAT_UNKNOWN),
	render_target_desc_null_flag(false),
	depth_target_format(DXGI_FORMAT_UNKNOWN),
	depth_target_desc_null_flag(false),
	sr_format(DXGI_FORMAT_UNKNOWN),
	sr_desc_null_flag(false),
	uasr_format(DXGI_FORMAT_UNKNOWN),
	uasr_desc_null_flag(false)
{
	this->texture_desc.BindFlags = 0U;

	return;
}


/**
 * @brief コンストラクタ
 * @param tex_desc_type_flg (texture_desc_type_flag)
 * @param tex_desc_format (texture_desc_format)
 * @param tex_desc_size (texture_desc_size)
 * @param tex_desc_buf_cnt (texture_desc_buf_count)
 * @param tex_desc_mm_cnt (texture_desc_mipmap_count)
 * @param tex_desc_ms_desc (texture_desc_multisample_desc)
 */
tml::graphic::TextureDesc::TextureDesc(const tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG tex_desc_type_flg, const DXGI_FORMAT tex_desc_format, const XMUINT2EX &tex_desc_size, const UINT tex_desc_buf_cnt, const UINT tex_desc_mm_cnt, const DXGI_SAMPLE_DESC &tex_desc_ms_desc)
{
	this->Set(tex_desc_type_flg, tex_desc_format, tex_desc_size, tex_desc_buf_cnt, tex_desc_mm_cnt, tex_desc_ms_desc);

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::TextureDesc::~TextureDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::TextureDesc::Init(void)
{
	this->file_read_desc_container.clear();
	this->swap_chain = nullptr;
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
 * @brief Set関数
 * @param tex_desc_type_flg (texture_desc_type_flag)
 * @param tex_desc_format (texture_desc_format)
 * @param tex_desc_size (texture_desc_size)
 * @param tex_desc_buf_cnt (texture_desc_buf_count)
 * @param tex_desc_mm_cnt (texture_desc_mipmap_count)
 * @param tex_desc_ms_desc (texture_desc_multisample_desc)
 */
void tml::graphic::TextureDesc::Set(const tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG tex_desc_type_flg, const DXGI_FORMAT tex_desc_format, const XMUINT2EX &tex_desc_size, const UINT tex_desc_buf_cnt, const UINT tex_desc_mm_cnt, const DXGI_SAMPLE_DESC &tex_desc_ms_desc)
{
	this->Init();

	for (UINT buf_i = 0U; buf_i < tex_desc_buf_cnt; ++buf_i) {
		this->file_read_desc_container.emplace_back();
	}

	this->texture_desc = CD3D11_TEXTURE2D_DESC(tex_desc_format, tex_desc_size.x, tex_desc_size.y, tex_desc_buf_cnt, tex_desc_mm_cnt);
	this->texture_desc.BindFlags = 0U;

	if (static_cast<bool>(tex_desc_type_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::RENDER_TARGET)) {
		this->texture_desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
	}

	if (static_cast<bool>(tex_desc_type_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::DEPTH_TARGET)) {
		this->texture_desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	}

	if (static_cast<bool>(tex_desc_type_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::SR)) {
		this->texture_desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	}

	if (static_cast<bool>(tex_desc_type_flg & tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG::UASR)) {
		this->texture_desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	}

	this->texture_desc.SampleDesc = tex_desc_ms_desc;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Texture::Texture() :
	tex_(nullptr),
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

	this->size_ = 0U;

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

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::TEXTURE, desc) < 0) {
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
				tex_desc = tmp_tex_desc;
				tex_desc.ArraySize = 1U;

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
			if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&tmp_tex_desc, nullptr, &this->tex_))) {
				this->Init();

				return (-1);
			}
		}
	} else {
		this->Init();

		return (-1);
	}

	CD3D11_TEXTURE2D_DESC tex_desc;

	this->tex_->GetDesc(&tex_desc);

	this->size_ = tml::XMUINT2EX(tex_desc.Width, tex_desc.Height);

	if (tex_desc.BindFlags & D3D11_BIND_RENDER_TARGET) {
		if (desc.render_target_desc_null_flag) {
			if (FAILED(this->GetManager()->GetDevice()->CreateRenderTargetView(this->tex_, nullptr, &this->rt_))) {
				this->Init();

				return (-1);
			}
		} else {
			D3D11_RTV_DIMENSION dimension;

			if (tex_desc.SampleDesc.Count > 1U) {
				if (tex_desc.ArraySize > 1U) {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (tex_desc.ArraySize > 1U) {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
				} else {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2D;
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
				if (tex_desc.ArraySize > 1U) {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (tex_desc.ArraySize > 1U) {
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
				if (tex_desc.ArraySize > 1U) {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (tex_desc.ArraySize > 1U) {
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
				if (tex_desc.ArraySize > 1U) {
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
void tml::graphic::Texture::ClearRenderTarget(const tml::XMFLOAT4EX &col)
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
void tml::graphic::Texture::ClearDepthTarget(void)
{
	this->GetManager()->GetDeviceContext()->ClearDepthStencilView(this->dt_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return;
}
