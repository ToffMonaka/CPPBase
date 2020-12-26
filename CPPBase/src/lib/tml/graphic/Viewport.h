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
/**
 * @brief Viewportクラス
 */
class Viewport
{
public: Viewport(const tml::Viewport &) = delete;
public: tml::Viewport &operator =(const tml::Viewport &) = delete;

private:
	CD3D11_VIEWPORT vp_;

public:
	Viewport();
	Viewport(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	virtual ~Viewport();

	virtual void Init(void);

	const CD3D11_VIEWPORT &Get(void) const;
	void Set(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	void SetX(const FLOAT);
	void SetY(const FLOAT);
	void SetWidth(const FLOAT);
	void SetHeight(const FLOAT);
};
}


/**
 * @brief Get関数
 * @return vp (viewport)
 */
inline const CD3D11_VIEWPORT &tml::Viewport::Get(void) const
{
	return (this->vp_);
}


/**
 * @brief Set関数
 * @param pos (position)
 * @param size (size)
 */
inline void tml::Viewport::Set(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size)
{
	this->vp_ = CD3D11_VIEWPORT(pos.x, pos.y, size.x, size.y, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH);

	return;
}


/**
 * @brief SetX関数
 * @param x (x)
 */
inline void tml::Viewport::SetX(const FLOAT x)
{
	this->vp_.TopLeftX = x;
	
	return;
}


/**
 * @brief SetY関数
 * @param y (y)
 */
inline void tml::Viewport::SetY(const FLOAT y)
{
	this->vp_.TopLeftY = y;
	
	return;
}


/**
 * @brief SetWidth関数
 * @param w (width)
 */
inline void tml::Viewport::SetWidth(const FLOAT w)
{
	this->vp_.Width = w;
	
	return;
}


/**
 * @brief SetHeight関数
 * @param h (height)
 */
inline void tml::Viewport::SetHeight(const FLOAT h)
{
	this->vp_.Height = h;
	
	return;
}
