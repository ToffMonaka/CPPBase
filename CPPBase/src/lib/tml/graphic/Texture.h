/**
 * @file
 * @brief Textureヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMath.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief TextureDescクラス
 */
class TextureDesc : public tml::graphic::ResourceDesc
{
public:
	IDXGISwapChain *swap_chain;
	std::vector<tml::BinaryFileReadDesc> file_read_desc_container;
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

protected:
	void Release(void);

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
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Textureクラス
 */
class Texture : public tml::graphic::Resource
{
public: Texture(const tml::graphic::Texture &) = delete;
public: tml::graphic::Texture &operator =(const tml::graphic::Texture &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11Texture2D *tex_;
	CD3D11_TEXTURE2D_DESC tex_desc_;
	std::vector<tml::XMUINT2EX> size_cont_;
	std::vector<tml::DynamicBuffer> cpu_buf_cont_;
	std::vector<D3D11_MAPPED_SUBRESOURCE> msr_cont_;
	std::vector<tml::DynamicBuffer> clear_cpu_buf_cont_;
	ID3D11RenderTargetView *rt_;
	ID3D11DepthStencilView *dt_;
	ID3D11ShaderResourceView *sr_;
	ID3D11UnorderedAccessView *uasr_;

protected:
	void Release(void);

public:
	Texture();
	virtual ~Texture();

	virtual void Init(void);
	INT Create(const tml::graphic::TextureDesc &);

	ID3D11Texture2D *GetTexture(void);
	const CD3D11_TEXTURE2D_DESC &GetTextureDesc(void) const;
	UINT GetSizeCount(void) const;
	const tml::XMUINT2EX *GetSize(const UINT) const;
	const tml::XMUINT2EX *GetSizeArray(void) const;
	UINT GetCPUBufferCount(void) const;
	tml::DynamicBuffer *GetCPUBuffer(const UINT, const UINT);
	tml::DynamicBuffer *GetCPUBufferArray(void);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
	UINT GetMappedSubresourceCount(void) const;
	const D3D11_MAPPED_SUBRESOURCE *GetMappedSubresource(const UINT, const UINT) const;
	const D3D11_MAPPED_SUBRESOURCE *GetMappedSubresourceArray(void) const;
	void ClearCPUBuffer(void);
	void DrawCPUBufferString(const WCHAR *, const tml::XMINT2EX &, tml::graphic::Font *);
	ID3D11RenderTargetView *GetRenderTarget(void);
	void ClearRenderTarget(const tml::XMFLOAT4EX &);
	ID3D11DepthStencilView *GetDepthTarget(void);
	void ClearDepthTarget(void);
	ID3D11ShaderResourceView *GetSR(void);
	ID3D11UnorderedAccessView *GetUASR(void);
};
}
}


/**
 * @brief GetTexture関数
 * @return tex (texture)
 */
inline ID3D11Texture2D *tml::graphic::Texture::GetTexture(void)
{
	return (this->tex_);
}


/**
 * @brief GetTextureDesc関数
 * @return tex_desc (texture_desc)
 */
inline const CD3D11_TEXTURE2D_DESC &tml::graphic::Texture::GetTextureDesc(void) const
{
	return (this->tex_desc_);
}


/**
 * @brief GetSizeCount関数
 * @return size_cnt (size_count)
 */
inline UINT tml::graphic::Texture::GetSizeCount(void) const
{
	return (this->size_cont_.size());
}


/**
 * @brief GetSize関数
 * @param mm_index (mipmap_index)
 * @return size (size)<br>
 * nullptr=失敗
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetSize(const UINT mm_index) const
{
	if (mm_index >= this->tex_desc_.MipLevels) {
		return (nullptr);
	}

	return (&this->size_cont_[mm_index]);
}


/**
 * @brief GetSizeArray関数
 * @return size_ary (size_array)
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetSizeArray(void) const
{
	return (this->size_cont_.data());
}


/**
 * @brief GetCPUBufferCount関数
 * @return cpu_buf_cnt (cpu_buffer_count)
 */
inline UINT tml::graphic::Texture::GetCPUBufferCount(void) const
{
	return (this->cpu_buf_cont_.size());
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
	if ((ary_index >= this->tex_desc_.ArraySize)
	|| (mm_index >= this->tex_desc_.MipLevels)) {
		return (nullptr);
	}

	return (&this->cpu_buf_cont_[D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels)]);
}


/**
 * @brief GetCPUBufferArray関数
 * @return cpu_buf_ary (cpu_buffer_array)
 */
inline tml::DynamicBuffer *tml::graphic::Texture::GetCPUBufferArray(void)
{
	return (this->cpu_buf_cont_.data());
}


/**
 * @brief GetMappedSubresourceCount関数
 * @return msr_cnt (mapped_subresource_count)
 */
inline UINT tml::graphic::Texture::GetMappedSubresourceCount(void) const
{
	return (this->msr_cont_.size());
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
	if ((ary_index >= this->tex_desc_.ArraySize)
	|| (mm_index >= this->tex_desc_.MipLevels)) {
		return (nullptr);
	}

	return (&this->msr_cont_[D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels)]);
}


/**
 * @brief GetMappedSubresourceArray関数
 * @return msr_ary (mapped_subresource_array)
 */
inline const D3D11_MAPPED_SUBRESOURCE *tml::graphic::Texture::GetMappedSubresourceArray(void) const
{
	return (this->msr_cont_.data());
}


/**
 * @brief GetRenderTarget関数
 * @return rt (render_target)
 */
inline ID3D11RenderTargetView *tml::graphic::Texture::GetRenderTarget(void)
{
	return (this->rt_);
}


/**
 * @brief GetDepthTarget関数
 * @return dt (depth_target)
 */
inline ID3D11DepthStencilView *tml::graphic::Texture::GetDepthTarget(void)
{
	return (this->dt_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::graphic::Texture::GetSR(void)
{
	return (this->sr_);
}


/**
 * @brief GetUASR関数
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::graphic::Texture::GetUASR(void)
{
	return (this->uasr_);
}
