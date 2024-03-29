/**
 * @file
 * @brief Textureヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "ManagerResource.h"
#include "Font.h"
#include "Atlas.h"
#include "Map.h"


namespace tml {
namespace graphic {
/**
 * @brief TextureRectクラス
 */
class TextureRect
{
private:
	tml::XMUINT2EX pos_;
	tml::XMUINT2EX size_;

private:
	void Release(void);

public:
	TextureRect();
	virtual ~TextureRect();

	virtual void Init(void);

	const tml::XMUINT2EX &GetPosition(void) const;
	void SetPosition(const tml::XMUINT2EX &);
	const tml::XMUINT2EX &GetSize(void) const;
	void SetSize(const tml::XMUINT2EX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::TextureRect::Release(void)
{
	return;
}


/**
 * @brief GetPosition関数
 * @return pos (position)
 */
inline const tml::XMUINT2EX &tml::graphic::TextureRect::GetPosition(void) const
{
	return (this->pos_);
}


/**
 * @brief SetPosition関数
 * @param pos (position)
 */
inline void tml::graphic::TextureRect::SetPosition(const tml::XMUINT2EX &pos)
{
	this->pos_ = pos;

	return;
}


/**
 * @brief GetSize関数
 * @return size (size)
 */
inline const tml::XMUINT2EX &tml::graphic::TextureRect::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief SetSize関数
 * @param size (size)
 */
inline void tml::graphic::TextureRect::SetSize(const tml::XMUINT2EX &size)
{
	this->size_ = size;

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief TextureDescクラス
 */
class TextureDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_TEXTURE2D_DESC texture_desc;
	bool cpu_buffer_flag;
	DXGI_FORMAT render_target_format;
	bool render_target_desc_null_flag;
	DXGI_FORMAT depth_target_format;
	bool depth_target_desc_null_flag;
	DXGI_FORMAT sr_format;
	bool sr_desc_null_flag;
	DXGI_FORMAT uasr_format;
	bool uasr_desc_null_flag;
	tml::graphic::TextureRect rect;
	bool rect_auto_flag;
	IDXGISwapChain *swap_chain;
	std::vector<tml::BinaryFileReadDesc> image_file_read_desc_container;
	tml::shared_ptr<tml::graphic::Texture> atlas_texture;
	tml::shared_ptr<tml::graphic::TextureDesc> atlas_texture_desc;
	tml::graphic::AtlasRect atlas_rect;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	TextureDesc();
	virtual ~TextureDesc();

	virtual void Init(void);

	void SetTextureDesc(const tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG, const DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN, const tml::XMUINT2EX &size = tml::XMUINT2EX(0U), const UINT ary_cnt = 1U, const UINT mm_cnt = 1U, const DXGI_SAMPLE_DESC &ms_desc = {1U, 0U}, const bool dynamic_flg = false);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::TextureDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Textureクラス
 */
class Texture : public tml::graphic::ManagerResource
{
public: Texture(const tml::graphic::Texture &) = delete;
public: tml::graphic::Texture &operator =(const tml::graphic::Texture &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::TEXTURE);

private:
	const tml::graphic::TextureDesc *desc_;
	tml::graphic::Texture *current_;
	ID3D11Texture2D *tex_;
	CD3D11_TEXTURE2D_DESC tex_desc_;
	tml::graphic::TextureRect rect_;
	std::vector<tml::XMUINT2EX> mm_size_cont_;
	std::vector<tml::DynamicBuffer> cpu_buf_cont_;
	std::vector<D3D11_MAPPED_SUBRESOURCE> msr_cont_;
	std::vector<tml::DynamicBuffer> clear_cpu_buf_cont_;
	std::vector<LONG> str_line_w_cont_;
	ID3D11RenderTargetView *rt_;
	ID3D11DepthStencilView *dt_;
	ID3D11ShaderResourceView *sr_;
	ID3D11UnorderedAccessView *uasr_;
	tml::shared_ptr<tml::graphic::Texture> atlas_tex_;
	tml::graphic::AtlasRect atlas_rect_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Texture();
	virtual ~Texture();

	virtual void Init(void);

	const tml::graphic::TextureDesc *GetDesc(void) const;
	ID3D11Texture2D *GetTexture(void);
	const CD3D11_TEXTURE2D_DESC &GetTextureDesc(void) const;
	const tml::graphic::TextureRect &GetRect(void) const;
	void SetRect(const tml::graphic::TextureRect &);
	UINT GetArrayCount(void) const;
	UINT GetMipmapCount(void) const;
	const tml::XMUINT2EX *GetMipmapSizeArray(void) const;
	const tml::XMUINT2EX *GetMipmapSize(const UINT) const;
	const tml::XMUINT2EX *GetMipmapSizeFast(const UINT) const;
	UINT GetCPUBufferCount(void) const;
	tml::DynamicBuffer *GetCPUBufferArray(void);
	tml::DynamicBuffer *GetCPUBuffer(const UINT, const UINT);
	tml::DynamicBuffer *GetCPUBufferFast(const UINT, const UINT);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
	UINT GetMappedSubresourceCount(void) const;
	const D3D11_MAPPED_SUBRESOURCE *GetMappedSubresourceArray(void) const;
	const D3D11_MAPPED_SUBRESOURCE *GetMappedSubresource(const UINT, const UINT) const;
	const D3D11_MAPPED_SUBRESOURCE *GetMappedSubresourceFast(const UINT, const UINT) const;
	void ClearCPUBuffer(void);
	void DrawCPUBufferString(const WCHAR *, const tml::ConstantUtil::GRAPHIC::STRING_ALIGNMENT_TYPE, const tml::XMINT2EX &, const tml::ConstantUtil::GRAPHIC::POSITION_FIT_TYPE, tml::graphic::Font *);
	ID3D11RenderTargetView *GetRenderTarget(void);
	void ClearRenderTarget(const tml::XMFLOAT4EX &);
	ID3D11DepthStencilView *GetDepthTarget(void);
	void ClearDepthTarget(void);
	ID3D11ShaderResourceView *GetSR(void);
	ID3D11UnorderedAccessView *GetUASR(void);
	const tml::shared_ptr<tml::graphic::Texture> &GetAtlasTexture(void);
	const tml::graphic::AtlasRect &GetAtlasRect(void) const;
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::TextureDesc *tml::graphic::Texture::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetTexture関数
 * @return tex (texture)
 */
inline ID3D11Texture2D *tml::graphic::Texture::GetTexture(void)
{
	return (this->current_->tex_);
}


/**
 * @brief GetTextureDesc関数
 * @return tex_desc (texture_desc)
 */
inline const CD3D11_TEXTURE2D_DESC &tml::graphic::Texture::GetTextureDesc(void) const
{
	return (this->current_->tex_desc_);
}


/**
 * @brief GetRect関数
 * @return rect (rect)
 */
inline const tml::graphic::TextureRect &tml::graphic::Texture::GetRect(void) const
{
	return (this->rect_);
}


/**
 * @brief SetRect関数
 * @param rect (rect)
 */
inline void tml::graphic::Texture::SetRect(const tml::graphic::TextureRect &rect)
{
	this->rect_ = rect;

	return;
}


/**
 * @brief GetArrayCount関数
 * @return ary_cnt (array_cnt)
 */
inline UINT tml::graphic::Texture::GetArrayCount(void) const
{
	return (this->current_->tex_desc_.ArraySize);
}


/**
 * @brief GetMipmapCount関数
 * @return mm_cnt (mm_cnt)
 */
inline UINT tml::graphic::Texture::GetMipmapCount(void) const
{
	return (this->current_->tex_desc_.MipLevels);
}


/**
 * @brief GetMipmapSizeArray関数
 * @return mm_size_ary (mm_size_array)
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetMipmapSizeArray(void) const
{
	return (this->current_->mm_size_cont_.data());
}


/**
 * @brief GetMipmapSize関数
 * @param mm_index (mipmap_index)
 * @return size (size)<br>
 * nullptr=失敗
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetMipmapSize(const UINT mm_index) const
{
	if (mm_index >= this->current_->mm_size_cont_.size()) {
		return (nullptr);
	}

	return (&this->current_->mm_size_cont_[mm_index]);
}


/**
 * @brief GetMipmapSizeFast関数
 * @param mm_index (mipmap_index)
 * @return size (size)<br>
 * nullptr=失敗
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetMipmapSizeFast(const UINT mm_index) const
{
	return (&this->current_->mm_size_cont_[mm_index]);
}


/**
 * @brief GetCPUBufferCount関数
 * @return cpu_buf_cnt (cpu_buffer_count)
 */
inline UINT tml::graphic::Texture::GetCPUBufferCount(void) const
{
	return (this->current_->cpu_buf_cont_.size());
}


/**
 * @brief GetCPUBufferArray関数
 * @return cpu_buf_ary (cpu_buffer_array)
 */
inline tml::DynamicBuffer *tml::graphic::Texture::GetCPUBufferArray(void)
{
	return (this->current_->cpu_buf_cont_.data());
}


/**
 * @brief GetCPUBuffer関数
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return cpu_buf (cpu_buffer)<br>
 * nullptr=失敗
 */
inline tml::DynamicBuffer *tml::graphic::Texture::GetCPUBuffer(const UINT ary_index, const UINT mm_index)
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->current_->tex_desc_.MipLevels);

	if (cpu_buf_index >= this->current_->cpu_buf_cont_.size()) {
		return (nullptr);
	}

	return (&this->current_->cpu_buf_cont_[cpu_buf_index]);
}


/**
 * @brief GetCPUBufferFast関数
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return cpu_buf (cpu_buffer)<br>
 * nullptr=失敗
 */
inline tml::DynamicBuffer *tml::graphic::Texture::GetCPUBufferFast(const UINT ary_index, const UINT mm_index)
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->current_->tex_desc_.MipLevels);

	return (&this->current_->cpu_buf_cont_[cpu_buf_index]);
}


/**
 * @brief GetMappedSubresourceCount関数
 * @return msr_cnt (mapped_subresource_count)
 */
inline UINT tml::graphic::Texture::GetMappedSubresourceCount(void) const
{
	return (this->current_->msr_cont_.size());
}


/**
 * @brief GetMappedSubresourceArray関数
 * @return msr_ary (mapped_subresource_array)
 */
inline const D3D11_MAPPED_SUBRESOURCE *tml::graphic::Texture::GetMappedSubresourceArray(void) const
{
	return (this->current_->msr_cont_.data());
}


/**
 * @brief GetMappedSubresource関数
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return msr (mapped_subresource)<br>
 * nullptr=失敗
 */
inline const D3D11_MAPPED_SUBRESOURCE *tml::graphic::Texture::GetMappedSubresource(const UINT ary_index, const UINT mm_index) const
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->current_->tex_desc_.MipLevels);

	if (cpu_buf_index >= this->current_->msr_cont_.size()) {
		return (nullptr);
	}

	return (&this->current_->msr_cont_[cpu_buf_index]);
}


/**
 * @brief GetMappedSubresourceFast関数
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return msr (mapped_subresource)<br>
 * nullptr=失敗
 */
inline const D3D11_MAPPED_SUBRESOURCE *tml::graphic::Texture::GetMappedSubresourceFast(const UINT ary_index, const UINT mm_index) const
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->current_->tex_desc_.MipLevels);

	return (&this->current_->msr_cont_[cpu_buf_index]);
}


/**
 * @brief GetRenderTarget関数
 * @return rt (render_target)
 */
inline ID3D11RenderTargetView *tml::graphic::Texture::GetRenderTarget(void)
{
	return (this->current_->rt_);
}


/**
 * @brief GetDepthTarget関数
 * @return dt (depth_target)
 */
inline ID3D11DepthStencilView *tml::graphic::Texture::GetDepthTarget(void)
{
	return (this->current_->dt_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::graphic::Texture::GetSR(void)
{
	return (this->current_->sr_);
}


/**
 * @brief GetUASR関数
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::graphic::Texture::GetUASR(void)
{
	return (this->current_->uasr_);
}


/**
 * @brief GetAtlasTexture関数
 * @return atlas_tex (atlas_texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Texture::GetAtlasTexture(void)
{
	return (this->atlas_tex_);
}


/**
 * @brief GetAtlasRect関数
 * @return atlas_rect (atlas_rect)
 */
inline const tml::graphic::AtlasRect &tml::graphic::Texture::GetAtlasRect(void) const
{
	return (this->atlas_rect_);
}
