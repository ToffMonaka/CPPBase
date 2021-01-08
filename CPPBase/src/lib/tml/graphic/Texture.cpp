/**
 * @file
 * @brief Texture�R�[�h�t�@�C��
 */


#include "Texture.h"
#include "GraphicManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::TextureDesc::TextureDesc() :
	file_parent_read_plan(nullptr),
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
 * @brief �f�X�g���N�^
 */
tml::TextureDesc::~TextureDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextureDesc::Init(void)
{
	this->file_read_plan.Init();
	this->file_parent_read_plan = nullptr;
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
 * @brief �R���X�g���N�^
 */
tml::Texture::Texture() :
	tex_(nullptr),
	size_(0.0f, 0.0f),
	rt_(nullptr),
	dt_(nullptr),
	sr_(nullptr),
	uasr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Texture::~Texture()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
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
 * @brief Init�֐�
 */
void tml::Texture::Init(void)
{
	this->Release();

	this->size_ = 0.0f;

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::Texture::Create(tml::TextureDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (desc.swap_chain_flag) {
		if (FAILED(this->GetManager()->GetSwapChain()->GetBuffer(0U, IID_PPV_ARGS(&this->tex_)))) {
			this->Init();

			return (-1);
		}
	} else if (desc.array_flag) {
	/*
	} else if (desc.flg & tm_l::graphic::_Texture::_FLAG::_ARRAY) { //�z��L��̎�
		if (desc.tex_desc.ArraySize <= 0U) { //�z�񖳂��̎�
			this->Init();

			return (-1);
		}

		std::list<D3D11_SUBRESOURCE_DATA> srd_cont;
		std::list<tm_l::buffer::DynamicBuffer> srd_buf_cont;
		bool tex_desc_fix_flg = false;

		auto tex_file_desc_itr = desc.tex_file_desc_cont.begin();

		for (UINT_M ary_i = 0U; ary_i < desc.tex_desc.ArraySize; ++ary_i) {
			if (tex_file_desc_itr != desc.tex_file_desc_cont.end()) { //�e�N�X�`���t�@�C���f�B�X�N���v�V�����L��̎�
				auto &tex_file_desc = (*tex_file_desc_itr);

				++tex_file_desc_itr;

				if (tex_file_desc.buf != nullptr) { //�e�N�X�`���t�@�C���o�b�t�@�L��̎�
					if (tex_file_desc.buf->GetLength() <= 0) { //�o�b�t�@�����O�X�����̎�
						this->Init();

						return (-1);
					}

					ID3D11Texture2D *tex = nullptr;
					CD3D11_TEXTURE2D_DESC tex_desc;
					D3DX11_IMAGE_LOAD_INFO img_load_info;

					img_load_info.Width = (desc.tex_desc.Width <= 0U) ? D3DX11_DEFAULT : desc.tex_desc.Width;
					img_load_info.Height = (desc.tex_desc.Height <= 0U) ? D3DX11_DEFAULT : desc.tex_desc.Height;
					img_load_info.FirstMipLevel = 0U;
					img_load_info.MipLevels = desc.tex_desc.MipLevels;
					img_load_info.Format = (desc.tex_desc.Format == DXGI_FORMAT_UNKNOWN) ? DXGI_FORMAT_FROM_FILE : desc.tex_desc.Format;

					if (FAILED(D3DX11CreateTextureFromMemory(this->GetManager()->GetDevice(), reinterpret_cast<LPCVOID>(tex_file_desc.buf->Get()), tex_file_desc.buf->GetLength(), &img_load_info, nullptr, reinterpret_cast<ID3D11Resource **>(&tex), nullptr))) { //���s�̎�
						this->Init();

						return (-1);
					}

					tex->GetDesc(&tex_desc);

					if (!(this->IsTextureDesc(desc.tex_desc, tex_desc, tex_desc_fix_flg))) { //���v�̎�
						tex->Release();

						this->Init();

						return (-1);
					}

					std::vector<tm_l::buffer::DynamicBuffer> buf_cont;
					std::vector<FLOAT> pitch_cont;
					INT_M res = 0;

					tm_l::graphic::Texture::GetBuffer(&buf_cont, this->GetManager(), tex, &pitch_cont, &res);

					if (res < 0) { //���s�̎�
						tex->Release();

						this->Init();

						return (-1);
					}

					tex->Release();

					this->SetSubResourceData(srd_cont, srd_buf_cont, buf_cont, pitch_cont);

					this->tex_file_path_cont.push_back(L"");

					continue;
				} else if (!(tex_file_desc.path.empty())) { //�e�N�X�`���t�@�C���p�X�L��̎�
					tm_l::file::BinaryFile tex_bin_file;

					tex_bin_file.Read(tex_file_desc.path.c_str(), 0);

					if (tex_bin_file.GetBuffer()->GetLength() <= 0) { //�o�b�t�@�����O�X�����̎�
						this->Init();

						return (-1);
					}

					ID3D11Texture2D *tex = nullptr;
					CD3D11_TEXTURE2D_DESC tex_desc;
					D3DX11_IMAGE_LOAD_INFO img_load_info;

					img_load_info.Width = (desc.tex_desc.Width <= 0U) ? D3DX11_DEFAULT : desc.tex_desc.Width;
					img_load_info.Height = (desc.tex_desc.Height <= 0U) ? D3DX11_DEFAULT : desc.tex_desc.Height;
					img_load_info.FirstMipLevel = 0U;
					img_load_info.MipLevels = desc.tex_desc.MipLevels;
					img_load_info.Format = (desc.tex_desc.Format == DXGI_FORMAT_UNKNOWN) ? DXGI_FORMAT_FROM_FILE : desc.tex_desc.Format;

					if (FAILED(D3DX11CreateTextureFromMemory(this->GetManager()->GetDevice(), reinterpret_cast<LPCVOID>(tex_bin_file.GetBuffer()->Get()), tex_bin_file.GetBuffer()->GetLength(), &img_load_info, nullptr, reinterpret_cast<ID3D11Resource **>(&tex), nullptr))) { //���s�̎�
						this->Init();

						return (-1);
					}

					tex->GetDesc(&tex_desc);

					if (!(this->IsTextureDesc(desc.tex_desc, tex_desc, tex_desc_fix_flg))) { //���v�̎�
						tex->Release();

						this->Init();

						return (-1);
					}

					std::vector<tm_l::buffer::DynamicBuffer> buf_cont;
					std::vector<FLOAT> pitch_cont;
					INT_M res = 0;

					tm_l::graphic::Texture::GetBuffer(&buf_cont, this->GetManager(), tex, &pitch_cont, &res);

					if (res < 0) { //���s�̎�
						tex->Release();

						this->Init();

						return (-1);
					}

					tex->Release();

					this->SetSubResourceData(srd_cont, srd_buf_cont, buf_cont, pitch_cont);

					this->tex_file_path_cont.push_back(tex_file_desc.path);

					continue;
				}
			}

			ID3D11Texture2D *tex = nullptr;
			CD3D11_TEXTURE2D_DESC tex_desc = desc.tex_desc;

			tex_desc.ArraySize = 1U;

			if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&tex_desc, nullptr, &tex))) { //���s�̎�
				this->Init();

				return (-1);
			}

			tex->GetDesc(&tex_desc);

			if (!(this->IsTextureDesc(desc.tex_desc, tex_desc, tex_desc_fix_flg))) { //���v�̎�
				tex->Release();

				this->Init();

				return (-1);
			}

			std::vector<tm_l::buffer::DynamicBuffer> buf_cont;
			std::vector<FLOAT> pitch_cont;
			INT_M res = 0;

			tm_l::graphic::Texture::GetBuffer(&buf_cont, this->GetManager(), tex, &pitch_cont, &res);

			if (res < 0) { //���s�̎�
				tex->Release();

				this->Init();

				return (-1);
			}

			tex->Release();

			this->SetSubResourceData(srd_cont, srd_buf_cont, buf_cont, pitch_cont);

			this->tex_file_path_cont.push_back(L"");
		}

		std::vector<D3D11_SUBRESOURCE_DATA> tmp_srd_cont(srd_cont.begin(), srd_cont.end());

		if (FAILED(this->GetManager()->GetDevice()->CreateTexture2D(&desc.tex_desc, tmp_srd_cont.data(), &this->tex))) { //���s�̎�
			this->Init();

			return (-1);
		}
	}
	*/
	} else {
		auto file_read_plan = (desc.file_parent_read_plan != nullptr) ? desc.file_parent_read_plan : &desc.file_read_plan;

		if (!file_read_plan->file_path.empty() || file_read_plan->file_buffer.GetLength() > 0U) {
			tml::BinaryFile bin_file;

			bin_file.parent_read_plan = file_read_plan;

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
			img_load_info.Usage = desc.texture_desc.Usage;
			img_load_info.BindFlags = desc.texture_desc.BindFlags;
			img_load_info.CpuAccessFlags = desc.texture_desc.CPUAccessFlags;
			img_load_info.FirstMipLevel = 0U;
			img_load_info.MipLevels = desc.texture_desc.MipLevels;
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

				if (desc.array_flag) {
					dimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
				}
			} else {
				dimension = D3D11_RTV_DIMENSION_TEXTURE2D;

				if (desc.array_flag) {
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
				if (desc.array_flag) {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (desc.array_flag) {
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
				if (desc.array_flag) {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
				} else {
					dimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
				}
			} else {
				if (desc.array_flag) {
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
				if (desc.array_flag) {
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
 * @brief ClearRenderTarget�֐�
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
 * @brief ClearDepthTarget�֐�
 */
void tml::Texture::ClearDepthTarget(void)
{
	this->GetManager()->GetDeviceContext()->ClearDepthStencilView(this->dt_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return;
}
