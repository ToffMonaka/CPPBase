/**
 * @file
 * @brief Viewport�R�[�h�t�@�C��
 */


#include "Viewport.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Viewport::Viewport()
{
	this->vp_.TopLeftX = 0.0f;
	this->vp_.TopLeftY = 0.0f;
	this->vp_.Width = 0.0f;
	this->vp_.Height = 0.0f;
	this->vp_.MinDepth = D3D11_MIN_DEPTH;
	this->vp_.MaxDepth = D3D11_MAX_DEPTH;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param vp (viewport)
 */
tml::graphic::Viewport::Viewport(const D3D11_VIEWPORT &vp)
{
	this->vp_ = vp;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param pos (position)
 * @param size (size)
 */
tml::graphic::Viewport::Viewport(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size)
{
	this->vp_.TopLeftX = pos.x;
	this->vp_.TopLeftY = pos.y;
	this->vp_.Width = size.x;
	this->vp_.Height = size.y;
	this->vp_.MinDepth = D3D11_MIN_DEPTH;
	this->vp_.MaxDepth = D3D11_MAX_DEPTH;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param pos (position)
 * @param size (size)
 * @param depth (depth)
 */
tml::graphic::Viewport::Viewport(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size, const tml::XMFLOAT2EX &depth)
{
	this->vp_.TopLeftX = pos.x;
	this->vp_.TopLeftY = pos.y;
	this->vp_.Width = size.x;
	this->vp_.Height = size.y;
	this->vp_.MinDepth = depth.x;
	this->vp_.MaxDepth = depth.y;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::graphic::Viewport::Viewport(const tml::graphic::Viewport &src)
{
	this->vp_ = src.vp_;

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::graphic::Viewport &tml::graphic::Viewport::operator =(const tml::graphic::Viewport &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->vp_ = src.vp_;

	return ((*this));
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::graphic::Viewport::Viewport(tml::graphic::Viewport &&src) noexcept
{
	this->vp_ = src.vp_;

	src.Init();

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::graphic::Viewport &tml::graphic::Viewport::operator =(tml::graphic::Viewport &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->vp_ = src.vp_;

	src.Init();

	return ((*this));
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Viewport::~Viewport()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Viewport::Init(void)
{
	this->Release();

	this->vp_.TopLeftX = 0.0f;
	this->vp_.TopLeftY = 0.0f;
	this->vp_.Width = 0.0f;
	this->vp_.Height = 0.0f;
	this->vp_.MinDepth = D3D11_MIN_DEPTH;
	this->vp_.MaxDepth = D3D11_MAX_DEPTH;

	return;
}


/**
 * @brief Init�֐�
 * @param vp (viewport)
 */
inline void tml::graphic::Viewport::Init(const D3D11_VIEWPORT &vp)
{
	this->Release();

	this->vp_ = vp;

	return;
}


/**
 * @brief Init�֐�
 * @param pos (position)
 * @param size (size)
 */
inline void tml::graphic::Viewport::Init(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size)
{
	this->Release();

	this->vp_.TopLeftX = pos.x;
	this->vp_.TopLeftY = pos.y;
	this->vp_.Width = size.x;
	this->vp_.Height = size.y;
	this->vp_.MinDepth = D3D11_MIN_DEPTH;
	this->vp_.MaxDepth = D3D11_MAX_DEPTH;

	return;
}


/**
 * @brief Init�֐�
 * @param pos (position)
 * @param size (size)
 * @param depth (depth)
 */
inline void tml::graphic::Viewport::Init(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size, const tml::XMFLOAT2EX &depth)
{
	this->Release();

	this->vp_.TopLeftX = pos.x;
	this->vp_.TopLeftY = pos.y;
	this->vp_.Width = size.x;
	this->vp_.Height = size.y;
	this->vp_.MinDepth = depth.x;
	this->vp_.MaxDepth = depth.y;

	return;
}
