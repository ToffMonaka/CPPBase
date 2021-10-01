/**
 * @file
 * @brief Texture�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathINT.h"
#include "../math/XNAMathUINT.h"
#include "../math/XNAMathFLOAT.h"
#include "ManagerResource.h"
#include "Font.h"


namespace tml {
namespace graphic {
/**
 * @brief TextureDesc�N���X
 */
class TextureDesc : public tml::graphic::ManagerResourceDesc
{
public:
	IDXGISwapChain *swap_chain;
	std::vector<tml::BinaryFileReadDesc> image_file_read_desc_container;
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
 * @brief Release�֐�
 */
inline void tml::graphic::TextureDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Texture�N���X
 */
class Texture : public tml::graphic::ManagerResource
{
public: Texture(const tml::graphic::Texture &) = delete;
public: tml::graphic::Texture &operator =(const tml::graphic::Texture &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::TEXTURE);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::TEXTURE_TYPE::BASE);

private:
	ID3D11Texture2D *tex_;
	CD3D11_TEXTURE2D_DESC tex_desc_;
	tml::XMUINT2EX size_;
	std::vector<tml::XMUINT2EX> mm_size_cont_;
	std::vector<tml::DynamicBuffer> cpu_buf_cont_;
	std::vector<D3D11_MAPPED_SUBRESOURCE> msr_cont_;
	std::vector<tml::DynamicBuffer> clear_cpu_buf_cont_;
	std::vector<LONG> str_line_w_cont_;
	ID3D11RenderTargetView *rt_;
	ID3D11DepthStencilView *dt_;
	ID3D11ShaderResourceView *sr_;
	ID3D11UnorderedAccessView *uasr_;

private:
	void Release(void);

public:
	Texture();
	virtual ~Texture();

	virtual void Init(void);
	INT Create(const tml::graphic::TextureDesc &);

	ID3D11Texture2D *GetTexture(void);
	const CD3D11_TEXTURE2D_DESC &GetTextureDesc(void) const;
	const tml::XMUINT2EX &GetSize(void) const;
	UINT GetMipmapCount(void) const;
	const std::vector<tml::XMUINT2EX> &GetMipmapSizeContainer(void) const;
	const tml::XMUINT2EX *GetMipmapSize(const UINT) const;
	const tml::XMUINT2EX *GetMipmapSizeFast(const UINT) const;
	UINT GetCPUBufferCount(void) const;
	tml::DynamicBuffer *GetCPUBuffer(const UINT, const UINT);
	tml::DynamicBuffer *GetCPUBufferFast(const UINT, const UINT);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
	UINT GetMappedSubresourceCount(void) const;
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
};
}
}


/**
 * @brief GetTexture�֐�
 * @return tex (texture)
 */
inline ID3D11Texture2D *tml::graphic::Texture::GetTexture(void)
{
	return (this->tex_);
}


/**
 * @brief GetTextureDesc�֐�
 * @return tex_desc (texture_desc)
 */
inline const CD3D11_TEXTURE2D_DESC &tml::graphic::Texture::GetTextureDesc(void) const
{
	return (this->tex_desc_);
}


/**
 * @brief GetSize�֐�
 * @return size (size)
 */
inline const tml::XMUINT2EX &tml::graphic::Texture::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief GetMipmapCount�֐�
 * @return mm_cnt (mm_cnt)
 */
inline UINT tml::graphic::Texture::GetMipmapCount(void) const
{
	return (this->mm_size_cont_.size());
}


/**
 * @brief GetMipmapSizeContainer�֐�
 * @return mm_size_cont (mm_size_container)
 */
inline const std::vector<tml::XMUINT2EX> &tml::graphic::Texture::GetMipmapSizeContainer(void) const
{
	return (this->mm_size_cont_);
}


/**
 * @brief GetMipmapSize�֐�
 * @param mm_index (mipmap_index)
 * @return size (size)<br>
 * nullptr=���s
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetMipmapSize(const UINT mm_index) const
{
	if (mm_index >= this->mm_size_cont_.size()) {
		return (nullptr);
	}

	return (&this->mm_size_cont_[mm_index]);
}


/**
 * @brief GetMipmapSizeFast�֐�
 * @param mm_index (mipmap_index)
 * @return size (size)<br>
 * nullptr=���s
 */
inline const tml::XMUINT2EX *tml::graphic::Texture::GetMipmapSizeFast(const UINT mm_index) const
{
	return (&this->mm_size_cont_[mm_index]);
}


/**
 * @brief GetCPUBufferCount�֐�
 * @return cpu_buf_cnt (cpu_buffer_count)
 */
inline UINT tml::graphic::Texture::GetCPUBufferCount(void) const
{
	return (this->cpu_buf_cont_.size());
}


/**
 * @brief GetCPUBuffer�֐�
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return cpu_buf (cpu_buffer)<br>
 * nullptr=���s
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
 * @brief GetCPUBufferFast�֐�
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return cpu_buf (cpu_buffer)<br>
 * nullptr=���s
 */
inline tml::DynamicBuffer *tml::graphic::Texture::GetCPUBufferFast(const UINT ary_index, const UINT mm_index)
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels);

	return (&this->cpu_buf_cont_[cpu_buf_index]);
}


/**
 * @brief GetMappedSubresourceCount�֐�
 * @return msr_cnt (mapped_subresource_count)
 */
inline UINT tml::graphic::Texture::GetMappedSubresourceCount(void) const
{
	return (this->msr_cont_.size());
}


/**
 * @brief GetMappedSubresource�֐�
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return msr (mapped_subresource)<br>
 * nullptr=���s
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
 * @brief GetMappedSubresourceFast�֐�
 * @param ary_index (array_index)
 * @param mm_index (mipmap_index)
 * @return msr (mapped_subresource)<br>
 * nullptr=���s
 */
inline const D3D11_MAPPED_SUBRESOURCE *tml::graphic::Texture::GetMappedSubresourceFast(const UINT ary_index, const UINT mm_index) const
{
	UINT cpu_buf_index = D3D11CalcSubresource(mm_index, ary_index, this->tex_desc_.MipLevels);

	return (&this->msr_cont_[cpu_buf_index]);
}


/**
 * @brief GetRenderTarget�֐�
 * @return rt (render_target)
 */
inline ID3D11RenderTargetView *tml::graphic::Texture::GetRenderTarget(void)
{
	return (this->rt_);
}


/**
 * @brief GetDepthTarget�֐�
 * @return dt (depth_target)
 */
inline ID3D11DepthStencilView *tml::graphic::Texture::GetDepthTarget(void)
{
	return (this->dt_);
}


/**
 * @brief GetSR�֐�
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::graphic::Texture::GetSR(void)
{
	return (this->sr_);
}


/**
 * @brief GetUASR�֐�
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::graphic::Texture::GetUASR(void)
{
	return (this->uasr_);
}
