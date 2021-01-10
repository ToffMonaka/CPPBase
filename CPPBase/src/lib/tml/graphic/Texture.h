/**
 * @file
 * @brief Textureヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
#include "../math/XNAMath.h"
#include "../file/BinaryFile.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief TextureDescクラス
 */
class TextureDesc : public tml::GraphicResourceDesc
{
public:
	std::list<tml::BinaryFileReadPlan> file_read_plan_container;
	CD3D11_TEXTURE2D_DESC texture_desc;
	DXGI_FORMAT render_target_format;
	bool render_target_desc_null_flag;
	DXGI_FORMAT depth_target_format;
	bool depth_target_desc_null_flag;
	DXGI_FORMAT sr_format;
	bool sr_desc_null_flag;
	DXGI_FORMAT uasr_format;
	bool uasr_desc_null_flag;
	bool swap_chain_flag;
	bool array_flag;

public:
	TextureDesc();
	virtual ~TextureDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Textureクラス
 */
class Texture : public tml::GraphicResource
{
public: Texture(const tml::Texture &) = delete;
public: tml::Texture &operator =(const tml::Texture &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11Texture2D *tex_;
	tml::XMFLOAT2EX size_;
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
	INT Create(tml::TextureDesc &);

	ID3D11Texture2D *GetTexture(void) const;
	const tml::XMFLOAT2EX &GetSize(void) const;
	ID3D11RenderTargetView *GetRenderTarget(void) const;
	void ClearRenderTarget(const tml::XMFLOAT4EX &);
	ID3D11DepthStencilView *GetDepthTarget(void) const;
	void ClearDepthTarget(void);
	ID3D11ShaderResourceView *GetSR(void) const;
	ID3D11UnorderedAccessView *GetUASR(void) const;
};
}


/**
 * @brief GetTexture関数
 * @return tex (texture)
 */
inline ID3D11Texture2D *tml::Texture::GetTexture(void) const
{
	return (this->tex_);
}


/**
 * @brief GetSize関数
 * @return size (size)
 */
inline const tml::XMFLOAT2EX &tml::Texture::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief GetRenderTarget関数
 * @return rt (render_target)
 */
inline ID3D11RenderTargetView *tml::Texture::GetRenderTarget(void) const
{
	return (this->rt_);
}


/**
 * @brief GetDepthTarget関数
 * @return dt (depth_target)
 */
inline ID3D11DepthStencilView *tml::Texture::GetDepthTarget(void) const
{
	return (this->dt_);
}


/**
 * @brief GetSR関数
 * @return sr (sr)
 */
inline ID3D11ShaderResourceView *tml::Texture::GetSR(void) const
{
	return (this->sr_);
}


/**
 * @brief GetUASR関数
 * @return uasr (uasr)
 */
inline ID3D11UnorderedAccessView *tml::Texture::GetUASR(void) const
{
	return (this->uasr_);
}
