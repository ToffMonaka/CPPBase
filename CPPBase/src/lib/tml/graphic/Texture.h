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
	std::vector<tml::BinaryFileReadDesc> file_read_desc_container;
	IDXGISwapChain *swap_chain;
	CD3D11_TEXTURE2D_DESC texture_desc;
	bool buffer_flag;
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

	void SetTextureDesc(const tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_TYPE_FLAG, const DXGI_FORMAT tex_desc_format = DXGI_FORMAT_UNKNOWN, const XMUINT2EX &tex_desc_size = XMUINT2EX(0U), const UINT tex_desc_buf_cnt = 1U, const UINT tex_desc_mm_cnt = 1U, const DXGI_SAMPLE_DESC &tex_desc_ms_desc = {1U, 0U});
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
	tml::XMUINT2EX size_;
	tml::DynamicBuffer buf_;
	tml::DynamicBuffer clear_buf_;
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
	const tml::XMUINT2EX &GetSize(void) const;
	tml::DynamicBuffer &GetBuffer(void);
	void ClearBuffer(void);
	void UpdateBuffer(void);
	void DrawBuffer(const WCHAR *);
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
 * @brief GetSize関数
 * @return size (size)
 */
inline const tml::XMUINT2EX &tml::graphic::Texture::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline tml::DynamicBuffer &tml::graphic::Texture::GetBuffer(void)
{
	return (this->buf_);
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
