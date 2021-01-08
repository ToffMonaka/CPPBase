/**
 * @file
 * @brief Viewport�w�b�_�[�t�@�C��
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
 * @brief Viewport�N���X
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


/**
 * @brief Set�֐�
 * @param pos (position)
 * @param size (size)
 */
inline void tml::Viewport::Set(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size)
{
	this->vp_ = CD3D11_VIEWPORT(pos.x, pos.y, size.x, size.y, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH);

	return;
}


/**
 * @brief GetX�֐�
 * @return x (x)
 */
inline FLOAT tml::Viewport::GetX(void) const
{
	return (this->vp_.TopLeftX);
}


/**
 * @brief SetX�֐�
 * @param x (x)
 */
inline void tml::Viewport::SetX(const FLOAT x)
{
	this->vp_.TopLeftX = x;
	
	return;
}


/**
 * @brief GetY�֐�
 * @return y (y)
 */
inline FLOAT tml::Viewport::GetY(void) const
{
	return (this->vp_.TopLeftY);
}


/**
 * @brief SetY�֐�
 * @param y (y)
 */
inline void tml::Viewport::SetY(const FLOAT y)
{
	this->vp_.TopLeftY = y;
	
	return;
}


/**
 * @brief GetWidth�֐�
 * @return w (width)
 */
inline FLOAT tml::Viewport::GetWidth(void) const
{
	return (this->vp_.Width);
}


/**
 * @brief SetWidth�֐�
 * @param w (width)
 */
inline void tml::Viewport::SetWidth(const FLOAT w)
{
	this->vp_.Width = w;
	
	return;
}


/**
 * @brief GetHeight�֐�
 * @return h (height)
 */
inline FLOAT tml::Viewport::GetHeight(void) const
{
	return (this->vp_.Height);
}


/**
 * @brief SetHeight�֐�
 * @param h (height)
 */
inline void tml::Viewport::SetHeight(const FLOAT h)
{
	this->vp_.Height = h;
	
	return;
}


/**
 * @brief GetViewport�֐�
 * @return vp (viewport)
 */
inline const CD3D11_VIEWPORT &tml::Viewport::GetViewport(void) const
{
	return (this->vp_);
}
