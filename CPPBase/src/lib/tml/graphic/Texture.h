/**
 * @file
 * @brief TextureÉwÉbÉ_Å[ÉtÉ@ÉCÉã
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMath.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief TextureDescÉNÉâÉX
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
 * @brief Releaseä÷êî
 */
inline void tml::graphic::TextureDesc::Release(void)
{
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief TextureÉNÉâÉX
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
	const tml::XMUINT2EX *GetSizeFast(const UINT) const;
	UINT GetCPUBufferCount(void) const;
	tml::DynamicBuffer *GetCPUBuffer(const UINT, const UINT);
	tml::DynamicBuffer *GetCPUBufferFast(const UINT, const UINT);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
	UINT GetMappedSubresourceCount(void) const;
	const D3D11_MAPPED_SUBRESOURCE *GetMappedSubresource(const UINT, const UINT) const;
	const D3D11_MAPPED_SUBRESOURCE *GetMappedSubresourceFast(const UINT, const UINT) const;
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
 * @brief GetTextureä÷êî
 * @return tex (texture)
 */
inline ID3D11Texture2D *tml::graphic::Texture::GetTexture(void)
{
	return (this->tex_);
}


/**
 * @brief GetTextureDescä÷êî
 * @return tex_desc (texture_desc)
 */
inline const CD3D11_TEXTURE2D_DESC &tml::graphic::Texture::GetTextureDesc(void) const
{
	return (this->tex_desc_);
}


/**
 * @brief GetSizeCountä÷êî
 * @return size_cnt (size_count)
 */
inline UINT tml::graphic::Texture::GetSizeCount(void) const
{
	return (this->size_cont_.size());
}


/**
 * @brief GetSizeä÷êî
 * @param mm_index (mipmap_index)
 * @return size (size)<br>
 * nullptr=é∏îs
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetSize(const UINT mm_index) const
{
	if (mm_index >= this->size_cont_.size()) {
		return (nullptr);
	}

	return (&this->size_cont_[mm_index]);
}


/**
 * @brief GetSizeFastä÷êî
 * @param mm_index (mipmap_index)
 * @return size (size)<br>
 * nullptr=é∏îs
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetSizeFast(const UINT mm_index) const
{
	return (&this->size_cont_[mm_index]);
}


/**
 * @brief GetCPUBufferCountä÷êî
 * @return cpu_buf_cnt (cpu_buffer_count)
 */
inline UINT tml::graphic::Texture::GetCPUBufferCount(void) const
{
	return (this->cpu_buf_cont_.size());
}


/**
 * @brief GetCPUBufferä÷êî
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return cpu_buf (cpu_buffer)<br>
 * nullptr=é∏îs
 */
inline tml::DynamicBuffer *tml::graphic::Texture::GetCPUBuffer(const UINT ary_index, const UINT mm_index)
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels);

	if (cpu_buf_index >= this->cpu_buf_cont_.size()) {
		return (nullptr);
	}

	return (&this->cpu_buf_cont_[cpu_buf_index]);
}


/**
 * @brief GetCPUBufferFastä÷êî
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return cpu_buf (cpu_buffer)<br>
 * nullptr=é∏îs
 */
inline tml::DynamicBuffer *tml::graphic::Texture::GetCPUBufferFast(const UINT ary_index, const UINT mm_index)
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels);

	return (&this->cpu_buf_cont_[cpu_buf_index]);
}


/**
 * @brief GetMappedSubresourceCountä÷êî
 * @return msr_cnt (mapped_subresource_count)
 */
inline UINT tml::graphic::Texture::GetMappedSubresourceCount(void) const
{
	return (this->msr_cont_.size());
}


/**
 * @brief GetMappedSubresourceä÷êî
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return msr (mapped_subresource)<br>
 * nullptr=é∏îs
 */
inline const D3D11_MAPPED_SUBRESOURCE *tml::graphic::Texture::GetMappedSubresource(const UINT ary_index, const UINT mm_index) const
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels);

	if (cpu_buf_index >= this->msr_cont_.size()) {
		return (nullptr);
	}

	return (&this->msr_cont_[cpu_buf_index]);
}


/**
 * @brief GetMappedSubresourceFastä÷êî
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return msr (mapped_subresource)<br>
 * nullptr=é∏îs
 */
inline const D3D11_MAPPED_SUBRESOURCE *tml::graphic::Texture::GetMappedSubresourceFast(const UINT ary_index, const UINT mm_index) const
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels);

	return (&this->msr_cont_[cpu_buf_index]);
}


/**
 * @brief GetRenderTargetä÷êî
 * @return rt (render_target)
 */
inline ID3D11RenderTargetView *tml::graphic::Texture::GetRenderTarget(void)
{
	return (this->rt_);
}


/**
 * @brief GetDepthTargetä÷êî
 * @return dt (depth_target)
 */
inline ID3D11DepthStencilView *tml::graphic::Texture::GetDepthTarget(void)
{
	return (this->dt_);
}


/**
 * @brief GetSRä÷êî
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::graphic::Texture::GetSR(void)
{
	return (this->sr_);
}


/**
 * @brief GetUASRä÷êî
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::graphic::Texture::GetUASR(void)
{
	return (this->uasr_);
}
