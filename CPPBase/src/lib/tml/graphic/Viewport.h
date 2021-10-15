/**
 * @file
 * @brief Viewport�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantInclude_Direct3DBase.h"
#include "../math/XNAMathVector.h"


namespace tml {
namespace graphic {
/**
 * @brief Viewport�N���X
 */
class Viewport
{
private:
	D3D11_VIEWPORT vp_;

private:
	void Release(void);

public:
	Viewport();
	Viewport(const D3D11_VIEWPORT &);
	Viewport(const FLOAT, const FLOAT, const FLOAT, const FLOAT);
	Viewport(const FLOAT, const FLOAT, const FLOAT, const FLOAT, const FLOAT, const FLOAT);
	Viewport(const tml::graphic::Viewport &);
	tml::graphic::Viewport &operator =(const tml::graphic::Viewport &);
	Viewport(tml::graphic::Viewport &&) noexcept;
	tml::graphic::Viewport &operator =(tml::graphic::Viewport &&) noexcept;
	virtual ~Viewport();

	virtual void Init(void);
	virtual void Init(const D3D11_VIEWPORT &);
	virtual void Init(const FLOAT, const FLOAT, const FLOAT, const FLOAT);
	virtual void Init(const FLOAT, const FLOAT, const FLOAT, const FLOAT, const FLOAT, const FLOAT);

	const D3D11_VIEWPORT &Get(void) const;
	void Set(const D3D11_VIEWPORT &);
	FLOAT GetX(void) const;
	void SetX(const FLOAT);
	FLOAT GetY(void) const;
	void SetY(const FLOAT);
	FLOAT GetWidth(void) const;
	void SetWidth(const FLOAT);
	FLOAT GetHeight(void) const;
	void SetHeight(const FLOAT);
	FLOAT GetMinDepth(void) const;
	void SetMinDepth(const FLOAT);
	FLOAT GetMaxDepth(void) const;
	void SetMaxDepth(const FLOAT);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Viewport::Release(void)
{
	return;
}


/**
 * @brief Get�֐�
 * @return vp (viewport)
 */
inline const D3D11_VIEWPORT &tml::graphic::Viewport::Get(void) const
{
	return (this->vp_);
}


/**
 * @brief Set�֐�
 * @param vp (viewport)
 */
inline void tml::graphic::Viewport::Set(const D3D11_VIEWPORT &vp)
{
	this->vp_ = vp;

	return;
}


/**
 * @brief GetX�֐�
 * @return x (x)
 */
inline FLOAT tml::graphic::Viewport::GetX(void) const
{
	return (this->vp_.TopLeftX);
}


/**
 * @brief SetX�֐�
 * @param x (x)
 */
inline void tml::graphic::Viewport::SetX(const FLOAT x)
{
	this->vp_.TopLeftX = x;

	return;
}


/**
 * @brief GetY�֐�
 * @return y (y)
 */
inline FLOAT tml::graphic::Viewport::GetY(void) const
{
	return (this->vp_.TopLeftY);
}


/**
 * @brief SetY�֐�
 * @param y (y)
 */
inline void tml::graphic::Viewport::SetY(const FLOAT y)
{
	this->vp_.TopLeftY = y;

	return;
}


/**
 * @brief GetWidth�֐�
 * @return w (width)
 */
inline FLOAT tml::graphic::Viewport::GetWidth(void) const
{
	return (this->vp_.Width);
}


/**
 * @brief SetWidth�֐�
 * @param w (width)
 */
inline void tml::graphic::Viewport::SetWidth(const FLOAT w)
{
	this->vp_.Width = w;

	return;
}


/**
 * @brief GetHeight�֐�
 * @return h (height)
 */
inline FLOAT tml::graphic::Viewport::GetHeight(void) const
{
	return (this->vp_.Height);
}


/**
 * @brief SetHeight�֐�
 * @param h (height)
 */
inline void tml::graphic::Viewport::SetHeight(const FLOAT h)
{
	this->vp_.Height = h;

	return;
}


/**
 * @brief GetMinDepth�֐�
 * @return min_depth (min_depth)
 */
inline FLOAT tml::graphic::Viewport::GetMinDepth(void) const
{
	return (this->vp_.MinDepth);
}


/**
 * @brief SetMinDepth�֐�
 * @param min_depth (min_depth)
 */
inline void tml::graphic::Viewport::SetMinDepth(const FLOAT min_depth)
{
	this->vp_.MinDepth = min_depth;

	return;
}


/**
 * @brief GetMaxDepth�֐�
 * @return max_depth (max_depth)
 */
inline FLOAT tml::graphic::Viewport::GetMaxDepth(void) const
{
	return (this->vp_.MaxDepth);
}


/**
 * @brief SetMaxDepth�֐�
 * @param max_depth (max_depth)
 */
inline void tml::graphic::Viewport::SetMaxDepth(const FLOAT max_depth)
{
	this->vp_.MaxDepth = max_depth;

	return;
}
