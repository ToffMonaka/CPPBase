/**
 * @file
 * @brief Viewportヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#pragma warning(pop)
#include "../math/XNAMath.h"


namespace tml {
namespace graphic {
/**
 * @brief Viewportクラス
 */
class Viewport
{
public: Viewport(const tml::graphic::Viewport &) = delete;
public: tml::graphic::Viewport &operator =(const tml::graphic::Viewport &) = delete;

private:
	CD3D11_VIEWPORT vp_;

public:
	Viewport();
	Viewport(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	virtual ~Viewport();

	virtual void Init(void);

	void Set(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	FLOAT GetX(void) const;
	void SetX(const FLOAT);
	FLOAT GetY(void) const;
	void SetY(const FLOAT);
	FLOAT GetWidth(void) const;
	void SetWidth(const FLOAT);
	FLOAT GetHeight(void) const;
	void SetHeight(const FLOAT);
	const CD3D11_VIEWPORT &GetViewport(void) const;
};
}
}


/**
 * @brief Set関数
 * @param pos (position)
 * @param size (size)
 */
inline void tml::graphic::Viewport::Set(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size)
{
	this->vp_ = CD3D11_VIEWPORT(pos.x, pos.y, size.x, size.y, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH);

	return;
}


/**
 * @brief GetX関数
 * @return x (x)
 */
inline FLOAT tml::graphic::Viewport::GetX(void) const
{
	return (this->vp_.TopLeftX);
}


/**
 * @brief SetX関数
 * @param x (x)
 */
inline void tml::graphic::Viewport::SetX(const FLOAT x)
{
	this->vp_.TopLeftX = x;
	
	return;
}


/**
 * @brief GetY関数
 * @return y (y)
 */
inline FLOAT tml::graphic::Viewport::GetY(void) const
{
	return (this->vp_.TopLeftY);
}


/**
 * @brief SetY関数
 * @param y (y)
 */
inline void tml::graphic::Viewport::SetY(const FLOAT y)
{
	this->vp_.TopLeftY = y;
	
	return;
}


/**
 * @brief GetWidth関数
 * @return w (width)
 */
inline FLOAT tml::graphic::Viewport::GetWidth(void) const
{
	return (this->vp_.Width);
}


/**
 * @brief SetWidth関数
 * @param w (width)
 */
inline void tml::graphic::Viewport::SetWidth(const FLOAT w)
{
	this->vp_.Width = w;
	
	return;
}


/**
 * @brief GetHeight関数
 * @return h (height)
 */
inline FLOAT tml::graphic::Viewport::GetHeight(void) const
{
	return (this->vp_.Height);
}


/**
 * @brief SetHeight関数
 * @param h (height)
 */
inline void tml::graphic::Viewport::SetHeight(const FLOAT h)
{
	this->vp_.Height = h;
	
	return;
}


/**
 * @brief GetViewport関数
 * @return vp (viewport)
 */
inline const CD3D11_VIEWPORT &tml::graphic::Viewport::GetViewport(void) const
{
	return (this->vp_);
}
